/*****************************************************************//**
 * \file   ObjectInspectorGui.cpp
 * \brief  オブジェクトのインスペクター表示
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

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
#include "Game/Component/Default/UI/SliderController.h"
#include "Game/Component/Default/UI/ButtonController.h"
#include "Game/Component/Default/UI/SpriteBobbing.h"
#include "Game/Component/Camera/TargetCameraController.h"
#include "Game/Component/Default/ScriptableComponent.h"

#include "Game/Component/Player/PlayerController.h"
#include "Game/Component/Player/PlayerStatusController.h"
#include "Game/Component/Enemy/EnemyController.h"
#include "Game/Component/Stage/StageController.h"
#include "Game/Component/Camera/TitleCameraController.h"
#include "Game/Component/Camera/GameCameraController.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
ObjectInspectorGui::ObjectInspectorGui()
{
	// Collider
	m_drawInspecter.emplace(typeid(Sphere), DrawSphere);
	m_drawInspecter.emplace(typeid(Mesh), DrawMesh);
	// Physics
	m_drawInspecter.emplace(typeid(Transform), DrawTransform);
	m_drawInspecter.emplace(typeid(RectTransform), DrawRectTransform);
	m_drawInspecter.emplace(typeid(Rigidbody), DrawRigidbody);
	// Renderer
	m_drawInspecter.emplace(typeid(ModelRenderer), DrawModelRenderer);
	m_drawInspecter.emplace(typeid(SpriteRenderer), DrawSpriteRenderer);
	m_drawInspecter.emplace(typeid(TextRenderer), DrawTextRenderer);
	// UI
	m_drawInspecter.emplace(typeid(SliderController), DrawSliderController);
	m_drawInspecter.emplace(typeid(SpriteBobbing), DrawSpriteBobbing);
	m_drawInspecter.emplace(typeid(SliderController), DrawSliderController);
	m_drawInspecter.emplace(typeid(ButtonController), DrawButtonController);
	// Camera
	m_drawInspecter.emplace(typeid(TargetCameraController), DrawTargetCamera);

	// Scriptable
	m_drawInspecter.emplace(typeid(ScriptableComponent), DrawScriptableComponent);

	// Others
	m_drawInspecter.emplace(typeid(PlayerController), DrawPlayerController);
	m_drawInspecter.emplace(typeid(PlayerStatusController), DrawPlayerStateController);
	m_drawInspecter.emplace(typeid(EnemyController), DrawEnemyController);
	m_drawInspecter.emplace(typeid(StageController), DrawStageController);
	m_drawInspecter.emplace(typeid(TitleCameraController), DrawTitleCameraController);
	m_drawInspecter.emplace(typeid(GameCameraController), DrawGameCameraController);
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
	ImGui::Begin("Inspector");

	if (selectedObject != nullptr)
	{
		ImGui::InputText("Name", &selectedObject->m_name);
		ImGui::InputInt("ID", &selectedObject->m_id);

		ImGui::BeginChild(selectedObject->GetName().c_str());

		for (auto& comp : *selectedObject->GetComponentsList())
		{
			// コンポーネント表示関数テーブルに存在すれば表示
			if (m_drawInspecter.find(typeid(*comp)) != m_drawInspecter.end())
			{
				m_drawInspecter[typeid(*comp)](comp.get());
			}
		}

		ImGui::EndChild();
	}

	ImGui::End();
}

// ------------------------- Inspector表示関数 ------------------------- //

/**
 * \brief 球コライダーの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawSphere(Component* comp)
{
	Sphere* sphere = static_cast<Sphere*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	ImGui::Separator();

	if (ImGui::TreeNodeEx("Sphere", flag))
	{
		ImGui::DragFloat("Radius", &sphere->m_radius);

		ImGui::TreePop();
	}
}

/**
 * \brief メッシュコライダーの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawMesh(Component* comp)
{
	Mesh* mesh = static_cast<Mesh*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	ImGui::Separator();

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

	ImGui::Separator();

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

	ImGui::Separator();

	if (ImGui::TreeNodeEx("SpriteRenderer", flag))
	{
		ImGui::InputText("SpriteKey", &spriteRenderer->m_spriteKey);

		ImGui::ColorEdit4("Color", &spriteRenderer->m_color.x);

		ImGui::DragFloat2("SpriteScale", &spriteRenderer->m_spriteScale.x, 0.1f);
		ImGui::DragFloat("LayerDepth", &spriteRenderer->m_layerDepth, 0.1f);

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

	ImGui::Separator();

	if (ImGui::TreeNodeEx("TextRenderer", flag))
	{
		std::string text = Utility::ConvertToMultiByteChar(textRenderer->m_text);

		ImGui::InputText("SpriteKey", &textRenderer->m_fontKey);
		ImGui::InputText("Text", &text);
		textRenderer->m_text = Utility::ConvertToWideChar(text);

		ImGui::ColorEdit4("Color", &textRenderer->m_color.x);
		ImGui::DragFloat("FontScale", &textRenderer->m_fontScale, 0.1f);
		ImGui::DragFloat("LayerDepth", &textRenderer->m_layerDepth, 0.1f);

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
	Transform* transform = static_cast<Transform*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	ImGui::Separator();

	if (ImGui::TreeNodeEx("Transform", flag))
	{
		// 回転
		SimpleMath::Vector3 rotate = transform->GetLocalRotate().ToEuler();

		rotate.x = XMConvertToDegrees(rotate.x);
		rotate.y = XMConvertToDegrees(rotate.y);
		rotate.z = XMConvertToDegrees(rotate.z);

		ImGui::DragFloat3("Position", &transform->m_localPosition.x);
		ImGui::DragFloat3("Rotate", &rotate.x);
		ImGui::DragFloat3("Scale", &transform->m_localScale.x, 0.1f);

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
	RectTransform* rectTransform = static_cast<RectTransform*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	ImGui::Separator();

	if (ImGui::TreeNodeEx("RectTransform", flag))
	{
		float rotate = XMConvertToDegrees(rectTransform->m_localRotate);

		ImGui::DragFloat2("Position", &rectTransform->m_localPosition.x);
		ImGui::DragFloat("Rotate", &rotate);
		ImGui::DragFloat2("Scale", &rectTransform->m_localScale.x, 0.1f);

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

	ImGui::Separator();

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

/**
 * \brief スライダーの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawSliderController(Component* comp)
{
	SliderController* sliderController = static_cast<SliderController*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	ImGui::Separator();

	if (ImGui::TreeNodeEx("SlideController", flag))
	{
		ImGui::SliderFloat("targetAmount", &sliderController->m_targetAmount, 0.0f, 1.0f);

		ImGui::DragFloat("SlideSpeed", &sliderController->m_slideSpeed);

		ImGui::TreePop();
	}
}

/**
 * \brief ボタンの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawButtonController(Component* comp)
{
	ButtonController* buttonController = static_cast<ButtonController*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	ImGui::Separator();

	if (ImGui::TreeNodeEx("ButtonController", flag))
	{
		ImGui::TreePop();
	}
}

/**
 * \brief スライダー浮遊コンポーネント
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawSpriteBobbing(Component* comp)
{
	SpriteBobbing* spriteBobbing = static_cast<SpriteBobbing*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	ImGui::Separator();

	if (ImGui::TreeNodeEx("SpriteBobbing", flag))
	{
		ImGui::DragFloat("Amplitude", &spriteBobbing->m_amplitude);
		ImGui::DragFloat("Frequency", &spriteBobbing->m_frequency);
		ImGui::DragFloat2("InitPos", &spriteBobbing->m_initPos.x);

		ImGui::TreePop();
	}
}

/**
 * \brief ターゲットカメラの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawTargetCamera(Component* comp)
{
	TargetCameraController* targetCamera = static_cast<TargetCameraController*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;
	
	ImGui::Separator();

	if (ImGui::TreeNodeEx("TargetCamera", flag))
	{
		ImGui::DragFloat3("Offset", &targetCamera->m_baseOffset.x);

		ImGui::TreePop();
	}
}

/**
 * \brief ScriptableObjectの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawScriptableComponent(Component* comp)
{
	ScriptableComponent* scriptable = static_cast<ScriptableComponent*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	ImGui::Separator();

	if (ImGui::TreeNodeEx("Scriptable", flag))
	{
		for (auto& value : scriptable->GetValueList())
		{
			switch (value.second.first)
			{
			case ValueType::Float:
				ImGui::DragFloat(value.first.c_str(), &std::get<float>(value.second.second));
				break;
			case ValueType::Vector2:
				ImGui::DragFloat2(value.first.c_str(), &std::get<SimpleMath::Vector2>(value.second.second).x);
				break;
			case ValueType::Vector3:
				ImGui::DragFloat3(value.first.c_str(), &std::get<SimpleMath::Vector3>(value.second.second).x);
				break;
			case ValueType::Color:
				ImGui::ColorEdit4(value.first.c_str(), &std::get<SimpleMath::Color>(value.second.second).x);
				break;
			case ValueType::String:
				ImGui::InputText(value.first.c_str(), &std::get<std::string>(value.second.second));
				break;
			default:
				break;
			}
		}

		ImGui::TreePop();
	}

}

/**
 * \brief プレイヤー操作コンポーネントの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawPlayerController(Component* comp)
{
	PlayerController* playerController = static_cast<PlayerController*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	ImGui::Separator();

	if (ImGui::TreeNodeEx("PlayerController", flag))
	{
		ImGui::DragFloat("AttackDuration", &playerController->m_attackDuration);
		ImGui::DragFloat("AttackSpeed", &playerController->m_attackSpeed);
		ImGui::DragFloat("Acceleration", &playerController->m_acceleration);
		ImGui::DragFloat("MaxSpeed", &playerController->m_maxSpeed);

		ImGui::TreePop();
	}
}

/**
 * \brief プレイヤーステータス操作コンポーネントの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawPlayerStateController(Component* comp)
{
	PlayerStatusController* playerStatusController = static_cast<PlayerStatusController*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	ImGui::Separator();

	if (ImGui::TreeNodeEx("PlayerStatusController", flag))
	{
		ImGui::DragInt("AttackCost", &playerStatusController->m_attackCost);
		ImGui::DragFloat("MinAttackPower", &playerStatusController->m_minAttackPower);

		ImGui::TreePop();
	}
}

/**
 * \brief 敵操作コンポーネントの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawEnemyController(Component* comp)
{
	EnemyController* enemyController = static_cast<EnemyController*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	ImGui::Separator();

	if (ImGui::TreeNodeEx("EnemyController", flag))
	{
		ImGui::DragFloat("Acceleration", &enemyController->m_acceleration);
		ImGui::DragFloat("AvoidWallDistance", &enemyController->m_avoidWallDistance);
		ImGui::DragFloat("AvoidWallWeakForce", &enemyController->m_avoidWallWeakForce);
		ImGui::DragFloat("AvoidWallStrongForce", &enemyController->m_avoidWallStrongForce);
		ImGui::DragFloat("MaxHp", &enemyController->m_maxHp);

		ImGui::DragFloat("DirectionCircleDistance", &enemyController->m_directionCircleDistance);
		ImGui::DragFloat("DirectionCircleRadius", &enemyController->m_directionCircleRadius);
		ImGui::DragFloat("DirectionChageInterval", &enemyController->m_directionChageInterval);

		ImGui::TreePop();
	}

}

/**
 * \brief ステージ操作コンポーネントの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawStageController(Component* comp)
{

	StageController* stageController = static_cast<StageController*>(comp);

	ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	ImGui::Separator();

	if (ImGui::TreeNodeEx("EnemyController", flag))
	{
		ImGui::DragFloat("FloorCenterPosY", &stageController->m_floorCenterPosY);
		ImGui::DragFloat("FloorNormalY", &stageController->m_floorNormalY);

		ImGui::TreePop();
	}
}

/**
 * \brief タイトルカメラ操作コンポーネントの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawTitleCameraController(Component* comp)
{
	TitleCameraController* titleCameraController 
		= static_cast<TitleCameraController*>(comp);

	ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	ImGui::Separator();

	if (ImGui::TreeNodeEx("TitleCameraController", flag))
	{
		ImGui::DragFloat("rotateAngleRad", &titleCameraController->m_rotateAngeleRad);

		ImGui::TreePop();
	}

	DrawTargetCamera(comp);
}

/**
 * \brief ゲームカメラ操作コンポーネントの表示
 * 
 * \param comp 基底コンポーネント
 */
void ObjectInspectorGui::DrawGameCameraController(Component* comp)
{
	GameCameraController* gameCameraController
		= static_cast<GameCameraController*>(comp);

	ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

	ImGui::Separator();

	if (ImGui::TreeNodeEx("GameCameraController", flag))
	{
		ImGui::DragFloat("rotateAngleRad", &gameCameraController->m_rotateAngleRad);

		ImGui::TreePop();
	}

	DrawTargetCamera(comp);
}
