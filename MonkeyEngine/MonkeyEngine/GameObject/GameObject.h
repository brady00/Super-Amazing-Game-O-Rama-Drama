#pragma once
#include "../Object/Object.h"
#include <vector>
class Scene;
namespace MEObject
{
	class Transform;
	class Component;
	class GameObject : public Object
	{
	public:
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
			eMonoBehaviour /* Script */,
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
	public:
		GameObject();
		~GameObject();
		void SetActive(bool _Active);
		bool GetActive();
		void SetStatic(bool _Static);
		bool GetStatic();
		void SetLayer(unsigned int _Layer);
		unsigned int GetLayer();
		void SetScene(Scene* _Scene);
		Scene* GetScene();
		void AddTag(std::string _Tag);
		std::vector<std::string>& GetTags();
		void SetTrasform(Transform* _Transform);
		Transform* GetTransform();
		template <typename CompType>
		void AddComponent();
		void BroadcastMessage(std::string _Message);
		void SendMessage(std::string _Message);
		void SendMessageUpwards(std::string _Message);
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
	protected:
		void Initialize();
		MEReturnValues::RETURNVALUE Update();
		void ShutDown();
	//helpers
	private:
		void SetActiveInHeirarchy();
	};
}
