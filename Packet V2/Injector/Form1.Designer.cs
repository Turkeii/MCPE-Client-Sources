
namespace PacketClient
{
    partial class Form1
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.panel1 = new System.Windows.Forms.Panel();
            this.SettingsPage = new System.Windows.Forms.Panel();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.panel6 = new System.Windows.Forms.Panel();
            this.panel7 = new System.Windows.Forms.Panel();
            this.label4 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.panel8 = new System.Windows.Forms.Panel();
            this.panel5 = new System.Windows.Forms.Panel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.HomePage = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.panel10 = new System.Windows.Forms.Panel();
            this.DevelopmentPage = new System.Windows.Forms.Panel();
            this.button4 = new System.Windows.Forms.Button();
            this.panel11 = new System.Windows.Forms.Panel();
            this.button2 = new System.Windows.Forms.Button();
            this.subStageText = new System.Windows.Forms.Label();
            this.OutlineFocused = new System.Windows.Forms.Timer(this.components);
            this.PacketTrayIcon = new System.Windows.Forms.NotifyIcon(this.components);
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.injectPacketToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.injectDLLToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.locateDLLToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.panel1.SuspendLayout();
            this.SettingsPage.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.panel6.SuspendLayout();
            this.panel7.SuspendLayout();
            this.HomePage.SuspendLayout();
            this.DevelopmentPage.SuspendLayout();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(24)))), ((int)(((byte)(24)))), ((int)(((byte)(24)))));
            this.panel1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.panel1.Controls.Add(this.SettingsPage);
            this.panel1.Controls.Add(this.panel6);
            this.panel1.Controls.Add(this.panel5);
            this.panel1.Controls.Add(this.panel4);
            this.panel1.Controls.Add(this.panel3);
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Controls.Add(this.HomePage);
            this.panel1.Controls.Add(this.DevelopmentPage);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(725, 400);
            this.panel1.TabIndex = 0;
            // 
            // SettingsPage
            // 
            this.SettingsPage.BackColor = System.Drawing.Color.Transparent;
            this.SettingsPage.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.SettingsPage.Controls.Add(this.groupBox1);
            this.SettingsPage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SettingsPage.Location = new System.Drawing.Point(1, 24);
            this.SettingsPage.Name = "SettingsPage";
            this.SettingsPage.Size = new System.Drawing.Size(723, 375);
            this.SettingsPage.TabIndex = 10;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.checkBox1);
            this.groupBox1.ForeColor = System.Drawing.Color.White;
            this.groupBox1.Location = new System.Drawing.Point(11, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(701, 358);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Checked = true;
            this.checkBox1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox1.Location = new System.Drawing.Point(10, 19);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(87, 17);
            this.checkBox1.TabIndex = 0;
            this.checkBox1.Text = "Discord RPC";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // panel6
            // 
            this.panel6.BackColor = System.Drawing.Color.Transparent;
            this.panel6.Controls.Add(this.panel7);
            this.panel6.Controls.Add(this.panel8);
            this.panel6.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel6.Location = new System.Drawing.Point(1, 1);
            this.panel6.Name = "panel6";
            this.panel6.Size = new System.Drawing.Size(723, 23);
            this.panel6.TabIndex = 8;
            // 
            // panel7
            // 
            this.panel7.BackColor = System.Drawing.Color.Transparent;
            this.panel7.Controls.Add(this.label4);
            this.panel7.Controls.Add(this.label2);
            this.panel7.Controls.Add(this.label6);
            this.panel7.Controls.Add(this.label5);
            this.panel7.Controls.Add(this.label3);
            this.panel7.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel7.Location = new System.Drawing.Point(30, 0);
            this.panel7.Name = "panel7";
            this.panel7.Size = new System.Drawing.Size(693, 23);
            this.panel7.TabIndex = 7;
            this.panel7.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel7_MouseDown);
            this.panel7.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panel7_MouseMove);
            // 
            // label4
            // 
            this.label4.BackColor = System.Drawing.Color.Transparent;
            this.label4.Dock = System.Windows.Forms.DockStyle.Left;
            this.label4.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.ForeColor = System.Drawing.Color.White;
            this.label4.Location = new System.Drawing.Point(117, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(50, 23);
            this.label4.TabIndex = 9;
            this.label4.Text = "Settings";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label4.Click += new System.EventHandler(this.label4_Click);
            this.label4.MouseEnter += new System.EventHandler(this.HoverEvent);
            this.label4.MouseLeave += new System.EventHandler(this.BlinkEvent);
            // 
            // label2
            // 
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.Dock = System.Windows.Forms.DockStyle.Left;
            this.label2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(41, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(76, 23);
            this.label2.TabIndex = 8;
            this.label2.Text = "Development";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label2.Click += new System.EventHandler(this.label2_Click);
            this.label2.MouseEnter += new System.EventHandler(this.HoverEvent);
            this.label2.MouseLeave += new System.EventHandler(this.BlinkEvent);
            // 
            // label6
            // 
            this.label6.BackColor = System.Drawing.Color.Transparent;
            this.label6.Dock = System.Windows.Forms.DockStyle.Right;
            this.label6.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label6.Font = new System.Drawing.Font("Marlett", 8.5F);
            this.label6.ForeColor = System.Drawing.Color.White;
            this.label6.Location = new System.Drawing.Point(655, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(19, 23);
            this.label6.TabIndex = 11;
            this.label6.Text = "0";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label6.Click += new System.EventHandler(this.label6_Click);
            this.label6.MouseEnter += new System.EventHandler(this.HoverEvent);
            this.label6.MouseLeave += new System.EventHandler(this.BlinkEvent);
            // 
            // label5
            // 
            this.label5.BackColor = System.Drawing.Color.Transparent;
            this.label5.Dock = System.Windows.Forms.DockStyle.Right;
            this.label5.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label5.Font = new System.Drawing.Font("Marlett", 8.5F);
            this.label5.ForeColor = System.Drawing.Color.White;
            this.label5.Location = new System.Drawing.Point(674, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(19, 23);
            this.label5.TabIndex = 10;
            this.label5.Text = "r";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label5.Click += new System.EventHandler(this.label5_Click);
            this.label5.MouseEnter += new System.EventHandler(this.HoverEvent);
            this.label5.MouseLeave += new System.EventHandler(this.BlinkEvent);
            // 
            // label3
            // 
            this.label3.BackColor = System.Drawing.Color.Transparent;
            this.label3.Dock = System.Windows.Forms.DockStyle.Left;
            this.label3.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.White;
            this.label3.Location = new System.Drawing.Point(0, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 23);
            this.label3.TabIndex = 7;
            this.label3.Text = "Home";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label3.Click += new System.EventHandler(this.label3_Click);
            this.label3.MouseEnter += new System.EventHandler(this.HoverEvent);
            this.label3.MouseLeave += new System.EventHandler(this.BlinkEvent);
            // 
            // panel8
            // 
            this.panel8.BackColor = System.Drawing.Color.Transparent;
            this.panel8.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("panel8.BackgroundImage")));
            this.panel8.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.panel8.Location = new System.Drawing.Point(2, 0);
            this.panel8.Name = "panel8";
            this.panel8.Size = new System.Drawing.Size(24, 23);
            this.panel8.TabIndex = 6;
            // 
            // panel5
            // 
            this.panel5.BackColor = System.Drawing.Color.White;
            this.panel5.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel5.Location = new System.Drawing.Point(1, 0);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(723, 1);
            this.panel5.TabIndex = 3;
            // 
            // panel4
            // 
            this.panel4.BackColor = System.Drawing.Color.White;
            this.panel4.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel4.Location = new System.Drawing.Point(1, 399);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(723, 1);
            this.panel4.TabIndex = 2;
            // 
            // panel3
            // 
            this.panel3.BackColor = System.Drawing.Color.White;
            this.panel3.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel3.Location = new System.Drawing.Point(0, 0);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(1, 400);
            this.panel3.TabIndex = 1;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.White;
            this.panel2.Dock = System.Windows.Forms.DockStyle.Right;
            this.panel2.Location = new System.Drawing.Point(724, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(1, 400);
            this.panel2.TabIndex = 0;
            // 
            // HomePage
            // 
            this.HomePage.BackColor = System.Drawing.Color.Transparent;
            this.HomePage.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.HomePage.Controls.Add(this.button1);
            this.HomePage.Controls.Add(this.label1);
            this.HomePage.Controls.Add(this.panel10);
            this.HomePage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.HomePage.Location = new System.Drawing.Point(0, 0);
            this.HomePage.Name = "HomePage";
            this.HomePage.Size = new System.Drawing.Size(725, 400);
            this.HomePage.TabIndex = 7;
            // 
            // button1
            // 
            this.button1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button1.FlatAppearance.BorderColor = System.Drawing.Color.DarkGray;
            this.button1.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.button1.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.Font = new System.Drawing.Font("Minecraft", 20F);
            this.button1.ForeColor = System.Drawing.Color.White;
            this.button1.Location = new System.Drawing.Point(204, 218);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(287, 76);
            this.button1.TabIndex = 5;
            this.button1.Text = "Inject";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            this.button1.MouseEnter += new System.EventHandler(this.HoverEvent);
            this.button1.MouseLeave += new System.EventHandler(this.BlinkEvent);
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label1.Font = new System.Drawing.Font("Minecraft", 14.25F);
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(11, 369);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(96, 23);
            this.label1.TabIndex = 4;
            this.label1.Text = "Injected!";
            // 
            // panel10
            // 
            this.panel10.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel10.BackColor = System.Drawing.Color.Transparent;
            this.panel10.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("panel10.BackgroundImage")));
            this.panel10.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.panel10.Location = new System.Drawing.Point(146, 98);
            this.panel10.Name = "panel10";
            this.panel10.Size = new System.Drawing.Size(403, 94);
            this.panel10.TabIndex = 7;
            // 
            // DevelopmentPage
            // 
            this.DevelopmentPage.BackColor = System.Drawing.Color.Transparent;
            this.DevelopmentPage.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.DevelopmentPage.Controls.Add(this.button4);
            this.DevelopmentPage.Controls.Add(this.panel11);
            this.DevelopmentPage.Controls.Add(this.button2);
            this.DevelopmentPage.Controls.Add(this.subStageText);
            this.DevelopmentPage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.DevelopmentPage.Location = new System.Drawing.Point(0, 0);
            this.DevelopmentPage.Name = "DevelopmentPage";
            this.DevelopmentPage.Size = new System.Drawing.Size(725, 400);
            this.DevelopmentPage.TabIndex = 9;
            // 
            // button4
            // 
            this.button4.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button4.FlatAppearance.BorderColor = System.Drawing.Color.White;
            this.button4.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.button4.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.button4.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button4.Font = new System.Drawing.Font("Minecraft", 20F);
            this.button4.ForeColor = System.Drawing.Color.White;
            this.button4.Location = new System.Drawing.Point(215, 218);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(130, 76);
            this.button4.TabIndex = 8;
            this.button4.Text = "Locate";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            this.button4.MouseEnter += new System.EventHandler(this.HoverEvent);
            this.button4.MouseLeave += new System.EventHandler(this.BlinkEvent);
            // 
            // panel11
            // 
            this.panel11.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel11.BackColor = System.Drawing.Color.Transparent;
            this.panel11.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("panel11.BackgroundImage")));
            this.panel11.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.panel11.Location = new System.Drawing.Point(146, 98);
            this.panel11.Name = "panel11";
            this.panel11.Size = new System.Drawing.Size(403, 94);
            this.panel11.TabIndex = 7;
            // 
            // button2
            // 
            this.button2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.button2.FlatAppearance.BorderColor = System.Drawing.Color.White;
            this.button2.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.button2.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button2.Font = new System.Drawing.Font("Minecraft", 20F);
            this.button2.ForeColor = System.Drawing.Color.White;
            this.button2.Location = new System.Drawing.Point(351, 218);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(130, 76);
            this.button2.TabIndex = 5;
            this.button2.Text = "Inject";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            this.button2.MouseEnter += new System.EventHandler(this.HoverEvent);
            this.button2.MouseLeave += new System.EventHandler(this.BlinkEvent);
            // 
            // subStageText
            // 
            this.subStageText.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.subStageText.AutoSize = true;
            this.subStageText.BackColor = System.Drawing.Color.Transparent;
            this.subStageText.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.subStageText.Font = new System.Drawing.Font("Minecraft", 14.25F);
            this.subStageText.ForeColor = System.Drawing.Color.White;
            this.subStageText.Location = new System.Drawing.Point(11, 369);
            this.subStageText.Name = "subStageText";
            this.subStageText.Size = new System.Drawing.Size(96, 23);
            this.subStageText.TabIndex = 4;
            this.subStageText.Text = "Injected!";
            // 
            // OutlineFocused
            // 
            this.OutlineFocused.Enabled = true;
            this.OutlineFocused.Interval = 50;
            this.OutlineFocused.Tick += new System.EventHandler(this.OutlineFocused_Tick);
            // 
            // PacketTrayIcon
            // 
            this.PacketTrayIcon.ContextMenuStrip = this.contextMenuStrip1;
            this.PacketTrayIcon.Icon = ((System.Drawing.Icon)(resources.GetObject("PacketTrayIcon.Icon")));
            this.PacketTrayIcon.Text = "Packet Client";
            this.PacketTrayIcon.Visible = true;
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem2,
            this.toolStripSeparator1,
            this.injectPacketToolStripMenuItem,
            this.toolStripSeparator2,
            this.injectDLLToolStripMenuItem,
            this.locateDLLToolStripMenuItem,
            this.toolStripSeparator3,
            this.toolStripMenuItem1});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(133, 132);
            this.contextMenuStrip1.Text = "Packet Launcher";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(132, 22);
            this.toolStripMenuItem2.Text = "Show";
            this.toolStripMenuItem2.Click += new System.EventHandler(this.toolStripMenuItem2_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(129, 6);
            // 
            // injectPacketToolStripMenuItem
            // 
            this.injectPacketToolStripMenuItem.Name = "injectPacketToolStripMenuItem";
            this.injectPacketToolStripMenuItem.Size = new System.Drawing.Size(132, 22);
            this.injectPacketToolStripMenuItem.Text = "Inject";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(129, 6);
            // 
            // injectDLLToolStripMenuItem
            // 
            this.injectDLLToolStripMenuItem.Name = "injectDLLToolStripMenuItem";
            this.injectDLLToolStripMenuItem.Size = new System.Drawing.Size(132, 22);
            this.injectDLLToolStripMenuItem.Text = "Inject DLL";
            this.injectDLLToolStripMenuItem.Click += new System.EventHandler(this.injectDLLToolStripMenuItem_Click);
            // 
            // locateDLLToolStripMenuItem
            // 
            this.locateDLLToolStripMenuItem.Name = "locateDLLToolStripMenuItem";
            this.locateDLLToolStripMenuItem.Size = new System.Drawing.Size(132, 22);
            this.locateDLLToolStripMenuItem.Text = "Locate DLL";
            this.locateDLLToolStripMenuItem.Click += new System.EventHandler(this.locateDLLToolStripMenuItem_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(129, 6);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(132, 22);
            this.toolStripMenuItem1.Text = "Exit";
            this.toolStripMenuItem1.Click += new System.EventHandler(this.toolStripMenuItem1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(16)))), ((int)(((byte)(16)))), ((int)(((byte)(16)))));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(725, 400);
            this.Controls.Add(this.panel1);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Packet Launcher";
            this.panel1.ResumeLayout(false);
            this.SettingsPage.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.panel6.ResumeLayout(false);
            this.panel7.ResumeLayout(false);
            this.HomePage.ResumeLayout(false);
            this.HomePage.PerformLayout();
            this.DevelopmentPage.ResumeLayout(false);
            this.DevelopmentPage.PerformLayout();
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Timer OutlineFocused;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel HomePage;
        private System.Windows.Forms.Panel panel6;
        private System.Windows.Forms.Panel panel7;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Panel panel8;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Panel panel10;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Panel SettingsPage;
        private System.Windows.Forms.Panel DevelopmentPage;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Panel panel11;
        private System.Windows.Forms.Label subStageText;
        private System.Windows.Forms.NotifyIcon PacketTrayIcon;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem injectPacketToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripMenuItem locateDLLToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem injectDLLToolStripMenuItem;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox checkBox1;
    }
}

