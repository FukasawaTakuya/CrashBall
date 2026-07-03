#include "pch.h"
#include "ObjectInspectorGui.h"

#include "ImGui/imgui.h"

#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Physics/RigidBody.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
ObjectInspectorGui::ObjectInspectorGui()
{
	m_drawInspecter.emplace(typeid(Transform), DrawTransform);
	m_drawInspecter.emplace(typeid(RectTransform), DrawRectTransform);
	m_drawInspecter.emplace(typeid(Rigidbody), DrawRigidbody);
}

/**
 * \brief デストラクタ
 * 
 */
ObjectInspectorGui::~ObjectInspectorGui()
{
}

/**
 * \brief 更新
 * 
 * \param selectedObject 選択中のオブジェクト
 */
void ObjectInspectorGui::Updata(GameObject* selectedObject)
{
	ImGui::Begin("Inspecter");

	if (selectedObject != nullptr)
	{
		ImGui::BeginChild(selectedObject->GetName().c_str());

		ImGui::Text(selectedObject->GetName().c_str());

		for (auto& comp : *selectedObject->GetComponentsList())
		{
			// コンポーネント表示関数テーブルに存在すれば表示
			if (m_drawInspecter.find(comp.first) != m_drawInspecter.end())
			{
				m_drawInspecter[comp.first](comp.second.get());
			}
		}

		ImGui::EndChild();
	}

	ImGui::End();
}

/**
 * \brief トランスフォームの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawTransform(Component* comp)
{
	// トランスフォームにキャスト
	Transform* transform = static_cast<Transform*>(comp);

	if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		// 回転
		SimpleMath::Vector3 rotate = transform->GetLocalRotate().ToEuler();

		rotate.x = XMConvertToDegrees(rotate.x);
		rotate.y = XMConvertToDegrees(rotate.y);
		rotate.z = XMConvertToDegrees(rotate.z);

		ImGui::DragFloat3("position", &transform->m_localPosition.x);
		ImGui::DragFloat3("rotate", &rotate.x);
		ImGui::DragFloat3("scale", &transform->m_localScale.x);

		rotate.x = XMConvertToRadians(rotate.x);
		rotate.y = XMConvertToRadians(rotate.y);
		rotate.z = XMConvertToRadians(rotate.z);

		transform->SetRotate(SimpleMath::Quaternion::CreateFromYawPitchRoll(rotate));

		ImGui::TreePop();
	}
}

/**
 * \brief 2Dトランスフォームの表示
 *
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawRectTransform(Component* comp)
{
	// トランスフォームにキャスト
	RectTransform* rectTransform = static_cast<RectTransform*>(comp);

	if (ImGui::TreeNodeEx("RectTransform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		float rotate = XMConvertToDegrees(rectTransform->m_localRotate);

		ImGui::DragFloat3("position", &rectTransform->m_localPosition.x);
		ImGui::DragFloat("rotate", &rotate);
		ImGui::DragFloat2("scale", &rectTransform->m_localScale.x);

		int currentOrigin = static_cast<int>(rectTransform->m_origin);

		if (ImGui::Combo("Origin", &currentOrigin, originNameList, IM_ARRAYSIZE(originNameList)))
		{
			rectTransform->m_origin = static_cast<Origin>(currentOrigin);
		}

		rectTransform->m_localRotate = XMConvertToRadians(rotate);

		ImGui::TreePop();
	}
}

/**
 * \brief 
 * 
 * \param comp
 */
void ObjectInspectorGui::DrawRigidbody(Component* comp)
{
	Rigidbody* rigidbody = static_cast<Rigidbody*>(comp);

	if (ImGui::TreeNodeEx("Rigidbody", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("gravityAcceleration", &rigidbody->m_gravityAcceleration,	0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("friction",			&rigidbody->m_friction,				0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("mass",				&rigidbody->m_mass,					0.1f, 0.0f, 100.0f);
		
		bool togle = rigidbody->m_isDynamic;

		ImGui::Checkbox("isDynamic", &togle);
		
		if (togle)
		{
			rigidbody->m_isDynamic = 1.0f;
		}
		else
		{
			rigidbody->m_isDynamic = 0.0f;
		}

		ImGui::TreePop();
	}

}
