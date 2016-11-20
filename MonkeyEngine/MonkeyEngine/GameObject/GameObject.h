#pragma once
#include "../Object/Object.h"
#include <vector>
class Scene;
class Transform;
namespace MEObject
{
	enum COMPONENT_ID 
	{ 
		BASECLASS = -1,
		AnchoredJoint2D,
		Animation,
		Animator,
		AreaEffector2D,
		AudioChorusFilter,
		AudioDistortionFilter,
		AudioEchoFilter,
		AudioHighPassFilter,
		AudioListenter,
		AudioLowPassFilter,
		AudioReverbFilter,
		AudioReverbZone,
		AudioSource,
		Behaviour,
		BillboardRenderer,
		BoxCollider,
		BoxCollider2D,
		BuoyancyEffector2D,
		Camera,
		Canvas,
		CanvasGroup,
		CanvasRenderer,
		CapsuleCollider,
		CharacterController,
		CharacterJoin,
		CircleCollider2D,
		Cloth,
		Collider,
		Collider2D,
		ConfigurableJoint,
		ConstantForce,
		ConstantForce2D,
		DistanceJoint2D,
		EdgeCollider2D,
		Effector2D,
		FixedJoint,
		FixedJoint2D,
		FlareLayer,
		FricitionJoint2D,
		GUIElement,
		GUILayer,
		GUIText,
		GUITexture,
		HingeJoint,
		HingeJoint2D,
		Joint,
		Joint2D,
		LensFlare,
		Light,
		LightProbeGroup,
		LightProbePoxyVolume,
		LineRenderer,
		LODGroup,
		MeshCollider,
		MeshFilter,
		MeshRenderer,
		MonoBehaviour /* Script */,
		NavMeshAgent,
		NavMeshObstacle,
		NetworkView,
		OcclusionArea,
		OcclusionPortal,
		OffMeshLink,
		ParticleSystem,
		ParticleSystemRenderer,
		PhysicsUpdateBehaviour2D,
		PlatformEffector2D,
		PointEffector2D,
		PolygonCollider2D,
		Projector,
		RectTransform,
		ReflectionProbe,
		RelativeJoint2D,
		Renderer,
		Rigidbody,
		Rigidbody2D,
		SkinnedMeshRenderer,
		Skybox,
		SliderJoint2D,
		SphereCollider,
		SpringJoint,
		SpringJoint2D,
		SpriteRenderer,
		SurfaceEffector2D,
		TargetJoint2D,
		Terrain,
		TerrainCollider,
		TextMesh,
		TrailRenderer,
		Transform,
		Tree,
		WheelCollider,
		WheelJoint2D,
		WindZone,
		NumComponents
	};
	class GameObject : public Object
	{
	private:
		bool m_bActiveInHeirarchy;
		bool m_bActiveSelf;
		bool m_bIsStatic;
		unsigned int m_uiLayer;
		Scene* m_pSCene;
		std::string m_sTag;
		Object* m_pTransform;
		std::vector<Object*> m_vComponents[NumComponents];
	public:
		GameObject();
		~GameObject();
	protected:
		void Initialize();
		MEReturnValues::RETURNVALUE Update();
		void ShutDown();
	};
}
