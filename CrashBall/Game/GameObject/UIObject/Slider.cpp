/*****************************************************************//**
 * \file   Slider.cpp
 * \brief  スライダー
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "Slider.h"
#include "Game/Engine/Time.h"

/**
 * \brief コンストラクタ
 * 
 */
Slider::Slider()
	: GameObject()
{
	AddComponent<RectTransform>();
	m_spriteRenderer = AddComponent<SpriteRenderer>();
	m_sliderController = AddComponent<SliderController>();
}

Slider::Slider(ordered_json* data)
	: GameObject(data)
{
	//AddComponent<RectTransform>((*m_data)["rectTransform"]);
	//m_spriteRenderer = AddComponent<SpriteRenderer>((*m_data)["spriteRenderer"]);
	//m_sliderController = AddComponent<SliderController>((*m_data)["sliderController"]);
}

/**
 * \brief デストラクタ
 *
 */
Slider::~Slider()
{
}

/**
 * \brief 初期化
 * 
 */
void Slider::Start(const GameContext& gameContext)
{
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void Slider::Update(const GameContext& gameContext)
{
	m_sliderController->Slide();
}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void Slider::Render(const RenderContext& renderContext)
{
	m_spriteRenderer->Render(renderContext);
}

/**
 * \brief パラメータの書き込み
 * 
 */
void Slider::SaveParam()
{
	GameObject::SaveParam();

	(*m_data)["rectTransform"]		= *GetComponent<RectTransform>();
	(*m_data)["spriteRenderer"]		= *GetComponent<SpriteRenderer>();
	(*m_data)["sliderController"]	= *GetComponent<SliderController>();
}

/**
 * \brief パラメータの再読み込み
 * 
 */
void Slider::ReloadParam()
{
	GameObject::ReloadParam();

	//*GetComponent<RectTransform>()		= (*m_data)["rectTransform"];
	//*GetComponent<SpriteRenderer>()		= (*m_data)["spriteRenderer"];
	//*GetComponent<SliderController>()	= (*m_data)["sliderController"];
}
