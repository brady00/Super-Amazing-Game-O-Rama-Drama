#include "FileIO.h"
#include <fstream>
#include <algorithm>
#include "ComponentObjectFactory.h"
#include "../Renderer/RenderSet/RenderSet.h"
#include "../Renderer/RenderSet/RenderContext.h"
#include "../Renderer/RenderSet/RenderMesh.h"
#include "../Renderer/RenderSet/RenderTexture.h"
#include "../Components/Renderer/MeshRenderer.h"

namespace MonkeyEngine
{
	namespace MEFileIO
	{
		FbxManager* FileIO::m_fbxManager = nullptr;
		FbxScene* FileIO::m_fbxScene = nullptr;
		bool FileIO::m_bHasAnimation = true;
		std::vector<CtrlPoint*> FileIO::m_mControlPoints;
		unsigned int FileIO::m_uiTriangleCount = 0;
		std::vector<Triangle> FileIO::m_vTriangles;
		std::vector<MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX> FileIO::m_vVertices;
		Animation FileIO::m_Skeleton;
		std::unordered_map<unsigned int, MEObject::Material*> FileIO::m_mMaterialLookUp;
		FbxLongLong FileIO::m_lAnimationLength = 0;
		std::string FileIO::m_sAnimationName;

		const std::unordered_map<std::string, compFuntion> FileIO::componentFunctions =
		{
			{"Transform", &FileIO::LoadTranform},
			{"MeshRenderer", &FileIO::LoadMeshRenderer},
			{"SkinnedMeshRenderer", &FileIO::LoadMeshRenderer}
		};

		const std::unordered_map<std::string, MEObject::GameObject::COMPONENT_ID> FileIO::componentIDS =
		{
			{ "Transform", MEObject::GameObject::COMPONENT_ID::eTransform },
			{ "MeshRenderer", MEObject::GameObject::COMPONENT_ID::eMeshRenderer },
			{ "SkinnedMeshRenderer", MEObject::GameObject::COMPONENT_ID::eSkinnedMeshRenderer }
		};

		FileIO::FileIO()
		{

		}

		FileIO::~FileIO()
		{

		}

		bool FileIO::LoadFBX(std::string _FileName, MERenderer::VertexFormat _VertexFormat, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies, MEObject::Material*& _Material)
		{
			std::string filepart;
			std::ifstream FileIn;
			filepart.append(_FileName.c_str(), _FileName.length() - 4);
			FileIn.open(filepart + ".Bfbx", std::ios_base::binary);
			if (FileIn.is_open())
			{
				FileIn.read((char*)& _NumVerticies, sizeof(unsigned int));
				_Verticies = new MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX[_NumVerticies];
				for (unsigned int i = 0; i < _NumVerticies; i++)
				{
					FileIn.read((char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].position), sizeof(DirectX::XMFLOAT3));
					FileIn.read((char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].normal), sizeof(DirectX::XMFLOAT3));
					FileIn.read((char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].texcoord), sizeof(DirectX::XMFLOAT2));
					((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].texcoord.x = 1 - ((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].texcoord.x;
					FileIn.read((char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].bone), sizeof(DirectX::XMINT4));
					FileIn.read((char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].determinant), sizeof(float));
					FileIn.read((char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].tangent), sizeof(DirectX::XMFLOAT3));
					FileIn.read((char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].weights), sizeof(DirectX::XMFLOAT4));
					FileIn.read((char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].binormal), sizeof(DirectX::XMFLOAT4));
				}
				char* dif, *emis, *gloss, *normal, *spec;
				unsigned int length;
				_Material = new Material();
				FileIn.read((char*)&length, sizeof(unsigned int));
				if (length > 1)
				{
					dif = new char[length];
					FileIn.read(dif, length);
					_Material->mDiffuseMapName = string(dif);
					delete dif;
				}
				FileIn.read((char*)&length, sizeof(unsigned int));
				if (length > 1)
				{
					emis = new char[length];
					FileIn.read(emis, length);
					_Material->mEmissiveMapName = string(emis);
					delete emis;
				}
				FileIn.read((char*)&length, sizeof(unsigned int));
				if (length > 1)
				{
					gloss = new char[length];
					FileIn.read(gloss, length);
					_Material->mGlossMapName = string(gloss);
					delete gloss;
				}
				FileIn.read((char*)&length, sizeof(unsigned int));
				if (length > 1)
				{
					normal = new char[length];
					FileIn.read(normal, length);
					_Material->mNormalMapName = string(normal);
					delete normal;
				}
				FileIn.read((char*)&length, sizeof(unsigned int));
				if (length > 1)
				{
					spec = new char[length];
					FileIn.read(spec, length);
					_Material->mSpecularMapName = string(spec);
					delete spec;
				}
				/*FileIn.read((char*)& _NumIndicies, sizeof(unsigned int));
				_Indicies = new unsigned int[_NumIndicies];
				for (unsigned int i = 0; i < _NumIndicies; i++)
					FileIn.read((char*)&_Indicies[i], sizeof(unsigned int));*/
				FileIn.close();
				return true;
			}
			FbxManager* fbxManager = FbxManager::Create();
			if (!fbxManager)
				return false;
			FbxIOSettings* fbxIOSettings = FbxIOSettings::Create(fbxManager, IOSROOT);
			fbxManager->SetIOSettings(fbxIOSettings);
			m_fbxScene = FbxScene::Create(fbxManager, "myScene");
			FbxImporter* fbxImporter = FbxImporter::Create(fbxManager, "myImporter");
			if (!fbxImporter)
				return false;
			if (!fbxImporter->Initialize(_FileName.c_str(), -1, fbxManager->GetIOSettings()))
				return false;
			if (!fbxImporter->Import(m_fbxScene))
				return false;
			fbxImporter->Destroy();
			ProcessSkeletonHierarchy(m_fbxScene->GetRootNode());
			if (m_Skeleton.mJoints.empty())
				m_bHasAnimation = false;
			ProcessGeometry(m_fbxScene->GetRootNode());
			//Optimize();
			_NumVerticies = (unsigned int)m_vVertices.size();
			_Verticies = new MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX[_NumVerticies];
			for (unsigned int i = 0; i < m_vVertices.size(); i++)
				((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i] = m_vVertices[i];
			_NumIndicies = (unsigned int)m_vTriangles.size() * 3;
			//_Indicies = new unsigned int[_NumIndicies];
			//for (unsigned int i = 0; i < m_vTriangles.size(); ++i)
			//	for (unsigned int j = 2; j < 3; ++j)
			//		_Indicies[i * 3 + j] = m_vTriangles[i].mIndices[2 - j];
			_Material = new Material();
			_Material->mDiffuseMapName = m_mMaterialLookUp[0]->mDiffuseMapName;
			_Material->mEmissiveMapName = m_mMaterialLookUp[0]->mEmissiveMapName;
			_Material->mGlossMapName = m_mMaterialLookUp[0]->mGlossMapName;
			_Material->mNormalMapName = m_mMaterialLookUp[0]->mNormalMapName;
			_Material->mSpecularMapName = m_mMaterialLookUp[0]->mSpecularMapName;
			std::ofstream out;
			out.open(filepart + std::string(".Bfbx"), std::ios_base::binary);
			if (out.is_open())
			{
				out.write((const char*)& _NumVerticies, sizeof(unsigned int));
				for (unsigned int i = 0; i < _NumVerticies; i++)
				{
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].position), sizeof(DirectX::XMFLOAT3));
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].normal), sizeof(DirectX::XMFLOAT3));
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].texcoord), sizeof(DirectX::XMFLOAT2));
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].bone), sizeof(DirectX::XMINT4));
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].determinant), sizeof(float));
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].tangent), sizeof(DirectX::XMFLOAT3));
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].weights), sizeof(DirectX::XMFLOAT4));
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].binormal), sizeof(DirectX::XMFLOAT4));
				}
				unsigned int length = (unsigned int)_Material->mDiffuseMapName.length() + 1;
				out.write((const char*)&length, sizeof(unsigned int));
				if (length > 1)
				{
					out.write(_Material->mDiffuseMapName.c_str(), length);
				}
				length = (unsigned int)_Material->mEmissiveMapName.length() + 1;
				out.write((const char*)&length, sizeof(unsigned int));
				if (length > 1)
				{
					out.write(_Material->mEmissiveMapName.c_str(), length);
				}
				length = (unsigned int)_Material->mGlossMapName.length() + 1;
				out.write((const char*)&length, sizeof(unsigned int));
				if (length > 1)
				{
					out.write(_Material->mGlossMapName.c_str(), length);
				}
				length = (unsigned int)_Material->mNormalMapName.length() + 1;
				out.write((const char*)&length, sizeof(unsigned int));
				if (length > 1)
				{
					out.write(_Material->mNormalMapName.c_str(), length);
				}
				length = (unsigned int)_Material->mSpecularMapName.length() + 1;
				out.write((const char*)&length, sizeof(unsigned int));
				if (length > 1)
				{
					out.write(_Material->mSpecularMapName.c_str(), length);
				}
				/*out.write((const char*)& _NumIndicies, sizeof(unsigned int));
				for (unsigned int i = 0; i < _NumIndicies; i++)
					out.write((const char*)&_Indicies[i], sizeof(unsigned int));*/
				out.close();
			}
			else
				return false;
			return true;
		}

		bool FileIO::LoadOBJ(std::string _FileName, MERenderer::VertexFormat _VertexFormat, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies)
		{
			std::string filepart;
			std::ifstream FileIn;
			filepart.append(_FileName.c_str(), _FileName.length() - 4);
			FileIn.open(filepart + ".Bobj", std::ios_base::binary);
			if (FileIn.is_open())
			{
				FileIn.read((char*)& _NumVerticies, sizeof(unsigned int));
				_Verticies = new MERenderer::VERTEX_POSNORMTEX[_NumVerticies];
				for (unsigned int i = 0; i < _NumVerticies; i++)
				{
					FileIn.read((char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].position), sizeof(DirectX::XMFLOAT3));
					FileIn.read((char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].normal), sizeof(DirectX::XMFLOAT3));
					FileIn.read((char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].texcoord), sizeof(DirectX::XMFLOAT2));
				}
				return true;
			}
			std::string finalPath(_FileName);
			std::vector<XMFLOAT3> temp_vertices;
			std::vector<XMFLOAT2> temp_uvs;
			std::vector<XMFLOAT3> temp_normals;
			std::vector< unsigned int > vertexIndices;
			std::vector< unsigned int > normalIndices;
			std::vector< unsigned int > uvIndices;
			FILE* file = nullptr;
			fopen_s(&file, finalPath.c_str(), "r");
			if (file == NULL)
				return false;
			while (true)
			{
				char lineheader[128];
				int res = fscanf_s(file, "%s", lineheader, 128);
				if (res == EOF)
					break;

				if (strcmp(lineheader, "v") == 0)
				{
					XMFLOAT3 vertex;
					fscanf_s(file, "%f %f %f \n", &vertex.x, &vertex.y, &vertex.z);
					temp_vertices.push_back(vertex);
				}
				else if (strcmp(lineheader, "vt") == 0)
				{
					XMFLOAT2 vertexuv;
					fscanf_s(file, "%f %f\n", &vertexuv.x, &vertexuv.y);
					vertexuv.x = vertexuv.x;
					vertexuv.y = 1 - vertexuv.y;
					temp_uvs.push_back(vertexuv);
				}
				else if (strcmp(lineheader, "vn") == 0)
				{
					XMFLOAT3 vertexn;
					fscanf_s(file, "%f %f %f \n", &vertexn.x, &vertexn.y, &vertexn.z);
					temp_normals.push_back(vertexn);
				}
				else if (strcmp(lineheader, "f") == 0)
				{
					std::string m_vertex1, m_vertex2, m_vertex3;
					unsigned int m_vertexindex[3], m_UVIndex[3], normalIndex[3];
					int matches = fscanf_s(file, " %i/%i/%i %i/%i/%i %i/%i/%i \n",
						&m_vertexindex[0], &m_UVIndex[0], &normalIndex[0],
						&m_vertexindex[1], &m_UVIndex[1], &normalIndex[1],
						&m_vertexindex[2], &m_UVIndex[2], &normalIndex[2]);
					if (matches != 9)
						return false;

					vertexIndices.push_back(m_vertexindex[0] - 1);
					vertexIndices.push_back(m_vertexindex[1] - 1);
					vertexIndices.push_back(m_vertexindex[2] - 1);
					normalIndices.push_back(normalIndex[0] - 1);
					normalIndices.push_back(normalIndex[1] - 1);
					normalIndices.push_back(normalIndex[2] - 1);
					uvIndices.push_back(m_UVIndex[0] - 1);
					uvIndices.push_back(m_UVIndex[1] - 1);
					uvIndices.push_back(m_UVIndex[2] - 1);
				}
			}
			_Verticies = new MERenderer::VERTEX_POSNORMTEX[vertexIndices.size()];
			for (unsigned int i = 0; i < vertexIndices.size(); i++)
			{
				((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].position = temp_vertices[vertexIndices[i]];
				((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].normal = temp_normals[normalIndices[i]];
				((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].texcoord = temp_uvs[uvIndices[i]];
			}

			_NumVerticies = (unsigned int)vertexIndices.size();
			_NumIndicies = 0;

			std::ofstream out;
			out.open(filepart + std::string(".Bobj"), std::ios_base::binary);
			if (out.is_open())
			{
				out.write((const char*)& _NumVerticies, sizeof(unsigned int));
				for (unsigned int i = 0; i < _NumVerticies; i++)
				{
					out.write((const char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].position), sizeof(DirectX::XMFLOAT3));
					out.write((const char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].normal), sizeof(DirectX::XMFLOAT3));
					out.write((const char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].texcoord), sizeof(DirectX::XMFLOAT2));
				}
				out.close();
			}
			else
				return false;
			return true;
		}

		bool FileIO::LoadScene(std::string _FileName, std::vector<MEObject::GameObject*>& _GameObjects)
		{
			tinyxml2::XMLDocument doc;
			doc.LoadFile(_FileName.c_str());
			XMLElement* root = doc.FirstChildElement();
			if (!root)
				return false;
			XMLElement* child = root->FirstChildElement();
			while (child)
			{
				switch (child->Name()[0])
				{
					//Scene Specific data
				case 'G':
				{
					//Objects
					MEObject::GameObject* Object = new MEObject::GameObject;
					if (!LoadGameObject(child, Object))
						delete Object;
					else
						_GameObjects.push_back(Object);
				}
				default:
					break;
				}
				child = child->NextSiblingElement();
			}
			return true;
		}

		bool FileIO::OutputSettings(std::string _FileName, std::vector<SettingData*> _SettingData)
		{
			ofstream ofile;
			ofile.open(_FileName.c_str());
			if (ofile.is_open())
			{
				for (unsigned int i = 0; i < _SettingData.size(); i++)
				{
					ofile << _SettingData[i]->Name << '=' << _SettingData[i]->Value << '\n';
				}
				return true;
			}
			return false;
		}

		bool FileIO::LoadSettings(std::string _FileName, std::vector<SettingData*> &_SettingData)
		{
			ifstream ifile(_FileName.c_str());
			if (ifile.good())
			{
				// Read in the Settings
				while (true)
				{
					SettingData temp;
					getline(ifile, temp.Name, '=');
					getline(ifile, temp.Value, '\n');
					for (unsigned int i = 0; i < _SettingData.size(); i++)
					{
						if (_SettingData[i]->Name == temp.Name)
							_SettingData[i]->Value = temp.Value;
					}
					if (ifile.eof())
						break;
				}
				return true;
			}
			else
			{
				// Create the config.txt file and output to it
				OutputSettings(_FileName, _SettingData);
				return false;
			}
		}

		bool FileIO::LoadGameObject(XMLElement* _ObjectRoot, MEObject::GameObject* _Object)
		{
			XMLElement* child = _ObjectRoot->FirstChildElement();
			while (child)
			{
				MEObject::Component* comp = ComponentObjectFactory::GetInstance()->Create(child->Name());
				if (componentFunctions.at(std::string(child->Name()))(child, comp))
					_Object->AddComponent(comp, componentIDS.at(std::string(child->Name())));
				else
					return false;
				child = child->NextSiblingElement();
			}
			_Object->SetActive(_ObjectRoot->BoolAttribute("Active"));
			_Object->SetLayer(_ObjectRoot->IntAttribute("Layer"));
			_Object->SetName(_ObjectRoot->Attribute("Name"));
			_Object->SetStatic(_ObjectRoot->BoolAttribute("Static"));
			return true;
		}

		bool FileIO::LoadTranform(XMLElement* _ObjectRoot, MEObject::Component*& _Object)
		{
			XMFLOAT3 pos, rot, scale;
			XMLElement* child = _ObjectRoot->FirstChildElement();
			if (child && !strcmp(child->Name(), "Position"))
			{
				pos.x = child->FloatAttribute("X");
				pos.y = child->FloatAttribute("Y");
				pos.z = child->FloatAttribute("Z");
			}
			else
				return false;
			child = child->NextSiblingElement();
			if (child && !strcmp(child->Name(), "Rotation"))
			{
				rot.x = child->FloatAttribute("X");
				rot.y = child->FloatAttribute("Y");
				rot.z = child->FloatAttribute("Z");
			}
			else
				return false;
			child = child->NextSiblingElement();
			if (child && !strcmp(child->Name(), "Scale"))
			{
				scale.x = child->FloatAttribute("X");
				scale.y = child->FloatAttribute("Y");
				scale.z = child->FloatAttribute("Z");
			}
			else
				return false;
			((MEObject::Transform*)_Object)->GetPosition() = pos;
			((MEObject::Transform*)_Object)->GetRotation() = rot;
			((MEObject::Transform*)_Object)->GetScale() = scale;
			_Object->SetName("Transform");
			return true;
		}

		bool FileIO::LoadMeshRenderer(XMLElement* _ObjectRoot, MEObject::Component*& _Object)
		{
			bool Enabled = _ObjectRoot->BoolAttribute("Enabled");
			bool Skiined = _ObjectRoot->BoolAttribute("Skinned");
			bool Opaque = _ObjectRoot->BoolAttribute("Opaque");
			std::string VertexFileName;
			std::string DiffuseFileName;
			MERenderer::BlendStateManager::BStates BlendState;
			XMLElement* child = _ObjectRoot->FirstChildElement();
			if (child && strcmp(child->Name(), "VertexFileName") == 0)
				VertexFileName = child->Attribute("File");
			child = child->NextSiblingElement();
			if (child && strcmp(child->Name(), "DiffuseFileName") == 0)
				DiffuseFileName = child->Attribute("File");
			if (Opaque)
				BlendState = MERenderer::BlendStateManager::BStates::BS_Default;
			else
				BlendState = MERenderer::BlendStateManager::BStates::BS_Alpha;
			MERenderer::VertexFormat VertFormat;
			std::string tempfilename(&VertexFileName[VertexFileName.length() - 4]);
			if (tempfilename == ".obj" || tempfilename == ".OBJ")
				VertFormat = MERenderer::eVERTEX_POSNORMTEX;
			else if (tempfilename == ".fbx" || tempfilename == ".FBX")
				VertFormat = MERenderer::eVERTEX_POSBONEWEIGHTNORMTANTEX;

			MERenderer::RenderContext* renderContext = new MERenderer::RenderContext;
			renderContext->Load(VertFormat, BlendState, MERenderer::RasterizerStateManager::RS_Default, MERenderer::DepthStencilStateManager::DSS_Default);
			if (Opaque)
				renderContext = MERenderer::Renderer::AddNewnonTransparentContext(renderContext);
			else
				renderContext = MERenderer::Renderer::AddNewnonTransparentContext(renderContext);
			MERenderer::RenderMesh* tempMesh = renderContext->AddMesh(VertexFileName);
			MERenderer::RenderTexture* tempTex = tempMesh->AddTexture(DiffuseFileName);
			MEObject::CompRenderer* comprend = (MEObject::CompRenderer*)_Object;
			tempTex->AddShape((MERenderer::RenderShape*)comprend);

			((MEObject::MeshRenderer*)_Object)->Load(&renderContext->m_BlendState,
				&renderContext->m_RasterState,
				&renderContext->m_DSState,
				tempMesh->m_vVerticies,
				&tempMesh->m_uiNumVerticies,
				tempMesh->m_vIndicies,
				&tempMesh->m_uiNumIndicies,
				&tempMesh->m_uiStartIndexLocation,
				&tempMesh->m_iBaseVertexLocation,
				&tempMesh->m_sVertexFileName,
				&tempMesh->m_eVertexFormat,
				tempTex->m_Material);
			_Object->SetName("MeshRenderer");
			return true;
		}

		bool FileIO::LoadSkinnedMeshRenderer(XMLElement* _ObjectRoot, MEObject::Component*& _Object)
		{
			bool Enabled = _ObjectRoot->BoolAttribute("Enabled");
			bool Skiined = _ObjectRoot->BoolAttribute("Skinned");
			bool Opaque = _ObjectRoot->BoolAttribute("Opaque");
			std::string VertexFileName;
			std::string DiffuseFileName;
			MERenderer::BlendStateManager::BStates BlendState;
			XMLElement* child = _ObjectRoot->FirstChildElement();
			if (child && strcmp(child->Name(), "VertexFileName") == 0)
				VertexFileName = child->Attribute("File");
			child = child->NextSiblingElement();
			if (child && strcmp(child->Name(), "DiffuseFileName") == 0)
				DiffuseFileName = child->Attribute("File");
			if (Opaque)
				BlendState = MERenderer::BlendStateManager::BStates::BS_Default;
			else
				BlendState = MERenderer::BlendStateManager::BStates::BS_Alpha;
			MERenderer::VertexFormat VertFormat;
			std::string tempfilename(&VertexFileName[VertexFileName.length() - 4]);
			if (tempfilename == ".obj" || tempfilename == ".OBJ")
				VertFormat = MERenderer::eVERTEX_POSNORMTEX;
			else if (tempfilename == ".fbx" || tempfilename == ".FBX")
				VertFormat = MERenderer::eVERTEX_POSBONEWEIGHTNORMTANTEX;

			MERenderer::RenderContext* renderContext = new MERenderer::RenderContext;
			renderContext->Load(VertFormat, BlendState, MERenderer::RasterizerStateManager::RS_Default, MERenderer::DepthStencilStateManager::DSS_Default);
			if (Opaque)
				renderContext = MERenderer::Renderer::AddNewnonTransparentContext(renderContext);
			else
				renderContext = MERenderer::Renderer::AddNewnonTransparentContext(renderContext);
			MERenderer::RenderMesh* tempMesh = renderContext->AddMesh(VertexFileName);
			MERenderer::RenderTexture* tempTex = tempMesh->AddTexture(DiffuseFileName);
			MEObject::CompRenderer* comprend = (MEObject::CompRenderer*)_Object;
			tempTex->AddShape((MERenderer::RenderShape*)comprend);
			std::vector<XMFLOAT4X4> currSkeleton;
			currSkeleton.resize(m_Skeleton.mJoints.size());
			for (unsigned int i = 0; i < m_Skeleton.mJoints.size(); i++)
			{
				currSkeleton[i]._11 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(0, 0);
				currSkeleton[i]._12 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(0, 1);
				currSkeleton[i]._13 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(0, 2);
				currSkeleton[i]._14 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(0, 3);
				currSkeleton[i]._21 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(1, 0);
				currSkeleton[i]._22 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(1, 1);
				currSkeleton[i]._23 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(1, 2);
				currSkeleton[i]._24 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(1, 3);
				currSkeleton[i]._31 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(2, 0);
				currSkeleton[i]._32 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(2, 1);
				currSkeleton[i]._33 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(2, 2);
				currSkeleton[i]._34 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(2, 3);
				currSkeleton[i]._41 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(3, 0);
				currSkeleton[i]._42 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(3, 1);
				currSkeleton[i]._43 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(3, 2);
				currSkeleton[i]._44 = (float)m_Skeleton.mJoints[i].mAnimation->mGlobalTransform.Get(3, 3);
			}
			((MEObject::SkinnedMeshRenderer*)_Object)->Load(&renderContext->m_BlendState,
				&renderContext->m_RasterState,
				&renderContext->m_DSState,
				tempMesh->m_vVerticies,
				&tempMesh->m_uiNumVerticies,
				tempMesh->m_vIndicies,
				&tempMesh->m_uiNumIndicies,
				&tempMesh->m_uiStartIndexLocation,
				&tempMesh->m_iBaseVertexLocation,
				&tempMesh->m_sVertexFileName,
				&tempMesh->m_eVertexFormat,
				tempTex->m_Material,
				currSkeleton);
			_Object->SetName("MeshRenderer");
			return true;
		}

		void FileIO::ProcessSkeletonHierarchy(FbxNode* inRootNode)
		{

			for (int childIndex = 0; childIndex < inRootNode->GetChildCount(); ++childIndex)
			{
				FbxNode* currNode = inRootNode->GetChild(childIndex);
				ProcessSkeletonHierarchyRecursively(currNode, 0, 0, -1);
			}
		}

		void FileIO::ProcessSkeletonHierarchyRecursively(FbxNode* inNode, int inDepth, int myIndex, int inParentIndex)
		{
			if (inNode->GetNodeAttribute() && inNode->GetNodeAttribute()->GetAttributeType() && inNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
			{
				Joint currJoint;
				currJoint.mParentIndex = inParentIndex;
				currJoint.mName = inNode->GetName();
				m_Skeleton.mJoints.push_back(currJoint);
			}
			for (int i = 0; i < inNode->GetChildCount(); i++)
				ProcessSkeletonHierarchyRecursively(inNode->GetChild(i), inDepth + 1, (unsigned int)m_Skeleton.mJoints.size(), myIndex);
		}

		void FileIO::ProcessControlPoints(FbxNode* inNode)
		{
			FbxMesh* currMesh = inNode->GetMesh();
			unsigned int ctrlPointCount = currMesh->GetControlPointsCount();
			m_mControlPoints.resize(ctrlPointCount);
			for (unsigned int i = 0; i < ctrlPointCount; ++i)
			{
				CtrlPoint* currCtrlPoint = new CtrlPoint();
				XMFLOAT3 currPosition;
				currPosition.x = static_cast<float>(currMesh->GetControlPointAt(i).mData[0]);
				currPosition.y = static_cast<float>(currMesh->GetControlPointAt(i).mData[1]);
				currPosition.z = static_cast<float>(currMesh->GetControlPointAt(i).mData[2]);
				currCtrlPoint->mPosition = currPosition;
				m_mControlPoints[i] = currCtrlPoint;
			}
		}

		void FileIO::ProcessJointsAndAnimations(FbxNode* inNode) // needs to be looked at
		{
			FbxMesh* currMesh = inNode->GetMesh();
			unsigned int numOfDeformers = currMesh->GetDeformerCount();
			if (!inNode)
				throw std::exception("Null for mesh geometry");
			const FbxVector4 lT = inNode->GetGeometricTranslation(FbxNode::eSourcePivot);
			const FbxVector4 lR = inNode->GetGeometricRotation(FbxNode::eSourcePivot);
			const FbxVector4 lS = inNode->GetGeometricScaling(FbxNode::eSourcePivot);
			FbxAMatrix geometryTransform = FbxAMatrix(lT, lR, lS);
			for (unsigned int deformerIndex = 0; deformerIndex < numOfDeformers; ++deformerIndex)
			{
				FbxSkin* currSkin = reinterpret_cast<FbxSkin*>(currMesh->GetDeformer(deformerIndex, FbxDeformer::eSkin));
				if (!currSkin)
					continue;
				unsigned int numOfClusters = currSkin->GetClusterCount();
				for (unsigned int clusterIndex = 0; clusterIndex < numOfClusters; ++clusterIndex)
				{
					FbxCluster* currCluster = currSkin->GetCluster(clusterIndex);
					std::string currJointName = currCluster->GetLink()->GetName();
					unsigned int currJointIndex = FindJointIndexUsingName(currJointName);
					FbxAMatrix transformMatrix;
					FbxAMatrix transformLinkMatrix;
					FbxAMatrix globalBindposeInverseMatrix;
					currCluster->GetTransformMatrix(transformMatrix);
					currCluster->GetTransformLinkMatrix(transformLinkMatrix);
					globalBindposeInverseMatrix = transformLinkMatrix.Inverse() * transformMatrix * geometryTransform;
					m_Skeleton.mJoints[currJointIndex].mGlobalBindposeInverse = globalBindposeInverseMatrix;
					m_Skeleton.mJoints[currJointIndex].mNode = currCluster->GetLink();
					unsigned int numOfIndices = currCluster->GetControlPointIndicesCount();
					for (unsigned int i = 0; i < numOfIndices; ++i)
					{
						BlendingIndexWeightPair currBlendingIndexWeightPair;
						currBlendingIndexWeightPair.mBlendingIndex = currJointIndex;
						currBlendingIndexWeightPair.mBlendingWeight = currCluster->GetControlPointWeights()[i];
						m_mControlPoints[currCluster->GetControlPointIndices()[i]]->mBlendingInfo.push_back(currBlendingIndexWeightPair);
					}
					FbxAnimStack* currAnimStack = m_fbxScene->GetSrcObject<FbxAnimStack>(0);
					FbxString animStackName = currAnimStack->GetName();
					m_sAnimationName = animStackName.Buffer();
					FbxTakeInfo* takeInfo = m_fbxScene->GetTakeInfo(animStackName);
					FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
					FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
					m_lAnimationLength = end.GetFrameCount(FbxTime::eFrames24) - start.GetFrameCount(FbxTime::eFrames24) + 1;
					Keyframe** currAnim = &m_Skeleton.mJoints[currJointIndex].mAnimation;
					for (FbxLongLong i = start.GetFrameCount(FbxTime::eFrames24); i <= end.GetFrameCount(FbxTime::eFrames24); ++i)
					{
						FbxTime currTime;
						currTime.SetFrame(i, FbxTime::eFrames24);
						*currAnim = new Keyframe();
						(*currAnim)->mFrameNum = i;
						FbxAMatrix currentTransformOffset = inNode->EvaluateGlobalTransform(currTime) * geometryTransform;
						(*currAnim)->mGlobalTransform = currentTransformOffset.Inverse() * currCluster->GetLink()->EvaluateGlobalTransform(currTime);
						currAnim = &((*currAnim)->mNext);
					}
				}
			}
			BlendingIndexWeightPair currBlendingIndexWeightPair;
			currBlendingIndexWeightPair.mBlendingIndex = 0;
			currBlendingIndexWeightPair.mBlendingWeight = 0;
			for (unsigned int i = 0; i < m_mControlPoints.size(); i++)
				for (unsigned int j = (unsigned int)(m_mControlPoints[i]->mBlendingInfo.size()); j <= 4; ++j)
					m_mControlPoints[i]->mBlendingInfo.push_back(currBlendingIndexWeightPair);
		}

		unsigned int FileIO::FindJointIndexUsingName(const std::string& inJointName)
		{
			for (unsigned int i = 0; i < m_Skeleton.mJoints.size(); ++i)
				if (m_Skeleton.mJoints[i].mName == inJointName)
					return i;
			throw std::exception("Skeleton information in FBX file is corrupted.");
		}

		void FileIO::ProcessMesh(FbxNode* inNode)
		{
			FbxMesh* currMesh = inNode->GetMesh();
			m_uiTriangleCount = currMesh->GetPolygonCount();
			int vertexCounter = 0;
			m_vTriangles.reserve(m_uiTriangleCount);
			for (unsigned int i = 0; i < m_uiTriangleCount; ++i)
			{
				XMFLOAT3 normal[3];
				XMFLOAT3 tangent[3];
				XMFLOAT3 binormal[3];
				XMFLOAT2 UV[3][2];
				Triangle currTriangle;
				m_vTriangles.push_back(currTriangle);

				for (int j = 0; j < 3; ++j)
				{
					int ctrlPointIndex = currMesh->GetPolygonVertex(i, j);
					CtrlPoint* currCtrlPoint = m_mControlPoints[ctrlPointIndex];
					ReadNormal(currMesh, ctrlPointIndex, vertexCounter, normal[j]);
					for (int k = 0; k < 1; ++k)
						ReadUV(currMesh, ctrlPointIndex, currMesh->GetTextureUVIndex(i, j), k, UV[j][k]);
					MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX temp;
					temp.position = currCtrlPoint->mPosition;
					temp.normal = normal[j];
					temp.texcoord = UV[j][0];
					temp.bone = XMINT4(0, 0, 0, 0);
					temp.weights = XMFLOAT4(0, 0, 0, 0);

					unsigned int Size = (unsigned int)currCtrlPoint->mBlendingInfo.size();
					for (unsigned int i = 0; i < Size; ++i)
					{
						switch (i)
						{
						case 0:
							temp.bone.x = currCtrlPoint->mBlendingInfo[0].mBlendingIndex;
							temp.weights.x = (float)currCtrlPoint->mBlendingInfo[0].mBlendingWeight;
							break;
						case 1:
							temp.bone.y = currCtrlPoint->mBlendingInfo[1].mBlendingIndex;
							temp.weights.y = (float)currCtrlPoint->mBlendingInfo[1].mBlendingWeight;
							break;
						case 2:
							temp.bone.z = currCtrlPoint->mBlendingInfo[2].mBlendingIndex;
							temp.weights.z = (float)currCtrlPoint->mBlendingInfo[2].mBlendingWeight;
							break;
						case 3:
							temp.bone.w = currCtrlPoint->mBlendingInfo[3].mBlendingIndex;
							temp.weights.w = (float)currCtrlPoint->mBlendingInfo[3].mBlendingWeight;
							break;
						default:
							break;
						}
					}
					m_vVertices.push_back(temp);
					m_vTriangles.back().mIndices.push_back(vertexCounter);
					++vertexCounter;
				}
			}

			unsigned int Size = (unsigned int)m_mControlPoints.size();
			for (unsigned int i = 0; i < Size; i++)
				delete m_mControlPoints[i];
			m_mControlPoints.clear();
		}

		void FileIO::CalculateTangentBinormal(VERTEX_POSBONEWEIGHTNORMTANTEX vertex1, VERTEX_POSBONEWEIGHTNORMTANTEX vertex2, VERTEX_POSBONEWEIGHTNORMTANTEX vertex3,
			XMFLOAT3& tangent, XMFLOAT3& binormal)
		{
			float vector1[3], vector2[3];
			float tuVector[2], tvVector[2];
			float den;
			float length;


			// Calculate the two vectors for this face.
			vector1[0] = vertex2.position.x - vertex1.position.x;
			vector1[1] = vertex2.position.y - vertex1.position.y;
			vector1[2] = vertex2.position.z - vertex1.position.z;

			vector2[0] = vertex3.position.x - vertex1.position.x;
			vector2[1] = vertex3.position.y - vertex1.position.y;
			vector2[2] = vertex3.position.z - vertex1.position.z;

			// Calculate the tu and tv texture space vectors.
			tuVector[0] = vertex2.texcoord.x - vertex1.texcoord.x;
			tvVector[0] = vertex2.texcoord.y - vertex1.texcoord.y;

			tuVector[1] = vertex3.texcoord.x - vertex1.texcoord.x;
			tvVector[1] = vertex3.texcoord.y - vertex1.texcoord.y;

			// Calculate the denominator of the tangent/binormal equation.
			den = 1.0f / (tuVector[0] * tvVector[1] - tuVector[1] * tvVector[0]);

			// Calculate the cross products and multiply by the coefficient to get the tangent and binormal.
			tangent.x = (tvVector[1] * vector1[0] - tvVector[0] * vector2[0]) * den;
			tangent.y = (tvVector[1] * vector1[1] - tvVector[0] * vector2[1]) * den;
			tangent.z = (tvVector[1] * vector1[2] - tvVector[0] * vector2[2]) * den;

			binormal.x = (tuVector[0] * vector2[0] - tuVector[1] * vector1[0]) * den;
			binormal.y = (tuVector[0] * vector2[1] - tuVector[1] * vector1[1]) * den;
			binormal.z = (tuVector[0] * vector2[2] - tuVector[1] * vector1[2]) * den;

			// Calculate the length of this normal.
			length = sqrt((tangent.x * tangent.x) + (tangent.y * tangent.y) + (tangent.z * tangent.z));

			// Normalize the normal and then store it
			tangent.x = tangent.x / length;
			tangent.y = tangent.y / length;
			tangent.z = tangent.z / length;

			// Calculate the length of this normal.
			length = sqrt((binormal.x * binormal.x) + (binormal.y * binormal.y) + (binormal.z * binormal.z));

			// Normalize the normal and then store it
			binormal.x = binormal.x / length;
			binormal.y = binormal.y / length;
			binormal.z = binormal.z / length;

			return;
		}

		void FileIO::CalculateNormal(XMFLOAT3 tangent, XMFLOAT3 binormal, XMFLOAT3& normal)
		{
			float length;


			// Calculate the cross product of the tangent and binormal which will give the normal vector.
			normal.x = (tangent.y * binormal.z) - (tangent.z * binormal.y);
			normal.y = (tangent.z * binormal.x) - (tangent.x * binormal.z);
			normal.z = (tangent.x * binormal.y) - (tangent.y * binormal.x);

			// Calculate the length of the normal.
			length = sqrt((normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z));

			// Normalize the normal.
			normal.x = normal.x / length;
			normal.y = normal.y / length;
			normal.z = normal.z / length;

			return;
		}

		void FileIO::CalculateModelVectors()
		{
			int faceCount, i, index;
			VERTEX_POSBONEWEIGHTNORMTANTEX vertex1, vertex2, vertex3;
			XMFLOAT3 tangent, binormal, normal;


			// Calculate the number of faces in the model.
			faceCount = (int)(m_vVertices.size() / 3.0f);

			// Initialize the index to the model data.
			index = 0;

			// Go through all the faces and calculate the the tangent, binormal, and normal vectors.
			for (i = 0; i < faceCount; i++)
			{
				// Get the three vertices for this face from the model.
				vertex1.position.x = m_vVertices[index].position.x;
				vertex1.position.y = m_vVertices[index].position.y;
				vertex1.position.z = m_vVertices[index].position.z;
				vertex1.texcoord.x = m_vVertices[index].texcoord.x;
				vertex1.texcoord.y = m_vVertices[index].texcoord.y;
				vertex1.normal.x = m_vVertices[index].normal.x;
				vertex1.normal.y = m_vVertices[index].normal.y;
				vertex1.normal.z = m_vVertices[index].normal.z;
				index++;

				vertex2.position.x = m_vVertices[index].position.x;
				vertex2.position.y = m_vVertices[index].position.y;
				vertex2.position.z = m_vVertices[index].position.z;
				vertex2.texcoord.x = m_vVertices[index].texcoord.x;
				vertex2.texcoord.y = m_vVertices[index].texcoord.y;
				vertex2.normal.x = m_vVertices[index].normal.x;
				vertex2.normal.y = m_vVertices[index].normal.y;
				vertex2.normal.z = m_vVertices[index].normal.z;
				index++;

				vertex3.position.x = m_vVertices[index].position.x;
				vertex3.position.y = m_vVertices[index].position.y;
				vertex3.position.z = m_vVertices[index].position.z;
				vertex3.texcoord.x = m_vVertices[index].texcoord.x;
				vertex3.texcoord.y = m_vVertices[index].texcoord.y;
				vertex3.normal.x = m_vVertices[index].normal.x;
				vertex3.normal.y = m_vVertices[index].normal.y;
				vertex3.normal.z = m_vVertices[index].normal.z;
				index++;

				// Calculate the tangent and binormal of that face.
				CalculateTangentBinormal(vertex1, vertex2, vertex3, tangent, binormal);

				// Calculate the new normal using the tangent and binormal.
				CalculateNormal(tangent, binormal, normal);

				// Store the normal, tangent, and binormal for this face back in the model structure.
				m_vVertices[index - 1].normal.x = normal.x;
				m_vVertices[index - 1].normal.y = normal.y;
				m_vVertices[index - 1].normal.z = normal.z;
				m_vVertices[index - 1].tangent.x = tangent.x;
				m_vVertices[index - 1].tangent.y = tangent.y;
				m_vVertices[index - 1].tangent.z = tangent.z;
				m_vVertices[index - 1].binormal.x = binormal.x;
				m_vVertices[index - 1].binormal.y = binormal.y;
				m_vVertices[index - 1].binormal.z = binormal.z;

				m_vVertices[index - 2].normal.x = normal.x;
				m_vVertices[index - 2].normal.y = normal.y;
				m_vVertices[index - 2].normal.z = normal.z;
				m_vVertices[index - 2].tangent.x = tangent.x;
				m_vVertices[index - 2].tangent.y = tangent.y;
				m_vVertices[index - 2].tangent.z = tangent.z;
				m_vVertices[index - 2].binormal.x = binormal.x;
				m_vVertices[index - 2].binormal.y = binormal.y;
				m_vVertices[index - 2].binormal.z = binormal.z;

				m_vVertices[index - 3].normal.x = normal.x;
				m_vVertices[index - 3].normal.y = normal.y;
				m_vVertices[index - 3].normal.z = normal.z;
				m_vVertices[index - 3].tangent.x = tangent.x;
				m_vVertices[index - 3].tangent.y = tangent.y;
				m_vVertices[index - 3].tangent.z = tangent.z;
				m_vVertices[index - 3].binormal.x = binormal.x;
				m_vVertices[index - 3].binormal.y = binormal.y;
				m_vVertices[index - 3].binormal.z = binormal.z;
			}

			return;
		}

		void FileIO::ReadUV(FbxMesh* inMesh, int inCtrlPointIndex, int inTextureUVIndex, int inUVLayer, XMFLOAT2& outUV)
		{
			if (inUVLayer >= 2 || inMesh->GetElementUVCount() <= inUVLayer)
			{
				throw std::exception("Invalid UV Layer Number");
			}
			FbxGeometryElementUV* vertexUV = inMesh->GetElementUV(inUVLayer);

			switch (vertexUV->GetMappingMode())
			{
			case FbxGeometryElement::eByControlPoint:
				switch (vertexUV->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
				{
					outUV.x = 1 - static_cast<float>(vertexUV->GetDirectArray().GetAt(inCtrlPointIndex).mData[0]);
					outUV.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(inCtrlPointIndex).mData[1]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexUV->GetIndexArray().GetAt(inCtrlPointIndex);
					outUV.x = 1 - static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[0]);
					outUV.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(index).mData[1]);
				}
				break;

				default:
					throw std::exception("Invalid Reference");
				}
				break;

			case FbxGeometryElement::eByPolygonVertex:
				switch (vertexUV->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
				case FbxGeometryElement::eIndexToDirect:
				{
					outUV.x = 1 - static_cast<float>(vertexUV->GetDirectArray().GetAt(inTextureUVIndex).mData[0]);
					outUV.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(inTextureUVIndex).mData[1]);
				}
				break;

				default:
					throw std::exception("Invalid Reference");
				}
				break;
			}
		}

		void FileIO::ReadNormal(FbxMesh* inMesh, int inCtrlPointIndex, int inVertexCounter, XMFLOAT3& outNormal)
		{
			if (inMesh->GetElementNormalCount() < 1)
			{
				throw std::exception("Invalid Normal Number");
			}

			FbxGeometryElementNormal* vertexNormal = inMesh->GetElementNormal(0);
			switch (vertexNormal->GetMappingMode())
			{
			case FbxGeometryElement::eByControlPoint:
				switch (vertexNormal->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
				{
					outNormal.x = -static_cast<float>(vertexNormal->GetDirectArray().GetAt(inCtrlPointIndex).mData[0]);
					outNormal.y = -static_cast<float>(vertexNormal->GetDirectArray().GetAt(inCtrlPointIndex).mData[1]);
					outNormal.z = -static_cast<float>(vertexNormal->GetDirectArray().GetAt(inCtrlPointIndex).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexNormal->GetIndexArray().GetAt(inCtrlPointIndex);
					outNormal.x = -static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
					outNormal.y = -static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
					outNormal.z = -static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
				}
				break;

				default:
					throw std::exception("Invalid Reference");
				}
				break;

			case FbxGeometryElement::eByPolygonVertex:
				switch (vertexNormal->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
				{
					outNormal.x = -static_cast<float>(vertexNormal->GetDirectArray().GetAt(inVertexCounter).mData[0]);
					outNormal.y = -static_cast<float>(vertexNormal->GetDirectArray().GetAt(inVertexCounter).mData[1]);
					outNormal.z = -static_cast<float>(vertexNormal->GetDirectArray().GetAt(inVertexCounter).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexNormal->GetIndexArray().GetAt(inVertexCounter);
					outNormal.x = -static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[0]);
					outNormal.y = -static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[1]);
					outNormal.z = -static_cast<float>(vertexNormal->GetDirectArray().GetAt(index).mData[2]);
				}
				break;

				default:
					throw std::exception("Invalid Reference");
				}
				break;
			}
		}

		void FileIO::ReadBinormal(FbxMesh* inMesh, int inCtrlPointIndex, int inVertexCounter, XMFLOAT3& outBinormal)
		{
			if (inMesh->GetElementBinormalCount() < 1)
			{
				throw std::exception("Invalid Binormal Number");
			}

			FbxGeometryElementBinormal* vertexBinormal = inMesh->GetElementBinormal(0);
			switch (vertexBinormal->GetMappingMode())
			{
			case FbxGeometryElement::eByControlPoint:
				switch (vertexBinormal->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
				{
					outBinormal.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(inCtrlPointIndex).mData[0]);
					outBinormal.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(inCtrlPointIndex).mData[1]);
					outBinormal.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(inCtrlPointIndex).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexBinormal->GetIndexArray().GetAt(inCtrlPointIndex);
					outBinormal.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[0]);
					outBinormal.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[1]);
					outBinormal.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[2]);
				}
				break;

				default:
					throw std::exception("Invalid Reference");
				}
				break;

			case FbxGeometryElement::eByPolygonVertex:
				switch (vertexBinormal->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
				{
					outBinormal.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(inVertexCounter).mData[0]);
					outBinormal.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(inVertexCounter).mData[1]);
					outBinormal.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(inVertexCounter).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexBinormal->GetIndexArray().GetAt(inVertexCounter);
					outBinormal.x = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[0]);
					outBinormal.y = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[1]);
					outBinormal.z = static_cast<float>(vertexBinormal->GetDirectArray().GetAt(index).mData[2]);
				}
				break;

				default:
					throw std::exception("Invalid Reference");
				}
				break;
			}
		}

		void FileIO::ReadTangent(FbxMesh* inMesh, int inCtrlPointIndex, int inVertexCounter, XMFLOAT3& outTangent)
		{
			if (inMesh->GetElementTangentCount() < 1)
			{
				throw std::exception("Invalid Tangent Number");
			}

			FbxGeometryElementTangent* vertexTangent = inMesh->GetElementTangent(0);
			switch (vertexTangent->GetMappingMode())
			{
			case FbxGeometryElement::eByControlPoint:
				switch (vertexTangent->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
				{
					outTangent.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(inCtrlPointIndex).mData[0]);
					outTangent.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(inCtrlPointIndex).mData[1]);
					outTangent.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(inCtrlPointIndex).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexTangent->GetIndexArray().GetAt(inCtrlPointIndex);
					outTangent.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[0]);
					outTangent.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[1]);
					outTangent.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[2]);
				}
				break;

				default:
					throw std::exception("Invalid Reference");
				}
				break;

			case FbxGeometryElement::eByPolygonVertex:
				switch (vertexTangent->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
				{
					outTangent.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(inVertexCounter).mData[0]);
					outTangent.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(inVertexCounter).mData[1]);
					outTangent.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(inVertexCounter).mData[2]);
				}
				break;

				case FbxGeometryElement::eIndexToDirect:
				{
					int index = vertexTangent->GetIndexArray().GetAt(inVertexCounter);
					outTangent.x = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[0]);
					outTangent.y = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[1]);
					outTangent.z = static_cast<float>(vertexTangent->GetDirectArray().GetAt(index).mData[2]);
				}
				break;

				default:
					throw std::exception("Invalid Reference");
				}
				break;
			}
		}

		void FileIO::ProcessGeometry(FbxNode* inNode)
		{
			if (inNode->GetNodeAttribute())
			{
				switch (inNode->GetNodeAttribute()->GetAttributeType())
				{
				case FbxNodeAttribute::eMesh:
					ProcessControlPoints(inNode);
					if (m_bHasAnimation)
					{
						ProcessJointsAndAnimations(inNode);
					}
					ProcessMesh(inNode);
					//CalculateModelVectors();
					AssociateMaterialToMesh(inNode);
					ProcessMaterials(inNode);
					break;
				}
			}

			for (int i = 0; i < inNode->GetChildCount(); ++i)
			{
				ProcessGeometry(inNode->GetChild(i));
			}
		}

		void FileIO::Optimize()
		{
			std::vector<MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX> uniqueVertices;
			for (unsigned int i = 0; i < m_vTriangles.size(); ++i)
				for (unsigned int j = 0; j < 3; ++j)
					if (FindVertex(m_vVertices[i * 3 + j], uniqueVertices) == -1)
						uniqueVertices.push_back(m_vVertices[i * 3 + j]);
			for (unsigned int i = 0; i < m_vTriangles.size(); ++i)
				for (unsigned int j = 0; j < 3; ++j)
					m_vTriangles[i].mIndices[j] = FindVertex(m_vVertices[i * 3 + j], uniqueVertices);
			m_vVertices.clear();
			m_vVertices = uniqueVertices;
			uniqueVertices.clear();
			std::sort(m_vTriangles.begin(), m_vTriangles.end());
		}

		int FileIO::FindVertex(const MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX& inTargetVertex, const std::vector<MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX>& uniqueVertices)
		{
			for (unsigned int i = 0; i < uniqueVertices.size(); ++i)
			{
				MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX temp = uniqueVertices[i];
				if (inTargetVertex.bone.x == temp.bone.x &&
					inTargetVertex.bone.y == temp.bone.y &&
					inTargetVertex.bone.z == temp.bone.z &&
					inTargetVertex.bone.w == temp.bone.w &&
					inTargetVertex.determinant == temp.determinant &&
					inTargetVertex.normal.x == temp.normal.x &&
					inTargetVertex.normal.y == temp.normal.y &&
					inTargetVertex.normal.z == temp.normal.z &&
					inTargetVertex.position.x == temp.position.x &&
					inTargetVertex.position.y == temp.position.y &&
					inTargetVertex.position.z == temp.position.z &&
					inTargetVertex.tangent.x == temp.tangent.x &&
					inTargetVertex.tangent.y == temp.tangent.y &&
					inTargetVertex.tangent.z == temp.tangent.z &&
					inTargetVertex.texcoord.x == temp.texcoord.x &&
					inTargetVertex.texcoord.y == temp.texcoord.y &&
					inTargetVertex.weights.x == temp.weights.x &&
					inTargetVertex.weights.y == temp.weights.y &&
					inTargetVertex.weights.z == temp.weights.z &&
					inTargetVertex.weights.w == temp.weights.w)
				{
					return i;
				}
			}

			return -1;
		}

		void FileIO::AssociateMaterialToMesh(FbxNode* inNode)
		{
			FbxLayerElementArrayTemplate<int>* materialIndices;
			FbxGeometryElement::EMappingMode materialMappingMode = FbxGeometryElement::eNone;
			FbxMesh* currMesh = inNode->GetMesh();

			if (currMesh->GetElementMaterial())
			{
				materialIndices = &(currMesh->GetElementMaterial()->GetIndexArray());
				materialMappingMode = currMesh->GetElementMaterial()->GetMappingMode();

				if (materialIndices)
				{
					switch (materialMappingMode)
					{
					case FbxGeometryElement::eByPolygon:
					{
						if (materialIndices->GetCount() == m_uiTriangleCount)
						{
							for (unsigned int i = 0; i < m_uiTriangleCount; ++i)
							{
								unsigned int materialIndex = materialIndices->GetAt(i);
								m_vTriangles[i].mMaterialIndex = materialIndex;
							}
						}
					}
					break;

					case FbxGeometryElement::eAllSame:
					{
						unsigned int materialIndex = materialIndices->GetAt(0);
						for (unsigned int i = 0; i < m_uiTriangleCount; ++i)
						{
							m_vTriangles[i].mMaterialIndex = materialIndex;
						}
					}
					break;

					default:
						throw std::exception("Invalid mapping mode for material\n");
					}
				}
			}
		}

		void FileIO::ProcessMaterials(FbxNode* inNode)
		{
			unsigned int materialCount = inNode->GetMaterialCount();

			for (unsigned int i = 0; i < materialCount; ++i)
			{
				FbxSurfaceMaterial* surfaceMaterial = inNode->GetMaterial(i);
				ProcessMaterialAttribute(surfaceMaterial, i);
				ProcessMaterialTexture(surfaceMaterial, m_mMaterialLookUp[i]);
			}
		}

		void FileIO::ProcessMaterialAttribute(FbxSurfaceMaterial* inMaterial, unsigned int inMaterialIndex)
		{
			FbxDouble3 double3;
			FbxDouble double1;
			MEObject::Material* currMaterial = new MEObject::Material();
			if (inMaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
			{

				// Amibent Color
				double3 = reinterpret_cast<FbxSurfacePhong *>(inMaterial)->Ambient;
				currMaterial->mAmbient.x = static_cast<float>(double3.mData[0]);
				currMaterial->mAmbient.y = static_cast<float>(double3.mData[1]);
				currMaterial->mAmbient.z = static_cast<float>(double3.mData[2]);

				// Diffuse Color
				double3 = reinterpret_cast<FbxSurfacePhong *>(inMaterial)->Diffuse;
				currMaterial->mDiffuse.x = static_cast<float>(double3.mData[0]);
				currMaterial->mDiffuse.y = static_cast<float>(double3.mData[1]);
				currMaterial->mDiffuse.z = static_cast<float>(double3.mData[2]);

				// Specular Color
				double3 = reinterpret_cast<FbxSurfacePhong *>(inMaterial)->Specular;
				currMaterial->mSpecular.x = static_cast<float>(double3.mData[0]);
				currMaterial->mSpecular.y = static_cast<float>(double3.mData[1]);
				currMaterial->mSpecular.z = static_cast<float>(double3.mData[2]);

				// Emissive Color
				double3 = reinterpret_cast<FbxSurfacePhong *>(inMaterial)->Emissive;
				currMaterial->mEmissive.x = static_cast<float>(double3.mData[0]);
				currMaterial->mEmissive.y = static_cast<float>(double3.mData[1]);
				currMaterial->mEmissive.z = static_cast<float>(double3.mData[2]);

				// Reflection
				double3 = reinterpret_cast<FbxSurfacePhong *>(inMaterial)->Reflection;
				currMaterial->mReflection.x = static_cast<float>(double3.mData[0]);
				currMaterial->mReflection.y = static_cast<float>(double3.mData[1]);
				currMaterial->mReflection.z = static_cast<float>(double3.mData[2]);

				// Transparency Factor
				double1 = reinterpret_cast<FbxSurfacePhong *>(inMaterial)->TransparencyFactor;
				currMaterial->mTransparencyFactor = double1;

				// Shininess
				double1 = reinterpret_cast<FbxSurfacePhong *>(inMaterial)->Shininess;
				currMaterial->mShininess = double1;

				// Specular Factor
				double1 = reinterpret_cast<FbxSurfacePhong *>(inMaterial)->SpecularFactor;
				currMaterial->mSpecularPower = double1;


				// Reflection Factor
				double1 = reinterpret_cast<FbxSurfacePhong *>(inMaterial)->ReflectionFactor;
				currMaterial->mReflectionFactor = double1;

				m_mMaterialLookUp[inMaterialIndex] = currMaterial;
			}
			else if (inMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId))
			{

				// Amibent Color
				double3 = reinterpret_cast<FbxSurfaceLambert *>(inMaterial)->Ambient;
				currMaterial->mAmbient.x = static_cast<float>(double3.mData[0]);
				currMaterial->mAmbient.y = static_cast<float>(double3.mData[1]);
				currMaterial->mAmbient.z = static_cast<float>(double3.mData[2]);

				// Diffuse Color
				double3 = reinterpret_cast<FbxSurfaceLambert *>(inMaterial)->Diffuse;
				currMaterial->mDiffuse.x = static_cast<float>(double3.mData[0]);
				currMaterial->mDiffuse.y = static_cast<float>(double3.mData[1]);
				currMaterial->mDiffuse.z = static_cast<float>(double3.mData[2]);

				// Emissive Color
				double3 = reinterpret_cast<FbxSurfaceLambert *>(inMaterial)->Emissive;
				currMaterial->mEmissive.x = static_cast<float>(double3.mData[0]);
				currMaterial->mEmissive.y = static_cast<float>(double3.mData[1]);
				currMaterial->mEmissive.z = static_cast<float>(double3.mData[2]);

				// Transparency Factor
				double1 = reinterpret_cast<FbxSurfaceLambert *>(inMaterial)->TransparencyFactor;
				currMaterial->mTransparencyFactor = double1;

				m_mMaterialLookUp[inMaterialIndex] = currMaterial;
			}
		}

		void FileIO::ProcessMaterialTexture(FbxSurfaceMaterial* inMaterial, MEObject::Material* ioMaterial)
		{
			unsigned int textureIndex = 0;
			FbxProperty property;

			FBXSDK_FOR_EACH_TEXTURE(textureIndex)
			{
				property = inMaterial->FindProperty(FbxLayerElement::sTextureChannelNames[textureIndex]);
				if (property.IsValid())
				{
					unsigned int textureCount = property.GetSrcObjectCount<FbxTexture>();
					for (unsigned int i = 0; i < textureCount; ++i)
					{
						FbxLayeredTexture* layeredTexture = property.GetSrcObject<FbxLayeredTexture>(i);
						if (layeredTexture)
						{
							throw std::exception("Layered Texture is currently unsupported\n");
						}
						else
						{
							FbxTexture* texture = property.GetSrcObject<FbxTexture>(i);
							if (texture)
							{
								std::string textureType = property.GetNameAsCStr();
								FbxFileTexture* fileTexture = FbxCast<FbxFileTexture>(texture);

								if (fileTexture)
								{
									if (textureType == "DiffuseColor")
									{
										ioMaterial->mDiffuseMapName = fileTexture->GetFileName();
									}
									else if (textureType == "SpecularColor")
									{
										ioMaterial->mSpecularMapName = fileTexture->GetFileName();
									}
									else if (textureType == "NormalMap")
									{
										ioMaterial->mNormalMapName = fileTexture->GetFileName();
									}
								}
							}
						}
					}
				}
			}
		}

	}
}