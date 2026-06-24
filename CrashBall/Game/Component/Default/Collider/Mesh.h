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
class Mesh
	: public Collider
{

	// データメンバの宣言 -----------------------------------------------
private:

	std::vector<std::unique_ptr<Triangle>> m_faces;	// 面のコンテナ

	std::vector<Triangle*> m_collideFace;	// 衝突した面

	std::wstring m_meshData;	// データのファイルパス

	// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Mesh(IGameObject* gameObject);

	// コンストラクタ
	Mesh(
		IGameObject* gameObject,
		const Mesh& mesh);

	// デストラクタ
	~Mesh();

	// 操作
public:

	// コライダーの描画
	void DrawCollider() override {}

	// データの読み込み
	void LoadJson(const wchar_t* fileName);

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


	// JsonConvert
private:
	friend void from_json(const json& j, Mesh& mesh);
	friend void to_json(json& j, const Mesh& mesh);

};
