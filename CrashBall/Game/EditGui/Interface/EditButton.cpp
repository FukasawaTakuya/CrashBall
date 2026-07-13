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

/**
 * \brief コンストラクタ
 * 
 */
EditButton::EditButton()
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
 * \param pSceneEditer シーン編集
 */
void EditButton::Update(ISceneEditer* pSceneEditer)
{
    ImGui::Begin("Buttons");

    ImGui::SameLine(0.0f, 10.0f);

    if (ImGui::Button("Play"))
    {
        pSceneEditer->SetEditMode(false);
    }

    ImGui::SameLine(0.0f, 10.0f);

    if (ImGui::Button("Stop"))
    {
        pSceneEditer->SetEditMode(true);
    }

    ImGui::End();
}
