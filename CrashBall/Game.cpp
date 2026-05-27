//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

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

    m_primitiveRendererManager  = std::make_unique<PrimitiveRendererManager>();
    m_spriteRendererManager     = std::make_unique<SpriteRendererManager>();
    m_modelRendererManager      = std::make_unique<ModelRendererManager>();
    m_textRendererManager       = std::make_unique<TextRendererManager>();

    m_soundPlayer               = std::make_unique<SoundPlayer>();


    // 各コンテキストの初期化
    m_gameContext.emplace();
    m_renderContext.emplace(
        m_modelRendererManager.get(),
        m_primitiveRendererManager.get(),
        m_spriteRendererManager.get(),
        m_textRendererManager.get()

    );
    m_resourceContext.emplace(
        m_modelManager.get(),
        m_spriteManager.get()
    );
    
    // サービスロケーターに設定
    ServiceLocator::Set<ITimeService>(m_timeManager.get());
    ServiceLocator::Set<IInputService>(m_inputSystem.get());

    // ファクトリーに作成するリソースを登録
    m_modelManager->RegisterFactory("ball", L"Resources/Models/Ball.sdkmesh");
    m_modelManager->RegisterFactory("Stage", L"Resources/Models/Stage.sdkmesh");
    m_spriteManager->RegisterFactory("test", L"Resources/Sprite/robot.dds");
    m_soundManager->RegisterFactory("test", L"Resources/Sound/ks043.wav");

    // サウンドの作成
    m_soundManager->CreateSound(m_soundPlayer->GetAudioEngine());

    // シーンの登録
    m_sceneManager = std::make_unique<SceneManager>();
    m_sceneManager->RegisterScene(SceneID::Game,
        std::make_unique<GameScene>(m_sceneManager.get()));

    // 初期シーンをセット
    m_sceneManager->SetStartScene();

    // デバイス依存のリソースの作成
    CreateDeviceDependentResources();

    auto device = m_deviceResources->GetD3DDevice();
    auto context = m_deviceResources->GetD3DDeviceContext();
    // 描画管理オブジェクトの初期化
    m_primitiveRendererManager->Create(device, context, m_state.get());
    m_spriteRendererManager->Create(context);
    m_textRendererManager->Create(device, context);

    // ウインドウサイズ依存のリソースの作成
    CreateWindowSizeDependentResources();

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

    // 
    m_timeManager->SetElapsedTime(elapsedTime);
    m_inputSystem->Update();
    m_soundPlayer->Update();

    m_sceneManager->Update(*m_gameContext);

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

    // 描画命令のクリア
    m_modelRendererManager->ClearRenderCommand();
    m_primitiveRendererManager->ClearRenderCommand();
    m_spriteRendererManager->ClearRenderCommand();
    m_textRendererManager->ClearnRenderCommand();

    // FPSの描画
    m_textRendererManager->RegisterRenderCommand(
        SimpleMath::Vector2::Zero,
        Colors::White,
        1.0f,
        L"FPS:{} \n debug {}",
        (int)m_timer.GetFramesPerSecond(),
        0.0f
    );


    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

    // シーン内での描画命令登録
    m_sceneManager->Render(*m_renderContext);

    // モデルの描画
    m_modelRendererManager->Render(context, m_state.get(), m_sceneManager->GetCamera());
    // プリミティブの描画
    m_primitiveRendererManager->Render(context, m_state.get(), m_sceneManager->GetCamera());
    // スプライトの描画
    m_spriteRendererManager->Reder();
    // テキストの描画
    m_textRendererManager->Render();

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
    width = 1280;
    height = 720;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
    m_state = std::make_unique<DirectX::CommonStates>(device);

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

    // モデルの生成
    m_spriteManager->CreateSprite(device);
    m_modelManager->CreateModel(device);
    
    // デバイス依存のリソース作成
    m_sceneManager->CreateDeviceResources(*m_resourceContext);
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.

    int w, h;

    GetDefaultSize(w, h);

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
