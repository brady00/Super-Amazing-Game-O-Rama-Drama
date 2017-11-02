#include "Transform.h"
namespace MonkeyEngine
{
	namespace MEObject
	{
		REGISTER_CLASS("Transform", Transform)
		Transform::Transform(XMFLOAT4X4 _WorldMatrix)
		{
			m_xmWorldMatrix = _WorldMatrix;
			XMVECTOR rotQuat;
			XMVECTOR Scale;
			XMVECTOR Pos;
			XMMatrixDecompose(&Scale, &rotQuat, &Pos, XMLoadFloat4x4(&m_xmWorldMatrix));
			XMFLOAT3 temp;
			XMStoreFloat3(&temp, Scale);
			m_xmScale = Float3(temp.x, temp.y, temp.z);
			XMStoreFloat3(&temp, Pos);
			m_xmPosition = Float3(temp.x, temp.y, temp.z);
			XMVECTOR axis;
			float angle;
			XMQuaternionToAxisAngle(&axis, &angle, rotQuat);
			axis = XMVectorScale(axis, angle);
			XMStoreFloat3(&temp, axis);
			m_xmRotation = Float3(temp.x, temp.y, temp.z);
			m_pParent = nullptr;
			dirty = true;
		}

		Transform::Transform(Float3 _Position, Float3 _Rotation, Float3 _Scale)
		{
			m_xmPosition = _Position;
			m_xmRotation = _Rotation;
			m_xmScale = _Scale;
			UpdateTransform();
			m_pParent = nullptr;
		}

		void Transform::UpdateTransform()
		{
			Float3 zerovector = Float3(0, 0, 0);
			XMMATRIX temp = XMMatrixAffineTransformation(XMLoadFloat3(&XMFLOAT3(m_xmScale.x, m_xmScale.y, m_xmScale.z)),
				XMVECTOR(XMLoadFloat3(&XMFLOAT3(zerovector.x, zerovector.y, zerovector.z))),
				XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3(&XMFLOAT3(m_xmRotation.x, m_xmRotation.y, m_xmRotation.z))),
				XMLoadFloat3(&XMFLOAT3(m_xmPosition.x, m_xmPosition.y, m_xmPosition.z)));
			XMStoreFloat4x4(&m_xmWorldMatrix, temp);
			dirty = false;
		}

		void Transform::Update()
		{
			UpdateTransform();
			for (unsigned int i = 0; i < m_vChildren.size(); i++)
				m_vChildren[i]->m_pParent->Update();
		}

		void Transform::ShutDown()
		{
			for (unsigned int i = 0; i < m_vChildren.size(); i++)
			{
				m_vChildren[i]->m_pParent->ShutDown();
				delete m_vChildren[i];
			}
		}

		Transform* Transform::GetParent()
		{
			return m_pParent;
		}

		void Transform::SetParent(Transform* _parent)
		{
			m_pParent = _parent;
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

		void Transform::AddChild(Transform* _child)
		{
			m_vChildren.push_back(_child);
			_child->SetParent(this);
		}

		void Transform::RemoveChild(Transform* _child)
		{
			for (unsigned int i = 0; i < m_vChildren.size(); i++)
			{
				if (m_vChildren[i] == _child)
				{
					m_vChildren.erase(m_vChildren.begin() + i);
					_child->SetParent(nullptr);
					break;
				}
			}

		}

		std::vector<Transform*>& Transform::GetChildren()
		{
			return m_vChildren;
		}

		Float3& Transform::GetPosition()
		{
			dirty = true;
			for (unsigned int i = 0; i < m_vChildren.size(); i++)
				m_vChildren[i]->dirty = true;
			return m_xmPosition;
		}

		Float3& Transform::GetRotation()
		{
			dirty = true;
			for (unsigned int i = 0; i < m_vChildren.size(); i++)
				m_vChildren[i]->dirty = true;
			return m_xmRotation;
		}

		Float3& Transform::GetScale()
		{
			dirty = true;
			for (unsigned int i = 0; i < m_vChildren.size(); i++)
				m_vChildren[i]->dirty = true;
			return m_xmScale;
		}

		XMFLOAT4X4 Transform::GetMatrix()
		{
			if (dirty)
				UpdateTransform();
			return m_xmWorldMatrix;
		}

	}
}
