#pragma once
#pragma warning(disable: 4793)
#pragma warning(disable: 4561)
#include <DirectXMath.h>
#include <Windows.h>
#include "../Behaviour/Behaviour.h"
#include "TextureLoaders/DDSTextureLoader.h"
#include "TextureLoaders\WICTextureLoader.h"
#include "Managers/ShaderManager.h"
#include "Managers/ConstantBufferManager.h"
#include "RenderStructures.h"
#include "Managers/VertexBufferManager.h"
#include "Containers/IndexBuffer.h"
using namespace DirectX;
using namespace MonkeyEngine::MEObject;
using namespace MonkeyEngine::MERenderer;

namespace MonkeyEngine
{
	namespace MEObject
	{
		class __declspec(dllexport) Skybox : public Behaviour
		{
		private:
			ID3D11Buffer* m_ObjectConstantBuffer;
			ID3D11Buffer* m_VertexBuffer;
			ID3D11Buffer* m_IndexBuffer;
			ID3D11VertexShader* m_VertexShaderTexture;
			ID3D11VertexShader* m_VertexShaderColor;
			ID3D11PixelShader* m_PixelShaderTexture;
			ID3D11PixelShader* m_PixelShaderColor;
			ID3D11InputLayout* m_Layout;
			Material m_Material;
			cbPerObject m_cbPerObject;
			UINT m_StartIndexLocation;
			UINT m_BaseVertexLocationTexture;
			UINT m_BaseVertexLocationColor;

		public:
			Skybox();
			~Skybox();
			void Initialize(ID3D11Device* _device, ID3D11DeviceContext* d3DeviceContext, wchar_t* _TextureFilePath);
			void Load(ID3D11Device* _device, ID3D11DeviceContext* d3DeviceContext, wchar_t* _TextureFilePath, Material _Material);
			void Update();
			void Draw(ID3D11DeviceContext* d3DeviceContext);
		};
	}
}