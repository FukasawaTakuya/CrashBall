#include "pch.h"
#include "Stage.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
Stage::Stage()
	: GameObject(ObjectTag::Stage)
{
	// コンポーネントの追加
	AddComponent<Transform>();
	AddComponent<Mesh>();
	AddComponent<ModelRenderer>();

	m_stageController = AddComponent<StageController>();
}

/**
 * \brief デストラクタ
 *
 */
Stage::~Stage()
{
}

/**
 * \brief 初期化
 *
 */
void Stage::Initialize()
{
	m_stageController->Initialize();
}

/**
 * \brief 更新
 *
 */
void Stage::Update(const GameContext& gameContext)
{
	m_stageController->Update(gameContext);
}

/**
 * \brief 描画
 *
 */
void Stage::Render(const RenderContext& renderContext)
{
	m_stageController->Render(renderContext);
}

/**
 * \brief 終了処理
 *
 * \param RenderContext
 */
void Stage::Finalize()
{
}