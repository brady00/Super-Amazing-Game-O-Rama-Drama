#include "DebugCamera.h"
#include "../Managers/ConstantBufferManager.h"
#include "../../Utils/Time.h"
#include "../../Engine Base/Settings/Settings.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{
		DebugCamera* DebugCamera::m_pDebugCamera = new MERenderer::DebugCamera;

		DebugCamera::DebugCamera()
		{
			m_RunOnce = true;
			m_Resize = false;
			m_RightMousePressed = false;
		}


		DebugCamera::~DebugCamera()
		{
		}

		void DebugCamera::Initialize(XMFLOAT4X4 _WorldMatrix, float _NearPlane, float _FarPlane, float _FOV, float _WindowHeight, float _WindowWidth)
		{
			m_xmViewMatrix = _WorldMatrix;
			XMStoreFloat4x4(&m_xmProjMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(_FOV), _WindowWidth / _WindowHeight, _NearPlane, _FarPlane));
			GetCursorPos(&m_pPrevMousePos);
		}

		void DebugCamera::Resize(float _NearPlane, float _FarPlane, float _FOV, float _WindowHeight, float _WindowWidth)
		{
			m_Resize = true;
			XMStoreFloat4x4(&m_xmProjMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(_FOV), (_WindowWidth / _WindowHeight), _NearPlane, _FarPlane));
		}

		void DebugCamera::Update()
		{
			if (m_RightMousePressed || m_RunOnce || m_Resize)
			{
				POINT curPos;
				GetCursorPos(&curPos);

				if (!m_RunOnce && !m_Resize)
				{
					if (m_pPrevMousePos.x != curPos.x || m_pPrevMousePos.y != curPos.y)
					{
						XMMATRIX temp = XMMatrixRotationRollPitchYaw(XMConvertToRadians(((float)(curPos.y - m_pPrevMousePos.y)) * Time::DeltaTime * Settings::GetInstance()->GetMouseSensitivity()), 0, 0);
						temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
						XMStoreFloat4x4(&m_xmViewMatrix, temp);

						temp = XMMatrixRotationRollPitchYaw(0, XMConvertToRadians(((float)(curPos.x - m_pPrevMousePos.x))) * Time::DeltaTime * Settings::GetInstance()->GetMouseSensitivity(), 0);
						XMFLOAT4X4 tempView = m_xmViewMatrix;
						tempView._41 = 0;
						tempView._42 = 0;
						tempView._43 = 0;
						temp = XMMatrixMultiply(XMLoadFloat4x4(&tempView), temp);
						XMStoreFloat4x4(&tempView, temp);
						tempView._41 = m_xmViewMatrix._41;
						tempView._42 = m_xmViewMatrix._42;
						tempView._43 = m_xmViewMatrix._43;
						m_xmViewMatrix = tempView;

						SetCursorPos(m_pPrevMousePos.x, m_pPrevMousePos.y);
					}

					if (GetAsyncKeyState('W'))
					{
						XMMATRIX temp = XMMatrixTranslation(0, 0, Time::DeltaTime * Settings::GetInstance()->GetMovementSpeed());
						temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
						XMStoreFloat4x4(&m_xmViewMatrix, temp);
					}
					if (GetAsyncKeyState('A'))
					{
						XMMATRIX temp = XMMatrixTranslation(-Time::DeltaTime * Settings::GetInstance()->GetMovementSpeed(), 0, 0);
						temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
						XMStoreFloat4x4(&m_xmViewMatrix, temp);
					}
					if (GetAsyncKeyState('S'))
					{
						XMMATRIX temp = XMMatrixTranslation(0, 0, -Time::DeltaTime * Settings::GetInstance()->GetMovementSpeed());
						temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
						XMStoreFloat4x4(&m_xmViewMatrix, temp);
					}
					if (GetAsyncKeyState('D'))
					{
						XMMATRIX temp = XMMatrixTranslation(Time::DeltaTime * Settings::GetInstance()->GetMovementSpeed(), 0, 0);
						temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
						XMStoreFloat4x4(&m_xmViewMatrix, temp);
					}
					if (GetAsyncKeyState('R'))
					{
						XMMATRIX temp = XMMatrixTranslation(0, Time::DeltaTime * Settings::GetInstance()->GetMovementSpeed(), 0);
						temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
						XMStoreFloat4x4(&m_xmViewMatrix, temp);
					}
					if (GetAsyncKeyState('F'))
					{
						XMMATRIX temp = XMMatrixTranslation(0, -Time::DeltaTime * Settings::GetInstance()->GetMovementSpeed(), 0);
						temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
						XMStoreFloat4x4(&m_xmViewMatrix, temp);
					}
				}

				cbPerCamera tempBuffer = ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().GetBufferValue();
				XMStoreFloat4x4(&tempBuffer.ViewProj, XMMatrixMultiply(XMLoadFloat4x4(&m_xmViewMatrix), XMLoadFloat4x4(&m_xmProjMatrix)));
				XMStoreFloat4x4(&tempBuffer.InvViewProj, XMMatrixMultiply(XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_xmViewMatrix)), XMLoadFloat4x4(&m_xmProjMatrix)));
				ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().Update(&tempBuffer, sizeof(tempBuffer));
				ID3D11Buffer* buf = ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().GetConstantBuffer();
				Renderer::m_d3DeviceContext->VSSetConstantBuffers(tempBuffer.REGISTER_SLOT, 1, &buf);

				m_Resize = false;
				m_RunOnce = false;
			}
		}

		void DebugCamera::RightMouseDown(POINT _CursorPos)
		{
			m_RightMousePressed = true;
			m_pPrevMousePos = _CursorPos;
		}

		void DebugCamera::RightMouseUp()
		{
			m_RightMousePressed = false;
		}

		XMFLOAT4X4 DebugCamera::GetViewMatrix()
		{
			return m_xmViewMatrix;
		}
	}
}