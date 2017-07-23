using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{

    class GameObject
    {
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetObjectNameChar", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern char GetNameChar(void* GameObject, uint index);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetObjectNameSize", CallingConvention = CallingConvention.StdCall)]
        private unsafe static extern uint GetNameSize(void* GameObject);
        [DllImport("MonkeyEngine.dll", EntryPoint = "SetObjectName", CallingConvention = CallingConvention.StdCall)]
        public unsafe static extern void SetName(void* GameObject, char[] _Name);
        [DllImport("MonkeyEngine.dll", EntryPoint = "GetObjectFlags", CallingConvention = CallingConvention.StdCall)]
        public unsafe static extern uint GetFlags(void* Gameobject);
        [DllImport("MonkeyEngine.dll", EntryPoint = "SetObjectFlags", CallingConvention = CallingConvention.StdCall)]
        public unsafe static extern void SetFlags(void* GameObject, uint _Flags);

        public unsafe static string GetFullName(void* _GameObject)
        {
            uint size = GetNameSize(_GameObject);
            char[] Name = new char[size];
            for (uint i = 0; i < size; i++)
                Name[i] = GetNameChar(_GameObject, i);
            return new string(Name);
        }
    }
}
