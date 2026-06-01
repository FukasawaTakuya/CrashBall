#include "pch.h"
#include "Stage.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
Stage::Stage()
	: GameObject(ObjectTag::Stage)
{
	// コンポーネントの追加
	m_transform		= AddComponent<Transform>();
	m_meshCollider	= AddComponent<Mesh>();
	m_renderer		= AddComponent<ModelRenderer>();

	// 
	m_transform->SetScale(SCALE);

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
					PaintFace(hitface, Colors::LightSkyBlue);
				}
			}
			// 衝突オブジェクトが敵の時の処理
			else if (other->GetGameObject()->GetTag() == ObjectTag::Enemy)
			{
				for (auto& hitface : m_meshCollider->GetCollideFace())
				{
					PaintFace(hitface, Colors::LightPink);
				}
			}
		});

	for (auto& face : m_meshCollider->GetFace())
	{
		// 床メッシュ
		if (face->GetPlane()->GetNormal().y >= 0.3f && 
			face->GetCenter().y <= 20.0f)
		{
			m_floorMesh.push_back(face.get());
			m_floorMeshColor.emplace(face.get(), Colors::White);
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
Stage::~Stage()
{
}

/**
 * \brief 初期化
 *
 */
void Stage::Initialize()
{
	for (auto& floorMeshColor : m_floorMeshColor)
	{
		floorMeshColor.second = Colors::White;
	}
}

/**
 * \brief 更新
 *
 */
void Stage::Update(const GameContext& gameContext)
{
	m_playerMeshCount =
		std::count_if(m_floorMeshColor.begin(), m_floorMeshColor.end(),
			[](const std::pair<Triangle*, XMVECTORF32>& floorMeshColor)
			{
				return XMVector4Equal(floorMeshColor.second, Colors::LightSkyBlue);
			});

	m_enemyMeshCount =
		std::count_if(m_floorMeshColor.begin(), m_floorMeshColor.end(),
			[](const std::pair<Triangle*, XMVECTORF32>& floorMeshColor)
			{
				return XMVector4Equal(floorMeshColor.second, Colors::LightPink);
			});
}

/**
 * \brief 描画
 *
 */
void Stage::Render(const RenderContext& renderContext)
{
	auto& primitiveRenderer = renderContext.m_pPrimitiveRendererManager;

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

	auto& textRenderer = renderContext.m_pTextRendererManager;

	textRenderer->RegisterRenderCommand({ 200.0f, 0.0f }, Colors::White, 1.0f,
		L"Player : {}  Enemy : {}", m_playerMeshCount, m_enemyMeshCount);
}

/**
 * \brief 終了処理
 *
 * \param RenderContext
 */
void Stage::Finalize()
{
}

/**
 * \brief 面に色を塗る
 *
 * \param color
 */
void Stage::PaintFace(Triangle* face, const XMVECTORF32& color)
{
	// 面情報が登録されているなら
	if (m_floorMeshColor.find(face) != m_floorMeshColor.end())
	{
		// 色の変更
		m_floorMeshColor[face] = color;
	}
}
