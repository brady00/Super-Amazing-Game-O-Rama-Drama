using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Editor
{
    class ComponentPanel : Panel
    {
        public Button CollapseButton;
        public uint Index;
        private Label label1;
        public Component Comp;

        public ComponentPanel() : base()
        {
            Comp = new Component();
            InitializeComponent();
        }

        private void InitializeComponent()
        {
            this.CollapseButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.label1.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(25, 5);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(200, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Component";
            // 
            // CollapseButton
            // 
            this.CollapseButton.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.CollapseButton.FlatAppearance.BorderColor = System.Drawing.SystemColors.ControlDarkDark;
            this.CollapseButton.FlatAppearance.MouseDownBackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.CollapseButton.FlatAppearance.MouseOverBackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.CollapseButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.CollapseButton.Location = new System.Drawing.Point(0, 0);
            this.CollapseButton.Name = "CollapseButton";
            this.CollapseButton.Size = new System.Drawing.Size(19, 23);
            this.CollapseButton.TabIndex = 1;
            this.CollapseButton.Text = "▶";
            this.CollapseButton.UseVisualStyleBackColor = false;
            this.CollapseButton.Click += new System.EventHandler(this.CollapseButton_Click);
            // 
            // ComponentPanel
            // 
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.Controls.Add(this.label1);
            this.Controls.Add(this.CollapseButton);
            this.Location = new System.Drawing.Point(-1, 107);
            this.MaximumSize = new System.Drawing.Size(335, 0);
            this.MinimumSize = new System.Drawing.Size(335, 23);
            this.Name = "panel1";
            this.Size = new System.Drawing.Size(335, 23);
            this.TabIndex = 18;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        private void CollapseButton_Click(object sender, EventArgs e)
        {
            if(CollapseButton.Text == "▶")
            {
                CollapseButton.Text = "▼";
                this.Size = new System.Drawing.Size(this.MinimumSize.Width, 200);
                Form1.ButtonExpanded(Index);
            }
            else
            {
                CollapseButton.Text = "▶";
                this.Size = new System.Drawing.Size(this.MinimumSize.Width, this.MinimumSize.Height);
                Form1.ButtonCollapsed(Index);
            }
        }

        public void CreatePanel(Panel InspectorBackgroundPanel, uint Index)
        {
            Point p = Form1.ComponentStartingLocation;
            p.Y += (int)Index * 23;
            InspectorBackgroundPanel.Controls.Add(this);
            this.Index = Index;
            this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
            this.Location = p;
            this.MaximumSize = new System.Drawing.Size(335, 0);
            this.MinimumSize = new System.Drawing.Size(335, 23);
            this.Name = "ComponentPanel" + Index.ToString();
            this.Size = new System.Drawing.Size(335, 23);
            this.TabIndex = 18;
            this.Visible = false;
            this.label1.Text = Comp.Name;
            this.BringToFront();
            this.Invalidate();
        }
    }
}
