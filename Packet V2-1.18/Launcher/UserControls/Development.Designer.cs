namespace PacketLauncher.UserControls
{
    partial class Development
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.PacketLogo = new System.Windows.Forms.Label();
            this.Locate = new Siticone.Desktop.UI.WinForms.SiticoneButton();
            this.Inject = new Siticone.Desktop.UI.WinForms.SiticoneButton();
            this.SuspendLayout();
            // 
            // PacketLogo
            // 
            this.PacketLogo.AutoSize = true;
            this.PacketLogo.Font = new System.Drawing.Font("Minecraft", 47.99999F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PacketLogo.Location = new System.Drawing.Point(193, 110);
            this.PacketLogo.Name = "PacketLogo";
            this.PacketLogo.Size = new System.Drawing.Size(441, 77);
            this.PacketLogo.TabIndex = 1;
            this.PacketLogo.Text = "Packet Client";
            // 
            // Locate
            // 
            this.Locate.Animated = true;
            this.Locate.BorderColor = System.Drawing.Color.White;
            this.Locate.BorderRadius = 2;
            this.Locate.BorderThickness = 1;
            this.Locate.CheckedState.Parent = this.Locate;
            this.Locate.CustomImages.Parent = this.Locate;
            this.Locate.DisabledState.BorderColor = System.Drawing.Color.DarkGray;
            this.Locate.DisabledState.CustomBorderColor = System.Drawing.Color.DarkGray;
            this.Locate.DisabledState.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(169)))), ((int)(((byte)(169)))), ((int)(((byte)(169)))));
            this.Locate.DisabledState.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(141)))), ((int)(((byte)(141)))), ((int)(((byte)(141)))));
            this.Locate.DisabledState.Parent = this.Locate;
            this.Locate.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(26)))), ((int)(((byte)(26)))));
            this.Locate.Font = new System.Drawing.Font("Minecraft", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Locate.ForeColor = System.Drawing.Color.White;
            this.Locate.HoverState.Parent = this.Locate;
            this.Locate.Location = new System.Drawing.Point(258, 209);
            this.Locate.Name = "Locate";
            this.Locate.ShadowDecoration.Parent = this.Locate;
            this.Locate.Size = new System.Drawing.Size(143, 76);
            this.Locate.TabIndex = 2;
            this.Locate.Text = "Locate";
            this.Locate.Click += new System.EventHandler(this.Locate_Click);
            // 
            // Inject
            // 
            this.Inject.Animated = true;
            this.Inject.BorderColor = System.Drawing.Color.White;
            this.Inject.BorderRadius = 2;
            this.Inject.BorderThickness = 1;
            this.Inject.CheckedState.Parent = this.Inject;
            this.Inject.CustomImages.Parent = this.Inject;
            this.Inject.DisabledState.BorderColor = System.Drawing.Color.DarkGray;
            this.Inject.DisabledState.CustomBorderColor = System.Drawing.Color.DarkGray;
            this.Inject.DisabledState.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(169)))), ((int)(((byte)(169)))), ((int)(((byte)(169)))));
            this.Inject.DisabledState.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(141)))), ((int)(((byte)(141)))), ((int)(((byte)(141)))));
            this.Inject.DisabledState.Parent = this.Inject;
            this.Inject.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(26)))), ((int)(((byte)(26)))), ((int)(((byte)(26)))));
            this.Inject.Font = new System.Drawing.Font("Minecraft", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Inject.ForeColor = System.Drawing.Color.White;
            this.Inject.HoverState.Parent = this.Inject;
            this.Inject.Location = new System.Drawing.Point(407, 209);
            this.Inject.Name = "Inject";
            this.Inject.ShadowDecoration.Parent = this.Inject;
            this.Inject.Size = new System.Drawing.Size(143, 76);
            this.Inject.TabIndex = 3;
            this.Inject.Text = "Inject";
            this.Inject.Click += new System.EventHandler(this.Inject_Click);
            // 
            // Development
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(24)))), ((int)(((byte)(24)))));
            this.Controls.Add(this.Inject);
            this.Controls.Add(this.Locate);
            this.Controls.Add(this.PacketLogo);
            this.ForeColor = System.Drawing.Color.White;
            this.Name = "Development";
            this.Size = new System.Drawing.Size(809, 409);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label PacketLogo;
        private Siticone.Desktop.UI.WinForms.SiticoneButton Locate;
        private Siticone.Desktop.UI.WinForms.SiticoneButton Inject;
    }
}
