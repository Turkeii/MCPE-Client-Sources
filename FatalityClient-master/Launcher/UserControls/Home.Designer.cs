namespace PacketLauncher.UserControls
{
    partial class Home
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
            this.PacketLabel = new System.Windows.Forms.Label();
            this.Inject = new Siticone.Desktop.UI.WinForms.SiticoneButton();
            this.Status = new System.Windows.Forms.Label();
            this.Progress = new Siticone.Desktop.UI.WinForms.SiticoneProgressBar();
            this.SuspendLayout();
            // 
            // PacketLabel
            // 
            this.PacketLabel.AutoSize = true;
            this.PacketLabel.Font = new System.Drawing.Font("Minecraft", 47.99999F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PacketLabel.Location = new System.Drawing.Point(193, 110);
            this.PacketLabel.Name = "PacketLabel";
            this.PacketLabel.Size = new System.Drawing.Size(439, 64);
            this.PacketLabel.TabIndex = 0;
            this.PacketLabel.Text = "Packet Client";
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
            this.Inject.Location = new System.Drawing.Point(261, 210);
            this.Inject.Name = "Inject";
            this.Inject.ShadowDecoration.Parent = this.Inject;
            this.Inject.Size = new System.Drawing.Size(287, 76);
            this.Inject.TabIndex = 1;
            this.Inject.Text = "Inject";
            this.Inject.Click += new System.EventHandler(this.Inject_Click);
            // 
            // Status
            // 
            this.Status.AutoSize = true;
            this.Status.Font = new System.Drawing.Font("Minecraft", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Status.Location = new System.Drawing.Point(3, 388);
            this.Status.Name = "Status";
            this.Status.Size = new System.Drawing.Size(84, 19);
            this.Status.TabIndex = 2;
            this.Status.Text = "Waiting...";
            // 
            // Progress
            // 
            this.Progress.BorderColor = System.Drawing.Color.White;
            this.Progress.BorderRadius = 1;
            this.Progress.BorderThickness = 1;
            this.Progress.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(24)))), ((int)(((byte)(24)))));
            this.Progress.Location = new System.Drawing.Point(261, 195);
            this.Progress.Maximum = 5;
            this.Progress.Name = "Progress";
            this.Progress.ProgressColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.Progress.ProgressColor2 = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.Progress.ShadowDecoration.Parent = this.Progress;
            this.Progress.Size = new System.Drawing.Size(287, 9);
            this.Progress.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.Progress.TabIndex = 3;
            this.Progress.TextRenderingHint = System.Drawing.Text.TextRenderingHint.SystemDefault;
            // 
            // Home
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(24)))), ((int)(((byte)(24)))));
            this.Controls.Add(this.Progress);
            this.Controls.Add(this.Status);
            this.Controls.Add(this.Inject);
            this.Controls.Add(this.PacketLabel);
            this.ForeColor = System.Drawing.Color.White;
            this.Name = "Home";
            this.Size = new System.Drawing.Size(809, 409);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label PacketLabel;
        private Siticone.Desktop.UI.WinForms.SiticoneButton Inject;
        public System.Windows.Forms.Label Status;
        private Siticone.Desktop.UI.WinForms.SiticoneProgressBar Progress;
    }
}
