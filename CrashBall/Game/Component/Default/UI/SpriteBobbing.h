/*****************************************************************//**
 * \file   SpriteBobbing.h
 * \brief  スプライトを浮遊させるコンポーネント
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Physics/RectTransform.h"

/**
 * @brief スプライトを浮遊させるコンポーネント
 */
class  SpriteBobbing : public Component {

	// パラメータの宣言 -------------------------------------------------
private:

	float						 m_amplitude;	// 揺れの大きさ
	float						 m_frequency;	// 揺れの速さ(元の位置に戻るまでの秒数)
	DirectX::SimpleMath::Vector2 m_initPos;		// 初期位置

	// データメンバの宣言 -----------------------------------------------
private:

	float						 m_radian;					// sin波に使う角度
	RectTransform*				 m_rectTransform = nullptr;	// トランスフォームのキャッシュ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	SpriteBobbing() = default;

	// コンストラクタ
	SpriteBobbing(IGameObject* gameObject);

	// コピーコンストラクタ
	SpriteBobbing(
		IGameObject* gameObject,
		const SpriteBobbing& other);

	// デストラクタ
	~SpriteBobbing();

	// 操作
public:

	// 浮遊
	void Bobbing();

	// 取得/設定
public:

	// 内部実装
private:

	// JsonConverter
private:
	friend void to_json(json& j, const SpriteBobbing& spriteBobbing);
	friend void from_json(const json& j, SpriteBobbing& spriteBobbing);

	// 演算子オーバーロード
public:

	void operator=(const SpriteBobbing& other)
	{
		m_amplitude = other.m_amplitude;
		m_frequency = other.m_frequency;
		m_initPos = other.m_initPos;
	}

};
