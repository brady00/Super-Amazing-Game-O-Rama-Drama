#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include "../TextureLoaders/DDSTextureLoader.h"
#include "../Managers/ShaderManager.h"
//#include "../Managers/InputLayoutManager.h"
#include "../Managers/ConstantBufferManager.h"
#include "../Containers/Material.h"
#include "../RenderSet/RenderMesh.h"
using namespace DirectX;
using namespace MonkeyEngine::MEObject;
using namespace MonkeyEngine::MERenderer;

namespace MonkeyEngine
{
	namespace MERenderer
	{
		class Skybox
		{
		private:
			ID3D11Buffer* m_ObjectConstantBuffer;
			ID3D11Buffer* m_CameraConstantBuffer;
			ID3D11Buffer* m_VertexBuffer;
			ID3D11Buffer* m_IndexBuffer;
			ID3D11VertexShader* m_VertexShader;
			ID3D11PixelShader* m_PixelShader;
			ID3D11InputLayout* m_Layout;
			Material m_Material;
			XMFLOAT4X4 m_LocalMatrix;
			cbPerObject m_cbPerObject;
			cbPerCamera m_cbPerCamera;

		public:
			Skybox();
			~Skybox();
			void Initialize(ID3D11Device* _device, wchar_t* _TextureFilePath);
			void Update();
			void Draw();
		};
	}
}