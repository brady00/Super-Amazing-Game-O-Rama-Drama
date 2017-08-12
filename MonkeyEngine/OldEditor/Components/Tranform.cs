using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Threading.Tasks;

namespace Editor
{
    struct Float3
    {
        public float x, y, z;
    }

    class Tranform : Component
    {
        private bool PosRotScaleGrabbed = false;
        private Float3 _Position;
        unsafe public Float3 Position
        {
            get
            {
                if(!PosRotScaleGrabbed)
                {
                    GetPosRotScale(EngineObject, out _Position.x, out _Position.y, out _Position.z, out _Rotation.x, out _Rotation.y, out _Rotation.z, out _Scale.x, out _Scale.y, out _Scale.z);
                    PosRotScaleGrabbed = true;
                }
                return _Position;
            }
            set
            {
                _Position = value;
                SetPosRotScale(EngineObject, _Position.x, _Position.y, _Position.z, _Rotation.x, _Rotation.y, _Rotation.z, _Scale.x, _Scale.y, _Scale.z);
            }
        }

        private Float3 _Rotation;
        unsafe public Float3 Rotation
        {
            get
            {
                if (!PosRotScaleGrabbed)
                {
                    GetPosRotScale(EngineObject, out _Position.x, out _Position.y, out _Position.z, out _Rotation.x, out _Rotation.y, out _Rotation.z, out _Scale.x, out _Scale.y, out _Scale.z);
                    PosRotScaleGrabbed = true;
                }
                return _Rotation;
            }
            set
            {
                _Rotation = value;
                SetPosRotScale(EngineObject, _Position.x, _Position.y, _Position.z, _Rotation.x, _Rotation.y, _Rotation.z, _Scale.x, _Scale.y, _Scale.z);
            }
        }
        private Float3 _Scale;
        unsafe public Float3 Scale
        {
            get
            {
                if (!PosRotScaleGrabbed)
                {
                    GetPosRotScale(EngineObject, out _Position.x, out _Position.y, out _Position.z, out _Rotation.x, out _Rotation.y, out _Rotation.z, out _Scale.x, out _Scale.y, out _Scale.z);
                    PosRotScaleGrabbed = true;
                }
                return _Scale;
            }
            set
            {
                _Scale = value;
                SetPosRotScale(EngineObject, _Position.x, _Position.y, _Position.z, _Rotation.x, _Rotation.y, _Rotation.z, _Scale.x, _Scale.y, _Scale.z);
            }
        }
        private bool ParentGrabbed = false;
        private GameObject _Parent;
        unsafe public GameObject Parent
        {
            get
            {
                if(!ParentGrabbed)
                {
                    _Parent.EngineObject = GetParent(EngineObject);
                    ParentGrabbed = true;
                }
                return _Parent;
            }
            set
            {
                _Parent = value;
                SetParent(EngineObject, _Parent.EngineObject);
            }
        }
        private bool ChildrenGrabbed = false;
        private List<Tranform> _Children;
        unsafe public List<Tranform> Children
        {
            get
            {
                if (!ChildrenGrabbed)
                {
                    uint amount;
                    void** children = GetChildren(EngineObject, out amount);
                    _Children = new List<Tranform>();
                    for(int i = 0; i < amount; i++)
                    {
                        _Children[i] = new Tranform();
                        _Children[i].EngineObject = children[i];
                    }
                    ChildrenGrabbed = true;
                }
                return _Children;
            }
        }
        
        unsafe void AddChild(Tranform _child)
        {
            _Children.Add(_child);
            AddChild(EngineObject, _child.EngineObject);
        }

        unsafe void RemoveChild(Tranform _child)
        {
            _Children.Remove(_child);
            RemoveChild(EngineObject, _child.EngineObject);
        }

        [DllImport("MonkeyEngine.dll", EntryPoint = "GetTransformPosRotScale", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern void GetPosRotScale(void* _object, out float posx, out float posy, out float posz, out float rotx, out float roty, out float rotz, out float scalex, out float sclaey, out float scalez);
        [DllImport("MonkeyEngine.dll", EntryPoint = "SetTransformPosRotScale", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern void SetPosRotScale(void* _object, float posx, float posy, float posz, float rotx, float roty, float rotz, float scalex, float sclaey, float scalez);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetTransformChildren", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern void** GetChildren(void* _object, out uint Amount);
        [DllImport("MonkeyEngine.dll", EntryPoint = "AddTransformChild", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern void AddChild(void* _object, void* _child);
        [DllImport("MonkeyEngine.dll", EntryPoint = "RemoveTransformChild", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern void RemoveChild(void* _object, void* _child);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetTransformParent", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern void* GetParent(void* _object);
        [DllImport("MonkeyEngine.dll", EntryPoint = "SetTransformParent", CallingConvention = CallingConvention.StdCall)]
        unsafe static public extern void SetParent(void* _object, void* _parent);
    }
}
