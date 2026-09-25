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
 * \param scriptableObjects Scriptableオブジェクト
 * \param srv レンダーテクスチャ
 */
void EditGuiManager::Update(
    ISceneEditer* sceneEditer,
    ID3D11ShaderResourceView* srv)
{
    if (!m_isActive) return;

    ImGuiID dockspaceID = ImGui::GetID("My Dockspace");

    ConstantLayout(dockspaceID);

    ImGui::DockSpaceOverViewport(dockspaceID);

    // 更新
    m_objectListGui->Update(sceneEditer);
    m_objectInspectorGui->Updata(m_objectListGui->GetSelectedObject());
    m_gameViewRenderer->Update(srv);
    m_editButton->Update(sceneEditer);
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
 * \brief レイアウト固定
 * 
 * \param dockSpace
 */
void EditGuiManager::ConstantLayout(ImGuiID dockspace)
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    // 描画領域が0以下ならreturn
    if (viewport->Size.x <= 0.0f || viewport->Size.y <= 0.0f) return;

    ImGui::DockBuilderAddNode(
        dockspace,
        ImGuiDockNodeFlags_DockSpace
    );

    ImGui::DockBuilderSetNodeSize(
        dockspace,
        viewport->Size
    );

    ImGuiID subR;
    ImGuiID subLTop;
    ImGuiID subLBottom;
    ImGuiID mainTop = dockspace;
    ImGuiID mainBottom;

    ImGui::DockBuilderSplitNode(
        dockspace,
        ImGuiDir_Right,
        0.35f,
        &subLBottom,
        &mainTop
    );

    ImGui::DockBuilderSplitNode(
        subLBottom,
        ImGuiDir_Right,
        0.6f,
        &subR,
        &subLBottom
    );

    ImGui::DockBuilderSplitNode(
        subLBottom,
        ImGuiDir_Up,
        0.08f,
        &subLTop,
        &subLBottom
    );

    ImGui::DockBuilderSplitNode(
        mainTop,
        ImGuiDir_Up,
        0.7f,
        &mainTop,
        &mainBottom
    );

    ImGui::DockBuilderDockWindow("Inspector", subR);
    ImGui::DockBuilderDockWindow("ObjectList", subLBottom);
    ImGui::DockBuilderDockWindow("Scene", subLTop);
    ImGui::DockBuilderDockWindow("Game", mainTop);
    ImGui::DockBuilderDockWindow("Buttons", mainBottom);

    ImGui::DockBuilderFinish(dockspace);

}
