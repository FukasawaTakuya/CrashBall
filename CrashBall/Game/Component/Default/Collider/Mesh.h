/*****************************************************************//**
 * \file   Mesh.h
 * \brief  メッシュコライダー
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/


#pragma once

#include "Game/Component/Default/Collider/Collider.h"
#include "Game/Geometory/Triangle.h"
#include "Game/Geometory/Segment.h"

/**
 * \brief メッシュコライダー
 */
class Mesh : public Collider
{
	// メンバ変数の宣言 -----------------------------------------------
private:

	std::vector<std::unique_ptr<Triangle>> m_faces;	// 面のコンテナ

	std::vector<Triangle*> m_collideFace;	// 衝突した面

	std::string m_meshData;	// データのファイルパス

	// プロパティの設定
	BeginProperty()
		AddProperty(m_meshData, PropertyType::String)
		AddProperty(m_layerMaskType, PropertyType::Enum)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("Mesh")


	// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Mesh(IGameObject* gameObject);

	// デストラクタ
	~Mesh();

	// 操作
public:

	// アタッチ時の処理
	void Awake() override;

	// コライダーの描画
	void DrawCollider() override {}

	// データの読み込み
	void LoadJson(const std::string& fileName);

	// 回転
	void Rotate();

	// 衝突した面のクリア
	void ClearCollideFace() { m_collideFace.clear(); }

	// 取得/設定
public:

	// 面の取得
	const std::vector<std::unique_ptr<Triangle>>& GetFace() const
	{ 
		return m_faces;
	}

	// 衝突した面の取得
	const std::vector<Triangle*>& GetCollideFace() const
	{ 
		return m_collideFace;
	}

	// 衝突した面の設定
	void SetCollideFace(Triangle* face) { m_collideFace.emplace_back(face); }

	// 内部実装
private:

	// プロパティの取得
	virtual const std::vector<PropertyInfo>& GetProperties() const override
	{
		return m_properties;
	}

	// コンポーネント名の取得
	virtual std::string GetCompName() const override
	{
		return m_compName;
	}
};
