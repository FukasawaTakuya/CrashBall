/*****************************************************************//**
 * \file   ObjectListGui.cpp
 * \brief  オブジェクトリスト表示
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "ObjectListGui.h"

#include "Game/ScriptableObject/Scriptable.h"

/**
 * \brief コンストラクタ
 * 
 */
ObjectListGui::ObjectListGui()
{
}

/**
 * \brief デストラクタ
 * 
 */
ObjectListGui::~ObjectListGui()
{
}

/**
 * \brief 更新
 * 
 */
void ObjectListGui::Update(std::vector<GameObject*>* gameObjects)
{
	ImGui::Begin("ObjectList");

	ImGui::BeginChild("ObjectList");

    // オブジェクトリストを表示
	if (gameObjects != nullptr)
	{
		for (auto& object : *gameObjects)
		{
			DrawObjectGui(object);
		}
	}

    for (auto& object : *Scriptable::GetScriptableObejctList())
    {
        DrawObjectGui(object.second.get());
    }

	ImGui::EndChild();

	ImGui::End();
}

/**
 * \brief オブジェクトの表示
 * 
 * \param object ゲームオブジェクト
 */
void ObjectListGui::DrawObjectGui(GameObject* object)
{
    // 表示詳細フラグ
    ImGuiBackendFlags flags = ImGuiTreeNodeFlags_FramePadding;

    // 子がいない場合葉ノード描画
    if (object->GetChildren().empty())
    {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    // 選択されているなら選択フラグをオンにする
    if (object == m_selectedObject)
    {
        flags |= ImGuiTreeNodeFlags_Selected;
    }

    // ノードの描画
    bool opened =
        ImGui::TreeNodeEx(
            object,
            flags,
            object->GetName().c_str());

    // クリック時の処理
    if (ImGui::IsItemClicked())
    {
        m_selectedObject = object;
    }

    // 開いているの時の処理
    if (opened)
    {
        // 子オブジェクトを描画
        for (auto& child : object->GetChildren())
        {
            DrawObjectGui(child);
        }

        ImGui::TreePop();
    }
}
