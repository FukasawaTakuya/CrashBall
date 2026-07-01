/*****************************************************************//**
 * \file   TitleLogo.cpp
 * \brief  タイトルロゴ
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "TitleLogo.h"

/**
 * \brief コンストラクタ
 * 
 * \param data データ
 */
TitleLogo::TitleLogo(json* data)
	: Object2D(data)
{
	m_spriteBobbing = AddComponent<SpriteBobbing>((*m_data)["spriteBobbing"]);
}

/**
 * \brief デストラクタ
 * 
 */
TitleLogo::~TitleLogo()
{
}

/**
 * \brief 初期化
 * 
 */
void TitleLogo::Initialize()
{
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void TitleLogo::Update(const GameContext& gameContext)
{
	m_spriteBobbing->Bobbing();
}

/**
 * \brief 描画
 * 
 * \param renderContext
 */
void TitleLogo::Render(const RenderContext& renderContext)
{
	Object2D::Render(renderContext);
}

/**
 * \brief 終了処理
 * 
 */
void TitleLogo::Finalize()
{
}

/**
 * \brief パラメータの書き込み
 * 
 */
void TitleLogo::SaveParam()
{
	Object2D::SaveParam();

	(*m_data)["spriteBobbing"] = *m_spriteBobbing;
}

/**
 * \brief 初期化用のパラメータの書き込み
 * 
 */
void TitleLogo::SaveInitParam()
{
	Object2D::SaveInitParam();
}

/**
 * \brief パラメータの再読み込み
 * 
 */
void TitleLogo::ReloadParam()
{
	Object2D::ReloadParam();

	*m_spriteBobbing = (*m_data)["spriteBobbing"];
}
