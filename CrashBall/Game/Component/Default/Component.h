/*****************************************************************//**
 * \file   Component.h
 * \brief  コンポーネント 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "IComponent.h"

#include "Game/GameObject/IGameObject.h"

#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"

#include "Game/Common/Utility.h"


/**
 * \brief 基底コンポーネント
 */
template<typename Comp>
class  Component : public IComponent {

	RegsterComponent(Comp)

	// データメンバの宣言 -----------------------------------------------
private:

	IGameObject* m_gameObject = nullptr;	// ゲームオブジェクト

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	Component() = default;

	// コンストラクタ
	Component(IGameObject* gameObject)
		: m_gameObject(gameObject)
	{}

	// デストラクタ
	virtual ~Component() = default;

	// 操作
public:

	// 初期化
	virtual void Initialize() override {} ;

	// 更新
	virtual void Update(const GameContext& gameContext) override {};

	// 描画
	virtual void Render(const RenderContext& renderContext) override {};

	// 取得/設定
public:

	// ゲームオブジェクトの取得
	IGameObject* GetGameObject() const override
	{ 
		return m_gameObject; 
	}

	// 内部実装
private:

	// プロパティの取得
	virtual const std::vector<PropertyInfo>& GetProperties() const = 0;

	// コンポーネント名の取得
	virtual std::string GetCompName() const
	{
		return s_compName;
	};
};
