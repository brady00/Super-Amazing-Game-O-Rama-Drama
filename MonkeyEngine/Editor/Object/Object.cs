using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{
    class Object
    {
        public unsafe void* EngineObject;
        private bool NameGrabbed = false;
        unsafe public string _Name;
        unsafe public string Name
        {
            get
            {
                if (!NameGrabbed)
                {
                    NameGrabbed = true;
                    _Name = GetFullName(EngineObject);
                }
                return _Name;
            }
            set
            {
                this._Name = value;
            }
        }
        private bool FlagsGrabbed = false;
        unsafe public uint _Flags;
        unsafe public uint Flags
        {
            get
            {
                if (!FlagsGrabbed)
                {
                    FlagsGrabbed = true;
                    _Flags = GetFlags(EngineObject);
                }
                return _Flags;
            }
            set
            {
                _Flags = value;
            }
        }
        private bool ActiveGrabbed = false;
        unsafe public bool _Active;
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
        unsafe public bool _Static;
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
        unsafe public uint _Layer;
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

        [DllImport("MonkeyEngine.dll", EntryPoint = "GetObjectNameChar", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern char GetNameChar(void* GameObject, uint index);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetObjectNameSize", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern uint GetNameSize(void* GameObject);
        [DllImport("MonkeyEngine.dll", EntryPoint = "SetObjectName", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern void SetName(void* GameObject, char[] _Name);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetObjectFlags", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern uint GetFlags(void* Gameobject);
        [DllImport("MonkeyEngine.dll", EntryPoint = "SetObjectFlags", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern void SetFlags(void* GameObject, uint _Flags);
        [DllImport("MonkeyEngine.dll", EntryPoint = "SetObjectActive", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern void SetActive(void* _object, bool _Active);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetObjectActive", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern bool GetActive(void* _object);
        [DllImport("MonkeyEngine.dll", EntryPoint = "SetObjectStatic", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern void SetStatic(void* _object, bool _Static);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetObjectStatic", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern bool GetStatic(void* _object);
        [DllImport("MonkeyEngine.dll", EntryPoint = "SetObjectLayer", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern void SetLayer(void* _object, uint _Layer);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetObjectLayer", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern uint GetLayer(void* _object);

        public unsafe static string GetFullName(void* _GameObject)
        {
            uint size = GetNameSize(_GameObject);
            char[] name = new char[size];
            for (uint i = 0; i < size; i++)
                name[i] = GetNameChar(_GameObject, i);
            return new string(name);
        }

        public unsafe override string ToString()
        {
            return Name;
        }
    }
}
