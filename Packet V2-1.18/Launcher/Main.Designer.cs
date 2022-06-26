namespace PacketLauncher
{
    partial class Main
    {
        private System.ComponentModel.IContainer components = null;

        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Main));
            this.Elipse = new Siticone.Desktop.UI.WinForms.SiticoneElipse(this.components);
            this.TaskbarIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.DragTitle = new Siticone.Desktop.UI.WinForms.SiticoneDragControl(this.components);
            this.TitleBar = new Siticone.Desktop.UI.WinForms.SiticonePanel();
            this.Settings = new Siticone.Desktop.UI.WinForms.SiticoneButton();
            this.Development = new Siticone.Desktop.UI.WinForms.SiticoneButton();
            this.Home = new Siticone.Desktop.UI.WinForms.SiticoneButton();
            this.Minimize = new Siticone.Desktop.UI.WinForms.SiticoneControlBox();
            this.Exit = new Siticone.Desktop.UI.WinForms.SiticoneControlBox();
            this.Logo = new System.Windows.Forms.Panel();
            this.DragMain = new Siticone.Desktop.UI.WinForms.SiticoneDragControl(this.components);
            this.ControlDockPanel = new System.Windows.Forms.Panel();
            this.Glow = new Siticone.Desktop.UI.WinForms.SiticoneShadowForm(this.components);
            this.TitleBar.SuspendLayout();
            this.SuspendLayout();
            // 
            // Elipse
            // 
            this.Elipse.BorderRadius = 16;
            this.Elipse.TargetControl = this;
            // 
            // TaskbarIcon
            // 
            this.TaskbarIcon.Text = "Packet Injector";
            this.TaskbarIcon.Visible = true;
            // 
            // DragTitle
            // 
            this.DragTitle.TargetControl = this.TitleBar;
            // 
            // TitleBar
            // 
            this.TitleBar.Controls.Add(this.Settings);
            this.TitleBar.Controls.Add(this.Development);
            this.TitleBar.Controls.Add(this.Home);
            this.TitleBar.Controls.Add(this.Minimize);
            this.TitleBar.Controls.Add(this.Exit);
            this.TitleBar.Controls.Add(this.Logo);
            this.TitleBar.Dock = System.Windows.Forms.DockStyle.Top;
            this.TitleBar.Location = new System.Drawing.Point(0, 0);
            this.TitleBar.Name = "TitleBar";
            this.TitleBar.ShadowDecoration.Parent = this.TitleBar;
            this.TitleBar.Size = new System.Drawing.Size(809, 28);
            this.TitleBar.TabIndex = 0;
            // 
            // Settings
            // 
            this.Settings.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.Settings.Animated = true;
            this.Settings.BackColor = System.Drawing.Color.Transparent;
            this.Settings.BorderColor = System.Drawing.Color.Transparent;
            this.Settings.CheckedState.Parent = this.Settings;
            this.Settings.CustomImages.Parent = this.Settings;
            this.Settings.DisabledState.BorderColor = System.Drawing.Color.DarkGray;
            this.Settings.DisabledState.CustomBorderColor = System.Drawing.Color.DarkGray;
            this.Settings.DisabledState.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(169)))), ((int)(((byte)(169)))), ((int)(((byte)(169)))));
            this.Settings.DisabledState.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(141)))), ((int)(((byte)(141)))), ((int)(((byte)(141)))));
            this.Settings.DisabledState.Parent = this.Settings;
            this.Settings.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(24)))), ((int)(((byte)(24)))));
            this.Settings.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.Settings.ForeColor = System.Drawing.Color.White;
            this.Settings.HoverState.Parent = this.Settings;
            this.Settings.Location = new System.Drawing.Point(451, 0);
            this.Settings.Name = "Settings";
            this.Settings.ShadowDecoration.Parent = this.Settings;
            this.Settings.Size = new System.Drawing.Size(73, 27);
            this.Settings.TabIndex = 12;
            this.Settings.Text = "Settings";
            this.Settings.UseTransparentBackground = true;
            this.Settings.Click += new System.EventHandler(this.Settings_Click);
            // 
            // Development
            // 
            this.Development.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.Development.Animated = true;
            this.Development.BackColor = System.Drawing.Color.Transparent;
            this.Development.BorderColor = System.Drawing.Color.Transparent;
            this.Development.CheckedState.Parent = this.Development;
            this.Development.CustomImages.Parent = this.Development;
            this.Development.DisabledState.BorderColor = System.Drawing.Color.DarkGray;
            this.Development.DisabledState.CustomBorderColor = System.Drawing.Color.DarkGray;
            this.Development.DisabledState.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(169)))), ((int)(((byte)(169)))), ((int)(((byte)(169)))));
            this.Development.DisabledState.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(141)))), ((int)(((byte)(141)))), ((int)(((byte)(141)))));
            this.Development.DisabledState.Parent = this.Development;
            this.Development.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(24)))), ((int)(((byte)(24)))));
            this.Development.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.Development.ForeColor = System.Drawing.Color.White;
            this.Development.HoverState.Parent = this.Development;
            this.Development.Location = new System.Drawing.Point(347, 0);
            this.Development.Name = "Development";
            this.Development.ShadowDecoration.Parent = this.Development;
            this.Development.Size = new System.Drawing.Size(103, 26);
            this.Development.TabIndex = 11;
            this.Development.Text = "Development";
            this.Development.UseTransparentBackground = true;
            this.Development.Click += new System.EventHandler(this.Development_Click);
            // 
            // Home
            // 
            this.Home.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.Home.Animated = true;
            this.Home.BackColor = System.Drawing.Color.Transparent;
            this.Home.BorderColor = System.Drawing.Color.Transparent;
            this.Home.CheckedState.Parent = this.Home;
            this.Home.CustomImages.Parent = this.Home;
            this.Home.DisabledState.BorderColor = System.Drawing.Color.DarkGray;
            this.Home.DisabledState.CustomBorderColor = System.Drawing.Color.DarkGray;
            this.Home.DisabledState.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(169)))), ((int)(((byte)(169)))), ((int)(((byte)(169)))));
            this.Home.DisabledState.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(141)))), ((int)(((byte)(141)))), ((int)(((byte)(141)))));
            this.Home.DisabledState.Parent = this.Home;
            this.Home.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(24)))), ((int)(((byte)(24)))));
            this.Home.Font = new System.Drawing.Font("Segoe UI", 9F);
            this.Home.ForeColor = System.Drawing.Color.White;
            this.Home.HoverState.Parent = this.Home;
            this.Home.Location = new System.Drawing.Point(284, 0);
            this.Home.Name = "Home";
            this.Home.ShadowDecoration.Parent = this.Home;
            this.Home.Size = new System.Drawing.Size(63, 26);
            this.Home.TabIndex = 10;
            this.Home.Text = "Home";
            this.Home.UseTransparentBackground = true;
            this.Home.Click += new System.EventHandler(this.Home_Click);
            // 
            // Minimize
            // 
            this.Minimize.ControlBoxStyle = Siticone.Desktop.UI.WinForms.Enums.ControlBoxStyle.Custom;
            this.Minimize.ControlBoxType = Siticone.Desktop.UI.WinForms.Enums.ControlBoxType.MinimizeBox;
            this.Minimize.Dock = System.Windows.Forms.DockStyle.Right;
            this.Minimize.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(24)))), ((int)(((byte)(24)))));
            this.Minimize.HoverState.Parent = this.Minimize;
            this.Minimize.IconColor = System.Drawing.Color.White;
            this.Minimize.Location = new System.Drawing.Point(753, 0);
            this.Minimize.Name = "Minimize";
            this.Minimize.ShadowDecoration.Parent = this.Minimize;
            this.Minimize.Size = new System.Drawing.Size(28, 28);
            this.Minimize.TabIndex = 9;
            // 
            // Exit
            // 
            this.Exit.ControlBoxStyle = Siticone.Desktop.UI.WinForms.Enums.ControlBoxStyle.Custom;
            this.Exit.Dock = System.Windows.Forms.DockStyle.Right;
            this.Exit.FillColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(24)))), ((int)(((byte)(24)))));
            this.Exit.HoverState.Parent = this.Exit;
            this.Exit.IconColor = System.Drawing.Color.White;
            this.Exit.Location = new System.Drawing.Point(781, 0);
            this.Exit.Name = "Exit";
            this.Exit.ShadowDecoration.Parent = this.Exit;
            this.Exit.Size = new System.Drawing.Size(28, 28);
            this.Exit.TabIndex = 8;
            // 
            // Logo
            // 
            this.Logo.BackColor = System.Drawing.Color.Transparent;
            this.Logo.BackgroundImage = global::PacketLauncher.Properties.Resources.icon2;
            this.Logo.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.Logo.Dock = System.Windows.Forms.DockStyle.Left;
            this.Logo.Location = new System.Drawing.Point(0, 0);
            this.Logo.Name = "Logo";
            this.Logo.Size = new System.Drawing.Size(28, 28);
            this.Logo.TabIndex = 7;
            // 
            // DragMain
            // 
            this.DragMain.TargetControl = this;
            // 
            // ControlDockPanel
            // 
            this.ControlDockPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ControlDockPanel.Location = new System.Drawing.Point(0, 28);
            this.ControlDockPanel.Name = "ControlDockPanel";
            this.ControlDockPanel.Size = new System.Drawing.Size(809, 409);
            this.ControlDockPanel.TabIndex = 1;
            // 
            // Glow
            // 
            this.Glow.BorderRadius = 22;
            this.Glow.ShadowColor = System.Drawing.Color.White;
            this.Glow.TargetForm = this;
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(24)))), ((int)(((byte)(24)))));
            this.ClientSize = new System.Drawing.Size(809, 437);
            this.Controls.Add(this.ControlDockPanel);
            this.Controls.Add(this.TitleBar);
            this.ForeColor = System.Drawing.Color.White;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Packet Injector";
            this.Load += new System.EventHandler(this.Main_Load);
            this.TitleBar.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.NotifyIcon TaskbarIcon;
        private Siticone.Desktop.UI.WinForms.SiticoneDragControl DragTitle;
        private Siticone.Desktop.UI.WinForms.SiticoneDragControl DragMain;
        private Siticone.Desktop.UI.WinForms.SiticonePanel TitleBar;
        private System.Windows.Forms.Panel Logo;
        private Siticone.Desktop.UI.WinForms.SiticoneControlBox Minimize;
        private Siticone.Desktop.UI.WinForms.SiticoneControlBox Exit;
        private Siticone.Desktop.UI.WinForms.SiticoneButton Home;
        private Siticone.Desktop.UI.WinForms.SiticoneButton Development;
        private Siticone.Desktop.UI.WinForms.SiticoneButton Settings;
        private System.Windows.Forms.Panel ControlDockPanel;
        public Siticone.Desktop.UI.WinForms.SiticoneElipse Elipse;
        private Siticone.Desktop.UI.WinForms.SiticoneShadowForm Glow;
    }
}

