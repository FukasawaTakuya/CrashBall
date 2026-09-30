/*****************************************************************//**
 * \file   ResultPanel.cpp
 * \brief  リザルトパネル
 *
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#include "pch.h"
#include "ResultPanel.h"

#include "Game/Engine/Time.h"

RegisterComponent(ResultPanel)

/**
 * \brief コンストラクタ
 * 
 * \param gameObject
 */
ResultPanel::ResultPanel(IGameObject* gameObject)
	: Component(gameObject)
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void ResultPanel::Awake()
{
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void ResultPanel::Start(const GameContext& gameContext)
{
}

/**
 * \brief 更新
 * 
 * \param gameContext
 */
void ResultPanel::Update(const GameContext& gameContext)
{
}
