#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <Windows.h>
#include "Behaviour\Camera.h"
#include "Behaviour\Skybox.h"
using namespace DirectX;
namespace MonkeyEngine
{
	namespace MERenderer
	{
		class __declspec(dllexport) DebugCamera : public MEObject::Camera
		{
		private:
			float m_MovementSpeed;
			float m_Mousesensitivity;
			XMFLOAT4X4 m_xmViewMatrix;
			XMFLOAT4X4 m_xmProjMatrix;
			POINT m_pPrevMousePos;
			bool m_RunOnce;
			bool m_Resize;
			bool m_RightMousePressed;
			GameObject* ThrowAwayObject;
			Transform* ThrowAwayTransform;
		public:
			DebugCamera();
			~DebugCamera();
			static DebugCamera* GetInstance();
			void Initialize(ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext, float _WindowHeight, float _WindowWidth);
			void Resize(float _WindowHeight, float _WindowWidth);
			void Update(ID3D11DeviceContext* d3DeviceContext);
			void RightMouseDown(POINT _CursorPos);
			void RightMouseUp();
			XMFLOAT4X4 GetViewMatrix();
			void SetMovementSpeed(float speed);
			void SetMouseSensitivity(float sensitivity);
			float GetMovementSpeed();
			float GetMouseSensitivity();
		};
	}
}

