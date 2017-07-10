#include "Transform.h"

namespace MEObject
{

	Transform::Transform(XMFLOAT4X4 _WorldMatrix)
	{
		m_xmWorldMatrix = _WorldMatrix;
		XMVECTOR rotQuat;
		XMVECTOR Scale;
		XMVECTOR Pos;
		XMMatrixDecompose(&Scale, &rotQuat, &Pos, XMLoadFloat4x4(&m_xmWorldMatrix));
		XMStoreFloat3(&m_xmScale, Scale);
		XMStoreFloat3(&m_xmPosition, Pos);
		XMVECTOR axis;
		float angle;
		XMQuaternionToAxisAngle(&axis, &angle, rotQuat);
		axis = XMVectorScale(axis, angle);
		XMStoreFloat3(&m_xmScale, axis);
		m_pParent = nullptr;
	}

	Transform::Transform(XMFLOAT3 _Position, XMFLOAT3 _Rotation, XMFLOAT3 _Scale)
	{
		m_xmPosition = _Position;
		m_xmRotation = _Rotation;
		m_xmScale = _Scale;
		UpdateTransform();
		m_pParent = nullptr;
	}

	void Transform::UpdateTransform()
	{
		XMMATRIX temp = XMMatrixAffineTransformation(XMLoadFloat3(&m_xmScale),
			XMVECTOR(XMLoadFloat3(&(XMFLOAT3(0, 0, 0)))),
			XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3(&m_xmRotation)),
			XMLoadFloat3(&m_xmPosition));
		XMStoreFloat4x4(&m_xmWorldMatrix, temp);
	}

	MEReturnValues::RETURNVALUE Transform::Update()
	{
		UpdateTransform();
		for (unsigned int i = 0; i < m_vChildren.size(); i++)
			m_vChildren[i]->Update();
		return MEReturnValues::TRANSFORMRETURN; 
	}

	void Transform::ShutDown()
	{
		for (unsigned int i = 0; i < m_vChildren.size(); i++)
		{
			m_vChildren[i]->ShutDown();
			delete m_vChildren[i];
		}
	}

	Transform* Transform::GetParent()
	{
		return m_pParent;
	}

	Transform* Transform::GetChild()
	{
		if (m_vChildren.size() != 0)
			return m_vChildren[0];
		return nullptr;
	}

	Transform* Transform::GetChild(unsigned int _index)
	{
		if (_index < m_vChildren.size())
			return m_vChildren[_index];
		return nullptr;
	}

	std::vector<Transform*>& Transform::GetChildren()
	{
		return m_vChildren;
	}

	XMFLOAT3& Transform::GetPosition()
	{
		return m_xmPosition;
	}

	XMFLOAT3& Transform::GetRotation()
	{
		return m_xmRotation;
	}

	XMFLOAT3& Transform::GetScale()
	{
		return m_xmScale;
	}

	XMFLOAT4X4 Transform::GetMatrix()
	{
		return m_xmWorldMatrix;
	}

}