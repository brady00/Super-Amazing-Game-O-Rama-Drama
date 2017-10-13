#include "FileIO.h"
#include <fstream>
#include <algorithm>
#include "RenderSet/RenderSet.h"
#include "RenderSet/RenderContext.h"
#include "RenderSet/RenderMesh.h"
#include "RenderSet/RenderTexture.h"
#include "Renderer/MeshRenderer.h"
#include "Containers\IndexBuffer.h"
#include "Renderer.h"
#include "Transform\Transform.h"
#include "Renderer/CompRenderer.h"
#include "Factory\ComponentObjectFactory.h"
#include "Renderer\SkinnedMeshRenderer.h"
#include "DebugCamera\DebugCamera.h"
namespace MonkeyEngine
{
	namespace MEFileIO
	{

		const std::unordered_map<std::string, compFuntion> FileIO::componentFunctions =
		{
			{ "Transform", &FileIO::LoadTranform },
			{ "MeshRenderer", &FileIO::LoadMeshRenderer },
			{ "SkinnedMeshRenderer", &FileIO::LoadSkinnedMeshRenderer },
			{ "Camera", &FileIO::LoadCamera }
		};

		const std::unordered_map<std::string, MEObject::GameObject::COMPONENT_ID> FileIO::componentIDS =
		{
			{ "Transform", MEObject::GameObject::COMPONENT_ID::eTransform },
			{ "MeshRenderer", MEObject::GameObject::COMPONENT_ID::eMeshRenderer },
			{ "SkinnedMeshRenderer", MEObject::GameObject::COMPONENT_ID::eSkinnedMeshRenderer },
			{ "Camera", MEObject::GameObject::COMPONENT_ID::eCamera }
		};

		FileIO::FileIO()
		{

		}

		FileIO::~FileIO()
		{

		}

		bool FileIO::LoadFBX(std::string _FileName, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies, Material*& _Material, Skeleton& _Skeleton)
		{
#pragma region Binary Loading
			std::string filepart;
			std::ifstream FileIn;
			char* File = new char[256];
			_splitpath_s(_FileName.c_str(), NULL, 0, NULL, 0, File, 256, NULL, 0);
			std::string finalPath("Assets/Binaries/" + std::string(File) + ".Bfbx");
			std::string finalSkelPath("Assets/Binaries/" + std::string(File) + ".Bskel");
			std::string AssetPath("Assets/Models/" + std::string(File) + ".fbx");
			FileIn.open(finalPath, std::ios_base::binary);
			bool BinarySkip = false;
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
					FileIn.read((char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].bones), sizeof(DirectX::XMINT4));
					FileIn.read((char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].determinant), sizeof(float));
					FileIn.read((char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].tangent), sizeof(DirectX::XMFLOAT3));
					FileIn.read((char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].weights), sizeof(DirectX::XMFLOAT4));
					FileIn.read((char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].binormal), sizeof(DirectX::XMFLOAT4));
				}
				FileIn.read((char*)& _NumIndicies, sizeof(unsigned int));
				_Indicies = new unsigned int[_NumIndicies];
				for (unsigned int i = 0; i < _NumIndicies; i++)
					FileIn.read((char*)&_Indicies[i], sizeof(unsigned int));
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
				FileIn.close();
				FileIn.open(finalSkelPath, std::ios_base::binary);
				if (FileIn.is_open())
				{
					unsigned int Size = 0;
					FileIn.read((char*)&Size, sizeof(unsigned int));
					_Skeleton.mJoints.resize(Size);
					for (unsigned int i = 0; i < Size; i++)
					{
						FileIn.read((char*)&Size, sizeof(unsigned int));
						char* boneName = new char[Size];
						FileIn.read(boneName, Size);
						_Skeleton.mJoints[i].mName = string(boneName);
						delete boneName;
						FileIn.read((char*)&_Skeleton.mJoints[i].mParentIndex, sizeof(int));
						FileIn.read((char*)&_Skeleton.mJoints[i].InverseBindpose, sizeof(XMFLOAT4X4));
						FileIn.read((char*)&_Skeleton.mJoints[i].Offset, sizeof(XMFLOAT4X4));
						FileIn.read((char*)&_Skeleton.mJoints[i].Local, sizeof(XMFLOAT4X4));
					}
				}
				return true;
			}
#pragma endregion
			FBXLoader Loader;
			if (!Loader.LoadFBX(AssetPath))
				return false;
			_NumVerticies = (unsigned int)Loader.m_Verticies.size();
			_Verticies = new MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX[_NumVerticies];
			for (unsigned int i = 0; i < Loader.m_Verticies.size(); i++)
				((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i] = Loader.m_Verticies[i];
			_NumIndicies = (unsigned int)Loader.m_Indices.size();
			_Indicies = new unsigned int[_NumIndicies];
			for (unsigned int i = 0; i < Loader.m_Indices.size(); i++)
				_Indicies[i] = Loader.m_Indices[i];
			_Material = new Material();
			_Material->mDiffuseMapName = Loader.m_Material->mDiffuseMapName;
			_Material->mEmissiveMapName = Loader.m_Material->mEmissiveMapName;
			_Material->mGlossMapName = Loader.m_Material->mGlossMapName;
			_Material->mNormalMapName = Loader.m_Material->mNormalMapName;
			_Material->mSpecularMapName = Loader.m_Material->mSpecularMapName;
			_Skeleton = Loader.m_Skeleton;
#pragma region Binary Saving
			string Xcopy = "\"xcopy " + _FileName + " " + AssetPath;
			system(Xcopy.c_str());
			std::ofstream out;
			out.open(finalPath.c_str(), std::ios_base::binary);
			if (out.is_open())
			{
				out.write((const char*)& _NumVerticies, sizeof(unsigned int));
				for (unsigned int i = 0; i < _NumVerticies; i++)
				{
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].position), sizeof(DirectX::XMFLOAT3));
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].normal), sizeof(DirectX::XMFLOAT3));
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].texcoord), sizeof(DirectX::XMFLOAT2));
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].bones), sizeof(DirectX::XMINT4));
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].determinant), sizeof(float));
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].tangent), sizeof(DirectX::XMFLOAT3));
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].weights), sizeof(DirectX::XMFLOAT4));
					out.write((const char*)&(((MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*)_Verticies)[i].binormal), sizeof(DirectX::XMFLOAT4));
				}
				out.write((const char*)& _NumIndicies, sizeof(unsigned int));
				for (unsigned int i = 0; i < _NumIndicies; i++)
					out.write((const char*)&_Indicies[i], sizeof(unsigned int));
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
				out.close();
			}
			else
				return false;
			string SkelFile;
			SkelFile.append(finalPath.c_str(), finalPath.length() - 4);
			out.open(SkelFile + std::string(".BSkel"), std::ios_base::binary);
			if (out.is_open())
			{
				unsigned int Size = (unsigned int)_Skeleton.mJoints.size();
				out.write((const char*)&Size, sizeof(unsigned int));
				for (unsigned int i = 0; i < Size; i++)
				{
					Size = (unsigned int)_Skeleton.mJoints[i].mName.size() + 1;
					out.write((const char*)&Size, sizeof(unsigned int));
					out.write(_Skeleton.mJoints[i].mName.c_str(), _Skeleton.mJoints[i].mName.size() + 1);
					out.write((const char*)&_Skeleton.mJoints[i].mParentIndex, sizeof(int));
					out.write((const char*)&_Skeleton.mJoints[i].InverseBindpose, sizeof(XMFLOAT4X4));
					out.write((const char*)&_Skeleton.mJoints[i].Offset, sizeof(XMFLOAT4X4));
					out.write((const char*)&_Skeleton.mJoints[i].Local, sizeof(XMFLOAT4X4));
				}
				out.close();
			}
			else
				return false;
			string AnimFile;
			AnimFile.append(finalPath.c_str(), finalPath.length() - 4);
			for (unsigned int i = 0; i < Loader.m_Animations.size(); i++)
			{
				Animation* Anim = Loader.m_Animations[i];
				out.open(AnimFile + Anim->AnimationName + std::string(".Anim"), std::ios_base::binary);
				if (out.is_open())
				{
					//Animation Name Size
					unsigned int size = (unsigned int)Anim->AnimationName.size() + 1;
					out.write((const char *)&size, sizeof(unsigned int));
					//Animation Name
					out.write(Anim->AnimationName.c_str(), size);
					//Animation Frame Count
					out.write((const char*)&Anim->mFrameCount, sizeof(int));
					//KeyFrames
					for (int j = 0; j < Anim->mFrameCount; j++)
					{
						Keyframe* Key = Anim->mKeyFrames[j];
						//Frame Number
						out.write((const char*)&Key->mFrameNum, sizeof(unsigned int));
						//Offsets Size
						size = (unsigned int)Key->mOffsets.size();
						out.write((const char*)&size, sizeof(unsigned int));
						//Offsets
						for (unsigned int k = 0; k < size; k++)
							out.write((const char*)&(Key->mOffsets[k]), sizeof(XMFLOAT4X4));
					}
					out.close();
				}
				else
					return false;
			}
#pragma endregion
			return true;
		}

		bool FileIO::LoadOBJ(std::string _FileName, MERenderer::VERTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies)
		{
			std::string filepart;
			std::ifstream FileIn;
			char* File = new char[256];
			_splitpath_s(_FileName.c_str(), NULL, 0, NULL, 0, File, 256, NULL, 0);
			std::string finalPath("Assets/Binaries/" + std::string(File) + ".BObj");
			std::string AssetPath("Assets/Models/" + std::string(File) + ".Obj");
			filepart.append(_FileName.c_str(), _FileName.length() - 4);
			FileIn.open(finalPath, std::ios_base::binary);
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
			string Xcopy = "\"xcopy " + _FileName + " " + AssetPath;
			system(Xcopy.c_str());
			delete File;
			std::vector<XMFLOAT3> temp_vertices;
			std::vector<XMFLOAT2> temp_uvs;
			std::vector<XMFLOAT3> temp_normals;
			std::vector< unsigned int > vertexIndices;
			std::vector< unsigned int > normalIndices;
			std::vector< unsigned int > uvIndices;
			FILE* file = nullptr;
			fopen_s(&file, AssetPath.c_str(), "r");
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

		void FileIO::LoadScene(std::string _FileName, std::vector<MEObject::GameObject*>& _GameObjects, float& percentLoaded, bool& Succeeded)
		{
			tinyxml2::XMLDocument doc;
			doc.LoadFile(_FileName.c_str());
			XMLElement* root = doc.FirstChildElement();
			if (!root)
			{
				Succeeded = false;
				return;
			}
			int childAmount = 0;
			XMLElement* findChild = root->FirstChildElement();
			while (findChild)
			{
				childAmount++;
				findChild = findChild->NextSiblingElement();
			}

			XMLElement* child = root->FirstChildElement();
			while (child)
			{
				switch (child->Value()[0])
				{
					//Scene Specific data
				case 'D':
				{
					LoadDebugCamera(child);
					break;
				}
					//GameObjects
				case 'G':
				{
					MEObject::GameObject* Object = new MEObject::GameObject;
					if (!LoadGameObject(child, Object, percentLoaded, childAmount))
						delete Object;
					else
						_GameObjects.push_back(Object);
				}
				default:
					break;
				}
				child = child->NextSiblingElement();
			}
			Succeeded = true;
			percentLoaded = 1.0f;
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

		bool FileIO::LoadSettings(std::vector<SettingData*> &_SettingData)
		{
			ifstream ifile;
			ifile.open("Assets/Settings/config.txt");
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

		bool FileIO::LoadGameObject(XMLElement* _ObjectRoot, MEObject::GameObject* _Object, float& percentLoaded, int GameObjectAmount)
		{
			XMLElement* findChild = _ObjectRoot->FirstChildElement();
			int ComponentAmount = 0;
			while (findChild)
			{
				ComponentAmount++;
				findChild = findChild->NextSiblingElement();
			}
			XMLElement* child = _ObjectRoot->FirstChildElement();
			while (child)
			{
				Component* comp = ComponentObjectFactory::GetInstance()->Create(std::string(child->Value()));
				if (componentFunctions.at(std::string(child->Value()))(child, comp))
					_Object->AddComponent(comp, componentIDS.at(std::string(child->Value())));
				else
					return false;
				percentLoaded += (1.0f / GameObjectAmount) * (1.0f / ComponentAmount);
				child = child->NextSiblingElement();
			}
			bool active;
			_ObjectRoot->QueryBoolAttribute("Active", &active);
			_Object->SetActive(active);
			int layer;
			_ObjectRoot->QueryIntAttribute("Layer", &layer);
			_Object->SetLayer(layer);
			_Object->SetName(_ObjectRoot->Attribute("Name"));
			bool Static;
			_ObjectRoot->QueryBoolAttribute("Static", &Static);
			_Object->SetStatic(Static);
			return true;
		}

		bool FileIO::LoadTranform(XMLElement* _ObjectRoot, MEObject::Component*& _Object)
		{
			XMFLOAT3 pos, rot, scale;
			XMLElement* child = _ObjectRoot->FirstChildElement();
			child->QueryFloatAttribute("X", &pos.x);
			child->QueryFloatAttribute("Y", &pos.y);
			child->QueryFloatAttribute("Z", &pos.z);
			child = child->NextSiblingElement();
			child->QueryFloatAttribute("X", &rot.x);
			child->QueryFloatAttribute("Y", &rot.y);
			child->QueryFloatAttribute("Z", &rot.z);
			child = child->NextSiblingElement();
			child->QueryFloatAttribute("X", &scale.x);
			child->QueryFloatAttribute("Y", &scale.y);
			child->QueryFloatAttribute("Z", &scale.z);
			((MEObject::Transform*)_Object)->GetPosition() = pos;
			((MEObject::Transform*)_Object)->GetRotation() = rot;
			((MEObject::Transform*)_Object)->GetScale() = scale;
			_Object->SetName("Transform");
			return true;
		}

		bool FileIO::LoadMeshRenderer(XMLElement* _ObjectRoot, MEObject::Component*& _Object)
		{
			bool Enabled;
			_ObjectRoot->QueryBoolAttribute("Enabled", &Enabled);
			bool Skiined;
			_ObjectRoot->QueryBoolAttribute("Skinned", &Skiined);
			bool Opaque;
			_ObjectRoot->QueryBoolAttribute("Opaque", &Opaque);
			std::string VertexFileName;
			std::string DiffuseFileName;
			MERenderer::BlendStateManager::BStates BlendState;
			XMLElement* child = _ObjectRoot->FirstChildElement();
			if (child && strcmp(child->Value(), "VertexFileName") == 0)
				VertexFileName = child->Attribute("File");
			child = child->NextSiblingElement();
			if (child && strcmp(child->Value(), "DiffuseFileName") == 0)
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



			MERenderer::RenderMesh* tempMesh = renderContext->AddMesh(VertexFileName, Renderer::GetDevice(), Renderer::GetDeviceContext());
			MERenderer::RenderTexture* tempTex = tempMesh->AddTexture(DiffuseFileName, Renderer::GetDevice());
			MEObject::CompRenderer* comprend = (MEObject::CompRenderer*)_Object;
			tempTex->AddShape((MERenderer::RenderShape*)comprend);
			if (tempfilename == ".obj" || tempfilename == ".OBJ")
			{
				if (!MEFileIO::FileIO::LoadOBJ(tempMesh->m_sVertexFileName, tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, tempMesh->m_vIndicies, tempMesh->m_uiNumIndicies))
					return false;
			}
			else if (tempfilename == ".fbx" || tempfilename == ".FBX")
			{
				if (!MEFileIO::FileIO::LoadFBX(tempMesh->m_sVertexFileName, tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, tempMesh->m_vIndicies, tempMesh->m_uiNumIndicies, tempMesh->temp_Material, tempMesh->temp_Skeleton))
					return false;
				IndexBuffer::GetInstance()->AddIndicies(tempMesh->m_vIndicies, tempMesh->m_uiNumIndicies, Renderer::GetDevice(), Renderer::GetDeviceContext());
			}
			switch (tempMesh->m_eVertexFormat)
			{
			case MERenderer::eVERTEX_POS:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPositionBuffer().AddVerts((VERTEX_POS*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			case MERenderer::eVERTEX_POSCOLOR:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPositionColorBuffer().AddVerts((VERTEX_POSCOLOR*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			case MERenderer::eVERTEX_POSTEX:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPositionTexBuffer().AddVerts((VERTEX_POSTEX*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			case MERenderer::eVERTEX_POSNORMTEX:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosNormTexBuffer().AddVerts((VERTEX_POSNORMTEX*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			case MERenderer::eVERTEX_POSNORMTANTEX:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosNormTanTexBuffer().AddVerts((VERTEX_POSNORMTANTEX*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			case MERenderer::eVERTEX_POSBONEWEIGHT:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosBoneWeightBuffer().AddVerts((VERTEX_POSBONEWEIGHT*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			case MERenderer::eVERTEX_POSBONEWEIGHTNORMTEX:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosBoneWeightNormTexBuffer().AddVerts((VERTEX_POSBONEWEIGHTNORMTEX*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			case MERenderer::eVERTEX_POSBONEWEIGHTNORMTANTEX:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosBoneWeightNormTanTexBuffer().AddVerts((VERTEX_POSBONEWEIGHTNORMTANTEX*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			default:
				break;
			}
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
				tempTex->m_Material,
				Skeleton());
			_Object->SetName("MeshRenderer");
			return true;
		}

		bool FileIO::LoadSkinnedMeshRenderer(XMLElement* _ObjectRoot, MEObject::Component*& _Object)
		{
			bool Enabled;
			_ObjectRoot->QueryBoolAttribute("Enabled", &Enabled);
			bool Skinned;
			_ObjectRoot->QueryBoolAttribute("Skinned", &Skinned);
			bool Opaque;
			_ObjectRoot->QueryBoolAttribute("Opaque", &Opaque);
			std::string VertexFileName;
			std::string DiffuseFileName;
			MERenderer::BlendStateManager::BStates BlendState;
			XMLElement* child = _ObjectRoot->FirstChildElement();
			if (child && strcmp(child->Value(), "VertexFileName") == 0)
				VertexFileName = child->Attribute("File");
			child = child->NextSiblingElement();
			if (child && strcmp(child->Value(), "DiffuseFileName") == 0)
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
			MERenderer::RenderMesh* tempMesh = renderContext->AddMesh(VertexFileName, Renderer::GetDevice(), Renderer::GetDeviceContext());
			MERenderer::RenderTexture* tempTex = tempMesh->AddTexture(DiffuseFileName, Renderer::GetDevice());
			MEObject::CompRenderer* comprend = (MEObject::CompRenderer*)_Object;
			tempTex->AddShape((MERenderer::RenderShape*)comprend);
			if (tempfilename == ".obj" || tempfilename == ".OBJ")
			{
				if (!MEFileIO::FileIO::LoadOBJ(tempMesh->m_sVertexFileName, tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, tempMesh->m_vIndicies, tempMesh->m_uiNumIndicies))
					return false;
			}
			else if (tempfilename == ".fbx" || tempfilename == ".FBX")
			{
				if (!MEFileIO::FileIO::LoadFBX(tempMesh->m_sVertexFileName, tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, tempMesh->m_vIndicies, tempMesh->m_uiNumIndicies, tempMesh->temp_Material, tempMesh->temp_Skeleton))
					return false;
				IndexBuffer::GetInstance()->AddIndicies(tempMesh->m_vIndicies, tempMesh->m_uiNumIndicies, Renderer::GetDevice(), Renderer::GetDeviceContext());
			}
			switch (tempMesh->m_eVertexFormat)
			{
			case MERenderer::eVERTEX_POS:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPositionBuffer().AddVerts((VERTEX_POS*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			case MERenderer::eVERTEX_POSCOLOR:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPositionColorBuffer().AddVerts((VERTEX_POSCOLOR*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			case MERenderer::eVERTEX_POSTEX:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPositionTexBuffer().AddVerts((VERTEX_POSTEX*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			case MERenderer::eVERTEX_POSNORMTEX:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosNormTexBuffer().AddVerts((VERTEX_POSNORMTEX*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			case MERenderer::eVERTEX_POSNORMTANTEX:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosNormTanTexBuffer().AddVerts((VERTEX_POSNORMTANTEX*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			case MERenderer::eVERTEX_POSBONEWEIGHT:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosBoneWeightBuffer().AddVerts((VERTEX_POSBONEWEIGHT*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			case MERenderer::eVERTEX_POSBONEWEIGHTNORMTEX:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosBoneWeightNormTexBuffer().AddVerts((VERTEX_POSBONEWEIGHTNORMTEX*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			case MERenderer::eVERTEX_POSBONEWEIGHTNORMTANTEX:
				tempMesh->m_iBaseVertexLocation = (int)VertexBufferManager::GetInstance()->GetPosBoneWeightNormTanTexBuffer().AddVerts((VERTEX_POSBONEWEIGHTNORMTANTEX*)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			default:
				break;
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
				tempMesh->temp_Skeleton);
			_Object->SetName("MeshRenderer");
			return true;
		}

		bool FileIO::LoadCamera(XMLElement* _ObjectRoot, MEObject::Component*& _Object)
		{
			bool Enabled = _ObjectRoot->BoolAttribute("Enabled");
			XMLElement* child = _ObjectRoot->FirstChildElement();
			if (strcmp(child->Name(), "Skybox") == 0)
			{	
				const char* text = child->Attribute("TextureName");
				size_t origsize = strlen(text) + 1;
				const size_t newsize = 100;
				size_t convertedChars = 0;
				wchar_t wText[newsize];
				mbstowcs_s(&convertedChars, wText, origsize, text, _TRUNCATE);
				((Camera*)_Object)->GetSkybox()->Load(Renderer::GetDevice(), Renderer::GetDeviceContext(), wText);
			}
			else
			{

			}
			_Object->SetName("Camera");
			Renderer::GetCameras().push_back((Camera*)_Object);
			return true;
		}

		bool FileIO::LoadDebugCamera(XMLElement* _ObjectRoot)
		{
			XMLElement* child = _ObjectRoot->FirstChildElement();
			if (strcmp(child->Name(), "Skybox") == 0)
			{
				const char* text = child->Attribute("TextureName");
				size_t origsize = strlen(text) + 1;
				const size_t newsize = 100;
				size_t convertedChars = 0;
				wchar_t wText[newsize];
				mbstowcs_s(&convertedChars, wText, origsize, text, _TRUNCATE);
				((Camera*)DebugCamera::GetInstance())->GetSkybox()->Load(Renderer::GetDevice(), Renderer::GetDeviceContext(), wText);
			}
			else
			{

			}
			Renderer::SetDebugCamera(DebugCamera::GetInstance());
			return true;
		}
	}
}