#include "pch.h"
#include "ObjectEditGui.h"

#include "Game/GameObject/GameObject.h"

ObjectEditGui::ObjectEditGui()
{
}

ObjectEditGui::~ObjectEditGui()
{
}

void ObjectEditGui::Update()
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


    ImGui::Begin("Inspecter");

    if (m_selectedObject != nullptr)
    {

        for (auto& comp : *m_selectedObject->GetComponentsList())
        {
            ImGui::Text(comp.first.name());

            if (comp.first == typeid(Transform))
            {
                Transform* transform = static_cast<Transform*>(comp.second.get());

                DirectX::SimpleMath::Vector3 pos = transform->GetLocalPosition();
                DirectX::SimpleMath::Vector3 rotate = transform->GetLocalRotate().ToEuler();
                DirectX::SimpleMath::Vector3 scale = transform->GetLocalScale();

                ImGui::DragFloat3(
                    "Position",
                    &pos.x,
                    0.1f
                );

                ImGui::DragFloat3(
                    "Rotate",
                    &rotate.x,
                    0.1f
                );

                ImGui::DragFloat3(
                    "Scale",
                    &scale.x,
                    0.1f
                );
            }
        }
    }

    ImGui::End();
}

/**
 * \brief 
 * 
 * \param object
 */
void ObjectEditGui::DrawObjectGui(GameObject* object)
{
    // 表示詳細フラグ
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;

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
