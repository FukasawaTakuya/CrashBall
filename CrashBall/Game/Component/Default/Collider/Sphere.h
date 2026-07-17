/*****************************************************************//**
 * \file   Sphere.h
 * \brief  球コライダー
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Collider/Collider.h"

 /**
 * \brief 球コライダー
 */
class Sphere
	: public Collider
{

	// インスペクター編集GUIをフレンド化
	friend class ObjectInspectorGui;

	// データメンバの宣言 -----------------------------------------------
private:

	float m_radius;	// 半径


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	Sphere() = default;

	// コンストラクタ
	Sphere(IGameObject* gameObject, float radius);

	// コピーコンストラクタ
	Sphere(IGameObject* gameObject, const Sphere& other);

	// デストラクタ
	~Sphere();

	// 操作
public:

	// コライダーの描画
	void DrawCollider() override {};

	// 取得/設定
public:

	// 半径の取得
	float GetRadius() const { return m_radius * m_transform->GetMaxScale(); }

	// 半径の設定
	void SetRadius(float radius) { m_radius = radius; }

	// JsonConverter
private:
	friend void from_json(const nlohmann::json& j, Sphere& sphere);
	friend void to_json(nlohmann::json& j, const Sphere& sphere);

public:
	
	// 演算子オーバーロード
	void operator=(Sphere s)
	{
		m_layerMaskType = s.m_layerMaskType;
		m_radius = s.m_radius;
	}

};

