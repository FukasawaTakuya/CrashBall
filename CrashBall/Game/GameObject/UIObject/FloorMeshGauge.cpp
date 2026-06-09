#include "pch.h"
#include "FloorMeshGauge.h"
#include "Game/Component/Default/SpriteRenderer.h"

/**
 * \brief コンストラクタ
 * 
 */
FloorMeshGauge::FloorMeshGauge()
{
	AddComponent<RectTransform>();
	AddComponent<SpriteRenderer>(Anchor::LeftTop);

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
}

void FloorMeshGauge::Render(const RenderContext& renderContext)
{
	m_floorMeshGaugeController->Render(renderContext);
}

void FloorMeshGauge::Finalize()
{
}
