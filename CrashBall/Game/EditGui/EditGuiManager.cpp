/*****************************************************************//**
 * \file   EditGuiManager.h
 * \brief  エディタGUI管理
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/


#include "pch.h"
#include "EditGuiManager.h"
#include "ImGui/imgui_internal.h"
#include "Game/Common/Screen.h"

/**
 * \brief コンストラクタ
 * 
 */
EditGuiManager::EditGuiManager()
{
    m_objectListGui         = std::make_unique<ObjectListGui>();
    m_objectInspectorGui    = std::make_unique<ObjectInspectorGui>();
    m_gameViewRenderer      = std::make_unique<GameViewRenderer>();
    m_editButton            = std::make_unique<EditButton>(this);
    m_sceneSelect           = std::make_unique<SceneSelect>();
}

/**
 * \brief デストラクタ
 * 
 */
EditGuiManager::~EditGuiManager()
{
}


/**
 * \brief 更新
 * 
 * \param gameObjects ゲームオブジェクト
 * \param scriptableObjectManager スクリプタブルオブジェクト用のマネージャー
 * \param resourceContext リソース用のコンテキスト
 */
void EditGuiManager::Update(
    ISceneEditer* sceneEditer,
    ScriptableObjectManager* scriptableObjectManager,
    const ResourceContext& resourceContext)
{
    if (!m_isActive) return;

    ImGuiID dockspaceID = ImGui::GetID("My Dockspace");

    // レイアウトの固定
    m_constantLayoutFunc();
    m_constantLayoutFunc = []() {};

    ImGui::DockSpaceOverViewport(dockspaceID);

    // 更新
    m_objectListGui->Update(sceneEditer);

    m_objectInspectorGui->Updata(
        m_objectListGui->GetSelectedObject(), 
        resourceContext);

    m_gameViewRenderer->Update(
        m_gameViewTexture->GetShaderResourceView(), 
        m_debugViewTexture->GetShaderResourceView());

    m_editButton->Update(
        sceneEditer,
        scriptableObjectManager);

    m_sceneSelect->Update(sceneEditer);
}

/**
 * \brief リセット
 * 
 */
void EditGuiManager::Reset()
{
    m_objectListGui->Reset();
}

/**
 * \brief レイアウト固定関数を登録
 * 
 */
void EditGuiManager::RegisterConstantLayout()
{
    m_constantLayoutFunc = [this]() { ConstantLayout(); };
}

/**
 * \brief レイアウト固定
 * 
 * \param dockSpace
 */
void EditGuiManager::ConstantLayout()
{
    if (!m_isActive) return;

    ImGuiID dockspaceID = ImGui::GetID("My Dockspace");

    ImGuiViewport* viewport = ImGui::GetMainViewport();

    // 描画領域が0以下ならreturn
    if (viewport->Size.x <= 0.0f || viewport->Size.y <= 0.0f) return;

    ImGui::DockBuilderAddNode(
        dockspaceID,
        ImGuiDockNodeFlags_DockSpace
    );

    ImGui::DockBuilderSetNodeSize(
        dockspaceID,
        viewport->Size
    );

    ImGuiID subR;
    ImGuiID subLTop;
    ImGuiID subLBottom;
    ImGuiID mainTop = dockspaceID;
    ImGuiID mainBottom;

    ImGui::DockBuilderSplitNode(
        dockspaceID,
        ImGuiDir_Right,
        0.35f,
        &subLBottom,
        &mainTop);

    ImGui::DockBuilderSplitNode(
        subLBottom,
        ImGuiDir_Right,
        0.6f,
        &subR,
        &subLBottom);

    ImGui::DockBuilderSplitNode(
        subLBottom,
        ImGuiDir_Up,
        0.15f,
        &subLTop,
        &subLBottom);

    ImGui::DockBuilderSplitNode(
        mainTop,
        ImGuiDir_Up,
        0.7f,
        &mainTop,
        &mainBottom);

    ImGui::DockBuilderDockWindow("Inspector", subR);
    ImGui::DockBuilderDockWindow("ObjectList", subLBottom);
    ImGui::DockBuilderDockWindow("Scene", subLTop);
    ImGui::DockBuilderDockWindow("GameView", mainTop);
    ImGui::DockBuilderDockWindow("DebugView", mainTop);
    ImGui::DockBuilderDockWindow("Buttons", mainBottom);

    ImGui::DockBuilderFinish(dockspaceID);
}
