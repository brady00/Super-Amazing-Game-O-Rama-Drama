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
        TreeNode PrevSelectedObject;
        SortedDictionary<string, GameObject> GameObjects;
        static ComponentPanel[] Components = new ComponentPanel[256];
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
            GameObjects = new SortedDictionary<string, GameObject>();
            Objects = GetSceneObjects(out amount);
            GameObject Object0 = new GameObject();
            GameObject Object1 = new GameObject();
            GameObject Object2 = new GameObject();
            Object0.EngineObject = Objects[0];
            Object1.EngineObject = Objects[1];
            Object2.EngineObject = Objects[2];
            GameObjects[Object0.Name] = Object0;
            GameObjects[Object1.Name] = Object1;
            GameObjects[Object2.Name] = Object2;

            ObjectTreeView.Nodes.Add(Object0.Name);
            ObjectTreeView.Nodes.Add(Object1.Name);
            ObjectTreeView.Nodes[0].Nodes.Add(Object2.Name);

            //add to component loading...
            Components[ComponentIndex] = new ComponentPanel();
            Point p = ComponentStartingLocation;
            p.Y += (int)ComponentIndex * 23;
            ComponentPanelSetup(Components[ComponentIndex], p, "ComponentPanel" + ComponentIndex.ToString());
            ComponentIndex++;
        }

        unsafe private void RenderingPanel_Paint(object sender, PaintEventArgs e)
        {
          
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            UpdateEngine();
            this.Invalidate();
        }

        private void NameBox_TextChanged(object sender, EventArgs e)
        {
            string OldName = ObjectTreeView.SelectedNode.Text;
            string NewName = NameBox.Text;
            if (OldName == NewName)
                return;
            GameObjects[OldName].Name = NewName;
            ObjectTreeView.SelectedNode.Text = NewName;
            GameObjects[NewName] = GameObjects[OldName];
            GameObjects.Remove(OldName);
        }

       Point ComponentStartingLocation = new Point(3, 107);

        private void ComponentPanelSetup(ComponentPanel panel, Point position, string name)
        {
            InspectorBackgroundPanel.Controls.Add(panel);
            panel.Index = ComponentIndex;
            panel.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            panel.Location = position;
            panel.MaximumSize = new System.Drawing.Size(335, 0);
            panel.MinimumSize = new System.Drawing.Size(335, 23);
            panel.Name = name;
            panel.Size = new System.Drawing.Size(335, 23);
            panel.TabIndex = 18;
            panel.BringToFront();
            panel.Invalidate();
        }

        static uint ComponentIndex = 0;
        private void ObjectTreeView_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if(ObjectTreeView.SelectedNode != PrevSelectedObject)
            {
                PrevSelectedObject = ObjectTreeView.SelectedNode;
                NameBox.Text = ObjectTreeView.SelectedNode.Text;
                ActiveBox.Checked = GameObjects[NameBox.Text].Active;
                StaticBox.Checked = GameObjects[NameBox.Text].Static;
                LayerComboBox.SelectedIndex = (int)GameObjects[NameBox.Text].Layer;
            }
        }

        private void splitContainer1_SplitterMoved(object sender, SplitterEventArgs e)
        {

        }

        public static void ButtonCollapsed(uint buttonIndex)
        {
            for (uint i = buttonIndex + 1; i < ComponentIndex; i++)
            {
                Components[i].Location = new Point(Components[buttonIndex].Location.X, Components[i - 1].Location.Y + Components[i - 1].Size.Height);
            }
        }

        public static void ButtonExpanded(uint buttonIndex)
        {
            for (uint i = buttonIndex + 1; i < ComponentIndex; i++)
            {
                Components[i].Location = new Point(Components[buttonIndex].Location.X, Components[i].Location.Y + Components[buttonIndex].Size.Height - Components[buttonIndex].MinimumSize.Height);
            }
        }
    }
}
