#include "pch.h"
#include "ObjectInspectorGui.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_stdlib.h"
#include "Game/Common/Utility.h"

#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Physics/RigidBody.h"
#include "Game/Component/Default/Collider/Sphere.h"
#include "Game/Component/Default/Collider/Mesh.h"
#include "Game/Component/Default/Renderer/ModelRenderer.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/Component/Default/Renderer/TextRenderer.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
ObjectInspectorGui::ObjectInspectorGui()
{
	m_drawInspecter.emplace(typeid(Sphere), DrawSphere);
	m_drawInspecter.emplace(typeid(ModelRenderer), DrawModelRenderer);
	m_drawInspecter.emplace(typeid(SpriteRenderer), DrawSpriteRenderer);
	m_drawInspecter.emplace(typeid(TextRenderer), DrawTextRenderer);
	m_drawInspecter.emplace(typeid(Mesh), DrawMesh);
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
 * \brief 球コライダーの表示
 * 
 * \param comp
 */
void ObjectInspectorGui::DrawSphere(Component* comp)
{
	Sphere* sphere = static_cast<Sphere*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	if (ImGui::TreeNodeEx("Sphere", flag))
	{
		ImGui::DragFloat("Radius", &sphere->m_radius);

		ImGui::TreePop();
	}
}

/**
 * \brief 
 * 
 * \param comp
 */
void ObjectInspectorGui::DrawMesh(Component* comp)
{
	Mesh* mesh = static_cast<Mesh*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	if (ImGui::TreeNodeEx("Mesh", flag))
	{
		ImGui::InputText("MeshData", &mesh->m_meshData);

		ImGui::TreePop();
	}
}

/**
 * \brief モデルレンダラーの表示
 *  
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawModelRenderer(Component* comp)
{
	ModelRenderer* modelRenderer = static_cast<ModelRenderer*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	if (ImGui::TreeNodeEx("ModelRenderer", flag))
	{
		ImGui::InputText("ModelKay", &modelRenderer->m_modelKey);

		ImGui::TreePop();
	}
}

/**
 * \brief スプライトレンダラーの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawSpriteRenderer(Component* comp)
{
	SpriteRenderer* spriteRenderer = static_cast<SpriteRenderer*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	if (ImGui::TreeNodeEx("SpriteRenderer", flag))
	{
		ImGui::InputText("SpriteKey", &spriteRenderer->m_spriteKey);

		ImGui::ColorEdit4("Color", &spriteRenderer->m_color.x);

		ImGui::DragFloat2("SpriteScale", &spriteRenderer->m_spriteScale.x);

		ImGui::DragFloat("LayerDepth", &spriteRenderer->m_layerDepth);

		int currentFillOrigin = static_cast<int>(spriteRenderer->m_fillOrigin);
		ImGui::Combo("FillOrigin", &currentFillOrigin, FillOriginName, IM_ARRAYSIZE(FillOriginName));
		spriteRenderer->m_fillOrigin = static_cast<FillOrigin>(currentFillOrigin);

		ImGui::TreePop();
	}
}

/**
 * \brief テキストレンダラーの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawTextRenderer(Component* comp)
{
	TextRenderer* textRenderer = static_cast<TextRenderer*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	if (ImGui::TreeNodeEx("TextRenderer", flag))
	{
		std::string text = Utility::ConvertToMultiByteChar(textRenderer->m_text);

		ImGui::InputText("SpriteKey", &textRenderer->m_fontKey);
		ImGui::InputText("Text", &text);
		textRenderer->m_text = Utility::ConvertToWideChar(text);

		ImGui::DragFloat("FontScale", &textRenderer->m_fontScale);
		ImGui::DragFloat("LayerDepth", &textRenderer->m_layerDepth);

		ImGui::TreePop();
	}
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

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	if (ImGui::TreeNodeEx("Transform", flag))
	{
		// 回転
		SimpleMath::Vector3 rotate = transform->GetLocalRotate().ToEuler();

		rotate.x = XMConvertToDegrees(rotate.x);
		rotate.y = XMConvertToDegrees(rotate.y);
		rotate.z = XMConvertToDegrees(rotate.z);

		ImGui::DragFloat3("Pposition", &transform->m_localPosition.x);
		ImGui::DragFloat3("Rotate", &rotate.x);
		ImGui::DragFloat3("Scale", &transform->m_localScale.x);

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

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	if (ImGui::TreeNodeEx("RectTransform", flag))
	{
		float rotate = XMConvertToDegrees(rectTransform->m_localRotate);

		ImGui::DragFloat3("Position", &rectTransform->m_localPosition.x);
		ImGui::DragFloat("Rotate", &rotate);
		ImGui::DragFloat2("Scale", &rectTransform->m_localScale.x);

		int currentOrigin = static_cast<int>(rectTransform->m_origin);

		if (ImGui::Combo("Origin", &currentOrigin, OriginNameList, IM_ARRAYSIZE(OriginNameList)))
		{
			rectTransform->m_origin = static_cast<Origin>(currentOrigin);
		}

		rectTransform->m_localRotate = XMConvertToRadians(rotate);

		ImGui::TreePop();
	}
}

/**
 * \brief 物理演算の表示
 * 
 * \param comp コンポーネント
 */
void ObjectInspectorGui::DrawRigidbody(Component* comp)
{
	Rigidbody* rigidbody = static_cast<Rigidbody*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	if (ImGui::TreeNodeEx("Rigidbody", flag))
	{
		ImGui::DragFloat("GravityAcceleration", &rigidbody->m_gravityAcceleration,	0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("Friction",			&rigidbody->m_friction,				0.1f, 0.0f, 100.0f);
		ImGui::DragFloat("Mass",				&rigidbody->m_mass,					0.1f, 0.0f, 100.0f);
		
		bool togle = rigidbody->m_isDynamic;

		ImGui::Checkbox("IsDynamic", &togle);
		
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
