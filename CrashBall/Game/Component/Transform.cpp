#include "pch.h"
#include "Transform.h"

Transform::~Transform()
{
}

void Transform::Translate(DirectX::SimpleMath::Vector3 trans)
{
	m_position += trans;
}

void Transform::Rotate(DirectX::SimpleMath::Matrix rotate)
{
	m_rotate *= rotate;
}

