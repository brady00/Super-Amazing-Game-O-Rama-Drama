#pragma once
#include "Base/Component.h"
#pragma warning(disable: 4793)
#include "Float3/Float3.h"
#include <DirectXMath.h>

using namespace DirectX;
namespace MonkeyEngine
{
	using namespace MEMath;
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
			Float3 m_xmPosition;
			Float3 m_xmRotation;
			Float3 m_xmScale;
			XMFLOAT4X4 m_xmWorldMatrix;
			Transform* m_pParent;
			vector<Transform*> m_vChildren;
			void UpdateTransform();
			virtual void Update();
			virtual void ShutDown();
			bool dirty;
		public:
			Transform() {};
			Transform(XMFLOAT4X4 _WorldMatrix);
			Transform(Float3 _Position, Float3 _Rotation, Float3 _Scale);
			~Transform() {};
			Transform* GetParent();
			void SetParent(Transform* _parent);
			Transform* GetChild();
			Transform* GetChild(unsigned int _index);
			vector<Transform*>& GetChildren();
			void AddChild(Transform* _child);
			void RemoveChild(Transform* _child);
			Float3& GetPosition();
			Float3& GetRotation();
			Float3& GetScale();
			XMFLOAT4X4 GetMatrix();
		};
	}
}