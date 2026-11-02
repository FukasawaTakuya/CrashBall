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


	// 床メッシュと壁メッシュに分ける
	for (auto& face : m_meshCollider->GetFace())
	{
		// 床メッシュ
		if (face->GetPlane()->GetNormal().y >= m_floorNormalY)
		{
			m_floorMesh.push_back(face.get());
			m_floorMeshColor.emplace(face.get(), m_gameColor->m_defaultFaceColor);
		}
	}
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void StageController::Start(const GameContext& gameContext)
{
	// 色をデフォルトに戻す
	for (auto& floorMeshColor : m_floorMeshColor)
	{
		floorMeshColor.second = m_gameColor->m_defaultFaceColor;
	}

	m_model = GetGameObject()->GetComponent<ModelRenderer>()->GetModel();
	m_paintTextureInfo = m_modelRenderer->GetPixelShader()->GetShaderTextrueInfo("PaintTexture");

	m_enemyMeshCount = 0;
	m_playerMeshCount = 0;

	// 衝突中の処理の登録
	m_meshCollider->SetOnCollisionStayCmd([this](Collider* other)
		{
			// 衝突オブジェクトがプレイヤーの時の処理
			if (other->GetGameObject()->GetTag() == ObjectTag::Player)
			{
				//for (auto& hitface : m_meshCollider->GetCollideFace())
				//{
				//	PaintFace(hitface, m_gameColor->m_playerColor);
				//}

				auto& faces = m_meshCollider->GetFace();
				auto& indexList = m_model->GetIndexList();
				for (auto& index : m_meshCollider->GetCollideFaceIndex())
				{
					const Vertex v0 = m_model->GetVertex(indexList[index] * 3 + 0);
					const Vertex v1 = m_model->GetVertex(indexList[index] * 3 + 1);
					const Vertex v2 = m_model->GetVertex(indexList[index] * 3 + 2);

					auto collisionPos = faces[index]->GetCollisionPos();

					SimpleMath::Vector2 uv;
					CalculateUV(collisionPos, v0, v1, v2, uv);
					Paint::Paint(uv, m_gameColor->m_playerColor);

					//OutputDebugStringA(std::format("fx:{} fy:{} fz:{}\n", collisionPos.x, collisionPos.y, collisionPos.z).c_str());
					//OutputDebugStringA(std::format("uvx:{} uvy:{}\n", uv.x, uv.y).c_str());
				}
			}
			// 衝突オブジェクトが敵の時の処理
			else if (other->GetGameObject()->GetTag() == ObjectTag::Enemy)
			{
				auto& faces = m_meshCollider->GetFace();
				auto& indexList = m_model->GetIndexList();
				for (auto& index : m_meshCollider->GetCollideFaceIndex())
				{
					const Vertex v0 = m_model->GetVertex(indexList[index] * 3 + 0);
					const Vertex v1 = m_model->GetVertex(indexList[index] * 3 + 1);
					const Vertex v2 = m_model->GetVertex(indexList[index] * 3 + 2);

					auto collisionPos = faces[index]->GetCollisionPos();

					SimpleMath::Vector2 uv;
					CalculateUV(collisionPos, v0, v1, v2, uv);
					Paint::Paint(uv, m_gameColor->m_enemyColor);
				}
			}
		});

}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void StageController::Update(const GameContext& gameContext)
{
	// プレイヤーが塗った面を数える
	m_playerMeshCount =
		std::count_if(m_floorMeshColor.begin(), m_floorMeshColor.end(),
			[&](const std::pair<Triangle*, SimpleMath::Color>& floorMeshColor)
			{
				return XMVector4Equal(floorMeshColor.second, m_gameColor->m_playerColor);
			});

	// 敵が塗った面を数える
	m_enemyMeshCount =
		std::count_if(m_floorMeshColor.begin(), m_floorMeshColor.end(),
			[&](const std::pair<Triangle*, SimpleMath::Color>& floorMeshColor)
			{
				return XMVector4Equal(floorMeshColor.second, m_gameColor->m_enemyColor);
			});

	auto& faces = m_meshCollider->GetFace();
	for (auto& index : m_meshCollider->GetCollideFaceIndex())
	{
		auto colPos = faces[index]->GetCollisionPos();
		//OutputDebugStringA(std::format("rx:{} ry:{} rz:{}\n\n", colPos.x, colPos.y, colPos.z).c_str());
	}

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
	auto& primitiveRenderer = renderContext.primitiveRendererManager;

	// 描画
	for (auto& face : m_meshCollider->GetCollideFace())
	{
		// 面の色
		DirectX::SimpleMath::Color faceColor = {1.0f, 0.0f, 0.0f, 1.0f};

		// 面の色情報が登録されているなら
		//auto it = m_floorMeshColor.find(face.get());
		//if (it != m_floorMeshColor.end())
		//{
		//	faceColor = it->second;
		//}

		// 頂点
		//std::vector<DirectX::VertexPositionNormalColor> pos
		//{
		//	VertexPositionNormalColor(face->GetPoint()[0], face->GetPlane()->GetNormal(), faceColor),
		//	VertexPositionNormalColor(face->GetPoint()[1], face->GetPlane()->GetNormal(), faceColor),
		//	VertexPositionNormalColor(face->GetPoint()[2], face->GetPlane()->GetNormal(), faceColor)
		//};

		//// 描画命令登録
		//primitiveRenderer->RegisterRenderCommand(
		//	D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		//	pos);

		auto colPos = face->GetCollisionPos();

		std::vector<DirectX::VertexPositionNormalColor> pos2
		{
			VertexPositionNormalColor(colPos, face->GetPlane()->GetNormal(), faceColor),
			VertexPositionNormalColor(colPos + face->GetPlane()->GetNormal() * 4, face->GetPlane()->GetNormal(), faceColor),
		};

		primitiveRenderer->RegisterRenderCommand(
			D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
			pos2);
		//OutputDebugStringA(std::format("x:{} y:{} z:{}\n\n", colPos.x, colPos.y, colPos.z).c_str());

	}
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
			return XMVector4Equal(floorMeshColor.second, m_gameColor->m_playerColor);
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
			PaintFace(floorMeshColor.first, m_gameColor->m_defaultFaceColor);
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

bool StageController::CalculateUV(
	const DirectX::SimpleMath::Vector3& p, 
	const Vertex& a, 
	const Vertex& b, 
	const Vertex& c, 
	DirectX::SimpleMath::Vector2& outUV)
{
	// それぞれの頂点から衝突点への係数を求める
	//α＝{ (By - Cy)(Px - Cx) + (Cx - Bx)(Py - Cy) } / {(By - Cy)(Ax - Cx) + (Cx - Bx)(Ay - Cy)}
	//β＝{ (Cy - Ay)(Px - Cx) + (Ax - Cx)(Py - Cy) } / {(By - Cy)(Ax - Cx) + (Cx - Bx)(Ay - Cy)}
	//γ＝１−αーβ
	//float denominator = (b.position.y - c.position.y) * (a.position.x - c.position.x) 
	//				+ (c.position.x - b.position.x) * (a.position.y - c.position.y);

	//if (denominator == 0.0f) return false;

	//float alpha = ((b.position.y - c.position.y) * (p.x - c.position.x) + (c.position.x - b.position.x) * (p.y - c.position.y))
	//	/ denominator;

	//float beta = ((c.position.y - a.position.y) * (p.x - c.position.x) + (a.position.x - c.position.x) * (p.y - c.position.y))
	//	/ denominator;

	//float gamma = 1.0f - alpha - beta;

	//outUV = a.uv * alpha + b.uv * beta + c.uv * gamma;

	// 三角形の辺と接触位置へのベクトル
	SimpleMath::Vector3 v0 = (b.position - a.position) * m_transform->GetWorldScale();
	SimpleMath::Vector3 v1 = (c.position - a.position) * m_transform->GetWorldScale();
	SimpleMath::Vector3 v2 = p - a.position * m_transform->GetWorldScale();

	// 内積
	float d00 = v0.Dot(v0);
	float d01 = v0.Dot(v1);
	float d11 = v1.Dot(v1);
	float d20 = v2.Dot(v0);
	float d21 = v2.Dot(v1);

	float denom = d00 * d11 - d01 * d01;

	// 退化した三角形を除外
	if (std::abs(denom) < 1e-8f)
		return false;

	// 重心座標
	float wB = (d11 * d20 - d01 * d21) / denom;
	float wC = (d00 * d21 - d01 * d20) / denom;
	float wA = 1.0f - wB - wC;

	// 三角形の外側なら失敗
	constexpr float epsilon = 1e-4f;

	if (wA < -epsilon || wB < -epsilon ||
		wC < -epsilon)
		return false;

	// UVを補間
	outUV = a.uv * wA + b.uv * wB + c.uv * wC;

	return true;
}
