#pragma once
#include "../../Components/Base/Component.h"
#include <DirectXMath.h>
using namespace DirectX;
namespace MonkeyEngine
{
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

extern "C"
{
	__declspec(dllexport) void GetTransformPosRotScale(MonkeyEngine::MEObject::Transform* _object, float& posx, float& posy, float& posz, float& rotx, float& roty, float& rotz, float& scalex, float& sclaey, float& scalez);
	__declspec(dllexport) void SetTransformPosRotScale(MonkeyEngine::MEObject::Transform* _object, float posx, float posy, float posz, float rotx, float roty, float rotz, float scalex, float sclaey, float scalez);
	__declspec(dllexport) MonkeyEngine::MEObject::Transform** GetTransformChildren(MonkeyEngine::MEObject::Transform* _object, unsigned int& size);
	__declspec(dllexport) void AddTransformChild(MonkeyEngine::MEObject::Transform* _object, MonkeyEngine::MEObject::Transform* _child);
	__declspec(dllexport) void RemoveTransformChild(MonkeyEngine::MEObject::Transform* _object, MonkeyEngine::MEObject::Transform* _child);
	__declspec(dllexport) MonkeyEngine::MEObject::Transform* GetTransformParent(MonkeyEngine::MEObject::Transform* _object);
	__declspec(dllexport) void SetTransformParent(MonkeyEngine::MEObject::Transform* _object, MonkeyEngine::MEObject::Transform* _parent);
}