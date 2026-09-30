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
#include "Game/Json/Component/JsonComponentDeserializers.h"
#include "Game/Component/Default/Physics/RectTransform.h"

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
	if (m_isActice)
	{
		for (auto& comp : m_components)
		{
			if (comp->GetIsActive())
			{
				comp->Start(gameContext);
			}
		}

		for (auto& childe : m_children)
		{
			childe->Start(gameContext);
		}
	}
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void GameObject::Update(const GameContext& gameContext)
{
	if (m_isActice)
	{
		for (auto& comp : m_components)
		{
			if (comp->GetIsActive())
			{
				comp->Update(gameContext);
			}
		}

		for (auto& childe : m_children)
		{
			childe->Update(gameContext);
		}
	}
}

/**
 * \brief　描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void GameObject::Render(const RenderContext& renderContext)
{
	if (m_isActice)
	{
		for (auto& comp : m_components)
		{
			if (comp->GetIsActive())
			{
				comp->Render(renderContext);
			}
		}

		for (auto& childe : m_children)
		{
			childe->Render(renderContext);
		}
	}
}

/**
 * \brief データの保存
 * 
 */
void GameObject::SaveData()
{
	*m_data = *this;
	for (auto& child : m_children)
	{
		child->SaveData();
	}
}

/**
 * \brief データの再読み込み
 * 
 */
void GameObject::ReloadData()
{
	if (!m_data->empty())
	{
		m_data->get_to(*this);
	}
	Awake();
	for (auto& child : m_children)
	{
		child->ReloadData();
	}
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
 * \brief ビルド時の子オブジェクトの追加
 * 
 */
void GameObject::AddChildrenInBuildTime(std::unique_ptr<GameObject> child)
{
	Transform* transform = child->GetComponent<Transform>();
	if (transform != nullptr)
	{
		transform->SetParentInBuildTime(GetComponent<Transform>());
	}
	RectTransform* rectTransform = child->GetComponent<RectTransform>();
	if (rectTransform != nullptr)
	{
		rectTransform->SetParentInBuildTime(GetComponent<RectTransform>());
	}

	child->SetParent(this);

	m_children.push_back(std::move(child));
}

/**
 * \brief 実行中の子オブジェクトの追加
 *
 */
void GameObject::AddChildrenInRunTime(std::unique_ptr<GameObject> child)
{
	Transform* transform = child->GetComponent<Transform>();
	if (transform != nullptr)
	{
		transform->SetParentInRunTime(GetComponent<Transform>());
	}
	RectTransform* rectTransform = child->GetComponent<RectTransform>();
	if (rectTransform != nullptr)
	{
		rectTransform->SetParentInRunTime(GetComponent<RectTransform>());
	}

	child->SetParent(this);

	m_children.push_back(std::move(child));
}

/**
 * \brief 子オブジェクトの削除
 * 
 * \param name オブジェクト名
 */
std::unique_ptr<GameObject> GameObject::RemoveChild(const std::string& name)
{
	auto it = std::ranges::find_if(m_children, [&](std::unique_ptr<GameObject>& child)
		{
			return child->GetName() == name;
		});

	if (it != m_children.end())
	{
		std::unique_ptr<GameObject> temp = std::move(*it);
		m_children.erase(it);
		return temp;
	}
}

/**
 * \brief 子オブジェクトの検索
 * 
 * \param name オブジェクト名
 * \return 子オブジェクトのポインタ
 */
GameObject* GameObject::FindChild(const std::string& name)
{
	auto it = std::ranges::find_if(m_children, [&](std::unique_ptr<GameObject>& child)
		{
			return child->GetName() == name;
		});
	return it->get();
}
