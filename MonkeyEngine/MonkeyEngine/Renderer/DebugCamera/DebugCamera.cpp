#include "DebugCamera.h"
#include "../Managers/ConstantBufferManager.h"


namespace MERenderer
{
	DebugCamera::DebugCamera()
	{
	}


	DebugCamera::~DebugCamera()
	{
	}

	void DebugCamera::Initialize(XMFLOAT4X4 _WorldMatrix, float _NearPlane, float _FarPlane, float _FOV, float _WindowHeight, float _WindowWidth)
	{
		//StoreFloat4x4(&m_xmViewMatrix, XMMatrixInverse(nullptr, XMLoadFloat4x4(&_WorldMatrix)));
		m_xmViewMatrix = _WorldMatrix;
		XMStoreFloat4x4(&m_xmProjMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(_FOV), _WindowHeight / _WindowWidth, _NearPlane, _FarPlane));
		GetCursorPos(&m_pPrevMousePos);
	}

	void DebugCamera::Update()
	{
		POINT curPos;
		GetCursorPos(&curPos);
		if (m_pPrevMousePos.x != curPos.x || m_pPrevMousePos.y != curPos.y)
		{
			XMMATRIX temp = XMMatrixRotationRollPitchYaw(XMConvertToRadians((float)(curPos.y - m_pPrevMousePos.y)), 0, 0);
			temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
			XMStoreFloat4x4(&m_xmViewMatrix, temp);
		
			temp = XMMatrixRotationRollPitchYaw(0, XMConvertToRadians((float)(curPos.x - m_pPrevMousePos.x)), 0);
			XMFLOAT4X4 tempView = m_xmViewMatrix;
			tempView._41 = 0;
			tempView._42 = 0;
			tempView._43 = 0;
			temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&tempView));
			XMStoreFloat4x4(&tempView, temp);
			tempView._41 = m_xmViewMatrix._41;
			tempView._42 = m_xmViewMatrix._42;
			tempView._43 = m_xmViewMatrix._43;
			m_xmViewMatrix = tempView;
			
		}
		if (GetAsyncKeyState('W'))
		{
			XMMATRIX temp = XMMatrixTranslation(0, 0,/*delta time*/ 0.05f);
			temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
			XMStoreFloat4x4(&m_xmViewMatrix, temp);
		}
		if (GetAsyncKeyState('A'))
		{
			XMMATRIX temp = XMMatrixTranslation(/*delta time*/ -0.05f, 0, 0);
			temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
			XMStoreFloat4x4(&m_xmViewMatrix, temp);
		}
		if (GetAsyncKeyState('S'))
		{
			XMMATRIX temp = XMMatrixTranslation(0, 0,/*delta time*/ -0.05f);
			temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
			XMStoreFloat4x4(&m_xmViewMatrix, temp);
		}
		if (GetAsyncKeyState('D'))
		{
			XMMATRIX temp = XMMatrixTranslation(/*delta time*/ 0.05f, 0, 0);
			temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
			XMStoreFloat4x4(&m_xmViewMatrix, temp);
		}
		if (GetAsyncKeyState('R'))
		{
			XMMATRIX temp = XMMatrixTranslation(0, /*delta time*/ 0.05f, 0);
			temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
			XMStoreFloat4x4(&m_xmViewMatrix, temp);
		}
		if (GetAsyncKeyState('F'))
		{
			XMMATRIX temp = XMMatrixTranslation(0, /*delta time*/ -0.05f, 0);
			temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
			XMStoreFloat4x4(&m_xmViewMatrix, temp);
		}
		cbPerCamera temp = ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().GetBufferValue();
		XMStoreFloat4x4(&temp.ViewProj, XMMatrixMultiply(XMLoadFloat4x4(&m_xmViewMatrix), XMLoadFloat4x4(&m_xmProjMatrix)));
		XMStoreFloat4x4(&temp.InvViewProj, XMMatrixMultiply(XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_xmViewMatrix)), XMLoadFloat4x4(&m_xmProjMatrix)));
		ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().Update(&temp, sizeof(temp));
		ID3D11Buffer* buf = ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().GetConstantBuffer();
		Renderer::m_d3DeviceContext->VSSetConstantBuffers(temp.REGISTER_SLOT, 1, &buf);
		m_pPrevMousePos = curPos;
	}
}
