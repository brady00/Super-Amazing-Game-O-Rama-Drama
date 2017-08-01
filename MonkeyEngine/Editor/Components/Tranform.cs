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
            }
        }
        private bool ChildrenGrabbed = false;
        private Tranform[] _Children;
        unsafe public Tranform[] Children
        {
            get
            {
                if (!ChildrenGrabbed)
                {
                    uint amount;
                    void** children = GetChildren(EngineObject, out amount);
                    _Children = new Tranform[amount];
                    for(uint i = 0; i < amount; i++)
                    {
                        _Children[i] = new Tranform();
                        _Children[i].EngineObject = children[i];
                    }
                    ChildrenGrabbed = true;
                }
                return _Children;
            }
            set
            {
                _Children = value;
            }
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
