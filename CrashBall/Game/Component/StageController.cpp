/*****************************************************************//**
 * \file   StageController.cpp
 * \brief  ステータス操作コンポーネント
 *
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/


#include "pch.h"
#include "Game/Common/Screen.h"
#include "StageController.h"

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
StageController::StageController(IGameObject* gameObject)
	: Component(gameObject)
{
	// コンポーネントの追加
	Transform* transform = GetGameObject()->GetComponent<Transform>();

	m_meshCollider = GetGameObject()->GetComponent<Mesh>();

	// スケールの設定
	transform->SetScale(SCALE);

	// コライダーデータの読み込み
	m_meshCollider->LoadJson(L"Resources/Models/Stage.json");

	// レイヤーマスクの設定
	m_meshCollider->SetLayerMask(LayerMask::Ground);

	// 衝突中の処理の登録
	m_meshCollider->SetOnCollisionStayCmd([this](Collider* other)
		{
			// 衝突オブジェクトがプレイヤーの時の処理
			if (other->GetGameObject()->GetTag() == ObjectTag::Player)
			{
				for (auto& hitface : m_meshCollider->GetCollideFace())
				{
					PaintFace(hitface, PLAYER_COLOR);
				}
			}
			// 衝突オブジェクトが敵の時の処理
			else if (other->GetGameObject()->GetTag() == ObjectTag::Enemy)
			{
				for (auto& hitface : m_meshCollider->GetCollideFace())
				{
					PaintFace(hitface, ENEMY_COLOR);
				}
			}
		});

	// 床メッシュと壁メッシュに分ける
	for (auto& face : m_meshCollider->GetFace())
	{
		// 床メッシュ
		if (face->GetPlane()->GetNormal().y >= 0.3f &&
			face->GetCenter().y <= 20.0f)
		{
			m_floorMesh.push_back(face.get());
			m_floorMeshColor.emplace(face.get(), DEFAULT_COLOR);
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
	m_playerMeshCount =
		std::count_if(m_floorMeshColor.begin(), m_floorMeshColor.end(),
			[&](const std::pair<Triangle*, XMVECTORF32>& floorMeshColor)
			{
				return XMVector4Equal(floorMeshColor.second, PLAYER_COLOR);
			});

	m_enemyMeshCount =
		std::count_if(m_floorMeshColor.begin(), m_floorMeshColor.end(),
			[&](const std::pair<Triangle*, XMVECTORF32>& floorMeshColor)
			{
				return XMVector4Equal(floorMeshColor.second, ENEMY_COLOR);
			});

	m_normalMeshCount
		= m_floorMesh.size() - m_playerMeshCount - m_enemyMeshCount;
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
		XMVECTORF32 faceColor = Colors::White;

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

	auto& textRenderer = renderContext.textRendererManager;

	textRenderer->DebugRender(
		SimpleMath::Vector2(200.0f, 200.0f), 
		Colors::Black, 
		0.0f,
		1.5f,
		SimpleMath::Vector2::Zero,
		1.0f,
		L"Player : {}  Enemy : {}", m_playerMeshCount, m_enemyMeshCount);

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
	std::vector<std::pair<Triangle*, XMVECTORF32>> playerFaceColor;

	// プレイヤーの面を取り出す
	std::copy_if(m_floorMeshColor.begin(), m_floorMeshColor.end(), std::back_inserter(playerFaceColor),
		[&](const std::pair<Triangle*, XMVECTORF32>& floorMeshColor) {
			return XMVector4Equal(floorMeshColor.second, PLAYER_COLOR);
		});

	// プレイヤーの面の数がリセットするプレイヤーの面の数より小さければreturn
	if (playerFaceColor.size() < consumePaintNum)
	{
		return;
	}

	// プレイヤーの面をデフォルトの色に戻す
	std::for_each_n(playerFaceColor.begin(), consumePaintNum,
		[&](const std::pair<Triangle*, XMVECTORF32>& floorMeshColor)
		{
			PaintFace(floorMeshColor.first, DEFAULT_COLOR);
		});
}


/**
 * \brief 面を塗る
 * 
 * \param face
 * \param color
 */
void StageController::PaintFace(
	Triangle* face, 
	const XMVECTORF32& color)
{
	// 面情報が登録されているなら
	if (m_floorMeshColor.find(face) != m_floorMeshColor.end())
	{
		// 色の変更
		m_floorMeshColor[face] = color;
	}
}
