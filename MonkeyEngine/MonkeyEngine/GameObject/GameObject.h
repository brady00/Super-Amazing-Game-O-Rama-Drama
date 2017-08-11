#pragma once
#include "../Object/Object.h"
#include <vector>
namespace MonkeyEngine
{
	class Scene;
	namespace MEObject
	{
		class Transform;
		class Component;
		class GameObject : public Object
		{
			friend class Scene;
		public:
			friend class Scene;
			enum COMPONENT_ID
			{
				eBaseClass = -1,
				eAnchoredJoint2D,
				eAnimation,
				eAnimator,
				eAreaEffector2D,
				eAudioChorusFilter,
				eAudioDistortionFilter,
				eAudioEchoFilter,
				eAudioHighPassFilter,
				eAudioListenter,
				eAudioLowPassFilter,
				eAudioReverbFilter,
				eAudioReverbZone,
				eAudioSource,
				eBehaviour,
				eBillboardRenderer,
				eBoxCollider,
				eBoxCollider2D,
				eBuoyancyEffector2D,
				eCamera,
				eCanvas,
				eCanvasGroup,
				eCanvasRenderer,
				eCapsuleCollider,
				eCharacterController,
				eCharacterJoin,
				eCircleCollider2D,
				eCloth,
				eCollider,
				eCollider2D,
				eConfigurableJoint,
				eConstantForce,
				eConstantForce2D,
				eDistanceJoint2D,
				eEdgeCollider2D,
				eEffector2D,
				eFixedJoint,
				eFixedJoint2D,
				eFlareLayer,
				eFricitionJoint2D,
				eGUIElement,
				eGUILayer,
				eGUIText,
				eGUITexture,
				eHingeJoint,
				eHingeJoint2D,
				eJoint,
				eJoint2D,
				eLensFlare,
				eLight,
				eLightProbeGroup,
				eLightProbePoxyVolume,
				eLineRenderer,
				eLODGroup,
				eMeshCollider,
				eMeshFilter,
				eMeshRenderer,
				eNavMeshAgent,
				eNavMeshObstacle,
				eNetworkView,
				eOcclusionArea,
				eOcclusionPortal,
				eOffMeshLink,
				eParticleSystem,
				eParticleSystemRenderer,
				ePhysicsUpdateBehaviour2D,
				ePlatformEffector2D,
				ePointEffector2D,
				ePolygonCollider2D,
				eProjector,
				eRectTransform,
				eReflectionProbe,
				eRelativeJoint2D,
				eCompRenderer,
				eRigidbody,
				eRigidbody2D,
				eSkinnedMeshRenderer,
				eSkybox,
				eSliderJoint2D,
				eSphereCollider,
				eSpringJoint,
				eSpringJoint2D,
				eSpriteRenderer,
				eSurfaceEffector2D,
				eTargetJoint2D,
				eTerrain,
				eTerrainCollider,
				eTextMesh,
				eTrailRenderer,
				eTransform,
				eTree,
				eWheelCollider,
				eWheelJoint2D,
				eWindZone,
				eScript,
				eNumComponents
			};
		private:
			bool m_bActiveInHeirarchy;
			bool m_bActiveSelf;
			bool m_bIsStatic;
			unsigned int m_uiLayer;
			Scene* m_pScene;
			std::vector<std::string> m_vTags;
			Transform* m_pTransform;
			std::vector<Component*> m_vComponents[eNumComponents];
			std::vector<Component*> m_vUpdatableComponents;
			std::vector<Component*> m_vScripts;
		public:
			GameObject();
			~GameObject();
			void __declspec(dllexport) SetActive(bool _Active);
			bool __declspec(dllexport) GetActive();
			void __declspec(dllexport) SetStatic(bool _Static);
			bool __declspec(dllexport) GetStatic();
			void __declspec(dllexport) SetLayer(unsigned int _Layer);
			unsigned int __declspec(dllexport) GetLayer();
			void SetScene(Scene* _Scene);
			Scene* GetScene();
			void AddTag(std::string _Tag);
			void RemoveTag(std::string _Tag);
			std::vector<std::string>& GetTags();
			Transform __declspec(dllexport) *GetTransform();
			void AddComponent(Component* _Component, COMPONENT_ID _ID);
			void RemoveComponent(Component* _Component, COMPONENT_ID _ID);
			void BroadcastMessage(std::string _Message);
			void SendMessageString(std::string _Message);
			void SendMessageUpwards(std::string _Message);
			void SendMessageDownwards(std::string _Message);
			void RecieveMessage(std::string _Message);
			bool CompareTag(std::string _Tag);
			template <typename CompType>
			CompType* GetComponent();
			template <typename CompType>
			CompType* GetComponentinCildren();
			template <typename CompType>
			CompType* GetComponentinParent();
			template <typename CompType>
			std::vector<CompType*> GetComponents();
			template <typename CompType>
			std::vector<CompType*> GetComponentsinCildren();
			template <typename CompType>
			std::vector<CompType*> GetComponentsinParent();

			std::vector<Component*> __declspec(dllexport) &GetAllComponents();
			std::vector<Component*> __declspec(dllexport) &GetAllScritps();
		private:
			void Initialize();
			void Update();
			void ShutDown();
			void SetActiveInHeirarchy();
		};
	}
}
