#pragma once
#include <string>
#include <d3d11.h>
#include <DirectXMath.h>
namespace MERenderer
{
	enum VertexFormat {
		eVERTEX_POS = 0,
		eVERTEX_POSCOLOR,
		eVERTEX_POSTEX, 
		eVERTEX_POSNORMTEX,
		eVERTEX_POSNORMTANTEX,
		eVERTEX_POSBONEWEIGHT,
		eVERTEX_POSBONEWEIGHTNORMTEX,
		eVERTEX_POSBONEWEIGHTNORMTANTEX,
		eVERTEX_MAX
	};
	extern std::string VertexFormatString[eVERTEX_MAX];
	struct VERTEX
	{

	};
	struct VERTEX_POS : public VERTEX
	{
		DirectX::XMFLOAT3 position;
	};
	struct VERTEX_POSCOLOR : public VERTEX
	{
		DirectX::XMFLOAT3 position;  
		DirectX::XMFLOAT4 color;	   
	};
	struct VERTEX_POSTEX : public VERTEX
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texcoord; 
	};
	struct VERTEX_POSNORMTEX : public VERTEX
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 normal;  
		DirectX::XMFLOAT2 texcoord;
	};
	struct VERTEX_POSNORMTANTEX : public VERTEX
	{
		DirectX::XMFLOAT3 position; 
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 texcoord; 
		DirectX::XMFLOAT3 tangent;
		float determinant;   
	};
	struct VERTEX_POSBONEWEIGHT : public VERTEX
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMINT4   bone;
		DirectX::XMFLOAT4 weights;
	};
	struct VERTEX_POSBONEWEIGHTNORMTEX : public VERTEX
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMINT4   bone;
		DirectX::XMFLOAT4 weights;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 texcoord;
	};
	struct VERTEX_POSBONEWEIGHTNORMTANTEX : public VERTEX
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 texcoord;
		DirectX::XMINT4   bone;
		DirectX::XMFLOAT4 weights;
		DirectX::XMFLOAT3 tangent;
		float determinant;
	};
	class InputLayoutManager
	{
	private:
		InputLayoutManager();
		InputLayoutManager(const InputLayoutManager &) {}
		InputLayoutManager(const InputLayoutManager &&) {}
		InputLayoutManager &operator=(const InputLayoutManager &) {}
		InputLayoutManager &operator=(const InputLayoutManager &&) {}
		static InputLayoutManager* m_pInstance;
		ID3D11InputLayout* m_pInputLayouts[eVERTEX_MAX];
		void Initialize(ID3D11Device* _Device);
	public:
		~InputLayoutManager();
		static InputLayoutManager* GetInstance(ID3D11Device* _Device = nullptr);
		static void DeleteInstance();
		ID3D11InputLayout* GetInputLayout(VertexFormat index);
	};

}