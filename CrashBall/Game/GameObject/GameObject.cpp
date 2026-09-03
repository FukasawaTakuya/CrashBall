/*****************************************************************//**
 * \file   GameObject.cpp
 * \brief  基底オブジェクト 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/
#include "pch.h"
#include "GameObject.h"

#include "Game/Json/Component/JsonComponentSerializers.h"

int GameObject::gameObejctID = 0;

/**
 * \brief コンストラクタ
 * 
 * \param tag タグ
 */
GameObject::GameObject(ObjectTag tag)
	: m_tag(tag)
{
}

GameObject::GameObject(ordered_json* data)
	: m_data(data)
{
}

/**
 * \brief 開始処理
 * 
 */
void GameObject::Awake()
{
	for (auto& comp : m_components)
	{
		comp->Awake();
	}
	for (auto& childe : m_children)
	{
		childe->Awake();
	}
}

/**
 * \brief 初期処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void GameObject::Start(const GameContext& gameContext)
{
	for (auto& comp : m_components)
	{
		comp->Start(gameContext);
	}

	for (auto& childe : m_children)
	{
		childe->Start(gameContext);
	}
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void GameObject::Update(const GameContext& gameContext)
{
	for (auto& comp : m_components)
	{
		comp->Update(gameContext);
	}

	for (auto& childe : m_children)
	{
		childe->Update(gameContext);
	}
}

/**
 * \brief　描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void GameObject::Render(const RenderContext& renderContext)
{
	for (auto& comp : m_components)
	{
		comp->Render(renderContext);
	}

	for (auto& childe : m_children)
	{
		childe->Render(renderContext);
	}
}

/**
 * \brief データの保存
 * 
 */
void GameObject::SaveData()
{
	*m_data = *this;
}

/**
 * \brief リソースの設定
 * 
 * \param resourceContext
 */
void GameObject::SetResource(const ResourceContext& resourceContext)
{
	for (auto& comp : m_components)
	{
		comp->SetResource(resourceContext);
	}

	for (auto& childe : m_children)
	{
		childe->SetResource(resourceContext);
	}
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

	Transform* transform = child->GetComponent<Transform>();
	if (transform != nullptr)
	{
		transform->SetParentInBuildTime(this->GetComponent<Transform>());
	}
}