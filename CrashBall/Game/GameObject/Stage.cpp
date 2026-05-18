#include "pch.h"
#include "Stage.h"
#include "Game/ResourceManager/ResourceManager.h"
#include "Game/Renderer/PrimitiveRendererManager.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
Stage::Stage()
	: GameObject(ObjectTag::Stage)
{
	// コンポーネントの追加
	m_transform = AddComponent<Transform>();
	m_meshCollider = AddComponent<Mesh>();
	m_renderer = AddComponent<ModelRenderer>();

	// レイヤーマスクの設定
	m_meshCollider->SetLayerMask(LayerMask::Ground);

	// 拡大率の設定
	m_meshCollider->SetScale(SCALE);
	m_transform->SetScale(SCALE);

	// 衝突中の処理の登録
	m_meshCollider->SetOnCollisionStayCmd([this](Collider* other)
		{
			// 衝突オブジェクトがプレイヤーの時の処理
			if (other->GetOwner()->GetTag() == ObjectTag::Player)
			{
				for (auto& hitface : m_meshCollider->GetCollideFace())
				{
					PaintFace(hitface, Colors::Blue);
				}
			}
			// 衝突オブジェクトが敵の時の処理
			else if (other->GetOwner()->GetTag() == ObjectTag::Enemy)
			{
				for (auto& hitface : m_meshCollider->GetCollideFace())
				{
					PaintFace(hitface, Colors::Red);
				}
			}
		});

	
	// コライダーデータの読み込み
	m_meshCollider->LoadJson(L"Resources/Models/Stage.json", SCALE);

	for (auto& face : m_meshCollider->GetFace())
	{
		// 床メッシュ
		if (face->GetCenter().y >= 4.0f && face->GetCenter().y <= 8.0f)
		{
			m_floorMesh.push_back(face.get());
			m_faceColor.emplace(face.get(), Colors::White);
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
void Stage::Update()
{
}

/**
 * \brief 描画
 *
 */
void Stage::Draw()
{
	auto& primitiveRenderer = PrimitiveRendererManager::Instance;

	// 描画
	for (auto& face : m_meshCollider->GetFace())
	{
		// 面の色
		XMVECTORF32 faceColor = Colors::White;

		// 面の色情報が登録されているなら
		auto it = m_faceColor.find(face.get());
		if (it != m_faceColor.end())
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
		primitiveRenderer().RegisterDrawCommand({
			D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			pos
			});
	}
}

/**
 * \brief 面に色を塗る
 * 
 * \param color
 */
void Stage::PaintFace(Triangle* face, const XMVECTORF32& color)
{
	// 面情報が登録されているなら
	if (m_faceColor.find(face) != m_faceColor.end())
	{
		// 色の変更
		m_faceColor[face] = color;
	}
}
