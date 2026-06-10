#include "pch.h"
#include "FloorMeshGauge.h"
#include "Game/Component/Default/SpriteRenderer.h"
#include "Game/Component/Default/TextRenderer.h"

/**
 * \brief コンストラクタ
 * 
 */
FloorMeshGauge::FloorMeshGauge()
{
	AddComponent<RectTransform>();
	AddComponent<SpriteRenderer>();
	AddComponent<TextRenderer>();

	m_floorMeshGaugeController = AddComponent<FloorMeshGaugeController>();
}

/**
 * \brief デストラクタ
 * 
 */
FloorMeshGauge::~FloorMeshGauge()
{
}

void FloorMeshGauge::Initialize()
{
}

void FloorMeshGauge::Update(const GameContext& gameContext)
{
	m_floorMeshGaugeController->Update(gameContext);
}

void FloorMeshGauge::Render(const RenderContext& renderContext)
{
	m_floorMeshGaugeController->Render(renderContext);
}

void FloorMeshGauge::Finalize()
{
}
