#include "pch.h"
#include "FloorMeshGaugeController.h"

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
FloorMeshGaugeController::FloorMeshGaugeController(IGameObject* gameObject)
	: Component(gameObject)
{
	// コンポーネントのキャッシュ
	m_rectTransfrom = GetGameObject()->GetComponent<RectTransform>();
}

/**
 * \brief デストラクタ
 * 
 */
FloorMeshGaugeController::~FloorMeshGaugeController()
{
}

void FloorMeshGaugeController::Update()
{

}
