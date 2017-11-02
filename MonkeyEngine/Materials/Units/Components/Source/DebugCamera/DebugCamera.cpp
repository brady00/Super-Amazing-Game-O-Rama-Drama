#pragma warning(disable: 4561)
#include "DebugCamera.h"
#include "Managers/ConstantBufferManager.h"
#include "Time.h"
#include "Transform\Transform.h"
#include "Factory\ComponentObjectFactory.h"
namespace MonkeyEngine
{
	namespace MERenderer
	{

		DebugCamera::DebugCamera()
		{
			m_RunOnce = true;
			m_Resize = false;
			m_RightMousePressed = false;
			ThrowAwayObject = new GameObject();
			ThrowAwayTransform = (MEObject::Transform*)ComponentObjectFactory::GetInstance()->Create("Transform");
			m_Skybox = (MEObject::Skybox*)ComponentObjectFactory::GetInstance()->Create("Skybox");
			ThrowAwayObject->AddComponent((Component*)ThrowAwayTransform, GameObject::eTransform);
			ThrowAwayObject->AddComponent((Component*)m_Skybox, GameObject::eSkybox);
			m_Mousesensitivity = m_MovementSpeed = 1.0f;
			ThrowAwayTransform->GetPosition() = Float3(0, 0, 0);
			ThrowAwayTransform->GetRotation() = Float3(0, 0, 0);
			ThrowAwayTransform->GetScale() = Float3(1, 1, 1);
			ThrowAwayTransform->UpdateTransform();
		}


		DebugCamera::~DebugCamera()
		{
		}

		DebugCamera* DebugCamera::GetInstance()
		{
			static DebugCamera m_pDebugCamera;
			return &m_pDebugCamera;
		}

		void DebugCamera::Initialize(ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext, float _WindowHeight, float _WindowWidth)
		{
			m_xmViewMatrix = XMFLOAT4X4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
			XMStoreFloat4x4(&m_xmProjMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0f), _WindowWidth / _WindowHeight, 0.1f, 99999.9f));
			GetCursorPos(&m_pPrevMousePos);
			cbPerCamera tempBuffer = ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().GetBufferValue();
			XMStoreFloat4x4(&tempBuffer.ViewProj, XMMatrixMultiply(XMLoadFloat4x4(&m_xmViewMatrix), XMLoadFloat4x4(&m_xmProjMatrix)));
			XMStoreFloat4x4(&tempBuffer.InvViewProj, XMMatrixMultiply(XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_xmViewMatrix)), XMLoadFloat4x4(&m_xmProjMatrix)));
			ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().Update(&tempBuffer, sizeof(tempBuffer), d3DeviceContext);
			ID3D11Buffer* buf = ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().GetConstantBuffer();
			d3DeviceContext->VSSetConstantBuffers(tempBuffer.REGISTER_SLOT, 1, &buf);
		}

		void DebugCamera::Resize(float _WindowHeight, float _WindowWidth)
		{
			m_Resize = true;
			XMStoreFloat4x4(&m_xmProjMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(90), (_WindowWidth / _WindowHeight), 0.1f, 99999.9f));
		}

		void DebugCamera::Update(ID3D11DeviceContext* d3DeviceContext)
		{
			if (m_RightMousePressed || m_RunOnce || m_Resize)
			{
				POINT curPos;
				GetCursorPos(&curPos);

				if (!m_RunOnce && !m_Resize)
				{
					if (m_pPrevMousePos.x != curPos.x || m_pPrevMousePos.y != curPos.y)
					{
						XMMATRIX temp = XMMatrixRotationRollPitchYaw(XMConvertToRadians(((float)(curPos.y - m_pPrevMousePos.y)) * Time::GetDeltaTime() * m_Mousesensitivity), 0, 0);
						temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
						XMStoreFloat4x4(&m_xmViewMatrix, temp);

						temp = XMMatrixRotationRollPitchYaw(0, XMConvertToRadians(((float)(curPos.x - m_pPrevMousePos.x))) * Time::GetDeltaTime() * m_Mousesensitivity, 0);
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
						XMMATRIX temp = XMMatrixTranslation(0, 0, Time::GetDeltaTime() * m_MovementSpeed);
						temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
						XMStoreFloat4x4(&m_xmViewMatrix, temp);
					}
					if (GetAsyncKeyState('A'))
					{
						XMMATRIX temp = XMMatrixTranslation(-Time::GetDeltaTime() * m_MovementSpeed, 0, 0);
						temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
						XMStoreFloat4x4(&m_xmViewMatrix, temp);
					}
					if (GetAsyncKeyState('S'))
					{
						XMMATRIX temp = XMMatrixTranslation(0, 0, -Time::GetDeltaTime() * m_MovementSpeed);
						temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
						XMStoreFloat4x4(&m_xmViewMatrix, temp);
					}
					if (GetAsyncKeyState('D'))
					{
						XMMATRIX temp = XMMatrixTranslation(Time::GetDeltaTime() * m_MovementSpeed, 0, 0);
						temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
						XMStoreFloat4x4(&m_xmViewMatrix, temp);
					}
					if (GetAsyncKeyState('R'))
					{
						XMMATRIX temp = XMMatrixTranslation(0, Time::GetDeltaTime() * m_MovementSpeed, 0);
						temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
						XMStoreFloat4x4(&m_xmViewMatrix, temp);
					}
					if (GetAsyncKeyState('F'))
					{
						XMMATRIX temp = XMMatrixTranslation(0, -Time::GetDeltaTime() * m_MovementSpeed, 0);
						temp = XMMatrixMultiply(temp, XMLoadFloat4x4(&m_xmViewMatrix));
						XMStoreFloat4x4(&m_xmViewMatrix, temp);
					}
				}
			}
			cbPerCamera tempBuffer = ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().GetBufferValue();
			XMStoreFloat4x4(&tempBuffer.ViewProj, XMMatrixMultiply(XMLoadFloat4x4(&m_xmViewMatrix), XMLoadFloat4x4(&m_xmProjMatrix)));
			XMStoreFloat4x4(&tempBuffer.InvViewProj, XMMatrixMultiply(XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_xmViewMatrix)), XMLoadFloat4x4(&m_xmProjMatrix)));
			ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().Update(&tempBuffer, sizeof(tempBuffer), d3DeviceContext);
			ID3D11Buffer* buf = ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().GetConstantBuffer();
			d3DeviceContext->VSSetConstantBuffers(tempBuffer.REGISTER_SLOT, 1, &buf);

			m_Resize = false;
			m_RunOnce = false;
			Float3& temp = ThrowAwayTransform->GetPosition();
			temp.x = m_xmViewMatrix._41;
			temp.y = m_xmViewMatrix._42;
			temp.z = m_xmViewMatrix._43;
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

		void DebugCamera::SetMovementSpeed(float speed)
		{
			m_MovementSpeed = speed;
		}

		void DebugCamera::SetMouseSensitivity(float sensitivity)
		{
			m_Mousesensitivity = sensitivity;
		}

		float DebugCamera::GetMovementSpeed()
		{
			return m_MovementSpeed;
		}

		float DebugCamera::GetMouseSensitivity()
		{
			return m_Mousesensitivity;
		}

	}
}