/*****************************************************************//**
 * \file   Skybox.cpp
 * \brief  スカイボックス
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#include "pch.h"
#include "Skybox.h"

RegisterComponent(Skybox)

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 * \return 
 */
Skybox::Skybox(IGameObject* gameObejct)
	: Component(gameObejct)
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void Skybox::Awake()
{
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void Skybox::Start(const GameContext& gameContext)
{
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void Skybox::Update(const GameContext& gameContext)
{
}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void Skybox::Render(const RenderContext& renderContext)
{
    renderContext.skyboxRenderManager->RegisterRenderCommand();
}

/**
 * \brief デバイス依存のリソースの設定
 * 
 * \param resourceContext リソース用のコンテキスト
 */
void Skybox::SetDeviceResource(const ResourceContext& resourceContext)
{
    auto skyboxManager = resourceContext.skyboxManager;

    auto spriteInfo = resourceContext.spriteManager->GetSpriteInfo(m_skyboxKey);
    if (spriteInfo != nullptr)
    {
        skyboxManager->SetCubeMap(spriteInfo->sprite.Get());
    }
}

/**
 * \brief 編集時に実行する関数
 * 
 * \param resourceContext リソース用のコンテキスト
 */
void Skybox::EditedFunc(const ResourceContext& resourceContext)
{
    SetDeviceResource(resourceContext);
}
