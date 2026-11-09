/*****************************************************************//**
 * \file   EditButton.cpp
 * \brief  編集ボタン
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "EditButton.h"
#include "ImGui/imgui.h"
#include "Game/ScriptableObject/Scriptable.h"

#include "Game/Engine/Time.h"

/**
 * \brief コンストラクタ
 * 
 * \param pEditModeChanger 編集モード切り替え
 * \param pSceneEditer シーン編集
 * \param pJsonDataManager Jsonデータ管理
 */
EditButton::EditButton(IEditModeChanger*editModeChanger)
    : m_editModeChanger(editModeChanger)
{
}

/**
 * \brief デストラクタ
 * 
 */
EditButton::~EditButton()
{
}

/**
 * \brief 更新
 * 
 * \param sceneEditer シーンエディタ
 * \param scriptableObjectManager スクリプタブルオブジェクト要のマネージャー
 */
void EditButton::Update(
    ISceneEditer* sceneEditer,
    ScriptableObjectManager* scriptableObjectManager)
{
    ImGui::Begin("Buttons");

    ImGui::SameLine(0.0f, 10.0f);

    // プレイモード切り替え
    if (ImGui::Button("Play"))
    {
        sceneEditer->Awake();
        m_editModeChanger->SetEditMode(false);
    }

    ImGui::SameLine(0.0f, 10.0f);

    // 編集モード切り替え
    if (ImGui::Button("Edit"))
    {
        m_editModeChanger->SetEditMode(true);
        sceneEditer->ReloadData();
        sceneEditer->Awake();
        sceneEditer->Start();
    }


    // 編集モードなら
    if (m_editModeChanger->GetEditMode())
    {
        ImGui::SameLine(0.0f, 40.0f);
        // セーブボタン
        if (ImGui::Button("Save"))
        {
            sceneEditer->SaveData();
            scriptableObjectManager->SaveData();
        }

        //ImGui::SameLine(0.0f, 10.0f);
    }

    std::string s = std::format("FPS:{}", Time::GetFPS());
    ImGui::Text(s.c_str());

    ImGui::End();
}
