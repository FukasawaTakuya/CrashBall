#pragma once
#include "Game/Component/Default/Component.h"


/**
 * \brief コンポーネントエクスポーター
 */
class  ComponentExorter {

	using CastFunc = void (*)(IComponent*, ordered_json);

	// データメンバの宣言 -----------------------------------------------
private:



	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ComponentExorter();

	// デストラクタ
	~ComponentExorter();

	// 操作
public:

	// コンポーネントのエクスポート
	ordered_json ExportComponent(IComponent* comp, const std::string& compName);

	// 取得/設定
public:

	// 内部実装
private:

};
