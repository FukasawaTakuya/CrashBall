#include "pch.h"
#include "CommonResources.h"

void CommonResources::Initialize(
	ID3D11Device1*			device, 
	ID3D11DeviceContext1*	context, 
	DirectX::CommonStates*	state)
{
	m_device = device;
	m_context = context;
	m_state = state;
}
