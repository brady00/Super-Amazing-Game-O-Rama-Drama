using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Reflection;

namespace Editor
{
    public partial class Form1 : Form
    {
        [DllImport("MonkeyEngine.dll", EntryPoint = "InitializeEngine", CallingConvention = CallingConvention.StdCall)]
        static extern void InitializeEngine(IntPtr window, int _ScreenWidth, int _ScreenHeight);

        [DllImport("MonkeyEngine.dll", EntryPoint = "UpdateEngine", CallingConvention = CallingConvention.StdCall)]
        static extern void UpdateEngine();

        [DllImport("MonkeyEngine.dll", EntryPoint = "ShutdownEngine", CallingConvention = CallingConvention.StdCall)]
        static extern void ShutdownEngine();

        [DllImport("MonkeyEngine.dll", EntryPoint = "GetSceneObjects", CallingConvention = CallingConvention.StdCall)]
        unsafe static extern void** GetSceneObjects(out uint Amount);


        unsafe void** Objects;

        public Form1()
        {
            InitializeComponent();
        }

        unsafe private void Form1_Load(object sender, EventArgs e)
        {
            InitializeEngine(RenderingPanel.Handle, RenderingPanel.Width, RenderingPanel.Height);
            Timer.Start();
            this.DoubleBuffered = true;
            // Enable double duffering to stop flickering.
            this.SetStyle(ControlStyles.DoubleBuffer, true);
            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            this.SetStyle(ControlStyles.UserPaint, true);
            this.SetStyle(ControlStyles.SupportsTransparentBackColor, false);
            this.SetStyle(ControlStyles.Opaque, false);
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            uint amount;
            Objects = GetSceneObjects(out amount);
            listBox1.Items.Add(GameObject.GetFullName(Objects[0]));
            listBox1.Items.Add(GameObject.GetFullName(Objects[1]));
            listBox1.Items.Add(GameObject.GetFullName(Objects[2]));
            listBox1.SelectedIndex = 0;
            listBox1.Update();
            listBox1.DisplayMember = "";
            listBox1.DisplayMember = "Name";
            listBox1.Update();
            listBox1.Refresh();
        }

        unsafe private void RenderingPanel_Paint(object sender, PaintEventArgs e)
        {
          
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            UpdateEngine();
            this.Invalidate();
            listBox1.Invalidate();
        }
    }
}
