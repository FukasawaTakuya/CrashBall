/*****************************************************************//**
 * \file   ISceneManager.h
 * \brief  シーン管理クラスのインターフェース
 * 
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#pragma once

#include "Game/ServiceLocator/Service.h"
#include "Game/Scene/Scene.h"
#include <string>

class GameObject;
enum class ObjectTag;

/**
 * \brief シーン管理クラスのインターフェース
 */
class  ISceneManager : public Service {

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ISceneManager() = default;

	// デストラクタ
	virtual ~ISceneManager() = default;

	// 操作
public:

	// シーンの変更
	virtual void RequestChangeScene(const std::string& sceneName) = 0;

	// ゲームオブジェクトの検索
	virtual GameObject* FindGameObject(const std::string& objectName) const = 0;

	// ゲームオブジェクトのタグでの検索
	virtual GameObject* FindGameObjectWithTag(ObjectTag tag) const = 0;

	// ゲームオブジェクトのタグでの検索
	virtual std::pair<TagMapIt, TagMapIt> FindGameObjectsWithTag(ObjectTag tag) const = 0;

	// 取得/設定
public:

	// 内部実装
private:

};
