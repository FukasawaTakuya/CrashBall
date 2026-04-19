// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include "Scene.h"
//#include <Game/Ball.h>
//#include <Game/Floor.h>
//#include <Game/Camera.h>
//#include <Game/MeshFloor.h>
//
// クラスの前方宣言 ===================================================


// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
class  GameScene : public Scene{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	//std::unique_ptr<Floor> m_floor;
	//std::unique_ptr<MeshFloor> m_meshFloor;

	//std::unique_ptr<Ball> m_ball;					// ボール
	//DirectX::SimpleMath::Quaternion m_quaternion;	// ボールのクオータニオン

	//std::unique_ptr<Camera> m_camera;				// カメラ

	//DirectX::SimpleMath::Vector2 m_mousePrevPos;	// 前フレームのマウスの位置

	//Triangle triangle;
	

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameScene(SceneManager* pSceneManager);

	// デストラクタ
	~GameScene();

	// 操作
public:

	// 初期化
	void Initialize() override;

	// 更新
	void Update(float elapsedTime) override;

	// 描画
	void Draw() override;

	// 終了
	void Finalize() override;

	// リソース作成
	void CreateResources(DirectX::SimpleMath::Matrix projMat) override;

	void SetModel() override;


	// 取得/設定
public:

	// 内部実装
private:

};
