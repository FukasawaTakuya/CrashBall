//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"

#include <memory>


#include "Game/Scene/SceneManager.h"

#include "Game/Common/InputSystem.h"
#include "Game/Common/TimeManager.h"

#include "Game/Renderer/PrimitiveRendererManager.h"
#include "Game/Renderer/ModelRendererManager.h"
#include "Game/Renderer/SpriteRendererManager.h"
#include "Game/Renderer/TextRendererManager.h"

#include "Game/ResourceManager/ModelManager.h"
#include "Game/ResourceManager/SpriteManager.h"

#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"
#include "Game/Context/ResourceContext.h"


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
private:

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

    
    std::unique_ptr<DirectX::CommonStates> m_state; // コモンステート

    DirectX::SimpleMath::Matrix m_proj; // 射影行列
    
    std::unique_ptr<SceneManager>   m_sceneManager; // シーン管理

    std::unique_ptr<InputSystem>                m_inputSystem;                  // 入力システム
    std::unique_ptr<TimeManager>                m_timeManager;                  // 時間管理
    std::unique_ptr<ModelManager>               m_modelManager;                 // モデル管理
    std::unique_ptr<SpriteManager>              m_spriteManager;                // スプライト管理
    std::unique_ptr<ModelRendererManager>       m_modelRendererManager;         // モデル描画管理
    std::unique_ptr<PrimitiveRendererManager>   m_primitiveRendererManager;     // プリミティブ描画管理
    std::unique_ptr<SpriteRendererManager>      m_spriteRendererManager;        // スプライト描画管理
    std::unique_ptr<TextRendererManager>        m_textRendererManager;          // テキスト描画管理

    std::optional<GameContext>      m_gameContext;      // ゲームプレイ用のコンテキスト
    std::optional<RenderContext>    m_renderContext;    // 描画用のコンテキスト
    std::optional<ResourceContext>  m_resourceContext;  // リソース用のコンテキスト

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
