/*****************************************************************//**
 * \file   GameObject.cpp
 * \brief  基底オブジェクト 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/
#include "pch.h"
#include "GameObject.h"

/**
 * \brief コンストラクタ
 * 
 * \param tag タグ
 */
GameObject::GameObject(ObjectTag tag)
	: m_tag(tag)
{
}

/**
 * \brief コンストラクタ
 * 
 * \param data Jsonデータ
 */
GameObject::GameObject(json* data)
	: m_data(data)
	, m_tag((*data)["ObjectTag"])
	, m_name((*data)["name"])
{
}

/**
 * \brief パラメータの書き込み
 * 
 */
void GameObject::SaveParam()
{
	(*m_data)["ObjectTag"] = m_tag;
	(*m_data)["name"] = m_name;
}

/**
 * \brief パラメータの再読み込み
 * 
 */
void GameObject::ReloadParam()
{
	m_tag = (*m_data)["ObjectTag"];
	m_name = (*m_data)["name"];
}

/**
 * \brief 子オブジェクトの追加
 * 
 */
void GameObject::AddChildren(GameObject* child)
{
	m_children.push_back(child);
}

/**
 * \brief 子オブジェクトの初期化
 * 
 */
void GameObject::InitializeChildren()
{
	for (auto& childe : m_children)
	{
		childe->Initialize();
	}

}

/**
 * \brief 子オブジェクトの更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void GameObject::UpdateChildren(const GameContext& gameContext)
{
	for (auto& childe : m_children)
	{
		childe->Update(gameContext);
	}
}

/**
 * \brief 子オブジェクトの描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void GameObject::RenderChildren(const RenderContext& renderContext)
{
	for (auto& childe : m_children)
	{
		childe->Render(renderContext);
	}
}

/**
 * \brief 子オブジェクトの終了処理
 * 
 */
void GameObject::FinalizeChildren()
{
	for (auto& childe : m_children)
	{
		childe->Finalize();
	}

}
