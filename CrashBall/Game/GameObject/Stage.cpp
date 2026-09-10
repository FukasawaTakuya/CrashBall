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
Stage::Stage(ordered_json* data)
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
