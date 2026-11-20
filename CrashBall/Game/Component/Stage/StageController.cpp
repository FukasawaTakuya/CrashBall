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

#include "Game/Framework/Time.h"

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
	// コンポーネントのキャッシュの取得
	m_transform					= GetGameObject()->GetComponent<Transform>();
	m_meshCollider				= GetGameObject()->GetComponent<Mesh>();
	m_modelRenderer				= GetGameObject()->GetComponent<ModelRenderer>();
	m_computShaderController	= GetGameObject()->GetComponent<ComputShaderController>();

	// ゲームカラーの取得
	m_gameColor = Scriptable::GetScriptableObject<GameColor>();

	m_colors[0] = m_gameColor->m_playerColor;
	m_colors[1] = m_gameColor->m_enemyColor;
	m_colors[2] = { 0,0,0,0 };
	m_colors[3] = { 0,0,0,0 };
	m_colors[4] = { 0,0,0,0 };
	m_colors[5] = { 0,0,0,0 };
	m_colors[6] = { 0,0,0,0 };
	m_colors[7] = { 0,0,0,0 };

	// モデルの取得
	m_model = GetGameObject()->GetComponent<ModelRenderer>()->GetModel();

	// 計算フラグ
	if (m_isCalculate)
	{
		// ======= CalcArea_CS =========== //
		// コンピュートシェーダーの取得
		auto cShader = m_computShaderController->GetShader("CalcArea_CS");
		// UAVの設定
		cShader->CreateRWStructuredUAV("outPutPaintArea", TEAM_NUM);
		// UAVの書き込み先を設定
		cShader->SetCpuData("outPutPaintArea", m_pixelCount);
		// 定数バッファの設定
		cShader->GetConstatntBufferInfo("Colors")->SetVariable("gameColor", m_colors);
		// テクスチャ
		cShader->GetShaderTextrueInfo("PaintTexture")->texture = Paint::GetPaintTexture();

		// ======= CalcPaintHist_CS =========== //
		// コンピュートシェーダーの取得
		cShader = m_computShaderController->GetShader("CalcPaintHist_CS");
		// UAVの設定
		cShader->CreateRWStructuredUAV("Hist", TEAM_NUM * BIN_NUM);
		// UAVの書き込み先
		cShader->SetCpuData("Hist", m_hist);
		// ヒストグラム情報の設定
		m_histCBufferInfo = cShader->GetConstatntBufferInfo("HistInfo");
		m_histCBufferInfo->SetVariable("BinWidth", BIN_WIDTH);
		m_histCBufferInfo->SetVariable("NowFrame", Time::GetFrameCount());
		// テクスチャ設定
		cShader->GetShaderTextrueInfo("PaintTimeTex")->texture = Paint::GetPaintTimeTex();

		// =========== PaintErase_CS =========== //
		cShader = m_computShaderController->GetShader("PaintErase_CS");
		// ヒストグラム情報
		auto cbuffer = cShader->GetConstatntBufferInfo("HistInfo");
		cbuffer->SetVariable("BinWidth", BIN_WIDTH);
		cbuffer->SetVariable("NowFrame", Time::GetFrameCount());
		// 削除ピクセル数
		cShader->GetConstatntBufferInfo("EraseInfo")->SetVariable("EraseNum", CONSUM_NUM);
		// テクスチャ設定
		// 書き換えテクスチャ
		cShader->CreateRWTextureUAV("PaintTexture", Paint::GetPaintRenderTarget());
		cShader->CreateRWTextureUAV("PaintTimeTex", Paint::GetPaintTimeRenderTarget());
		// UAV作成
		cShader->CreateRWStructuredUAV("partialCount", 1);
		cShader->SetCpuData("partialCount", m_partialCount);
	}

	m_modelRenderer->GetPixelShader()->GetShaderTextrueInfo("PaintTexture")->texture = Paint::GetPaintTexture();

	Time::ResetFrameCount();
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void StageController::Start(const GameContext& gameContext)
{
	// 衝突中の処理の登録
	m_meshCollider->SetOnCollisionStayCmd([this](Collider* other)
		{
			ObjectTag tag = other->GetGameObject()->GetTag();
			// 衝突オブジェクトがプレイヤーの時の処理
			if (tag == ObjectTag::Player)
			{
				PaintFace(m_gameColor->m_playerColor, 0);
			}
			// 衝突オブジェクトが敵の時の処理
			else if (tag == ObjectTag::Enemy)
			{
				PaintFace(m_gameColor->m_enemyColor, 1);
			}
		});

	Paint::ClearPaint();
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void StageController::Update(const GameContext& gameContext)
{
	m_playerMeshCount = m_pixelCount[0];
	m_enemyMeshCount = m_pixelCount[1];

	if (m_isCalculate)
	{
		m_histCBufferInfo->SetVariable("NowFrame", Time::GetFrameCount());
		int xx = m_hist[0];
		xx = Time::GetFrameCount();
	}
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
void StageController::ConsumePaint(int id)
{
	int eraseNum = CONSUM_NUM;
	int partial = 0;
	int eraseBin;
	// 消去する便を求める(0を後でidに変える)
	for (int i = (0 + 1) * BIN_NUM - 1; i >= 0; i--)
	{
		eraseNum -= m_hist[i];
		eraseBin = i;
		if (eraseNum <= 0)
		{
			partial = (m_hist[i] + eraseNum);
			break;
		}
	}

	auto cShader = m_computShaderController->GetShader("PaintErase_CS");
	// 定数バッファの設定
	auto cbuffer = cShader->GetConstatntBufferInfo("EraseInfo");
	cbuffer->SetVariable("EraseBin", eraseBin);
	cbuffer->SetVariable("PartialNum", partial);
	cShader->GetConstatntBufferInfo("HistInfo")->SetVariable("NowFrame", Time::GetFrameCount());
	// シェーダー更新トリガーを起こす
	m_computShaderController->EnableUpdateTrigger("PaintErase_CS");
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
void StageController::PaintFace(const DirectX::SimpleMath::Color& color, int id)
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
		Paint::Paint(uv, color, id);
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
