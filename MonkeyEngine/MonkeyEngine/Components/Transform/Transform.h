#pragma once
#include "../../Components/Base/Component.h"
#include <DirectXMath.h>
using namespace DirectX;
namespace MEObject
{
	class Transform : public Component
	{
		friend class GameObject;
	private:
		XMFLOAT3 m_xmPosition;
		XMFLOAT3 m_xmRotation;
		XMFLOAT3 m_xmScale;
		XMFLOAT4X4 m_xmWorldMatrix;
		Transform* m_pParent;
		std::vector<Transform*> m_vChildren;
		void UpdateTransform();
		virtual MEReturnValues::RETURNVALUE Update();
		virtual void ShutDown();
	public:
		Transform() {};
		Transform(XMFLOAT4X4 _WorldMatrix);
		Transform(XMFLOAT3 _Position, XMFLOAT3 _Rotation, XMFLOAT3 _Scale);
		~Transform() {};
		Transform* GetParent();
		Transform* GetChild();
		Transform* GetChild(unsigned int _index);
		std::vector<Transform*>& GetChildren();
		XMFLOAT3& GetPosition();
		XMFLOAT3& GetRotation();
		XMFLOAT3& GetScale();
		XMFLOAT4X4 GetMatrix();
	};
}

