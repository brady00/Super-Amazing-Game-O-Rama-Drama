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
			//static Instance for Singleton
			static DebugCamera* m_pDebugCamera;

			XMFLOAT4X4 m_xmViewMatrix;
			XMFLOAT4X4 m_xmProjMatrix;
			POINT m_pPrevMousePos;
		public:
			DebugCamera();
			~DebugCamera();
			static DebugCamera* GetInstance() { if (!m_pDebugCamera) m_pDebugCamera = new DebugCamera;  return m_pDebugCamera; }
			static void DestroyInstance() { if (m_pDebugCamera) delete m_pDebugCamera; m_pDebugCamera = m_pDebugCamera; }
			void Initialize(XMFLOAT4X4 _WorldMatrix, float _NearPlane, float _FarPlane, float _FOV, float _WindowHeight, float _WindowWidth);
			void Resize(float _NearPlane, float _FarPlane, float _FOV, float _WindowHeight, float _WindowWidth);
			void Update();
			XMFLOAT4X4 GetViewMatrix();
		};
	}
}

