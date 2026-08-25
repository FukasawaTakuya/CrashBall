/*****************************************************************//**
 * \file   Stage.cpp
 * \brief  ステージオブジェクト
 *
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/


#include "pch.h"
#include "Stage.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param data jsonデータ
 */
Stage::Stage(json* data)
	: GameObject(data)
{
	//// コンポーネントの追加
	//AddComponent<Transform>((*data)["transform"]);
	//AddComponent<Mesh>((*data)["mesh"]);

	//m_stageController = AddComponent<StageController>((*data)["stageController"]);
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
void Stage::Start(const GameContext& gameContext)
{
	m_stageController->Start(gameContext);
}

/**
 * \brief 更新
 *
 */
void Stage::Update(const GameContext& gameContext)
{
	m_stageController->Update(gameContext);
}

/**
 * \brief 描画
 *
 */
void Stage::Render(const RenderContext& renderContext)
{
	m_stageController->Render(renderContext);
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
 * \brief パラメータの書き込み
 * 
 */
void Stage::SaveParam()
{
	GameObject::SaveParam();

	(*m_data)["transform"] = *GetComponent<Transform>();
	//(*m_data)["mesh"] = *GetComponent<Mesh>();
	(*m_data)["stageController"] = *m_stageController;
}

/**
 * \brief データの再読み込み
 * 
 */
void Stage::ReloadParam()
{
	GameObject::ReloadParam();

	*GetComponent<Transform>() = (*m_data)["transform"];
	//*GetComponent<Mesh>() = (*m_data)["mesh"];
	*GetComponent<StageController>() = (*m_data)["stageController"];
}
