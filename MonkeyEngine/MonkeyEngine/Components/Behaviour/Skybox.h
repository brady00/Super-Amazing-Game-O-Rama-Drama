#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include "../Behaviour/Behaviour.h"
#include "../../Renderer/TextureLoaders/DDSTextureLoader.h"
#include "../../Renderer/Managers/ShaderManager.h"
#include "../../Renderer/Managers/ConstantBufferManager.h"
#include "../../Renderer/Containers/Material.h"
//#include "../../Renderer/Managers/InputLayoutManager.h"
#include "../../Renderer/Managers/VertexBufferManager.h"
#include "../../Renderer/Containers/IndexBuffer.h"
using namespace DirectX;
using namespace MonkeyEngine::MEObject;
using namespace MonkeyEngine::MERenderer;

namespace MonkeyEngine
{
	namespace MERenderer
	{
		class Skybox : public Behaviour // *Behavior
		{
		private:
			ID3D11Buffer* m_ObjectConstantBuffer;
			ID3D11Buffer* m_VertexBuffer;
			ID3D11Buffer* m_IndexBuffer;
			ID3D11VertexShader* m_VertexShader;
			ID3D11PixelShader* m_PixelShader;
			ID3D11InputLayout* m_Layout;
			Material m_Material;
			cbPerObject m_cbPerObject;
			UINT m_StartIndexLocation;
			UINT m_BaseVertexLocation;

		public:
			Skybox();
			~Skybox();
			void Initialize(ID3D11Device* _device, wchar_t* _TextureFilePath);
			void Update();
			void Draw(float _cameraPosX, float _cameraPosY, float _cameraPosZ);
		};
	}
}