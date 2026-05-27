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

	// トランスフォームの設定
	m_meshCollider->SetTransform(m_transform);
	// レイヤーマスクの設定
	m_meshCollider->SetLayerMask(LayerMask::Ground);

	// 衝突中の処理の登録
	m_meshCollider->SetOnCollisionStayCmd([this](Collider* other)
		{
			// 衝突オブジェクトがプレイヤーの時の処理
			if (other->GetOwner()->GetTag() == ObjectTag::Player)
			{
				for (auto& hitface : m_meshCollider->GetCollideFace())
				{
					PaintFace(hitface, Colors::LightSkyBlue);
				}
			}
			// 衝突オブジェクトが敵の時の処理
			else if (other->GetOwner()->GetTag() == ObjectTag::Enemy)
			{
				for (auto& hitface : m_meshCollider->GetCollideFace())
				{
					PaintFace(hitface, Colors::LightPink);
				}
			}
		});

	
	// コライダーデータの読み込み
	m_meshCollider->LoadJson(L"Resources/Models/Stage.json", SCALE);

	for (auto& face : m_meshCollider->GetFace())
	{
		// 床メッシュ
		if (face->GetPlane()->GetNormal().y >= 0.3f && 
			face->GetCenter().y <= 20.0f)
		{
			m_floorMesh.push_back(face.get());
			m_floorColor.emplace(face.get(), Colors::White);
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
}

/**
 * \brief 更新
 *
 */
void Stage::Update(const GameContext& gameContext)
{
	m_playerMeshCount =
		std::count_if(m_floorColor.begin(), m_floorColor.end(),
			[](const std::pair<Triangle*, XMVECTORF32>& floorColor)
			{
				return floorColor.second == Colors::White;
			});

	m_enemyMeshCount =
		std::count_if(m_floorColor.begin(), m_floorColor.end(),
			[](const std::pair<Triangle*, XMVECTORF32>& floorColor)
			{
				return floorColor.second == Colors::LightPink;
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
		auto it = m_floorColor.find(face.get());
		if (it != m_floorColor.end())
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
		L"Player : {}  Enemy : {}", 1, 2);
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
	if (m_floorColor.find(face) != m_floorColor.end())
	{
		// 色の変更
		m_floorColor[face] = color;
	}
}
