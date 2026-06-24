#include "pch.h"
#include "Triangle.h"

/**
 * \brief コンストラクタ
 * 
 */
Triangle::Triangle()
	: m_plane(std::make_unique<Plane>())
{
}

/**
 * \brief Jsonから読み込んだ時用のコンストラクタ
 * 
 * \param triangle 三角形
 * \param scale スケール
 */
Triangle::Triangle(
	const Triangle& triangle, 
	const DirectX::SimpleMath::Vector3& scale)
	: m_plane(std::make_unique<Plane>())
	, m_point{
		triangle.m_point[0] * scale,
		triangle.m_point[1] * scale,
		triangle.m_point[2] * scale
	}
{
	// 平面情報の設定
	m_plane->SetPlane(m_point[0], m_point[1], m_point[2]);

	m_initPoint[0] = m_point[0];
	m_initPoint[1] = m_point[1];
	m_initPoint[2] = m_point[2];

}

/**
 * \brief 回転
 * 
 * \param rotate 回転
 * \param basePosition 基準座標
 */
void Triangle::Rotate(
	const DirectX::SimpleMath::Quaternion& rotate, 
	const DirectX::SimpleMath::Vector3& basePosition)
{
	for (int i = 0; i < 3; i++)
	{
		// 基準位置の分だけ移動する
		SimpleMath::Matrix trans
			= SimpleMath::Matrix::CreateTranslation(basePosition);

		// 移動を戻す
		SimpleMath::Matrix invert = SimpleMath::Matrix::CreateTranslation(-basePosition);

		SimpleMath::Matrix world 
			= trans * SimpleMath::Matrix::CreateFromQuaternion(rotate) * invert;

		// 初期位置から回転
		m_point[i] = XMVector3Transform(m_initPoint[i], world);
	}

	// 平面の再定義
	m_plane->SetPlane(
		m_point[0],
		m_point[1],
		m_point[2]
	);
}

/**
 * \brief スケーリング
 * 
 * \param scale スケール
 */
void Triangle::Scale(DirectX::SimpleMath::Vector3& scale)
{
	m_point[0] *= scale;
	m_point[1] *= scale;
	m_point[2] *= scale;

	m_plane->SetPlane(m_point[0], m_point[1], m_point[2]);
}

/**
 * \brief 三角形の設定
 * 
 * \param point1 頂点1
 * \param point2 頂点2
 * \param point3 頂点3
 */
void Triangle::SetTriangle(
	DirectX::SimpleMath::Vector3 point1,
	DirectX::SimpleMath::Vector3 point2,
	DirectX::SimpleMath::Vector3 point3)
{
	m_point[0] = point1;
	m_point[1] = point2;
	m_point[2] = point3;

	m_initPoint[0] = point1;
	m_initPoint[1] = point2;
	m_initPoint[2] = point3;

	m_plane->SetPlane(point1, point2, point3);
}