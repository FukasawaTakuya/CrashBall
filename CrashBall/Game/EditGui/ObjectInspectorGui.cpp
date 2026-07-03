#include "pch.h"
#include "ObjectInspectorGui.h"

#include "ImGui/imgui.h"

#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Default/Physics/RigidBody.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
ObjectInspectorGui::ObjectInspectorGui()
{
	m_drawInspecter.emplace(typeid(Transform), DrawTransform);
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

	// 座標
	SimpleMath::Vector3 position = transform->GetLocalPosition();
	// 回転
	SimpleMath::Vector3 rotate = transform->GetLocalRotate().ToEuler();
	// スケール
	SimpleMath::Vector3 scale = transform->GetLocalScale();

	if (ImGui::TreeNode(transform, "Transform"))
	{
		ImGui::DragFloat3("position", &position.x);
		ImGui::DragFloat3("rotate", &rotate.x);
		ImGui::DragFloat3("scale", &scale.x);

		transform->SetLocalPosition(position);
		transform->SetRotate(SimpleMath::Quaternion::CreateFromYawPitchRoll(rotate));
		transform->SetScale(scale);

		ImGui::TreePop();
	}
}

void ObjectInspectorGui::DrawRigidbody(Component* comp)
{
	Rigidbody* rigidbody = static_cast<Rigidbody*>(comp);

	float gravityAcceleration = 0.0f;	// 重力加速度
	float friction = 0.0f;				// 摩擦係数
	float mass = 1.0f;					// 質量
	float isDynamic = 1.0f;				// 動的か(1 = ture, 0 = false)
}
