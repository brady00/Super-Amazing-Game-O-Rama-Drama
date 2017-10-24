#pragma warning(disable: 4561)
#include "Camera.h"
#include "Transform\Transform.h"

namespace MonkeyEngine
{
	namespace MEObject
	{
		REGISTER_CLASS("Camera", Camera)

		Camera::Camera()
		{
			m_Skybox = (MEObject::Skybox*)ComponentObjectFactory::GetInstance()->Create("Skybox");
		}
		void Camera::Initialize()
		{
			GetGameObject()->m_vComponents[GameObject::eSkybox].push_back(m_Skybox);
			((Component*)m_Skybox)->m_pGameObject = GetGameObject();
		}

		void Camera::Update()
		{
			
		}

		Skybox* Camera::GetSkybox()
		{
			return m_Skybox;
		}

		void Camera::Load(ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext, float _WindowHeight, float _WindowWidth)
		{
			XMStoreFloat4x4(&ProjectionMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0f), _WindowWidth / _WindowHeight, 0.1f, 99999.9f));
		}

		void Camera::Draw(ID3D11DeviceContext* d3DeviceContext)
		{
			cbPerCamera tempBuffer = ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().GetBufferValue();
			XMStoreFloat4x4(&tempBuffer.ViewProj, XMMatrixMultiply(XMLoadFloat4x4(&GetTransform()->GetMatrix()), XMLoadFloat4x4(&ProjectionMatrix)));
			XMStoreFloat4x4(&tempBuffer.InvViewProj, XMMatrixMultiply(XMMatrixInverse(nullptr, XMLoadFloat4x4(&GetTransform()->GetMatrix())), XMLoadFloat4x4(&ProjectionMatrix)));
			ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().Update(&tempBuffer, sizeof(tempBuffer), d3DeviceContext);
			ID3D11Buffer* buf = ConstantBufferManager::GetInstance()->GetPerCameraCBuffer().GetConstantBuffer();
			d3DeviceContext->VSSetConstantBuffers(tempBuffer.REGISTER_SLOT, 1, &buf);
		}
	}
}