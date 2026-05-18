//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"

#include <memory>


#include "Game/Scene/SceneManager.h"

#include "Game/Common/InputSystem.h"
#include "Game/Common/CommonResources.h"
#include "Game/Common/TimeManager.h"
#include "Game/Common/InputService.h"

#include "Game/Renderer/PrimitiveRendererManager.h"
#include "Game/Renderer/ModelRendererManager.h"
#include "Game/ResourceManager/ModelManager.h"

#include "Game/Common/GameContext.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
private:

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

    // コモンステート
    std::unique_ptr<DirectX::CommonStates> m_state;

    // 射影行列
    DirectX::SimpleMath::Matrix m_proj;

    // シーン管理オブジェクト
    std::unique_ptr<SceneManager>   m_sceneManager;

    std::unique_ptr<InputSystem> m_inputSystem;
    std::unique_ptr<TimeManager> m_timeManager;
    std::unique_ptr<ModelManager> m_modelManager;
    std::unique_ptr<ModelRendererManager> m_modelRendererManager;
    std::unique_ptr<PrimitiveRendererManager> m_primitiveRendererManager;

    std::optional<GameContext> m_gameContext;

public:

    Game() noexcept(false);
    ~Game() = default;

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();
};
