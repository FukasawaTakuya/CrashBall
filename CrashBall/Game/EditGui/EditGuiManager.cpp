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
 * \param pSceneEditer シーン編集
 * \param pJsonDataManager Jsonデータ管理
 */
EditGuiManager::EditGuiManager(
    ISceneEditer* pSceneEditer,
    IJsonDataManager* pJsonDataManager)
{
    m_objectListGui         = std::make_unique<ObjectListGui>();
    m_objectInspectorGui    = std::make_unique<ObjectInspectorGui>();
    m_gameViewRenderer      = std::make_unique<GameViewRenderer>();
    m_editButton            = std::make_unique<EditButton>(
                                    this,
                                    pSceneEditer,
                                    pJsonDataManager
                                    );
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
    std::vector<GameObject*>* gameObjects, 
    ID3D11ShaderResourceView* srv)
{
    if (!m_isActive) return;

    // -------------------- レイアウトの設定 -------------------- //

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

    ImGuiID rightR = 0;
    ImGuiID rightL = 0;
    ImGuiID mainTop = dockspaceID;
    ImGuiID mainBottom = 0;

    ImGui::DockBuilderSplitNode(
            dockspaceID,
            ImGuiDir_Right,
            0.35f,
            &rightL,
            &mainTop
        );

       ImGui::DockBuilderSplitNode(
            rightL,
            ImGuiDir_Right,
            0.6f,
            &rightR,
            &rightL
        );

        ImGui::DockBuilderSplitNode(
            mainTop,
            ImGuiDir_Up,
            0.7f,
            &mainTop,
            &mainBottom
        );

    ImGui::DockBuilderDockWindow("Inspector", rightR);
    ImGui::DockBuilderDockWindow("ObjectList", rightL);
    ImGui::DockBuilderDockWindow("Game", mainTop);
    ImGui::DockBuilderDockWindow("Buttons", mainBottom);

    ImGui::DockBuilderFinish(dockspaceID);

    // ------------------------------------------------------ //

    ImGui::DockSpaceOverViewport(dockspaceID);

    // 更新
    m_objectListGui->Update(gameObjects);
    m_objectInspectorGui->Updata(m_objectListGui->GetSelectedObject());
    m_gameViewRenderer->Update(srv);
    m_editButton->Update();
}
