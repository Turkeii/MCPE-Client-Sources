namespace BadmanInjector
{
    partial class MainForm
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.MinimizeLabel = new System.Windows.Forms.Label();
            this.CloseLabel = new System.Windows.Forms.Label();
            this.TitleLabel = new System.Windows.Forms.Label();
            this.RightBorderPanel = new System.Windows.Forms.Panel();
            this.LeftBorderPanel = new System.Windows.Forms.Panel();
            this.BottomBorderPanel = new System.Windows.Forms.Panel();
            this.TopBorderPanel = new System.Windows.Forms.Panel();
            this.DecorationToolTip = new System.Windows.Forms.ToolTip(this.components);
            this.TabControl = new System.Windows.Forms.TabControl();
            this.Home = new System.Windows.Forms.TabPage();
            this.ProgressBar = new System.Windows.Forms.Panel();
            this.Infolabel = new System.Windows.Forms.Label();
            this.InjectButton = new System.Windows.Forms.Label();
            this.Dev = new System.Windows.Forms.TabPage();
            this.Help = new System.Windows.Forms.TabPage();
            this.label3 = new System.Windows.Forms.Label();
            this.HomePageTab = new System.Windows.Forms.Label();
            this.DevInjectPageTab = new System.Windows.Forms.Label();
            this.HelpPageTab = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.DevInfoText = new System.Windows.Forms.Label();
            this.LocateDllButton = new System.Windows.Forms.Label();
            this.InjectDllButton = new System.Windows.Forms.Label();
            this.uselessthingjustneededfortheinjectfunction = new System.Windows.Forms.Panel();
            this.TabControl.SuspendLayout();
            this.Home.SuspendLayout();
            this.Dev.SuspendLayout();
            this.Help.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            this.SuspendLayout();
            // 
            // MinimizeLabel
            // 
            this.MinimizeLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.MinimizeLabel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(44)))), ((int)(((byte)(44)))));
            this.MinimizeLabel.Font = new System.Drawing.Font("Marlett", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MinimizeLabel.Location = new System.Drawing.Point(683, 1);
            this.MinimizeLabel.Name = "MinimizeLabel";
            this.MinimizeLabel.Size = new System.Drawing.Size(23, 23);
            this.MinimizeLabel.TabIndex = 20;
            this.MinimizeLabel.Text = "0";
            this.MinimizeLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.DecorationToolTip.SetToolTip(this.MinimizeLabel, "Minimize");
            this.MinimizeLabel.Click += new System.EventHandler(this.MinimizeLabel_Click);
            // 
            // CloseLabel
            // 
            this.CloseLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.CloseLabel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(44)))), ((int)(((byte)(44)))));
            this.CloseLabel.Font = new System.Drawing.Font("Marlett", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CloseLabel.Location = new System.Drawing.Point(709, 1);
            this.CloseLabel.Name = "CloseLabel";
            this.CloseLabel.Size = new System.Drawing.Size(23, 23);
            this.CloseLabel.TabIndex = 22;
            this.CloseLabel.Text = "r";
            this.CloseLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.DecorationToolTip.SetToolTip(this.CloseLabel, "Close");
            // 
            // TitleLabel
            // 
            this.TitleLabel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(44)))), ((int)(((byte)(44)))));
            this.TitleLabel.Dock = System.Windows.Forms.DockStyle.Top;
            this.TitleLabel.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TitleLabel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(68)))), ((int)(((byte)(68)))), ((int)(((byte)(68)))));
            this.TitleLabel.Location = new System.Drawing.Point(0, 0);
            this.TitleLabel.Name = "TitleLabel";
            this.TitleLabel.Size = new System.Drawing.Size(734, 24);
            this.TitleLabel.TabIndex = 23;
            this.TitleLabel.Text = "Title";
            this.TitleLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.TitleLabel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.TitleLabel_MouseDown);
            this.TitleLabel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.TitleLabel_MouseMove);
            this.TitleLabel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.TitleLabel_MouseUp);
            // 
            // RightBorderPanel
            // 
            this.RightBorderPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.RightBorderPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(43)))), ((int)(((byte)(87)))), ((int)(((byte)(154)))));
            this.RightBorderPanel.Cursor = System.Windows.Forms.Cursors.SizeWE;
            this.RightBorderPanel.Location = new System.Drawing.Point(733, 1);
            this.RightBorderPanel.Name = "RightBorderPanel";
            this.RightBorderPanel.Size = new System.Drawing.Size(1, 409);
            this.RightBorderPanel.TabIndex = 19;
            // 
            // LeftBorderPanel
            // 
            this.LeftBorderPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.LeftBorderPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(43)))), ((int)(((byte)(87)))), ((int)(((byte)(154)))));
            this.LeftBorderPanel.Cursor = System.Windows.Forms.Cursors.SizeWE;
            this.LeftBorderPanel.Location = new System.Drawing.Point(0, 1);
            this.LeftBorderPanel.Name = "LeftBorderPanel";
            this.LeftBorderPanel.Size = new System.Drawing.Size(1, 409);
            this.LeftBorderPanel.TabIndex = 18;
            // 
            // BottomBorderPanel
            // 
            this.BottomBorderPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.BottomBorderPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(43)))), ((int)(((byte)(87)))), ((int)(((byte)(154)))));
            this.BottomBorderPanel.Cursor = System.Windows.Forms.Cursors.SizeNS;
            this.BottomBorderPanel.Location = new System.Drawing.Point(-5, 410);
            this.BottomBorderPanel.Name = "BottomBorderPanel";
            this.BottomBorderPanel.Size = new System.Drawing.Size(742, 1);
            this.BottomBorderPanel.TabIndex = 17;
            // 
            // TopBorderPanel
            // 
            this.TopBorderPanel.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.TopBorderPanel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(43)))), ((int)(((byte)(87)))), ((int)(((byte)(154)))));
            this.TopBorderPanel.Cursor = System.Windows.Forms.Cursors.SizeNS;
            this.TopBorderPanel.Location = new System.Drawing.Point(-2, 0);
            this.TopBorderPanel.Name = "TopBorderPanel";
            this.TopBorderPanel.Size = new System.Drawing.Size(737, 1);
            this.TopBorderPanel.TabIndex = 16;
            // 
            // TabControl
            // 
            this.TabControl.Controls.Add(this.Home);
            this.TabControl.Controls.Add(this.Dev);
            this.TabControl.Controls.Add(this.Help);
            this.TabControl.Location = new System.Drawing.Point(-7, 0);
            this.TabControl.Name = "TabControl";
            this.TabControl.SelectedIndex = 0;
            this.TabControl.Size = new System.Drawing.Size(749, 416);
            this.TabControl.TabIndex = 25;
            // 
            // Home
            // 
            this.Home.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.Home.Controls.Add(this.pictureBox2);
            this.Home.Controls.Add(this.ProgressBar);
            this.Home.Controls.Add(this.Infolabel);
            this.Home.Controls.Add(this.InjectButton);
            this.Home.Location = new System.Drawing.Point(4, 22);
            this.Home.Name = "Home";
            this.Home.Padding = new System.Windows.Forms.Padding(3);
            this.Home.Size = new System.Drawing.Size(741, 390);
            this.Home.TabIndex = 0;
            this.Home.Text = "Home";
            // 
            // ProgressBar
            // 
            this.ProgressBar.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(44)))), ((int)(((byte)(44)))));
            this.ProgressBar.Location = new System.Drawing.Point(233, 186);
            this.ProgressBar.Name = "ProgressBar";
            this.ProgressBar.Size = new System.Drawing.Size(270, 7);
            this.ProgressBar.TabIndex = 33;
            // 
            // Infolabel
            // 
            this.Infolabel.AutoSize = true;
            this.Infolabel.ForeColor = System.Drawing.Color.White;
            this.Infolabel.Location = new System.Drawing.Point(7, 369);
            this.Infolabel.Name = "Infolabel";
            this.Infolabel.Size = new System.Drawing.Size(65, 13);
            this.Infolabel.TabIndex = 32;
            this.Infolabel.Text = "Not Injected";
            // 
            // InjectButton
            // 
            this.InjectButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(44)))), ((int)(((byte)(44)))));
            this.InjectButton.Font = new System.Drawing.Font("Segoe UI", 15.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.InjectButton.ForeColor = System.Drawing.Color.White;
            this.InjectButton.Location = new System.Drawing.Point(233, 198);
            this.InjectButton.Name = "InjectButton";
            this.InjectButton.Size = new System.Drawing.Size(270, 80);
            this.InjectButton.TabIndex = 30;
            this.InjectButton.Text = "Inject";
            this.InjectButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.InjectButton.Click += new System.EventHandler(this.InjectButton_Click);
            // 
            // Dev
            // 
            this.Dev.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.Dev.Controls.Add(this.uselessthingjustneededfortheinjectfunction);
            this.Dev.Controls.Add(this.InjectDllButton);
            this.Dev.Controls.Add(this.pictureBox3);
            this.Dev.Controls.Add(this.DevInfoText);
            this.Dev.Controls.Add(this.LocateDllButton);
            this.Dev.Location = new System.Drawing.Point(4, 22);
            this.Dev.Name = "Dev";
            this.Dev.Padding = new System.Windows.Forms.Padding(3);
            this.Dev.Size = new System.Drawing.Size(741, 390);
            this.Dev.TabIndex = 1;
            this.Dev.Text = "Dev";
            // 
            // Help
            // 
            this.Help.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.Help.Controls.Add(this.label3);
            this.Help.Location = new System.Drawing.Point(4, 22);
            this.Help.Name = "Help";
            this.Help.Padding = new System.Windows.Forms.Padding(3);
            this.Help.Size = new System.Drawing.Size(741, 390);
            this.Help.TabIndex = 2;
            this.Help.Text = "Help";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(182, 6);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 13);
            this.label3.TabIndex = 0;
            this.label3.Text = "Help Page";
            // 
            // HomePageTab
            // 
            this.HomePageTab.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(44)))), ((int)(((byte)(44)))));
            this.HomePageTab.ForeColor = System.Drawing.Color.White;
            this.HomePageTab.Location = new System.Drawing.Point(26, 1);
            this.HomePageTab.Name = "HomePageTab";
            this.HomePageTab.Size = new System.Drawing.Size(65, 23);
            this.HomePageTab.TabIndex = 26;
            this.HomePageTab.Text = "Home";
            this.HomePageTab.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.HomePageTab.Click += new System.EventHandler(this.HomePageTab_Click);
            // 
            // DevInjectPageTab
            // 
            this.DevInjectPageTab.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(44)))), ((int)(((byte)(44)))));
            this.DevInjectPageTab.ForeColor = System.Drawing.Color.White;
            this.DevInjectPageTab.Location = new System.Drawing.Point(94, 1);
            this.DevInjectPageTab.Name = "DevInjectPageTab";
            this.DevInjectPageTab.Size = new System.Drawing.Size(75, 23);
            this.DevInjectPageTab.TabIndex = 27;
            this.DevInjectPageTab.Text = "Development";
            this.DevInjectPageTab.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.DevInjectPageTab.Click += new System.EventHandler(this.DevInjectPageTab_Click);
            // 
            // HelpPageTab
            // 
            this.HelpPageTab.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(44)))), ((int)(((byte)(44)))));
            this.HelpPageTab.ForeColor = System.Drawing.Color.White;
            this.HelpPageTab.Location = new System.Drawing.Point(172, 1);
            this.HelpPageTab.Name = "HelpPageTab";
            this.HelpPageTab.Size = new System.Drawing.Size(70, 23);
            this.HelpPageTab.TabIndex = 28;
            this.HelpPageTab.Text = "Help";
            this.HelpPageTab.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.HelpPageTab.Click += new System.EventHandler(this.HelpPageTab_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(44)))), ((int)(((byte)(44)))));
            this.pictureBox1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.BackgroundImage")));
            this.pictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox1.Location = new System.Drawing.Point(1, 1);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(24, 23);
            this.pictureBox1.TabIndex = 29;
            this.pictureBox1.TabStop = false;
            // 
            // pictureBox2
            // 
            this.pictureBox2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.pictureBox2.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox2.BackgroundImage")));
            this.pictureBox2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox2.Location = new System.Drawing.Point(162, 77);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(405, 103);
            this.pictureBox2.TabIndex = 30;
            this.pictureBox2.TabStop = false;
            // 
            // pictureBox3
            // 
            this.pictureBox3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.pictureBox3.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox3.BackgroundImage")));
            this.pictureBox3.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox3.Location = new System.Drawing.Point(162, 77);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(405, 103);
            this.pictureBox3.TabIndex = 34;
            this.pictureBox3.TabStop = false;
            // 
            // DevInfoText
            // 
            this.DevInfoText.AutoSize = true;
            this.DevInfoText.ForeColor = System.Drawing.Color.White;
            this.DevInfoText.Location = new System.Drawing.Point(7, 369);
            this.DevInfoText.Name = "DevInfoText";
            this.DevInfoText.Size = new System.Drawing.Size(65, 13);
            this.DevInfoText.TabIndex = 36;
            this.DevInfoText.Text = "Not Injected";
            // 
            // LocateDllButton
            // 
            this.LocateDllButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(44)))), ((int)(((byte)(44)))));
            this.LocateDllButton.Font = new System.Drawing.Font("Segoe UI", 15.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LocateDllButton.ForeColor = System.Drawing.Color.White;
            this.LocateDllButton.Location = new System.Drawing.Point(233, 193);
            this.LocateDllButton.Name = "LocateDllButton";
            this.LocateDllButton.Size = new System.Drawing.Size(133, 90);
            this.LocateDllButton.TabIndex = 35;
            this.LocateDllButton.Text = "Locate";
            this.LocateDllButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.LocateDllButton.Click += new System.EventHandler(this.LocateDllButton_Click);
            // 
            // InjectDllButton
            // 
            this.InjectDllButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(44)))), ((int)(((byte)(44)))), ((int)(((byte)(44)))));
            this.InjectDllButton.Font = new System.Drawing.Font("Segoe UI", 15.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.InjectDllButton.ForeColor = System.Drawing.Color.White;
            this.InjectDllButton.Location = new System.Drawing.Point(370, 193);
            this.InjectDllButton.Name = "InjectDllButton";
            this.InjectDllButton.Size = new System.Drawing.Size(133, 90);
            this.InjectDllButton.TabIndex = 38;
            this.InjectDllButton.Text = "Inject";
            this.InjectDllButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.InjectDllButton.Click += new System.EventHandler(this.InjectDllButton_Click);
            // 
            // uselessthingjustneededfortheinjectfunction
            // 
            this.uselessthingjustneededfortheinjectfunction.Location = new System.Drawing.Point(999, 999);
            this.uselessthingjustneededfortheinjectfunction.Name = "uselessthingjustneededfortheinjectfunction";
            this.uselessthingjustneededfortheinjectfunction.Size = new System.Drawing.Size(10, 10);
            this.uselessthingjustneededfortheinjectfunction.TabIndex = 39;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(33)))), ((int)(((byte)(33)))), ((int)(((byte)(33)))));
            this.ClientSize = new System.Drawing.Size(734, 411);
            this.Controls.Add(this.TabControl);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.HelpPageTab);
            this.Controls.Add(this.DevInjectPageTab);
            this.Controls.Add(this.HomePageTab);
            this.Controls.Add(this.MinimizeLabel);
            this.Controls.Add(this.CloseLabel);
            this.Controls.Add(this.RightBorderPanel);
            this.Controls.Add(this.LeftBorderPanel);
            this.Controls.Add(this.BottomBorderPanel);
            this.Controls.Add(this.TopBorderPanel);
            this.Controls.Add(this.TitleLabel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainForm";
            this.Text = "Badman Injector";
            this.TabControl.ResumeLayout(false);
            this.Home.ResumeLayout(false);
            this.Home.PerformLayout();
            this.Dev.ResumeLayout(false);
            this.Dev.PerformLayout();
            this.Help.ResumeLayout(false);
            this.Help.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Label MinimizeLabel;
        private System.Windows.Forms.ToolTip DecorationToolTip;
        private System.Windows.Forms.Label CloseLabel;
        private System.Windows.Forms.Label TitleLabel;
        private System.Windows.Forms.Panel RightBorderPanel;
        private System.Windows.Forms.Panel LeftBorderPanel;
        private System.Windows.Forms.Panel BottomBorderPanel;
        private System.Windows.Forms.Panel TopBorderPanel;
        private System.Windows.Forms.TabControl TabControl;
        private System.Windows.Forms.TabPage Home;
        private System.Windows.Forms.TabPage Dev;
        private System.Windows.Forms.Label HomePageTab;
        private System.Windows.Forms.Label DevInjectPageTab;
        private System.Windows.Forms.Label HelpPageTab;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.TabPage Help;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label InjectButton;
        private System.Windows.Forms.Label Infolabel;
        private System.Windows.Forms.Panel ProgressBar;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.Label InjectDllButton;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.Label DevInfoText;
        private System.Windows.Forms.Label LocateDllButton;
        private System.Windows.Forms.Panel uselessthingjustneededfortheinjectfunction;
    }
}

