#include "pch.h"
#include "ObjectListGui.h"

#include "Game/GameObject/GameObject.h"

ObjectListGui::ObjectListGui()
{
}

ObjectListGui::~ObjectListGui()
{
}

void ObjectListGui::Update()
{
	ImGui::Begin("ObejctList");

	ImGui::BeginChild("ObjectList", ImVec2(0, 0));

    // オブジェクトリストを表示
	if (m_gameObjects != nullptr)
	{
		for (auto& object : *m_gameObjects)
		{
			DrawObjectGui(object);
		}
	}

    //if (m_scriptableObjects != nullptr)
    //{
    //    for (auto& object : *m_scriptableObjects)
    //    {
    //        DrawObjectGui(object);
    //    }
    //}

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
