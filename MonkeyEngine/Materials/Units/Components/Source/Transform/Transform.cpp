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
			XMFLOAT3 zerovector = XMFLOAT3(0, 0, 0);
			XMMATRIX temp = XMMatrixAffineTransformation(XMLoadFloat3(&m_xmScale),
				XMVECTOR(XMLoadFloat3(&(zerovector))),
				XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3(&m_xmRotation)),
				XMLoadFloat3(&m_xmPosition));
			XMStoreFloat4x4(&m_xmWorldMatrix, temp);
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
}
