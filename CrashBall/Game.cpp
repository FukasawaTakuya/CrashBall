//
// Game.cpp
//

#include "pch.h"
#include "Game.h"


#include "Game/CommonResources/CommonResources.h"
#include "Game/ResourceManager/ResourceManager.h"
#include "Game/ResourceManager/ModelManager.h"
#include "Game/Scene/GameScene.h"

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

    // マネージャーの作成
    auto resourceManager = ResourceManager::Instance;
    resourceManager().CreateManager();

    // モデルの登録
    ModelManager* modelManager = resourceManager().GetModelManager();
    modelManager->RegisterModel("ball", L"Resources/Models/Ball2.sdkmesh");
    modelManager->RegisterModel("floor", L"Resources/Models/floor.sdkmesh");
    modelManager->RegisterModel("meshFloor", L"Resources/Models/meshFloor2.sdkmesh");
    modelManager->RegisterModel("Stage", L"Resources/Models/Stage.sdkmesh");

    // シーンの登録
    m_sceneManager = std::make_unique<SceneManager>();

    m_sceneManager->RegisterScene("GameScene",
        std::make_unique<GameScene>(m_sceneManager.get()));

    // 初期シーンをセット
    m_sceneManager->SetStartScene();


    CreateDeviceDependentResources();
    CreateWindowSizeDependentResources();

    // 共通リソースの作成
    auto commonResources = CommonResources::Instance;
    commonResources().Initialize(
        m_deviceResources->GetD3DDevice(),
        m_deviceResources->GetD3DDeviceContext(),
        m_state.get()
    );
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

    //InputSystem::Instance().Update();

    m_sceneManager->Update(elapsedTime);

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

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

    m_sceneManager->Draw();

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
    auto context = m_deviceResources->GetD3DDeviceContext();
    m_state = std::make_unique<DirectX::CommonStates>(device);

    int w, h;

    GetDefaultSize(w, h);

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

    // リソースの生成
    //ResourceManager::Instance().CreateResources(device);


    // 射影行列の定義
    m_proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
        XMConvertToRadians(45), static_cast<float>(w) / static_cast<float>(h),
        0.01f, 100.0f
    );

    //PrimitiveManager::Instance().CreateResource(device, context, m_proj);

    // リソース作成
    m_sceneManager->CreateResources(m_proj);
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
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
