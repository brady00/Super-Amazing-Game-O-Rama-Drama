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
#include "Behaviour\Skybox.h"
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

		bool FileIO::LoadFBX(std::string _FileName, MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies, Material*& _Material, Skeleton& _Skeleton)
		{
			char* File = new char[256];
			_splitpath_s(_FileName.c_str(), NULL, 0, NULL, 0, File, 256, NULL, 0);
			std::string finalPath("Assets/Binaries/" + std::string(File) + ".Bfbx");
			std::string finalSkelPath("Assets/Binaries/" + std::string(File) + ".Bskel");
			std::string AssetPath("Assets/Models/" + std::string(File) + ".fbx");
#pragma region Binary Loading
			std::string filepart;
			std::ifstream FileIn;
			FileIn.open(finalPath, std::ios_base::binary);
			bool BinarySkip = false;
			if (FileIn.is_open())
			{
				FileIn.read((char*)& _NumVerticies, sizeof(unsigned int));
				_Verticies = new MERenderer::VERTEX_POSBONEWEIGHTNORMTANTEX[_NumVerticies];
				for (unsigned int i = 0; i < _NumVerticies; i++)
				{
					FileIn.read((char*)&(_Verticies[i].position), sizeof(Float3));
					FileIn.read((char*)&(_Verticies[i].normal), sizeof(Float3));
					FileIn.read((char*)&(_Verticies[i].texcoord), sizeof(DirectX::XMFLOAT2));
					_Verticies[i].texcoord.x = 1 - _Verticies[i].texcoord.x;
					FileIn.read((char*)&(_Verticies[i].bones), sizeof(DirectX::XMINT4));
					FileIn.read((char*)&(_Verticies[i].determinant), sizeof(float));
					FileIn.read((char*)&(_Verticies[i].tangent), sizeof(Float3));
					FileIn.read((char*)&(_Verticies[i].weights), sizeof(DirectX::XMFLOAT4));
					FileIn.read((char*)&(_Verticies[i].binormal), sizeof(Float3));
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
				_Verticies[i] = Loader.m_Verticies[i];
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
					out.write((const char*)&(_Verticies[i].position), sizeof(Float3));
					out.write((const char*)&(_Verticies[i].normal), sizeof(Float3));
					out.write((const char*)&(_Verticies[i].texcoord), sizeof(DirectX::XMFLOAT2));
					out.write((const char*)&(_Verticies[i].bones), sizeof(DirectX::XMINT4));
					out.write((const char*)&(_Verticies[i].determinant), sizeof(float));
					out.write((const char*)&(_Verticies[i].tangent), sizeof(Float3));
					out.write((const char*)&(_Verticies[i].weights), sizeof(DirectX::XMFLOAT4));
					out.write((const char*)&(_Verticies[i].binormal), sizeof(Float3));
				}
				out.write((const char*)& _NumIndicies, sizeof(unsigned int));
				for (unsigned int i = 0; i < _NumIndicies; i++)
					out.write((const char*)&_Indicies[i], sizeof(unsigned int));
				unsigned int length = (unsigned int)_Material->mDiffuseMapName.length() + 1;
				out.write((const char*)&length, sizeof(unsigned int));
				if (length > 1)
					out.write(_Material->mDiffuseMapName.c_str(), length);
				length = (unsigned int)_Material->mEmissiveMapName.length() + 1;
				out.write((const char*)&length, sizeof(unsigned int));
				if (length > 1)
					out.write(_Material->mEmissiveMapName.c_str(), length);
				length = (unsigned int)_Material->mGlossMapName.length() + 1;
				out.write((const char*)&length, sizeof(unsigned int));
				if (length > 1)
					out.write(_Material->mGlossMapName.c_str(), length);
				length = (unsigned int)_Material->mNormalMapName.length() + 1;
				out.write((const char*)&length, sizeof(unsigned int));
				if (length > 1)
					out.write(_Material->mNormalMapName.c_str(), length);
				length = (unsigned int)_Material->mSpecularMapName.length() + 1;
				out.write((const char*)&length, sizeof(unsigned int));
				if (length > 1)
					out.write(_Material->mSpecularMapName.c_str(), length);
				out.close();
			}
			else
				return false;
			string SkelFile;
			SkelFile.append(finalPath.c_str(), finalPath.length() - 5);
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

		bool FileIO::LoadOBJ(std::string _FileName, MERenderer::VERTEX_POSNORMTEX*& _Verticies, unsigned int& _NumVerticies, unsigned int*& _Indicies, unsigned int& _NumIndicies)
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
					FileIn.read((char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].position), sizeof(Float3));
					FileIn.read((char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].normal), sizeof(Float3));
					FileIn.read((char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].texcoord), sizeof(DirectX::XMFLOAT2));
				}
				return true;
			}
			string Xcopy = "\"xcopy " + _FileName + " " + AssetPath;
			system(Xcopy.c_str());
			delete File;
			std::vector<Float3> temp_vertices;
			std::vector<XMFLOAT2> temp_uvs;
			std::vector<Float3> temp_normals;
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
					Float3 vertex;
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
					Float3 vertexn;
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
					out.write((const char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].position), sizeof(Float3));
					out.write((const char*)&(((MERenderer::VERTEX_POSNORMTEX*)_Verticies)[i].normal), sizeof(Float3));
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

		bool FileIO::SaveScene(std::string _FileName, std::vector<MEObject::GameObject*>& _GameObjects)
		{
			tinyxml2::XMLDocument doc;
			XMLElement* root = doc.NewElement("MonkeyEngineScene");
			doc.InsertFirstChild(root);
			XMLElement* prevElem = doc.NewElement("DebugCamera");
			root->InsertFirstChild(prevElem);
			SaveDebugCamera(prevElem, doc);
			for (unsigned int i = 0; i < _GameObjects.size(); i++)
			{
				XMLElement* elem = doc.NewElement("GameObject");
				root->InsertAfterChild(prevElem, elem);
				SaveGameObject(elem, doc, _GameObjects[i]);
				prevElem = elem;
			}
			doc.SaveFile(_FileName.c_str());
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

		bool FileIO::SaveGameObject(XMLElement* _ObjectRoot, tinyxml2::XMLDocument& doc, MEObject::GameObject* _Object)
		{
			_ObjectRoot->SetAttribute("Name", _Object->GetCharName());
			_ObjectRoot->SetAttribute("Static", _Object->GetStatic());
			_ObjectRoot->SetAttribute("Active", _Object->GetActive());
			_ObjectRoot->SetAttribute("Layer", _Object->GetLayer());
			XMLElement* prevElem = doc.NewElement("Transform");
			_ObjectRoot->InsertFirstChild(prevElem);
			SaveTranform(prevElem, doc, _Object->m_pTransform);
			for (unsigned int i = 0; i < _Object->eNumComponents; i++)
			{
				for (unsigned int j = 0; j < _Object->m_vComponents[i].size(); j++)
				{
					switch (i)
					{
					case GameObject::COMPONENT_ID::eMeshRenderer:
					{
						XMLElement* Elem = doc.NewElement("MeshRenderer");
						_ObjectRoot->InsertAfterChild(prevElem, Elem);
						SaveMeshRenderer(Elem, doc, _Object->m_vComponents[i][j]);
						prevElem = Elem;
						break;
					}
					case GameObject::COMPONENT_ID::eSkinnedMeshRenderer:
					{
						XMLElement* Elem = doc.NewElement("SkinnedMeshRenderer");
						_ObjectRoot->InsertAfterChild(prevElem, Elem);
						SaveSkinnedMeshRenderer(Elem, doc, _Object->m_vComponents[i][j]);
						prevElem = Elem;
						break;
					}
					case GameObject::COMPONENT_ID::eCamera:
					{
						XMLElement* Elem = doc.NewElement("Camera");
						_ObjectRoot->InsertAfterChild(prevElem, Elem);
						SaveCamera(Elem, doc, _Object->m_vComponents[i][j]);
						prevElem = Elem;
						break;
					}
					default:
						break;
					}
				}
			}
			return true;
		}

		bool FileIO::LoadTranform(XMLElement* _ObjectRoot, MEObject::Component*& _Object)
		{
			Float3 pos, rot, scale;
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

		bool FileIO::SaveTranform(XMLElement* _ObjectRoot, tinyxml2::XMLDocument& doc, MEObject::Component* _Object)
		{
			XMLElement* Position = doc.NewElement("Position");
			Position->SetAttribute("X", ((Transform*)_Object)->GetPosition().x);
			Position->SetAttribute("Y", ((Transform*)_Object)->GetPosition().y);
			Position->SetAttribute("Z", ((Transform*)_Object)->GetPosition().z);
			XMLElement* Rotation = doc.NewElement("Rotation");
			Rotation->SetAttribute("X", ((Transform*)_Object)->GetRotation().x);
			Rotation->SetAttribute("Y", ((Transform*)_Object)->GetRotation().y);
			Rotation->SetAttribute("Z", ((Transform*)_Object)->GetRotation().z);
			XMLElement* Scale = doc.NewElement("Scale");
			Scale->SetAttribute("X", ((Transform*)_Object)->GetScale().x);
			Scale->SetAttribute("Y", ((Transform*)_Object)->GetScale().y);
			Scale->SetAttribute("Z", ((Transform*)_Object)->GetScale().z);
			_ObjectRoot->InsertFirstChild(Position);
			_ObjectRoot->InsertAfterChild(Position, Rotation);
			_ObjectRoot->InsertAfterChild(Rotation, Scale);
			return true;
		}

		bool FileIO::LoadMeshRenderer(XMLElement* _ObjectRoot, MEObject::Component*& _Object)
		{
			bool Enabled;
			_ObjectRoot->QueryBoolAttribute("Enabled", &Enabled);
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
				if (!MEFileIO::FileIO::LoadOBJ(tempMesh->m_sVertexFileName, (VERTEX_POSNORMTEX*&)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, tempMesh->m_vIndicies, tempMesh->m_uiNumIndicies))
					return false;
			}
			else if (tempfilename == ".fbx" || tempfilename == ".FBX")
			{
				if (!MEFileIO::FileIO::LoadFBX(tempMesh->m_sVertexFileName, (VERTEX_POSBONEWEIGHTNORMTANTEX*&)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, tempMesh->m_vIndicies, tempMesh->m_uiNumIndicies, tempMesh->temp_Material, tempMesh->temp_Skeleton))
					return false;
				IndexBuffer::GetInstance()->AddIndicies(tempMesh->m_vIndicies, tempMesh->m_uiNumIndicies, Renderer::GetDevice(), Renderer::GetDeviceContext());
			}
			LoadVertexBuffer(tempMesh->m_eVertexFormat, tempMesh, tempTex->m_Material);
			((MEObject::MeshRenderer*)_Object)->Load(&renderContext->m_BlendState,
				&renderContext->m_RasterState,
				&renderContext->m_DSState,
				tempMesh->m_vVerticies,
				&tempMesh->m_uiNumVerticies,
				tempMesh->m_vIndicies,
				&tempMesh->m_uiNumIndicies,
				&tempMesh->m_uiStartIndexLocation,
				&tempMesh->m_iBaseVertexLocationGame,
				&tempMesh->m_sVertexFileName,
				&tempMesh->m_eVertexFormat,
				tempTex->m_Material,
				Skeleton());
			_Object->SetName("MeshRenderer");
			return true;
		}

		bool FileIO::SaveMeshRenderer(XMLElement* _ObjectRoot, tinyxml2::XMLDocument& doc, MEObject::Component* _Object)
		{
			_ObjectRoot->SetAttribute("Enabled", ((MeshRenderer*)_Object)->GetEnabled());
			_ObjectRoot->SetAttribute("Opaque", (*((MeshRenderer*)_Object)->m_BlendState) != BlendStateManager::BStates::BS_Alpha);
			XMLElement* Vertex = doc.NewElement("VertexFileName");
			Vertex->SetAttribute("File", ((MeshRenderer*)_Object)->GetVertexFileName().c_str());
			XMLElement* Diffuse = doc.NewElement("DiffuseFileName");
			Diffuse->SetAttribute("File", ((MeshRenderer*)_Object)->GetMaterial().mDiffuseMapName.c_str());
			_ObjectRoot->InsertFirstChild(Vertex);
			_ObjectRoot->InsertAfterChild(Vertex, Diffuse);
			return true;
		}

		bool FileIO::LoadSkinnedMeshRenderer(XMLElement* _ObjectRoot, MEObject::Component*& _Object)
		{
			bool Enabled;
			_ObjectRoot->QueryBoolAttribute("Enabled", &Enabled);
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
				renderContext = MERenderer::Renderer::AddNewTransparentContext(renderContext);
			MERenderer::RenderMesh* tempMesh = renderContext->AddMesh(VertexFileName, Renderer::GetDevice(), Renderer::GetDeviceContext());
			MERenderer::RenderTexture* tempTex = tempMesh->AddTexture(DiffuseFileName, Renderer::GetDevice());
			MEObject::CompRenderer* comprend = (MEObject::CompRenderer*)_Object;
			tempTex->AddShape((MERenderer::RenderShape*)comprend);
			if (tempfilename == ".obj" || tempfilename == ".OBJ")
			{
				if (!MEFileIO::FileIO::LoadOBJ(tempMesh->m_sVertexFileName, (VERTEX_POSNORMTEX*&)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, tempMesh->m_vIndicies, tempMesh->m_uiNumIndicies))
					return false;
			}
			else if (tempfilename == ".fbx" || tempfilename == ".FBX")
			{
				if (!MEFileIO::FileIO::LoadFBX(tempMesh->m_sVertexFileName, (VERTEX_POSBONEWEIGHTNORMTANTEX*&)tempMesh->m_vVerticies, tempMesh->m_uiNumVerticies, tempMesh->m_vIndicies, tempMesh->m_uiNumIndicies, tempMesh->temp_Material, tempMesh->temp_Skeleton))
					return false;
				IndexBuffer::GetInstance()->AddIndicies(tempMesh->m_vIndicies, tempMesh->m_uiNumIndicies, Renderer::GetDevice(), Renderer::GetDeviceContext());
			}
			LoadVertexBuffer(tempMesh->m_eVertexFormat, tempMesh, tempTex->m_Material);
			((MEObject::SkinnedMeshRenderer*)_Object)->Load(&renderContext->m_BlendState,
				&renderContext->m_RasterState,
				&renderContext->m_DSState,
				tempMesh->m_vVerticies,
				&tempMesh->m_uiNumVerticies,
				tempMesh->m_vIndicies,
				&tempMesh->m_uiNumIndicies,
				&tempMesh->m_uiStartIndexLocation,
				&tempMesh->m_iBaseVertexLocationGame,
				&tempMesh->m_sVertexFileName,
				&tempMesh->m_eVertexFormat,
				tempTex->m_Material,
				tempMesh->temp_Skeleton);
			_Object->SetName("MeshRenderer");
			return true;
		}

		bool FileIO::SaveSkinnedMeshRenderer(XMLElement* _ObjectRoot, tinyxml2::XMLDocument& doc, MEObject::Component* _Object)
		{
			_ObjectRoot->SetAttribute("Enabled", ((SkinnedMeshRenderer*)_Object)->GetEnabled());
			_ObjectRoot->SetAttribute("Opaque", (*((SkinnedMeshRenderer*)_Object)->m_BlendState) != BlendStateManager::BStates::BS_Alpha);
			XMLElement* Vertex = doc.NewElement("VertexFileName");
			Vertex->SetAttribute("File", ((SkinnedMeshRenderer*)_Object)->GetVertexFileName().c_str());
			XMLElement* Diffuse = doc.NewElement("DiffuseFileName");
			Diffuse->SetAttribute("File", ((SkinnedMeshRenderer*)_Object)->GetMaterial().mDiffuseMapName.c_str());
			_ObjectRoot->InsertFirstChild(Vertex);
			_ObjectRoot->InsertAfterChild(Vertex, Diffuse);
			return true;
		}

		bool FileIO::LoadCamera(XMLElement* _ObjectRoot, MEObject::Component*& _Object)
		{
			bool Enabled = _ObjectRoot->BoolAttribute("Enabled");
			XMLElement* child = _ObjectRoot->FirstChildElement();
			if (strcmp(child->Name(), "Skybox") == 0)
				LoadSkybox(child, (Component*)((Camera*)_Object)->GetSkybox());
			else
			{

			}
			_Object->SetName("Camera");
			((Camera*)_Object)->Load(Renderer::GetDevice(), Renderer::GetDeviceContext(), (float)Renderer::GetScreenWidth(), (float)Renderer::GetScreenHeight());
			Renderer::GetCameras().push_back((Camera*)_Object);
			return true;
		}

		bool FileIO::SaveCamera(XMLElement* _ObjectRoot, tinyxml2::XMLDocument& doc, MEObject::Component* _Object)
		{
			XMLElement* skybox = doc.NewElement("Skybox");
			_ObjectRoot->InsertFirstChild(skybox);
			SaveSkybox(skybox, doc, ((Camera*)_Object)->GetSkybox());
			return true;
		}

		bool FileIO::LoadDebugCamera(XMLElement* _ObjectRoot)
		{
			XMLElement* child = _ObjectRoot->FirstChildElement();
			if (strcmp(child->Name(), "Skybox") == 0)
				LoadSkybox(child, (Component*)DebugCamera::GetInstance()->GetSkybox());
			else
			{

			}
			Renderer::SetDebugCamera(DebugCamera::GetInstance());
			return true;
		}

		bool FileIO::SaveDebugCamera(XMLElement* _ObjectRoot, tinyxml2::XMLDocument& doc)
		{
			XMLElement* skybox = doc.NewElement("Skybox");
			_ObjectRoot->InsertFirstChild(skybox);
			SaveSkybox(skybox, doc, DebugCamera::GetInstance()->GetSkybox());
			return true;
		}

		bool FileIO::LoadSkybox(XMLElement* _ObjectRoot, MEObject::Component* _Object)
		{
			XMLElement* material = _ObjectRoot->FirstChildElement();
			XMLElement* child = material->FirstChildElement();
			Material temp;
			const char* text;
			const size_t newsize = 100;
			wchar_t wText[newsize];
			if (strcmp(child->Name(), "TextureName") == 0)
			{
				text = child->Attribute("File");
				temp.mDiffuseMapName = std::string(text);
				child = child->NextSiblingElement();
				size_t origsize = strlen(temp.mDiffuseMapName.c_str()) + 1;
				size_t convertedChars = 0;
				mbstowcs_s(&convertedChars, wText, origsize, temp.mDiffuseMapName.c_str(), _TRUNCATE);
			}
			if (strcmp(child->Name(), "Color") == 0)
			{
				temp.Color.x = child->FloatAttribute("R");
				temp.Color.y = child->FloatAttribute("G");
				temp.Color.z = child->FloatAttribute("B");
				temp.Color.w = child->FloatAttribute("A");
			}

			((MEObject::Skybox*)_Object)->Load(Renderer::GetDevice(), Renderer::GetDeviceContext(), wText, temp);
			return true;
		}

		bool FileIO::SaveSkybox(XMLElement* _ObjectRoot, tinyxml2::XMLDocument& doc, MEObject::Component* _Object)
		{
			XMLElement* material = doc.NewElement("Material");
			_ObjectRoot->InsertFirstChild(material);
			XMLElement* texture = doc.NewElement("TextureName");
			texture->SetAttribute("File", ((MEObject::Skybox*)_Object)->m_Material.mDiffuseMapName.c_str());
			XMLElement* color = doc.NewElement("Color");
			color->SetAttribute("R", ((MEObject::Skybox*)_Object)->m_Material.Color.x);
			color->SetAttribute("G", ((MEObject::Skybox*)_Object)->m_Material.Color.y);
			color->SetAttribute("B", ((MEObject::Skybox*)_Object)->m_Material.Color.z);
			color->SetAttribute("A", ((MEObject::Skybox*)_Object)->m_Material.Color.w);
			material->InsertFirstChild(texture);
			material->InsertAfterChild(texture, color);
			return true;
		}

		bool FileIO::LoadVertexBuffer(VertexFormat format, MERenderer::RenderMesh* mesh, Material* material)
		{
			switch (format)
			{
			case MERenderer::eVERTEX_POS:
			{
				mesh->m_iBaseVertexLocationGame = (int)VertexBufferManager::GetInstance()->GetPositionBuffer().AddVerts((VERTEX_POS*)mesh->m_vVerticies, mesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				VERTEX_POSCOLOR* temp = new VERTEX_POSCOLOR[mesh->m_uiNumVerticies];
				for (unsigned int i = 0; i < mesh->m_uiNumVerticies; i++)
				{
					temp[i].position = ((VERTEX_POS*)mesh->m_vVerticies)[i].position;
					temp[i].color = material->Color;
				}
				mesh->m_iBaseVertexLocationEditor = (int)VertexBufferManager::GetInstance()->GetPositionColorBuffer().AddVerts((VERTEX_POSCOLOR*)mesh->m_vVerticies, mesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			}
			case MERenderer::eVERTEX_POSTEX:
			{
				mesh->m_iBaseVertexLocationGame = (int)VertexBufferManager::GetInstance()->GetPositionTexBuffer().AddVerts((VERTEX_POSTEX*)mesh->m_vVerticies, mesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				VERTEX_POSTEXCOLOR* temp = new VERTEX_POSTEXCOLOR[mesh->m_uiNumVerticies];
				for (unsigned int i = 0; i < mesh->m_uiNumVerticies; i++)
				{
					temp[i].position = ((VERTEX_POSTEX*)mesh->m_vVerticies)[i].position;
					temp[i].texcoord = ((VERTEX_POSTEX*)mesh->m_vVerticies)[i].texcoord;
					temp[i].color = material->Color;
				}
				mesh->m_iBaseVertexLocationEditor = (int)VertexBufferManager::GetInstance()->GetPositionTexColorBuffer().AddVerts((VERTEX_POSTEXCOLOR*)mesh->m_vVerticies, mesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			}
			case MERenderer::eVERTEX_POSNORMTEX:
			{
				mesh->m_iBaseVertexLocationGame = (int)VertexBufferManager::GetInstance()->GetPosNormTexBuffer().AddVerts((VERTEX_POSNORMTEX*)mesh->m_vVerticies, mesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				VERTEX_POSNORMTEXCOLOR* temp = new VERTEX_POSNORMTEXCOLOR[mesh->m_uiNumVerticies];
				for (unsigned int i = 0; i < mesh->m_uiNumVerticies; i++)
				{
					temp[i].position = ((VERTEX_POSNORMTEX*)mesh->m_vVerticies)[i].position;
					temp[i].texcoord = ((VERTEX_POSNORMTEX*)mesh->m_vVerticies)[i].texcoord;
					temp[i].normal = ((VERTEX_POSNORMTEX*)mesh->m_vVerticies)[i].normal;
					temp[i].color = material->Color;
				}
				mesh->m_iBaseVertexLocationEditor = (int)VertexBufferManager::GetInstance()->GetPosNormTexColorBuffer().AddVerts((VERTEX_POSNORMTEXCOLOR*)mesh->m_vVerticies, mesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			}
			case MERenderer::eVERTEX_POSNORMTANTEX:
			{
				mesh->m_iBaseVertexLocationGame = (int)VertexBufferManager::GetInstance()->GetPosNormTanTexBuffer().AddVerts((VERTEX_POSNORMTANTEX*)mesh->m_vVerticies, mesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			}
			case MERenderer::eVERTEX_POSBONEWEIGHT:
			{
				mesh->m_iBaseVertexLocationGame = (int)VertexBufferManager::GetInstance()->GetPosBoneWeightBuffer().AddVerts((VERTEX_POSBONEWEIGHT*)mesh->m_vVerticies, mesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			}
			case MERenderer::eVERTEX_POSBONEWEIGHTNORMTEX:
			{
				mesh->m_iBaseVertexLocationGame = (int)VertexBufferManager::GetInstance()->GetPosBoneWeightNormTexBuffer().AddVerts((VERTEX_POSBONEWEIGHTNORMTEX*)mesh->m_vVerticies, mesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			}
			case MERenderer::eVERTEX_POSBONEWEIGHTNORMTANTEX:
			{
				mesh->m_iBaseVertexLocationGame = (int)VertexBufferManager::GetInstance()->GetPosBoneWeightNormTanTexBuffer().AddVerts((VERTEX_POSBONEWEIGHTNORMTANTEX*)mesh->m_vVerticies, mesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR* temp = new VERTEX_POSBONEWEIGHTNORMTANTEXCOLOR[mesh->m_uiNumVerticies];
				for (unsigned int i = 0; i < mesh->m_uiNumVerticies; i++)
				{
					temp[i].position = ((VERTEX_POSBONEWEIGHTNORMTANTEX*)mesh->m_vVerticies)[i].position;
					temp[i].texcoord = ((VERTEX_POSBONEWEIGHTNORMTANTEX*)mesh->m_vVerticies)[i].texcoord;
					temp[i].normal = ((VERTEX_POSBONEWEIGHTNORMTANTEX*)mesh->m_vVerticies)[i].normal;
					temp[i].bones = ((VERTEX_POSBONEWEIGHTNORMTANTEX*)mesh->m_vVerticies)[i].bones;
					temp[i].weights = ((VERTEX_POSBONEWEIGHTNORMTANTEX*)mesh->m_vVerticies)[i].weights;
					temp[i].tangent = ((VERTEX_POSBONEWEIGHTNORMTANTEX*)mesh->m_vVerticies)[i].tangent;
					temp[i].binormal = ((VERTEX_POSBONEWEIGHTNORMTANTEX*)mesh->m_vVerticies)[i].binormal;
					temp[i].determinant = ((VERTEX_POSBONEWEIGHTNORMTANTEX*)mesh->m_vVerticies)[i].determinant;
					temp[i].tangent = ((VERTEX_POSBONEWEIGHTNORMTANTEX*)mesh->m_vVerticies)[i].tangent;
					temp[i].color = material->Color;
				}
				mesh->m_iBaseVertexLocationEditor = (int)VertexBufferManager::GetInstance()->GetPosBoneWeightNormTanTexColorBuffer().AddVerts(temp, mesh->m_uiNumVerticies, Renderer::GetDevice(), Renderer::GetDeviceContext());
				break;
			}
			default:
				break;
			}
			return true;
		}
	}
}