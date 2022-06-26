namespace PacketLauncher.UserControls
{
    partial class Settings
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
            this.Rpc = new Siticone.Desktop.UI.WinForms.SiticoneCheckBox();
            this.RoundedCorners = new Siticone.Desktop.UI.WinForms.SiticoneCheckBox();
            this.RoundnessSlider = new Siticone.Desktop.UI.WinForms.SiticoneTrackBar();
            this.RoundnessLabel = new Siticone.Desktop.UI.WinForms.SiticoneHtmlLabel();
            this.SuspendLayout();
            // 
            // Rpc
            // 
            this.Rpc.Animated = true;
            this.Rpc.AutoSize = true;
            this.Rpc.Checked = true;
            this.Rpc.CheckedState.BorderColor = System.Drawing.Color.White;
            this.Rpc.CheckedState.BorderRadius = 0;
            this.Rpc.CheckedState.BorderThickness = 0;
            this.Rpc.CheckedState.FillColor = System.Drawing.Color.White;
            this.Rpc.CheckMarkColor = System.Drawing.Color.Black;
            this.Rpc.CheckState = System.Windows.Forms.CheckState.Checked;
            this.Rpc.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F);
            this.Rpc.ForeColor = System.Drawing.Color.White;
            this.Rpc.Location = new System.Drawing.Point(3, 3);
            this.Rpc.Name = "Rpc";
            this.Rpc.Size = new System.Drawing.Size(135, 17);
            this.Rpc.TabIndex = 0;
            this.Rpc.Text = "Discord Rich Presence";
            this.Rpc.UncheckedState.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(125)))), ((int)(((byte)(137)))), ((int)(((byte)(149)))));
            this.Rpc.UncheckedState.BorderRadius = 0;
            this.Rpc.UncheckedState.BorderThickness = 0;
            this.Rpc.UncheckedState.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(125)))), ((int)(((byte)(137)))), ((int)(((byte)(149)))));
            this.Rpc.CheckedChanged += new System.EventHandler(this.Rpc_CheckedChanged);
            // 
            // RoundedCorners
            // 
            this.RoundedCorners.Animated = true;
            this.RoundedCorners.AutoSize = true;
            this.RoundedCorners.Checked = true;
            this.RoundedCorners.CheckedState.BorderColor = System.Drawing.Color.White;
            this.RoundedCorners.CheckedState.BorderRadius = 0;
            this.RoundedCorners.CheckedState.BorderThickness = 0;
            this.RoundedCorners.CheckedState.FillColor = System.Drawing.Color.White;
            this.RoundedCorners.CheckMarkColor = System.Drawing.Color.Black;
            this.RoundedCorners.CheckState = System.Windows.Forms.CheckState.Checked;
            this.RoundedCorners.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F);
            this.RoundedCorners.Location = new System.Drawing.Point(3, 26);
            this.RoundedCorners.Name = "RoundedCorners";
            this.RoundedCorners.Size = new System.Drawing.Size(109, 17);
            this.RoundedCorners.TabIndex = 1;
            this.RoundedCorners.Text = "Rounded Corners";
            this.RoundedCorners.UncheckedState.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(125)))), ((int)(((byte)(137)))), ((int)(((byte)(149)))));
            this.RoundedCorners.UncheckedState.BorderRadius = 0;
            this.RoundedCorners.UncheckedState.BorderThickness = 0;
            this.RoundedCorners.UncheckedState.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(125)))), ((int)(((byte)(137)))), ((int)(((byte)(149)))));
            this.RoundedCorners.CheckedChanged += new System.EventHandler(this.RoundedCorners_CheckedChanged);
            // 
            // RoundnessSlider
            // 
            this.RoundnessSlider.FillColor = System.Drawing.Color.DarkGray;
            this.RoundnessSlider.HoverState.Parent = this.RoundnessSlider;
            this.RoundnessSlider.Location = new System.Drawing.Point(118, 26);
            this.RoundnessSlider.Maximum = 20;
            this.RoundnessSlider.Minimum = 3;
            this.RoundnessSlider.Name = "RoundnessSlider";
            this.RoundnessSlider.Size = new System.Drawing.Size(300, 17);
            this.RoundnessSlider.Style = Siticone.Desktop.UI.WinForms.Enums.TrackBarStyle.Metro;
            this.RoundnessSlider.TabIndex = 2;
            this.RoundnessSlider.ThumbColor = System.Drawing.Color.White;
            this.RoundnessSlider.Value = 7;
            this.RoundnessSlider.Scroll += new System.Windows.Forms.ScrollEventHandler(this.RoundnessSlider_Scroll);
            // 
            // RoundnessLabel
            // 
            this.RoundnessLabel.BackColor = System.Drawing.Color.Transparent;
            this.RoundnessLabel.Location = new System.Drawing.Point(424, 28);
            this.RoundnessLabel.Name = "RoundnessLabel";
            this.RoundnessLabel.Size = new System.Drawing.Size(50, 15);
            this.RoundnessLabel.TabIndex = 3;
            this.RoundnessLabel.Text = "Value: <b>7</b>";
            // 
            // Settings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(24)))), ((int)(((byte)(24)))));
            this.Controls.Add(this.RoundnessLabel);
            this.Controls.Add(this.RoundnessSlider);
            this.Controls.Add(this.RoundedCorners);
            this.Controls.Add(this.Rpc);
            this.ForeColor = System.Drawing.Color.White;
            this.Name = "Settings";
            this.Size = new System.Drawing.Size(809, 409);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Siticone.Desktop.UI.WinForms.SiticoneCheckBox Rpc;
        private Siticone.Desktop.UI.WinForms.SiticoneCheckBox RoundedCorners;
        public Siticone.Desktop.UI.WinForms.SiticoneTrackBar RoundnessSlider;
        private Siticone.Desktop.UI.WinForms.SiticoneHtmlLabel RoundnessLabel;
    }
}
