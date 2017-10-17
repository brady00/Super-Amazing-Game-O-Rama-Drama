#pragma once
#include "Base/Component.h"
#include <DirectXMath.h>

using namespace DirectX;
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class DebugCamera;
	}
	namespace MEObject
	{
		class __declspec(dllexport) Transform : public Component
		{
			friend class GameObject;
			friend class MERenderer::DebugCamera;
		private:
			XMFLOAT3 m_xmPosition;
			XMFLOAT3 m_xmRotation;
			XMFLOAT3 m_xmScale;
			XMFLOAT4X4 m_xmWorldMatrix;
			Transform* m_pParent;
			vector<Transform*> m_vChildren;
			void UpdateTransform();
			virtual void Update();
			virtual void ShutDown();
		public:
			Transform() {};
			Transform(XMFLOAT4X4 _WorldMatrix);
			Transform(XMFLOAT3 _Position, XMFLOAT3 _Rotation, XMFLOAT3 _Scale);
			~Transform() {};
			Transform* GetParent();
			void SetParent(Transform* _parent);
			Transform* GetChild();
			Transform* GetChild(unsigned int _index);
			vector<Transform*>& GetChildren();
			void AddChild(Transform* _child);
			void RemoveChild(Transform* _child);
			XMFLOAT3& GetPosition();
			XMFLOAT3& GetRotation();
			XMFLOAT3& GetScale();
			XMFLOAT4X4 GetMatrix();
		};
	}
}