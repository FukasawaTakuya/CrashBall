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
#include "Game/PaintTexture/Paint.h"

using namespace DirectX;

RegisterComponent(StageController)

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
StageController::StageController(IGameObject* gameObject)
	: Component(gameObject)
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void StageController::Awake()
{
	// キャッシュの取得
	m_transform = GetGameObject()->GetComponent<Transform>();
	m_meshCollider = GetGameObject()->GetComponent<Mesh>();
	m_modelRenderer = GetGameObject()->GetComponent<ModelRenderer>();

	m_gameColor = Scriptable::GetScriptableObject<GameColor>();

	m_model = GetGameObject()->GetComponent<ModelRenderer>()->GetModel();
	m_paintTextureInfo = m_modelRenderer->GetPixelShader()->GetShaderTextrueInfo("PaintTexture");

	// 衝突中の処理の登録
	m_meshCollider->SetOnCollisionStayCmd([this](Collider* other)
		{
			ObjectTag tag = other->GetGameObject()->GetTag();
			// 衝突オブジェクトがプレイヤーの時の処理
			if (tag == ObjectTag::Player)
			{
				PaintFace(m_gameColor->m_playerColor);
			}
			// 衝突オブジェクトが敵の時の処理
			else if (tag == ObjectTag::Enemy)
			{
				PaintFace(m_gameColor->m_enemyColor);
			}
		});

	//auto csShader = m_modelRenderer->ComputeShader("name");
	// csShader->CreateUAV("name", count);


	// 床メッシュと壁メッシュに分ける
	//for (auto& face : m_meshCollider->GetFace())
	//{
	//	// 床メッシュ
	//	if (face->GetPlane()->GetNormal().y >= m_floorNormalY)
	//	{
	//		m_floorMesh.push_back(face.get());
	//		m_floorMeshColor.emplace(face.get(), m_gameColor->m_defaultFaceColor);
	//	}
	//}
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void StageController::Start(const GameContext& gameContext)
{
	// 色をデフォルトに戻す
	//for (auto& floorMeshColor : m_floorMeshColor)
	//{
	//	floorMeshColor.second = m_gameColor->m_defaultFaceColor;
	//}

	Paint::ClearPaint();

	//m_enemyMeshCount = 0;
	//m_playerMeshCount = 0;

}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void StageController::Update(const GameContext& gameContext)
{
	// プレイヤーが塗った面を数える
	//m_playerMeshCount =
	//	std::count_if(m_floorMeshColor.begin(), m_floorMeshColor.end(),
	//		[&](const std::pair<Triangle*, SimpleMath::Color>& floorMeshColor)
	//		{
	//			return XMVector4Equal(floorMeshColor.second, m_gameColor->m_playerColor);
	//		});

	//// 敵が塗った面を数える
	//m_enemyMeshCount =
	//	std::count_if(m_floorMeshColor.begin(), m_floorMeshColor.end(),
	//		[&](const std::pair<Triangle*, SimpleMath::Color>& floorMeshColor)
	//		{
	//			return XMVector4Equal(floorMeshColor.second, m_gameColor->m_enemyColor);
	//		});

	if(m_paintTextureInfo)
		m_paintTextureInfo->texture = Paint::GetPaintTexture();
}


/**
 * \brief 描画
 * 
 * \param renderContext
 */
void StageController::Render(const RenderContext& renderContext)
{
}


/**
 * \brief 面の消費
 * 
 * \param 消費する面の数
 */
void StageController::ConsumePaint(int consumePaintNum)
{
	//std::vector<std::pair<Triangle*, SimpleMath::Color>> playerFaceColor;

	//// プレイヤーの面を取り出す
	//std::copy_if(m_floorMeshColor.begin(), m_floorMeshColor.end(), std::back_inserter(playerFaceColor),
	//	[&](const std::pair<Triangle*, SimpleMath::Color>& floorMeshColor) {
	//		return XMVector4Equal(floorMeshColor.second, m_gameColor->m_playerColor);
	//	});

	//// プレイヤーの面の数が消費するプレイヤーの面の数より少なければreturn
	//if (playerFaceColor.size() < consumePaintNum)
	//{
	//	return;
	//}

	//// プレイヤーの面を定数枚デフォルトの色に戻す
	//std::for_each_n(playerFaceColor.begin(), consumePaintNum,
	//	[&](const std::pair<Triangle*, SimpleMath::Color>& floorMeshColor)
	//	{
	//		PaintFace(floorMeshColor.first, m_gameColor->m_defaultFaceColor);
	//	});

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

/**
 * \brief 面を塗る
 * 
 * \param color 色
 */
void StageController::PaintFace(const DirectX::SimpleMath::Color& color)
{
	auto& faces = m_meshCollider->GetFace();
	auto& indexList = m_model->GetIndexList();
	for (auto& index : m_meshCollider->GetCollideFaceIndex())
	{
		// 衝突面の頂点情報
		const Vertex& v0 = m_model->GetVertex(indexList[index] * 3 + 0);
		const Vertex& v1 = m_model->GetVertex(indexList[index] * 3 + 1);
		const Vertex& v2 = m_model->GetVertex(indexList[index] * 3 + 2);

		// 衝突点
		SimpleMath::Vector3 collisionPos = faces[index]->GetCollisionPos();

		// 衝突点からUV座標を求める
		SimpleMath::Vector2 uv = CalcUV(collisionPos, v0, v1, v2);

		// 塗り
		Paint::Paint(uv, color);
	}
}

/**
 * \brief 衝突点からUV座標を求める
 * 
 * \param p 衝突点
 * \param a 三角形の頂点
 * \param b 三角形の頂点
 * \param c 三角形の頂点
 * \return 
 */
DirectX::SimpleMath::Vector2 StageController::CalcUV(
	const DirectX::SimpleMath::Vector3& p, 
	const Vertex& a, 
	const Vertex& b, 
	const Vertex& c)
{
	SimpleMath::Vector2 outUV;

	// 2D座標に直す
	// 基準の軸
	SimpleMath::Vector3 axisX = XMVector3Normalize(b.position - a.position);
	SimpleMath::Vector3 axisY = a.normal.Cross(axisX);
	// ローカル座標の各点
	SimpleMath::Vector2 localA = To2DPosition(axisX, axisY, a.position, a.position);
	SimpleMath::Vector2 localB = To2DPosition(axisX, axisY, a.position, b.position);
	SimpleMath::Vector2 localC = To2DPosition(axisX, axisY, a.position, c.position);
	SimpleMath::Vector2 localP = To2DPosition(axisX, axisY, a.position, p / m_transform->GetWorldScale());

	// それぞれの頂点から衝突点への係数を求める
	float denominator = (localB.y - localC.y) * (localA.x - localC.x) 
					+ (localC.x - localB.x) * (localA.y - localC.y);

	if (denominator == 0.0f) return outUV;

	float alpha = ((localB.y - localC.y) * (localP.x - localC.x) + (localC.x - localB.x) * (localP.y - localC.y))
		/ denominator;

	float beta = ((localC.y - localA.y) * (localP.x - localC.x) + (localA.x - localC.x) * (localP.y - localC.y))
		/ denominator;

	float gamma = 1.0f - alpha - beta;

	outUV = a.uv * alpha + b.uv * beta + c.uv * gamma;

	return outUV;
}

/**
 * \brief 2D座標に直す
 * 
 * \param axisX X軸
 * \param axisY Y軸
 * \param origin 原点
 * \param point 直したい点
 * \return 
 */
DirectX::SimpleMath::Vector2 StageController::To2DPosition(
	const DirectX::SimpleMath::Vector3& axisX, 
	const DirectX::SimpleMath::Vector3& axisY, 
	const DirectX::SimpleMath::Vector3& origin, 
	const DirectX::SimpleMath::Vector3& point)
{
	// 原点から目標へのベクトル
	SimpleMath::Vector3 vec = point - origin;

	SimpleMath::Vector2 pos =
	{
		axisX.Dot(vec),
		axisY.Dot(vec)
	};

	return pos;
}
