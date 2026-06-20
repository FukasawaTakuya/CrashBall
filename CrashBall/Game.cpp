//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include "Game/Common/Screen.h"
#include "Game/Scene/GameScene.h"
#include "Game/ServiceLocator/ServiceLocator.h"
#include "Game/ServiceLocator/ITimeService.h"
#include "Game/ServiceLocator/IInputService.h"

extern void ExitGame() noexcept;

using namespace DirectX;

using Microsoft::WRL::ComPtr;

Game::Game() noexcept(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    // TODO: Provide parameters for swapchain format, depth/stencil format, and backbuffer count.
    //   Add DX::DeviceResources::c_AllowTearing to opt-in to variable rate displays.
    //   Add DX::DeviceResources::c_EnableHDR for HDR10 display.
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    m_deviceResources->CreateWindowSizeDependentResources();

    m_inputSystem               = std::make_unique<InputSystem>();
    m_timeManager               = std::make_unique<TimeManager>();

    m_modelManager              = std::make_unique<ModelManager>();
    m_spriteManager             = std::make_unique<SpriteManager>();
    m_soundManager              = std::make_unique<SoundManager>();
    m_textManager               = std::make_unique<TextManager>();

    m_primitiveRendererManager  = std::make_unique<PrimitiveRendererManager>();
    m_spriteRendererManager     = std::make_unique<SpriteRendererManager>();
    m_modelRendererManager      = std::make_unique<ModelRendererManager>();
    m_textRendererManager       = std::make_unique<TextRendererManager>();

    m_soundPlayer               = std::make_unique<SoundPlayer>();

    m_sceneManager              = std::make_unique<SceneManager>();

    // 各コンテキストの初期化
    m_gameContext =
    {

    };
    m_renderContext =
    {
        m_modelRendererManager.get(),
        m_primitiveRendererManager.get(),
        m_spriteRendererManager.get(),
        m_textRendererManager.get()
    };
    m_resourceContext =
    {
        m_modelManager.get(),
        m_spriteManager.get(),
        m_textManager.get()
    };
    
    // サービスロケーターに設定
    ServiceLocator::Set<ITimeService>(m_timeManager.get());
    ServiceLocator::Set<IInputService>(m_inputSystem.get());

    // 作成するリソースのファイル名を登録
    m_modelManager->RegisterFile("player", L"Resources/Models/ball.sdkmesh");
    m_modelManager->RegisterFile("enemy", L"Resources/Models/ball.sdkmesh");
    m_modelManager->RegisterFile("stage", L"Resources/Models/stage.sdkmesh");
    m_spriteManager->RegisterFile("UI", L"Resources/Sprite/UI.dds");
    m_spriteManager->RegisterFile("Gauge", L"Resources/Sprite/Gauge.dds");
    m_spriteManager->RegisterFile("AttackIcon", L"Resources/Sprite/AttackIcon.dds");
    m_textManager->RegisterFile("default", L"Resources/SpriteFont/makinas.spritefont");

    // サウンドの作成
    m_soundManager->CreateSound(m_soundPlayer->GetAudioEngine());

    // シーンの登録
    m_sceneManager->CreateScene<GameScene>(SceneID::Game);

    // デバイス依存のリソースの作成
    CreateDeviceDependentResources();

    // ウインドウサイズ依存のリソースの作成
    CreateWindowSizeDependentResources();

    // 初期シーンをセット
    m_sceneManager->SetStartScene();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
}
#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{ 
    m_timer.Tick([&]()
        {
            Update(m_timer);
        });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

    // 経過時間のセット
    m_timeManager->SetElapsedTime(elapsedTime);

    m_inputSystem->Update();
    m_soundPlayer->Update();

    m_sceneManager->Update(m_gameContext);

    m_soundPlayer->PlayBgm(m_soundManager.get());
    m_soundPlayer->PlaySe(m_soundManager.get());

}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();


    // FPSの描画
    m_textRendererManager->DebugRender(
        SimpleMath::Vector2::Zero,
        Colors::White,
        0.0f,
        1.5f,
        SimpleMath::Vector2::Zero,
        0.0f,
        L"FPS:{}",
        m_timer.GetFramesPerSecond()
    );

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

    SimpleMath::Matrix view = m_sceneManager->GetCamera()->GetView();

    // シーン内での描画命令登録
    m_sceneManager->Render(m_renderContext);

    // モデルの描画
    m_modelRendererManager->Render(context, m_state.get(), view, m_proj);
    // プリミティブの描画
    m_primitiveRendererManager->Render(context, m_state.get(), view);

    // スプライト関連描画開始
    m_spriteBatch->Begin(SpriteSortMode_FrontToBack);

    // スプライトの描画
    m_spriteRendererManager->Render(m_spriteBatch.get());
    // テキストの描画
    m_textRendererManager->Render(m_spriteBatch.get());

    // スプライト関連描画終了
    m_spriteBatch->End();

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    const auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();

    // 描画命令のクリア
    m_modelRendererManager->ClearRenderCommand();
    m_primitiveRendererManager->ClearRenderCommand();
    m_spriteRendererManager->ClearRenderCommand();
    m_textRendererManager->ClearnRenderCommand();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    const auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = Screen::WIDTH;
    height = Screen::HEIGHT;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
    auto context = m_deviceResources->GetD3DDeviceContext();

    // コモンステートの作成
    m_state = std::make_unique<DirectX::CommonStates>(device);
    // スプライトバッチの作成
    m_spriteBatch = std::make_unique<SpriteBatch>(context);

    // モデルの生成
    m_spriteManager->CreateSprite(device);
    m_modelManager->CreateModel(device);
    m_textManager->CreateSpriteFont(device);
    
    // デバイス依存のリソース作成
    m_sceneManager->CreateDeviceResources(m_resourceContext);

    // 描画管理オブジェクトの初期化
    m_primitiveRendererManager->Create(device, context, m_state.get());
    m_spriteRendererManager->Create(context);
    m_textRendererManager->Create(device, context);
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.

    int w, h;

    GetDefaultSize(w, h);

    Screen::CalcScreenRate(m_deviceResources->IsFullscreen());

    // 射影行列の定義
    m_proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
        XMConvertToRadians(45), static_cast<float>(w) / static_cast<float>(h),
        0.01f, 150.0f
    );

    // 射影行列の設定
    m_primitiveRendererManager->SetProj(m_proj);

    // ウィンドウサイズ依存のリソース作成リソース作成
    m_sceneManager->CreateWindowSizeResources(m_proj);
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
