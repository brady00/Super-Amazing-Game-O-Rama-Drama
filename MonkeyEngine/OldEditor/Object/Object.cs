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
        unsafe private string _Name;
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
                _Name = value;
                SetName(EngineObject, _Name.ToArray<char>());
            }
        }
        private bool FlagsGrabbed = false;
        unsafe private uint _Flags;
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
                SetFlags(EngineObject, _Flags);
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
