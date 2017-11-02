#include "FBXLoader.h"
#include "RenderStructures.h"
#include <unordered_map>
namespace MonkeyEngine
{
	using namespace MERenderer;
	namespace MEFileIO
	{
#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(pManager->GetIOSettings()))
#endif
		FBXLoader::FBXLoader()
		{
		}


		FBXLoader::~FBXLoader()
		{
		}

		bool FBXLoader::LoadFBX(std::string _FileName)
		{
			FbxManager* lSdkManager = NULL;
			FbxScene* lScene = NULL;
			bool lResult;

			// Prepare the FBX SDK.
			if (!InitializeSdkObjects(lSdkManager, lScene))
				return false;
			// Load the scene.

			// The example can take a FBX file as an argument.
			FbxString lFilePath(_FileName.c_str());

			if (lFilePath.IsEmpty())
				return false;
			else
				lResult = LoadScene(lSdkManager, lScene, lFilePath.Buffer());

			if (!lResult)
				return false;
			else
			{
				DisplayContent(lScene);
				DisplayAnimation(lScene);
			}

			// Destroy all objects created by the FBX SDK.
			DestroySdkObjects(lSdkManager, lResult);

			return true;
		}

		bool FBXLoader::InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene)
		{
			//The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
			pManager = FbxManager::Create();
			if (!pManager)
				return false;

			//Create an IOSettings object. This object holds all import/export settings.
			FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
			pManager->SetIOSettings(ios);

			//Create an FBX scene. This object holds most objects imported/exported from/to files.
			pScene = FbxScene::Create(pManager, "My Scene");
			if (!pScene)
				return false;
			return true;
		}

		bool FBXLoader::LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename)
		{
			bool lStatus;
			// Create an importer.
			FbxImporter* lImporter = FbxImporter::Create(pManager, "");

			// Initialize the importer by providing a filename.
			const bool lImportStatus = lImporter->Initialize(pFilename, -1, pManager->GetIOSettings());

			if (!lImportStatus)
				return false;

			if (lImporter->IsFBX())
			{
				// Set the import states. By default, the import states are always set to 
				// true. The code below shows how to change these states.
				IOS_REF.SetBoolProp(IMP_FBX_MATERIAL, true);
				IOS_REF.SetBoolProp(IMP_FBX_TEXTURE, false);
				IOS_REF.SetBoolProp(IMP_FBX_LINK, true);
				IOS_REF.SetBoolProp(IMP_FBX_SHAPE, true);
				IOS_REF.SetBoolProp(IMP_FBX_GOBO, false);
				IOS_REF.SetBoolProp(IMP_FBX_ANIMATION, true);
				IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, false);
			}

			// Import the scene.
			lStatus = lImporter->Import(pScene);

			// Destroy the importer.
			lImporter->Destroy();

			return lStatus;
		}
		void FBXLoader::DestroySdkObjects(FbxManager* pManager, bool pExitStatus)
		{
			//Delete the FBX Manager. All the objects that have been allocated using the FBX Manager and that haven't been explicitly destroyed are also automatically destroyed.
			if (pManager)
				pManager->Destroy();
		}

		void FBXLoader::DisplayContent(FbxScene* pScene)
		{
			FbxNode* lNode = pScene->GetRootNode();

			if (lNode)
			{
				for (int i = 0; i < lNode->GetChildCount(); i++)
				{
					DisplayContent(lNode->GetChild(i), 0);
				}
			}
		}

		void FBXLoader::DisplayContent(FbxNode* pNode, int depth)
		{
			FbxNodeAttribute::EType lAttributeType;

			if (pNode->GetNodeAttribute())
			{
				lAttributeType = pNode->GetNodeAttribute()->GetAttributeType();

				switch (lAttributeType)
				{
				default:
					break;
				case FbxNodeAttribute::eSkeleton:
				{
					Bone temp;
					temp.mParentIndex = depth - 1;
					BoneToNode[(unsigned int)m_Skeleton.mJoints.size()] = pNode;
					m_Skeleton.mJoints.push_back(temp);
					break;
				}
				case FbxNodeAttribute::eMesh:
					DisplayMesh(pNode);
					break;
				}
				for (int i = 0; i < pNode->GetChildCount(); i++)
				{
					DisplayContent(pNode->GetChild(i), depth + 1);
				}
			}
		}

		void FBXLoader::DisplayMesh(FbxNode* pNode)
		{
			FbxMesh* lMesh = (FbxMesh*)pNode->GetNodeAttribute();

			DisplayControlsPoints(lMesh);
			DisplayPolygons(lMesh);
			//DisplayMaterialMapping(lMesh);  This is for mulitple textures affecting one mesh I think
			DisplayMaterial(lMesh);
			DisplayLink(lMesh);
		}

		void FBXLoader::DisplayControlsPoints(FbxMesh* pMesh)
		{
			int lControlPointsCount = pMesh->GetControlPointsCount();
			FbxVector4* lControlPoints = pMesh->GetControlPoints();

			startingIndex = (int)m_Verticies.size();
			m_Verticies.resize(lControlPointsCount + m_Verticies.size());
			for (int i = 0; i < lControlPointsCount; i++)
			{
				m_Verticies[i + startingIndex].position.x = (float)lControlPoints[i].mData[0];
				m_Verticies[i + startingIndex].position.y = (float)lControlPoints[i].mData[1];
				m_Verticies[i + startingIndex].position.z = (float)lControlPoints[i].mData[2];
			}

		}

		void FBXLoader::DisplayPolygons(FbxMesh* pMesh) //adjust to add in square loading Brady
		{
			int lPolygonCount = pMesh->GetPolygonCount();

			int vertexId = 0;
			m_Indices.reserve(lPolygonCount * 4);
			for (int i = 0; i < lPolygonCount; i++)
			{
				int lPolygonSize = pMesh->GetPolygonSize(i);

				for (int j = 0; j < /*lPolygonSize*/3; j++)
				{
					int lControlPointIndex = pMesh->GetPolygonVertex(i, j) + startingIndex;
					m_Indices.push_back(lControlPointIndex);
					for (int l = 0; l < pMesh->GetElementUVCount(); ++l)
					{
						FbxGeometryElementUV* leUV = pMesh->GetElementUV(l);
						switch (leUV->GetMappingMode())
						{
						default:
							break;
						case FbxGeometryElement::eByControlPoint:
							switch (leUV->GetReferenceMode())
							{
							case FbxGeometryElement::eDirect:
							{
								FbxVector2 uv = leUV->GetDirectArray().GetAt(lControlPointIndex);
								m_Verticies[lControlPointIndex].texcoord.x = (float)uv.mData[0];
								m_Verticies[lControlPointIndex].texcoord.y = (float)uv.mData[1];
								break;
							}
							case FbxGeometryElement::eIndexToDirect:
							{
								int id = leUV->GetIndexArray().GetAt(lControlPointIndex);
								FbxVector2 uv = leUV->GetDirectArray().GetAt(id);
								m_Verticies[lControlPointIndex].texcoord.x = (float)uv.mData[0];
								m_Verticies[lControlPointIndex].texcoord.y = (float)uv.mData[1];
								break;
							}
							break;
							default:
								break; // other reference modes not shown here!
							}
							break;

						case FbxGeometryElement::eByPolygonVertex:
						{
							int lTextureUVIndex = pMesh->GetTextureUVIndex(i, j);
							switch (leUV->GetReferenceMode())
							{
							case FbxGeometryElement::eDirect:
							case FbxGeometryElement::eIndexToDirect:
							{
								FbxVector2 uv = leUV->GetDirectArray().GetAt(lTextureUVIndex);
								m_Verticies[lControlPointIndex].texcoord.x = (float)uv.mData[0];
								m_Verticies[lControlPointIndex].texcoord.y = (float)uv.mData[1];
								break;
							}
							default:
								break; // other reference modes not shown here!
							}
						}
						break;
						}
					}
					for (int l = 0; l < pMesh->GetElementNormalCount(); ++l)
					{
						FbxGeometryElementNormal* leNormal = pMesh->GetElementNormal(l);

						if (leNormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
						{
							switch (leNormal->GetReferenceMode())
							{
							case FbxGeometryElement::eDirect:
							{
								FbxVector4 normal = leNormal->GetDirectArray().GetAt(vertexId);
								m_Verticies[lControlPointIndex].normal.x = (float)normal.mData[0];
								m_Verticies[lControlPointIndex].normal.y = (float)normal.mData[1];
								m_Verticies[lControlPointIndex].normal.z = (float)normal.mData[2];
								break;
							}
							case FbxGeometryElement::eIndexToDirect:
							{
								int id = leNormal->GetIndexArray().GetAt(vertexId);
								FbxVector4 normal = leNormal->GetDirectArray().GetAt(id);
								m_Verticies[lControlPointIndex].normal.x = (float)normal.mData[0];
								m_Verticies[lControlPointIndex].normal.y = (float)normal.mData[1];
								m_Verticies[lControlPointIndex].normal.z = (float)normal.mData[2];
								break;
							}
							break;
							default:
								break; // other reference modes not shown here!
							}
						}

					}
					for (int l = 0; l < pMesh->GetElementTangentCount(); ++l)
					{
						FbxGeometryElementTangent* leTangent = pMesh->GetElementTangent(l);

						if (leTangent->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
						{
							switch (leTangent->GetReferenceMode())
							{
							case FbxGeometryElement::eDirect:
							{
								FbxVector4 tangent = leTangent->GetDirectArray().GetAt(vertexId);
								m_Verticies[lControlPointIndex].tangent.x = (float)tangent.mData[0];
								m_Verticies[lControlPointIndex].tangent.y = (float)tangent.mData[1];
								m_Verticies[lControlPointIndex].tangent.z = (float)tangent.mData[2];
								break;
							}
							case FbxGeometryElement::eIndexToDirect:
							{
								int id = leTangent->GetIndexArray().GetAt(vertexId);
								FbxVector4 tangent = leTangent->GetDirectArray().GetAt(id);
								m_Verticies[lControlPointIndex].tangent.x = (float)tangent.mData[0];
								m_Verticies[lControlPointIndex].tangent.y = (float)tangent.mData[1];
								m_Verticies[lControlPointIndex].tangent.z = (float)tangent.mData[2];
								break;
							}
							break;
							default:
								break; // other reference modes not shown here!
							}
						}

					}
					for (int l = 0; l < pMesh->GetElementBinormalCount(); ++l)
					{

						FbxGeometryElementBinormal* leBinormal = pMesh->GetElementBinormal(l);
						if (leBinormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
						{
							switch (leBinormal->GetReferenceMode())
							{
							case FbxGeometryElement::eDirect:
							{
								FbxVector4 binormal = leBinormal->GetDirectArray().GetAt(vertexId);
								m_Verticies[lControlPointIndex].binormal.x = (float)binormal.mData[0];
								m_Verticies[lControlPointIndex].binormal.y = (float)binormal.mData[1];
								m_Verticies[lControlPointIndex].binormal.z = (float)binormal.mData[2];
								break;
							}
							case FbxGeometryElement::eIndexToDirect:
							{
								int id = leBinormal->GetIndexArray().GetAt(vertexId);
								FbxVector4 binormal = leBinormal->GetDirectArray().GetAt(id);
								m_Verticies[lControlPointIndex].binormal.x = (float)binormal.mData[0];
								m_Verticies[lControlPointIndex].binormal.y = (float)binormal.mData[1];
								m_Verticies[lControlPointIndex].binormal.z = (float)binormal.mData[2];
								break;
							}
							break;
							default:
								break; // other reference modes not shown here!
							}
						}
					}
					vertexId++;
				} // for polygonSize
			} // for polygonCount
		}

		void FBXLoader::DisplayMaterial(FbxGeometry * pGeometry)
		{
			int lMaterialCount = 0;
			FbxNode* lNode = NULL;
			if (pGeometry)
				if (lNode = pGeometry->GetNode())
					lMaterialCount = lNode->GetMaterialCount();
			if (lMaterialCount > 0)
			{

				FbxPropertyT<FbxDouble3> lKFbxDouble3;
				FbxPropertyT<FbxDouble> lKFbxDouble1;
				FbxColor theColor;
				//Only 1 for now
				for (int lCount = 0; lCount < 1; lCount++)
				{
					FbxSurfaceMaterial *lMaterial = lNode->GetMaterial(lCount);
					m_Material = new Material();
					m_Material->mName = lMaterial->GetName();

					unsigned int textureIndex = 0;
					FbxProperty property;

					FBXSDK_FOR_EACH_TEXTURE(textureIndex)
					{
						property = lMaterial->FindProperty(FbxLayerElement::sTextureChannelNames[textureIndex]);
						if (property.IsValid())
						{
							unsigned int textureCount = property.GetSrcObjectCount<FbxTexture>();
							for (unsigned int i = 0; i < textureCount; ++i)
							{
								FbxLayeredTexture* layeredTexture = property.GetSrcObject<FbxLayeredTexture>(i);
								if (layeredTexture)
									continue; //to be implemented later
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
												m_Material->mDiffuseMapName = fileTexture->GetFileName();
											}
											else if (textureType == "SpecularColor")
											{
												m_Material->mSpecularMapName = fileTexture->GetFileName();
											}
											else if (textureType == "NormalMap")
											{
												m_Material->mNormalMapName = fileTexture->GetFileName();
											}
											else if (textureType == "EmmissivelMap")
											{
												m_Material->mEmissiveMapName = fileTexture->GetFileName();
											}
											else if (textureType == "GlossMap")
											{
												m_Material->mGlossMapName = fileTexture->GetFileName();
											}
										}
									}
								}
							}
						}
					}

					if (lMaterial->GetClassId().Is(FbxSurfacePhong::ClassId))
					{
						// We found a Phong material.  Display its properties.

						// Display the Ambient Color
						lKFbxDouble3 = ((FbxSurfacePhong *)lMaterial)->Ambient;
						m_Material->mAmbient.x = (float)lKFbxDouble3.Get()[0];
						m_Material->mAmbient.y = (float)lKFbxDouble3.Get()[1];
						m_Material->mAmbient.z = (float)lKFbxDouble3.Get()[2];

						// Display the Diffuse Color
						lKFbxDouble3 = ((FbxSurfacePhong *)lMaterial)->Diffuse;
						m_Material->mDiffuse.x = (float)lKFbxDouble3.Get()[0];
						m_Material->mDiffuse.y = (float)lKFbxDouble3.Get()[1];
						m_Material->mDiffuse.z = (float)lKFbxDouble3.Get()[2];

						// Display the Specular Color (unique to Phong materials)
						lKFbxDouble3 = ((FbxSurfacePhong *)lMaterial)->Specular;
						m_Material->mSpecular.x = (float)lKFbxDouble3.Get()[0];
						m_Material->mSpecular.y = (float)lKFbxDouble3.Get()[1];
						m_Material->mSpecular.z = (float)lKFbxDouble3.Get()[2];

						// Display the Emissive Color
						lKFbxDouble3 = ((FbxSurfacePhong *)lMaterial)->Emissive;
						m_Material->mSpecular.x = (float)lKFbxDouble3.Get()[0];
						m_Material->mSpecular.y = (float)lKFbxDouble3.Get()[1];
						m_Material->mSpecular.z = (float)lKFbxDouble3.Get()[2];

						//Opacity is Transparency factor now
						lKFbxDouble1 = ((FbxSurfacePhong *)lMaterial)->TransparencyFactor;
						m_Material->mTransparencyFactor = (float)lKFbxDouble1.Get();

						// Display the Shininess
						lKFbxDouble1 = ((FbxSurfacePhong *)lMaterial)->Shininess;
						m_Material->mShininess = (float)lKFbxDouble1.Get();

						// Display the Reflectivity
						lKFbxDouble1 = ((FbxSurfacePhong *)lMaterial)->ReflectionFactor;
						m_Material->mReflectionFactor = (float)lKFbxDouble1.Get();
					}
					else if (lMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId))
					{
						// We found a Lambert material. Display its properties.
						// Display the Ambient Color
						lKFbxDouble3 = ((FbxSurfacePhong *)lMaterial)->Ambient;
						m_Material->mAmbient.x = (float)lKFbxDouble3.Get()[0];
						m_Material->mAmbient.y = (float)lKFbxDouble3.Get()[1];
						m_Material->mAmbient.z = (float)lKFbxDouble3.Get()[2];

						// Display the Diffuse Color
						lKFbxDouble3 = ((FbxSurfacePhong *)lMaterial)->Diffuse;
						m_Material->mDiffuse.x = (float)lKFbxDouble3.Get()[0];
						m_Material->mDiffuse.y = (float)lKFbxDouble3.Get()[1];
						m_Material->mDiffuse.z = (float)lKFbxDouble3.Get()[2];

						// Display the Emissive
						lKFbxDouble3 = ((FbxSurfacePhong *)lMaterial)->Emissive;
						m_Material->mSpecular.x = (float)lKFbxDouble3.Get()[0];
						m_Material->mSpecular.y = (float)lKFbxDouble3.Get()[1];
						m_Material->mSpecular.z = (float)lKFbxDouble3.Get()[2];

						// Display the Opacity
						lKFbxDouble1 = ((FbxSurfacePhong *)lMaterial)->TransparencyFactor;
						m_Material->mTransparencyFactor = (float)lKFbxDouble1.Get();
					}
				}
			}
		}
		void FBXLoader::DisplayLink(FbxGeometry* pGeometry)
		{
			int lSkinCount = 0;
			int lClusterCount = 0;
			FbxCluster* lCluster;

			lSkinCount = pGeometry->GetDeformerCount(FbxDeformer::eSkin);
			for (int i = 0; i != lSkinCount; ++i)
			{
				FbxSkin* deformer = (FbxSkin *)pGeometry->GetDeformer(i, FbxDeformer::eSkin);
				lClusterCount = deformer->GetClusterCount();
				for (int j = 0; j != lClusterCount; ++j)
				{
					lCluster = deformer->GetCluster(j);

					int lIndexCount = lCluster->GetControlPointIndicesCount();
					int* lIndices = lCluster->GetControlPointIndices();
					double* lWeights = lCluster->GetControlPointWeights();

					for (int k = 0; k < lIndexCount; k++)
					{
						if (m_Verticies[lIndices[k]].bones.x == -1)
						{
							m_Verticies[lIndices[k]].bones.x = j;
							m_Verticies[lIndices[k]].weights.x += (float)lWeights[k];
						}
					}
					FbxAMatrix lMatrix;

					lMatrix = lCluster->GetTransformMatrix(lMatrix);
					m_Skeleton.mJoints[j].Local._11 = (float)lMatrix.Get(0, 0);
					m_Skeleton.mJoints[j].Local._12 = (float)lMatrix.Get(0, 1);
					m_Skeleton.mJoints[j].Local._13 = (float)lMatrix.Get(0, 2);
					m_Skeleton.mJoints[j].Local._14 = (float)lMatrix.Get(0, 3);
					m_Skeleton.mJoints[j].Local._21 = (float)lMatrix.Get(1, 0);
					m_Skeleton.mJoints[j].Local._22 = (float)lMatrix.Get(1, 1);
					m_Skeleton.mJoints[j].Local._23 = (float)lMatrix.Get(1, 2);
					m_Skeleton.mJoints[j].Local._24 = (float)lMatrix.Get(1, 3);
					m_Skeleton.mJoints[j].Local._31 = (float)lMatrix.Get(2, 0);
					m_Skeleton.mJoints[j].Local._32 = (float)lMatrix.Get(2, 1);
					m_Skeleton.mJoints[j].Local._33 = (float)lMatrix.Get(2, 2);
					m_Skeleton.mJoints[j].Local._34 = (float)lMatrix.Get(2, 3);
					m_Skeleton.mJoints[j].Local._41 = (float)lMatrix.Get(3, 0);
					m_Skeleton.mJoints[j].Local._42 = (float)lMatrix.Get(3, 1);
					m_Skeleton.mJoints[j].Local._43 = (float)lMatrix.Get(3, 2);
					m_Skeleton.mJoints[j].Local._44 = (float)lMatrix.Get(3, 3);

					lMatrix = lCluster->GetTransformLinkMatrix(lMatrix);
					m_Skeleton.mJoints[j].Offset._11 = (float)lMatrix.Get(0, 0);
					m_Skeleton.mJoints[j].Offset._12 = (float)lMatrix.Get(0, 1);
					m_Skeleton.mJoints[j].Offset._13 = (float)lMatrix.Get(0, 2);
					m_Skeleton.mJoints[j].Offset._14 = (float)lMatrix.Get(0, 3);
					m_Skeleton.mJoints[j].Offset._21 = (float)lMatrix.Get(1, 0);
					m_Skeleton.mJoints[j].Offset._22 = (float)lMatrix.Get(1, 1);
					m_Skeleton.mJoints[j].Offset._23 = (float)lMatrix.Get(1, 2);
					m_Skeleton.mJoints[j].Offset._24 = (float)lMatrix.Get(1, 3);
					m_Skeleton.mJoints[j].Offset._31 = (float)lMatrix.Get(2, 0);
					m_Skeleton.mJoints[j].Offset._32 = (float)lMatrix.Get(2, 1);
					m_Skeleton.mJoints[j].Offset._33 = (float)lMatrix.Get(2, 2);
					m_Skeleton.mJoints[j].Offset._34 = (float)lMatrix.Get(2, 3);
					m_Skeleton.mJoints[j].Offset._41 = (float)lMatrix.Get(3, 0);
					m_Skeleton.mJoints[j].Offset._42 = (float)lMatrix.Get(3, 1);
					m_Skeleton.mJoints[j].Offset._43 = (float)lMatrix.Get(3, 2);
					m_Skeleton.mJoints[j].Offset._44 = (float)lMatrix.Get(3, 3);

					XMStoreFloat4x4(&m_Skeleton.mJoints[j].InverseBindpose, XMMatrixInverse(0, XMLoadFloat4x4(&m_Skeleton.mJoints[j].Offset)) * XMLoadFloat4x4(&m_Skeleton.mJoints[j].Local));
				}
			}
		}

		void FBXLoader::DisplayAnimation(FbxScene* pScene)
		{
			int AnimationCount = pScene->GetSrcObjectCount<FbxAnimStack>();
			m_Animations.resize(AnimationCount);
			for (int i = 0; i < AnimationCount; i++)
			{
				FbxAnimStack* lAnimStack = pScene->GetSrcObject<FbxAnimStack>(i);
				m_Animations[i] = new Animation();
				m_Animations[i]->AnimationName = std::string(lAnimStack->GetName());
				DisplayAnimation(m_Animations[i], lAnimStack, pScene);
			}
		}

		void FBXLoader::DisplayAnimation(Animation* pAnim, FbxAnimStack* pAnimStack, FbxScene* pScene)
		{
			FbxTakeInfo* takeInfo = pScene->GetTakeInfo(pAnimStack->GetName());
			FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
			FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
			FbxLongLong tempend = end.GetFrameCount(FbxTime::eFrames24);
			pAnim->mFrameCount = (int)(tempend + 1);
			pAnim->mKeyFrames.resize(pAnim->mFrameCount);
			for (FbxLongLong i = 0; i <= tempend; ++i)
			{
				FbxTime currTime;
				currTime.SetFrame(i, FbxTime::eFrames24);
				pAnim->mKeyFrames[(unsigned int)i] = new Keyframe();
				pAnim->mKeyFrames[(unsigned int)i]->mFrameNum = (int)i;
				int boneCount = (int)m_Skeleton.mJoints.size();
				pAnim->mKeyFrames[(unsigned int)i]->mOffsets.resize(boneCount);
				for (int j = 0; j < boneCount; j++)
				{
					FbxAMatrix currentTransformOffset = BoneToNode[j]->EvaluateGlobalTransform(currTime);
					FbxAMatrix temp = currentTransformOffset.Inverse();
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._11 = (float)temp.Get(0, 0);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._12 = (float)temp.Get(0, 1);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._13 = (float)temp.Get(0, 2);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._14 = (float)temp.Get(0, 3);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._21 = (float)temp.Get(1, 0);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._22 = (float)temp.Get(1, 1);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._23 = (float)temp.Get(1, 2);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._24 = (float)temp.Get(1, 3);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._31 = (float)temp.Get(2, 0);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._32 = (float)temp.Get(2, 1);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._33 = (float)temp.Get(2, 2);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._34 = (float)temp.Get(2, 3);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._41 = (float)temp.Get(3, 0);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._42 = (float)temp.Get(3, 1);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._43 = (float)temp.Get(3, 2);
					pAnim->mKeyFrames[(unsigned int)i]->mOffsets[j]._44 = (float)temp.Get(3, 3);
				}
			}
		}
	}
}
