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

/**
 * \brief コンストラクタ
 * 
 * \param pEditModeChanger 編集モード切り替え
 * \param pSceneEditer シーン編集
 * \param pJsonDataManager Jsonデータ管理
 */
EditButton::EditButton(IEditModeChanger*   pEditModeChanger)
    : m_pEditModeChanger(pEditModeChanger)
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
 */
void EditButton::Update(ISceneEditer* sceneEditer)
{
    ImGui::Begin("Buttons");

    ImGui::SameLine(0.0f, 10.0f);

    // プレイモード切り替え
    if (ImGui::Button("Play"))
    {
        m_pEditModeChanger->SetEditMode(false);
    }

    ImGui::SameLine(0.0f, 10.0f);

    // 編集モード切り替え
    if (ImGui::Button("Edit"))
    {
        m_pEditModeChanger->SetEditMode(true);
        sceneEditer->Start();
    }

    ImGui::SameLine(0.0f, 40.0f);

    // 編集モードなら
    if (m_pEditModeChanger->GetEditMode())
    {
        // セーブボタン
        if (ImGui::Button("Save"))
        {
            //sceneEditer->SaveParam();
            //for (auto& obj : *Scriptable::GetScriptableObejctList())
            //{
            //    //obj.second->SaveParam();
            //}

            //m_pJsonDataManager->SaveFile();
        }

        ImGui::SameLine(0.0f, 10.0f);

        // ロードボタン
        if (ImGui::Button("Load"))
        {
            //m_pJsonDataManager->ReloadFile();
            //sceneEditer->ReloadParam();
            //for (auto& obj : *Scriptable::GetScriptableObejctList())
            //{
            //    //obj.second->ReloadParam();
            //}
        }
    }

    ImGui::End();
}
