#pragma once

#include "GameObject.h"
#include "Game/Component/Collider/Mesh.h"
#include "Game/Component/ModelRenderer.h"
#include "Game/Component/Transform.h"

struct HitFloorInfo
{
	Triangle* face;

};

/**
 * @brief 床オブジェクト
 */
class  MeshFloor : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	const float SCALE = 10.0f;

	// データメンバの宣言 -----------------------------------------------
private:

	Transform*		m_transform = nullptr;
	Mesh*			m_collider	= nullptr;
	ModelRenderer*	m_renderer	= nullptr;

	std::vector<Triangle*> m_stageMesh;
	std::vector<Triangle*> m_wallMesh;

	std::unordered_map<Triangle*, XMVECTORF32> m_faceColor;	// 面の色情報

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	MeshFloor();

	// デストラクタ
	~MeshFloor();

	// 操作
public:
	void Initialize();

	void Update();

	void Draw();

	void Rotate(DirectX::SimpleMath::Matrix rotate);


	// 取得/設定
public:

	Mesh* GetMesh() { return m_collider; }

	const std::vector<Triangle*>& GetStageMesh()
	{
		return m_stageMesh;
	}

	const std::vector<Triangle*>& GetWallMesh()
	{
		return m_wallMesh;
	}


	void SetModel(DirectX::Model* pModel) {
		m_renderer->SetModel(pModel);
	}

	// 内部実装
private:

	// 面に色を塗る
	void PaintFace(Triangle* face, const XMVECTORF32& color);

};
