using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{

    class GameObject : Object
    {
        public enum COMPONENT_ID
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

        private bool ComponentsGrabbed = false;
        unsafe private ComponentPanel[] _Components;
        unsafe public ComponentPanel[] Components
        {
            get
            {
                if(!ComponentsGrabbed)
                {
                    uint CompAmount = GetComponentCount(EngineObject);
                    uint ScriptAmount = GetScriptCount(EngineObject);
                    void** comps = GetComponents(EngineObject);
                    void** scripts = GetScripts(EngineObject);
                    _Components = new ComponentPanel[CompAmount + ScriptAmount + 1];
                    _Components[0] = new ComponentPanel();
                    _Components[0].Comp = Trans;
                    for (uint i = 0; i < CompAmount; i++)
                    {
                        _Components[i + 1] = new ComponentPanel();
                        _Components[i + 1].Comp.EngineObject = comps[i];
                    }
                    for (uint i = CompAmount; i < CompAmount + ScriptAmount; i++)
                    {
                        _Components[i + 1] = new ComponentPanel();
                        _Components[i + 1].Comp.EngineObject = scripts[i - CompAmount];
                    }
                    ComponentsGrabbed = true;
                }
                return _Components;
            }
            set
            {
                _Components = value;
            }
        }

        private bool TagsGrabbed = false;
        unsafe private string[] _Tags;
        unsafe public string[] Tags
        {
            get
            {
                if(!TagsGrabbed)
                {
                    TagsGrabbed = true;
                }
                return _Tags;
            }
            set
            {
                _Tags = value;
            }
        }
        private bool TranformGrabbed = false;
        unsafe private Tranform _Trans;
        unsafe public Tranform Trans
        {
            get
            {
                if(!TranformGrabbed)
                {
                    _Trans = new Tranform();
                    _Trans.EngineObject = GetTransform(EngineObject);
                    TranformGrabbed = true;
                }
                return _Trans;
            }
            set
            {
                _Trans = value;
            }
        }
        private bool ActiveGrabbed = false;
        unsafe private bool _Active;
        unsafe public bool Active
        {
            get
            {
                if (!ActiveGrabbed)
                {
                    ActiveGrabbed = true;
                    _Active = GetActive(EngineObject);
                }
                return _Active;
            }
            set
            {
                _Active = value;
            }
        }
        private bool StaticGrabbed = false;
        unsafe private bool _Static;
        unsafe public bool Static
        {
            get
            {
                if (!StaticGrabbed)
                {
                    StaticGrabbed = true;
                    _Static = GetStatic(EngineObject);
                }
                return _Static;
            }
            set
            {
                _Static = value;
            }
        }
        private bool LayerGrabbed = false;
        unsafe private uint _Layer;
        unsafe public uint Layer
        {
            get
            {
                if (!LayerGrabbed)
                {
                    LayerGrabbed = true;
                    _Layer = GetLayer(EngineObject);
                }
                return _Layer;
            }
            set
            {
                _Layer = value;
            }
        }


        [DllImport("MonkeyEngine.dll", EntryPoint = "AddGameObjectTag", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern void AddTag(void* _object, string _Tag);
        [DllImport("MonkeyEngine.dll", EntryPoint = "RemoveGameObjectTag", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern void RemoveTag(void* _object, string _Tag);

        //needs to be split
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetGameObjectTags", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern string GetTags(void* _object);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetGameObjectTransform", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern void* GetTransform(void* _object);
        [DllImport("MonkeyEngine.dll", EntryPoint = "UpdateGameObjectTransform", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern void UpdateTransform(void* _Object, float posx, float posy, float posz, float rotx, float roty, float rotz, float scalex, float scaley, float scalez);
        [DllImport("MonkeyEngine.dll", EntryPoint = "RemoveGameObjectComponent", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern void RemoveComponent(void* _object, COMPONENT_ID _ID, void* _comp);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetGameObjectComponents", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern void** GetComponents(void* _object);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetGameObjectScripts", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern void** GetScripts(void* _object);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetGameObjectComponentCount", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern uint GetComponentCount(void* _object);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetGameObjectScriptCount", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern uint GetScriptCount(void* _object);
        [DllImport("MonkeyEngine.dll", EntryPoint = "SetGameObjectActive", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern void SetActive(void* _object, bool _Active);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetGameObjectActive", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern bool GetActive(void* _object);
        [DllImport("MonkeyEngine.dll", EntryPoint = "SetGameObjectStatic", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern void SetStatic(void* _object, bool _Static);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetGameObjectStatic", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern bool GetStatic(void* _object);
        [DllImport("MonkeyEngine.dll", EntryPoint = "SetGameObjectLayer", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern void SetLayer(void* _object, uint _Layer);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetGameObjectLayer", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern uint GetLayer(void* _object);


        public void GUIActivate()
        {
            foreach (ComponentPanel comp in Components)
            {
                comp.Show();
                comp.Refresh();
            }
        }

        public void GUIDeactivate()
        {
            foreach (ComponentPanel comp in Components)
            {
                comp.Hide();
                comp.Refresh();
            }
        }
    }
}
