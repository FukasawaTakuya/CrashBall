/*****************************************************************//**
 * \file   SliderController.h
 * \brief  スライダー操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"

/**
 * @brief スライダー操作コンポーネント
 */
class  SliderController : public Component {

	// パラメータの宣言 -------------------------------------------------
private:

	float m_slideSpeed;	// スライド速度

	// データメンバの宣言 -----------------------------------------------
private:

	float m_targetAmount;	// 目標値

	SpriteRenderer* m_spriteRenderer = nullptr;	// コンポーネントのキャッシュ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	SliderController() = default;

	// コンストラクタ
	SliderController(IGameObject* gameObject);

	// コピーコンストラクタ
	SliderController(
		IGameObject* gameObject,
		const SliderController& other);

	// デストラクタ
	~SliderController();

	// 更新 
	void Slide();

	// 操作
public:

	// 取得/設定
public:

	// 目標値の設定
	void SetTargetAmount(float targetAmount)
	{
		m_targetAmount = targetAmount;
	}

	// 現在値の設定
	void SetCurrentAmount(float currentAmount)
	{
		m_spriteRenderer->SetFillAmount(currentAmount);
	}


	// 内部実装
private:

	// JsonConverter
private:

	friend void from_json(const json& j, SliderController& sliderController);
	friend void to_json(json& j, const SliderController& sliderController);

	// 演算子オーバーロード
public:

	void operator=(const SliderController& other)
	{
		m_slideSpeed = other.m_slideSpeed;
	}
};
