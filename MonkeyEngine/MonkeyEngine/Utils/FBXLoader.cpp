#include "FBXLoader.h"
namespace MonkeyEngine
{
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
				//DisplayHierarchy(lScene);
				//DisplayContent(lScene);
				//DisplayPose(lScene);
				//DisplayAnimation(lScene);
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
			int lAnimStackCount;
			bool lStatus;
			// Create an importer.
			FbxImporter* lImporter = FbxImporter::Create(pManager, "");

			// Initialize the importer by providing a filename.
			const bool lImportStatus = lImporter->Initialize(pFilename, -1, pManager->GetIOSettings());

			if (!lImportStatus)
				return false;

			if (lImporter->IsFBX())
			{
				// From this point, it is possible to access animation stack information without
				// the expense of loading the entire file.

				lAnimStackCount = lImporter->GetAnimStackCount();

				for (int i = 0; i < lAnimStackCount; i++)
				{
					//Do Animation Stuffs
				}

				// Set the import states. By default, the import states are always set to 
				// true. The code below shows how to change these states.
				IOS_REF.SetBoolProp(IMP_FBX_MATERIAL, true);
				IOS_REF.SetBoolProp(IMP_FBX_TEXTURE, true);
				IOS_REF.SetBoolProp(IMP_FBX_LINK, true);
				IOS_REF.SetBoolProp(IMP_FBX_SHAPE, true);
				IOS_REF.SetBoolProp(IMP_FBX_GOBO, true);
				IOS_REF.SetBoolProp(IMP_FBX_ANIMATION, true);
				IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
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
	}


}
