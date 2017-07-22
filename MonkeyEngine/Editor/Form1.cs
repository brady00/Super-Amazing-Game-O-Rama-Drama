﻿using System;
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

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            InitializeEngine(panel1.Handle, panel1.Width, panel1.Height);
            this.DoubleBuffered = true;
            // Enable double duffering to stop flickering.
            this.SetStyle(ControlStyles.DoubleBuffer, true);
            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            this.SetStyle(ControlStyles.UserPaint, true);
            this.SetStyle(ControlStyles.SupportsTransparentBackColor, false);
            this.SetStyle(ControlStyles.Opaque, false);
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            this.SetStyle(ControlStyles.ResizeRedraw, true);
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            UpdateEngine();
            this.Invalidate();
        }
    }
}