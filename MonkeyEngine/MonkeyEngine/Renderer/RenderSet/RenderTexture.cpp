#include "RenderTexture.h"
#include "RenderShape.h"
#include "../../../DirectXTK/Inc/WICTextureLoader.h"
#include "../../../DirectXTK/Inc/DDSTextureLoader.h"
#include "../Renderer.h"

namespace MERenderer
{
	RenderTexture::RenderTexture() : m_d3DiffuseTexture(nullptr), m_pRenderShapes(nullptr)
	{

	}


	RenderTexture::~RenderTexture()
	{
		delete m_pRenderShapes;
		ReleaseCOM(m_d3DiffuseTexture);
	}

	void RenderTexture::Draw()
	{
		Renderer::m_d3DeviceContext->PSSetShaderResources(0, 1, &m_d3DiffuseTexture);
		m_pRenderShapes->Draw();
	}

	bool RenderTexture::Load(std::string _TextureFileName)
	{
		std::string extention(&_TextureFileName[_TextureFileName.length() - 4]);
		if (extention == ".dds" || extention == ".DDS")
		{
			std::wstring temp(_TextureFileName.begin(), _TextureFileName.end());
			DirectX::CreateDDSTextureFromFile(Renderer::m_d3Device, temp.c_str(), nullptr, &m_d3DiffuseTexture);
		}
		else
		{
			std::wstring temp(_TextureFileName.begin(), _TextureFileName.end());
			DirectX::CreateWICTextureFromFile(Renderer::m_d3Device, temp.c_str(), nullptr, &m_d3DiffuseTexture);
		}
		return true;
	}

	const std::string& RenderTexture::GetTextureFileName()
	{
		return m_TextureFileName;
	}

	bool RenderTexture::AddShape(MEObject::RenderComponent* _RenderComp, MEObject::AnimationComponent* _AnimationComp)
	{
		if (!ShapeExsits(_RenderComp, _AnimationComp))
		{
			RenderShape* _Shape;
			if (!LoadShape(_RenderComp, _AnimationComp, _Shape))
			{
				delete _Shape;
				return false;
			}
			m_pRenderShapes->AddNode(_Shape);
		}
		else
		{
			RenderShape* temp = (RenderShape*)m_pRenderShapes->getHead();
			while (temp)
			{
				if (temp->GetRenderComp() == _RenderComp || temp->GetAnimationComp() == _AnimationComp)
					if (!LoadShape(_RenderComp, _AnimationComp, temp))
						return false;
				temp = (RenderShape*)temp->GetNext();
			}
		}
		return true;
	}

	bool RenderTexture::ShapeExsits(MEObject::RenderComponent* _RenderComp, MEObject::AnimationComponent* _AnimationComp)
	{
		if (m_pRenderShapes == nullptr)
		{
			m_pRenderShapes = new RenderSet;
			return nullptr;
		}
		RenderShape* temp = (RenderShape*)m_pRenderShapes->getHead();
		while (temp)
		{
			if (temp->GetRenderComp() == _RenderComp || temp->GetAnimationComp() == _AnimationComp)
				return true;
			temp = (RenderShape*)temp->GetNext();
		}
		return false;
	}

	bool RenderTexture::LoadShape(MEObject::RenderComponent* _RenderComp, MEObject::AnimationComponent* _AnimationComp, RenderShape*& _Shape)
	{
		_Shape = new RenderShape;
		return _Shape->Load(_RenderComp, _AnimationComp);
	}

	ID3D11ShaderResourceView* RenderTexture::GetDiffuseTexture()
	{
		return m_d3DiffuseTexture;
	}

	void RenderTexture::SetDiffuseTexture(ID3D11ShaderResourceView* _Diffuse)
	{
		m_d3DiffuseTexture = _Diffuse;
	}
}