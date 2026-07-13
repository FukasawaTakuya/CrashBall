/*****************************************************************//**
 * \file   StageController.cpp
 * \brief  ステージ操作コンポーネント
 *
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "StageController.h"

#include "Game/ScriptableObject/Scriptable.h"

using namespace DirectX;

/**
 * \brief コピーコンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param other コピー元
 */
StageController::StageController(
	IGameObject* gameObject, 
	const StageController& other)
	: Component(gameObject)
	, m_floorNormalY(other.m_floorNormalY)
	, m_floorCenterPosY(other.m_floorCenterPosY)
{
	// キャッシュの取得
	Transform* transform = GetGameObject()->GetComponent<Transform>();
	m_meshCollider = GetGameObject()->GetComponent<Mesh>();

	m_gameColor = Scriptable::GetScriptableObject("gameColor");

	// 衝突中の処理の登録
	m_meshCollider->SetOnCollisionStayCmd([this](Collider* other)
		{
			// 衝突オブジェクトがプレイヤーの時の処理
			if (other->GetGameObject()->GetTag() == ObjectTag::Player)
			{
				for (auto& hitface : m_meshCollider->GetCollideFace())
				{
					PaintFace(hitface, m_gameColor->GetValue<SimpleMath::Color>("PlayerColor"));
				}
			}
			// 衝突オブジェクトが敵の時の処理
			else if (other->GetGameObject()->GetTag() == ObjectTag::Enemy)
			{
				for (auto& hitface : m_meshCollider->GetCollideFace())
				{
					PaintFace(hitface, m_gameColor->GetValue<SimpleMath::Color>("EnemyColor"));
				}
			}
		});

	// 床メッシュと壁メッシュに分ける
	for (auto& face : m_meshCollider->GetFace())
	{
		// 床メッシュ
		if (face->GetPlane()->GetNormal().y >= m_floorNormalY &&
			face->GetCenter().y <= m_floorCenterPosY)
		{
			m_floorMesh.push_back(face.get());
			m_floorMeshColor.emplace(face.get(), m_gameColor->GetValue<SimpleMath::Color>("DefaultFaceColor"));
		}
		// 壁メッシュ
		else {
			m_wallMesh.push_back(face.get());
		}
	}
}

/**
 * \brief デストラクタ
 * 
 */
StageController::~StageController()
{
}

/**
 * \brief 初期化
 * 
 */
void StageController::Initialize()
{
	// 色をデフォルトに戻す
	for (auto& floorMeshColor : m_floorMeshColor)
	{
		floorMeshColor.second = Colors::White;
	}
}

/**
 * \brief 更新
 * 
 * \param gameContext
 */
void StageController::Update(const GameContext& gameContext)
{
	// プレイヤーが塗った面を数える
	m_playerMeshCount =
		std::count_if(m_floorMeshColor.begin(), m_floorMeshColor.end(),
			[&](const std::pair<Triangle*, SimpleMath::Color>& floorMeshColor)
			{
				return XMVector4Equal(floorMeshColor.second, m_gameColor->GetValue<SimpleMath::Color>("PlayerColor"));
			});

	// 敵が塗った面を数える
	m_enemyMeshCount =
		std::count_if(m_floorMeshColor.begin(), m_floorMeshColor.end(),
			[&](const std::pair<Triangle*, SimpleMath::Color>& floorMeshColor)
			{
				return XMVector4Equal(floorMeshColor.second, m_gameColor->GetValue<SimpleMath::Color>("EnemyColor"));
			});
}


/**
 * \brief 描画
 * 
 * \param renderContext
 */
void StageController::Render(const RenderContext& renderContext)
{
	auto& primitiveRenderer = renderContext.primitiveRendererManager;

	// 描画
	for (auto& face : m_meshCollider->GetFace())
	{
		// 面の色
		DirectX::SimpleMath::Color faceColor = {1.0f, 1.0f, 1.0f, 1.0f};

		// 面の色情報が登録されているなら
		auto it = m_floorMeshColor.find(face.get());
		if (it != m_floorMeshColor.end())
		{
			faceColor = it->second;
		}

		// 頂点
		std::vector<DirectX::VertexPositionNormalColor> pos
		{
			VertexPositionNormalColor(face->GetPoint()[0], face->GetPlane()->GetNormal(), faceColor),
			VertexPositionNormalColor(face->GetPoint()[1], face->GetPlane()->GetNormal(), faceColor),
			VertexPositionNormalColor(face->GetPoint()[2], face->GetPlane()->GetNormal(), faceColor)
		};

		// 描画命令登録
		primitiveRenderer->RegisterRenderCommand(
			D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			pos
		);
	}
}

/**
 * \brief 終了処理
 * 
 */
void StageController::Finalize()
{
}

/**
 * \brief 面の消費
 * 
 * \param 消費する面の数
 */
void StageController::ConsumePaint(int consumePaintNum)
{
	std::vector<std::pair<Triangle*, SimpleMath::Color>> playerFaceColor;

	// プレイヤーの面を取り出す
	std::copy_if(m_floorMeshColor.begin(), m_floorMeshColor.end(), std::back_inserter(playerFaceColor),
		[&](const std::pair<Triangle*, SimpleMath::Color>& floorMeshColor) {
			return XMVector4Equal(floorMeshColor.second, m_gameColor->GetValue<SimpleMath::Color>("PlayerColor"));
		});

	// プレイヤーの面の数が消費するプレイヤーの面の数より少なければreturn
	if (playerFaceColor.size() < consumePaintNum)
	{
		return;
	}

	// プレイヤーの面を定数枚デフォルトの色に戻す
	std::for_each_n(playerFaceColor.begin(), consumePaintNum,
		[&](const std::pair<Triangle*, SimpleMath::Color>& floorMeshColor)
		{
			PaintFace(floorMeshColor.first, m_gameColor->GetValue<SimpleMath::Color>("DefaultFaceColor"));
		});
}

/**
 * \brief 面を塗る
 * 
 * \param face 塗る面のポインタ
 * \param color 色
 */
void StageController::PaintFace(
	Triangle* face, 
	const DirectX::SimpleMath::Color& color)
{
	// 面情報が登録されているなら
	if (m_floorMeshColor.find(face) != m_floorMeshColor.end())
	{
		// 色の変更
		m_floorMeshColor[face] = color;
	}
}
