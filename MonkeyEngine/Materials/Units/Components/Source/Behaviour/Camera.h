#pragma once
#pragma warning(disable: 4561)
#include <d3d11.h>
#pragma warning(disable: 4793)
#include "Float3/Float3.h"
#include "Behaviour.h"
#include "Skybox.h"
using namespace DirectX;
namespace MonkeyEngine
{
	using namespace MEMath;
	namespace MEObject
	{
		
		class __declspec(dllexport) Camera : public Behaviour
		{
		public:
			static std::vector<Camera*> AllCameras();
			static unsigned int AllCamerasCount();
			static const Camera* Current();
		private:
			//RenderTarget activeTexture;
			//RenderingPath actualRenderingPath
			bool AllowHDR;
			bool AllowMSAA;
			bool AreVRStereoViewMatricesWithinSingleCullTolerance;
			float Aspect;
			/*Color*/ XMFLOAT4 BackgroundColor;
			XMFLOAT4X4 CameraToWorldMatrix;
			unsigned int CommandBufferCount;
			int CullingMask;
			XMFLOAT4X4 CullingMatrix;
			float Depth;
			//DepthTextureMode DepthTextureMode
			int Eventmask;
			float FarClipPlane;
			float FieldOfView;
			bool ForceIntoRenderTexutre;
			std::vector<float> LayerCullDistances;
			bool LayerCullSpherical;
			float NearClipPlane;
			XMFLOAT4X4 NonJitteredProjectionMatrix;
			//OpaqueSortMode OpaqueSortMode
			bool Orthographic;
			float OrthographicSize;
			unsigned int PixelHeight;
			/*Rect*/ XMFLOAT4 PixelRect;
			float PixelWidth;
			XMFLOAT4X4 ProjectionMatrix;
			/*Rect*/ XMFLOAT4 Rect;
			//RenderingPath RenderingPath
			Scene* scene;
			//MonoOrStereoscopicEye StereoActiveEye
			float StereoConvergence;
			bool StereoEnabled;
			//StereoTargetMask StereoTargetEye;
			int TargetDisplay;
			//RenderTarget targetTexture;
			Float3 TrasparencySortAxis;
			bool UseJitteredProjectionMatrixForTransparentRendering;
			bool UseOcclusionCulling;
			Float3 Velocity;
			XMFLOAT4X4 WorldToCameraMatrix;
		protected: 
			Skybox* m_Skybox;
		public:
			Camera();
			~Camera() {};
			void AddCommandBuffer(/*CameraEvent, CommandBuffer*/);
			void CalculateFrustumCorners(/*Rect*/XMFLOAT4 viewport, float x/*MonoOrStereoscropicEye*/, Float3* outCorners);
			XMFLOAT4X4 CalculateObliqueMatrix(XMFLOAT4 clipPlane);
			void CopyFrom(Camera* other);
			std::vector</*CommandBuffer*/void> GetCommandBuffers(/*CameraEvent*/);
			XMFLOAT4X4 GetStereoProjectionMatrix(/*StereoscopicEye*/);
			XMFLOAT4X4 GetStereoViewMatrix(/*StereoscopicEye*/);
			void RemoveAllCommandBuffers();
			void RemoveCommandBuffer(/*CameraEvent, CommandBuffer*/);
			void RemoveCommandBuffers(/*CameraEvent*/);
			void Draw(ID3D11DeviceContext* d3DeviceContext);
			void RenderToCubemap(/*CubeMap*/int faceMask = 66);
			void RenderWithShader(/*Shader*/string ReplacementTag);
			void ResetAspect();
			void ResetCullingMatrix();
			void ResetProjectionMatrix();
			void ResetReplacementShader();
			void ResetStereoProjectionMatrices();
			void ResetStereoViewMatrices();
			void ResetTransparencySortSettings();
			void ResetWorldToCameraMatrix();
			/*Ray*/void ScreenPointToRay(Float3 position);
			Float3 ScreenToViewportPoint(Float3 position);
			Float3 ScreenToWorldPoint(Float3 position);
			void SetReplacementShader(/*Shader*/string ReplacementTag);
			void SetStereoProjectionMatrix(/*StereoscopicEye*/ XMFLOAT4X4 matrix);
			void SetStereoViewMatrix(/*StereoscopicEye*/ XMFLOAT4X4 matrix);
			void SetTargetBuffers(/*RenderBuffer colorBuffer, RenderBuffer depthBuffer*/);
			Float3 ViewportPointToRay(Float3 position);
			Float3 ViewportToScreenPoint(Float3 position);
			Float3 ViewportToWorldPoint(Float3 position);
			Float3 WorldToScreenPoint(Float3 position);
			Float3 WorldToViewportPoint(Float3 position);
			/*Callback*/void OnPostRender();
			/*Callback*/void OnPreCull();
			/*Callback*/void OnPreRender();
			/*Callback*/void OnRenderImage();
			/*Callback*/void OnRenderObject();
			/*Callback*/void OnWillRenderObject();
			Skybox* GetSkybox();
			virtual void Initialize();
			virtual void Update();
			void Load(ID3D11Device* d3Device, ID3D11DeviceContext* d3DeviceContext, float _WindowHeight, float _WindowWidth);
		};
	}
}

