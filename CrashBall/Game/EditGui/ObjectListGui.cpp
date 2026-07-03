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
	static int current = 0;

	ImGui::Begin("ObejctList");

	ImGui::BeginChild("ObjectList", ImVec2(0, 0));

	if (m_objects != nullptr)
	{
		for (int i = 0; i < m_objects->size(); i++)
		{
			bool is_selected = (current == i);

			DrawObjectGui((*m_objects)[i]);
		}
	}

	ImGui::EndChild();

	ImGui::End();
}

/**
 * \brief 
 * 
 * \param object
 */
void ObjectListGui::DrawObjectGui(GameObject* object)
{
    // 表示詳細フラグ
    ImGuiBackendFlags flags = ImGuiTreeNodeFlags_FramePadding;

    // 子がいない場合三角を描画しない
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
