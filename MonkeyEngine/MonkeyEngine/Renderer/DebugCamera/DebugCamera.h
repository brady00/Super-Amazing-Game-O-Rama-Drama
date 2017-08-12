#pragma once
#include <DirectXMath.h>
#include <Windows.h>
using namespace DirectX;
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class DebugCamera
		{
		private:
			XMFLOAT4X4 m_xmViewMatrix;
			XMFLOAT4X4 m_xmProjMatrix;
			POINT m_pPrevMousePos;
		public:
			DebugCamera();
			~DebugCamera();
			void Initialize(XMFLOAT4X4 _WorldMatrix, float _NearPlane, float _FarPlane, float _FOV, float _WindowHeight, float _WindowWidth);
			void Resize(float _NearPlane, float _FarPlane, float _FOV, float _WindowHeight, float _WindowWidth);
			void Update();
			XMFLOAT4X4 GetViewMatrix();
		};
	}
}

