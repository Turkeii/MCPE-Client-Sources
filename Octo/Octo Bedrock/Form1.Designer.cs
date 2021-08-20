namespace Octo_Gamma
{
	// Token: 0x02000002 RID: 2
	public partial class Form1 : global::System.Windows.Forms.Form
	{
		// Token: 0x06000019 RID: 25 RVA: 0x000025E0 File Offset: 0x000007E0
		protected override void Dispose(bool disposing)
		{
			bool flag = disposing && this.components != null;
			if (flag)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}

		// Token: 0x0600001A RID: 26 RVA: 0x00002618 File Offset: 0x00000818
		private void InitializeComponent()
		{
			this.components = new global::System.ComponentModel.Container();
			global::System.ComponentModel.ComponentResourceManager componentResourceManager = new global::System.ComponentModel.ComponentResourceManager(typeof(global::Octo_Gamma.Form1));
			this.panel1 = new global::System.Windows.Forms.Panel();
			this.flowLayoutPanel1 = new global::System.Windows.Forms.FlowLayoutPanel();
			this.panel2 = new global::System.Windows.Forms.Panel();
			this.panel3 = new global::System.Windows.Forms.Panel();
			this.panel4 = new global::System.Windows.Forms.Panel();
			this.label1 = new global::System.Windows.Forms.Label();
			this.label2 = new global::System.Windows.Forms.Label();
			this.exit = new global::System.Windows.Forms.Label();
			this.zoomLabel = new global::System.Windows.Forms.Label();
			this.zoomKey = new global::System.Windows.Forms.ComboBox();
			this.label3 = new global::System.Windows.Forms.Label();
			this.label4 = new global::System.Windows.Forms.Label();
			this.label5 = new global::System.Windows.Forms.Label();
			this.label6 = new global::System.Windows.Forms.Label();
			this.speedvalue = new global::System.Windows.Forms.ComboBox();
			this.label7 = new global::System.Windows.Forms.Label();
			this.label8 = new global::System.Windows.Forms.Label();
			this.memTick = new global::System.Windows.Forms.Timer(this.components);
			this.label9 = new global::System.Windows.Forms.Label();
			this.label10 = new global::System.Windows.Forms.Label();
			this.label11 = new global::System.Windows.Forms.Label();
			base.SuspendLayout();
			this.panel1.BackColor = global::System.Drawing.Color.Aquamarine;
			this.panel1.Location = new global::System.Drawing.Point(0, -11);
			this.panel1.Margin = new global::System.Windows.Forms.Padding(2, 2, 2, 2);
			this.panel1.Name = "panel1";
			this.panel1.Size = new global::System.Drawing.Size(4, 381);
			this.panel1.TabIndex = 0;
			this.flowLayoutPanel1.Location = new global::System.Drawing.Point(8, 2);
			this.flowLayoutPanel1.Margin = new global::System.Windows.Forms.Padding(2, 2, 2, 2);
			this.flowLayoutPanel1.Name = "flowLayoutPanel1";
			this.flowLayoutPanel1.Size = new global::System.Drawing.Size(6, 11);
			this.flowLayoutPanel1.TabIndex = 1;
			this.flowLayoutPanel1.MouseClick += new global::System.Windows.Forms.MouseEventHandler(this.flowLayoutPanel1_MouseClick);
			this.panel2.BackColor = global::System.Drawing.Color.Aquamarine;
			this.panel2.Location = new global::System.Drawing.Point(416, -29);
			this.panel2.Margin = new global::System.Windows.Forms.Padding(2, 2, 2, 2);
			this.panel2.Name = "panel2";
			this.panel2.Size = new global::System.Drawing.Size(4, 414);
			this.panel2.TabIndex = 2;
			this.panel3.BackColor = global::System.Drawing.Color.Aquamarine;
			this.panel3.Location = new global::System.Drawing.Point(0, 362);
			this.panel3.Margin = new global::System.Windows.Forms.Padding(2, 2, 2, 2);
			this.panel3.Name = "panel3";
			this.panel3.Size = new global::System.Drawing.Size(420, 21);
			this.panel3.TabIndex = 3;
			this.panel4.BackColor = global::System.Drawing.Color.Aquamarine;
			this.panel4.Location = new global::System.Drawing.Point(0, -17);
			this.panel4.Margin = new global::System.Windows.Forms.Padding(2, 2, 2, 2);
			this.panel4.Name = "panel4";
			this.panel4.Size = new global::System.Drawing.Size(420, 21);
			this.panel4.TabIndex = 4;
			this.label1.AutoSize = true;
			this.label1.BackColor = global::System.Drawing.Color.White;
			this.label1.Font = new global::System.Drawing.Font("Lucida Console", 22.2f, global::System.Drawing.FontStyle.Bold, global::System.Drawing.GraphicsUnit.Point, 0);
			this.label1.ForeColor = global::System.Drawing.Color.Aquamarine;
			this.label1.Location = new global::System.Drawing.Point(163, 7);
			this.label1.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label1.Name = "label1";
			this.label1.Size = new global::System.Drawing.Size(89, 30);
			this.label1.TabIndex = 5;
			this.label1.Text = "Octo";
			this.label2.AutoSize = true;
			this.label2.BackColor = global::System.Drawing.Color.Aquamarine;
			this.label2.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.label2.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.label2.ForeColor = global::System.Drawing.Color.White;
			this.label2.Location = new global::System.Drawing.Point(19, 110);
			this.label2.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label2.Name = "label2";
			this.label2.Size = new global::System.Drawing.Size(130, 19);
			this.label2.TabIndex = 6;
			this.label2.Text = "Full Bright";
			this.label2.MouseClick += new global::System.Windows.Forms.MouseEventHandler(this.label2_MouseClick);
			this.exit.AutoSize = true;
			this.exit.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.exit.Font = new global::System.Drawing.Font("Lucida Console", 18.2f, global::System.Drawing.FontStyle.Bold);
			this.exit.ForeColor = global::System.Drawing.Color.Aquamarine;
			this.exit.Location = new global::System.Drawing.Point(386, 6);
			this.exit.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.exit.Name = "exit";
			this.exit.Size = new global::System.Drawing.Size(28, 25);
			this.exit.TabIndex = 7;
			this.exit.Text = "X";
			this.exit.Click += new global::System.EventHandler(this.exit_Click);
			this.zoomLabel.AutoSize = true;
			this.zoomLabel.BackColor = global::System.Drawing.Color.Aquamarine;
			this.zoomLabel.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.zoomLabel.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.zoomLabel.ForeColor = global::System.Drawing.Color.White;
			this.zoomLabel.Location = new global::System.Drawing.Point(19, 273);
			this.zoomLabel.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.zoomLabel.Name = "zoomLabel";
			this.zoomLabel.Size = new global::System.Drawing.Size(130, 19);
			this.zoomLabel.TabIndex = 8;
			this.zoomLabel.Text = "Zoom Hotkey";
			this.zoomKey.BackColor = global::System.Drawing.Color.WhiteSmoke;
			this.zoomKey.DropDownStyle = global::System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.zoomKey.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.zoomKey.ForeColor = global::System.Drawing.Color.Aquamarine;
			this.zoomKey.FormattingEnabled = true;
			this.zoomKey.Items.AddRange(new object[]
			{
				"C",
				"Z",
				"X"
			});
			this.zoomKey.Location = new global::System.Drawing.Point(22, 303);
			this.zoomKey.Margin = new global::System.Windows.Forms.Padding(2, 2, 2, 2);
			this.zoomKey.Name = "zoomKey";
			this.zoomKey.Size = new global::System.Drawing.Size(121, 27);
			this.zoomKey.TabIndex = 10;
			this.zoomKey.SelectedIndexChanged += new global::System.EventHandler(this.zoomKey_SelectedIndexChanged);
			this.label3.AutoSize = true;
			this.label3.BackColor = global::System.Drawing.Color.Aquamarine;
			this.label3.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.label3.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.label3.ForeColor = global::System.Drawing.Color.White;
			this.label3.Location = new global::System.Drawing.Point(19, 144);
			this.label3.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label3.Name = "label3";
			this.label3.Padding = new global::System.Windows.Forms.Padding(30, 0, 30, 0);
			this.label3.Size = new global::System.Drawing.Size(124, 19);
			this.label3.TabIndex = 12;
			this.label3.Text = "Phase";
			this.label3.Click += new global::System.EventHandler(this.label3_Click);
			this.label4.AutoSize = true;
			this.label4.BackColor = global::System.Drawing.Color.Aquamarine;
			this.label4.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.label4.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.label4.ForeColor = global::System.Drawing.Color.White;
			this.label4.Location = new global::System.Drawing.Point(19, 176);
			this.label4.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label4.MaximumSize = new global::System.Drawing.Size(123, 0);
			this.label4.Name = "label4";
			this.label4.Size = new global::System.Drawing.Size(86, 19);
			this.label4.TabIndex = 13;
			this.label4.Text = "Airjump";
			this.label4.Click += new global::System.EventHandler(this.label4_Click);
			this.label5.AutoSize = true;
			this.label5.BackColor = global::System.Drawing.Color.Aquamarine;
			this.label5.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.label5.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.label5.ForeColor = global::System.Drawing.Color.White;
			this.label5.Location = new global::System.Drawing.Point(19, 209);
			this.label5.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label5.MaximumSize = new global::System.Drawing.Size(123, 0);
			this.label5.Name = "label5";
			this.label5.Size = new global::System.Drawing.Size(75, 19);
			this.label5.TabIndex = 14;
			this.label5.Text = "Nofall";
			this.label5.Click += new global::System.EventHandler(this.label5_Click);
			this.label6.AutoSize = true;
			this.label6.BackColor = global::System.Drawing.Color.Aquamarine;
			this.label6.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.label6.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.label6.ForeColor = global::System.Drawing.Color.White;
			this.label6.Location = new global::System.Drawing.Point(19, 240);
			this.label6.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label6.MaximumSize = new global::System.Drawing.Size(123, 0);
			this.label6.Name = "label6";
			this.label6.Size = new global::System.Drawing.Size(119, 19);
			this.label6.TabIndex = 15;
			this.label6.Text = "AutoSprint";
			this.label6.Click += new global::System.EventHandler(this.label6_Click);
			this.speedvalue.BackColor = global::System.Drawing.Color.WhiteSmoke;
			this.speedvalue.DropDownStyle = global::System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.speedvalue.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.speedvalue.ForeColor = global::System.Drawing.Color.Aquamarine;
			this.speedvalue.FormattingEnabled = true;
			this.speedvalue.Items.AddRange(new object[]
			{
				"Slow",
				"Basic",
				"Fast",
				"Very Fast"
			});
			this.speedvalue.Location = new global::System.Drawing.Point(277, 303);
			this.speedvalue.Margin = new global::System.Windows.Forms.Padding(2, 2, 2, 2);
			this.speedvalue.Name = "speedvalue";
			this.speedvalue.Size = new global::System.Drawing.Size(121, 27);
			this.speedvalue.TabIndex = 17;
			this.label7.AutoSize = true;
			this.label7.BackColor = global::System.Drawing.Color.Aquamarine;
			this.label7.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.label7.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.label7.ForeColor = global::System.Drawing.Color.White;
			this.label7.Location = new global::System.Drawing.Point(306, 273);
			this.label7.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label7.Name = "label7";
			this.label7.Size = new global::System.Drawing.Size(64, 19);
			this.label7.TabIndex = 16;
			this.label7.Text = "Speed";
			this.label7.Click += new global::System.EventHandler(this.label7_Click);
			this.label8.AutoSize = true;
			this.label8.BackColor = global::System.Drawing.Color.Aquamarine;
			this.label8.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.label8.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.label8.ForeColor = global::System.Drawing.Color.White;
			this.label8.Location = new global::System.Drawing.Point(274, 110);
			this.label8.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label8.Name = "label8";
			this.label8.Size = new global::System.Drawing.Size(130, 19);
			this.label8.TabIndex = 18;
			this.label8.Text = "Trigger Bot";
			this.label8.Click += new global::System.EventHandler(this.label8_Click_1);
			this.memTick.Enabled = true;
			this.memTick.Interval = 10;
			this.memTick.Tick += new global::System.EventHandler(this.memTick_Tick);
			this.label9.AutoSize = true;
			this.label9.BackColor = global::System.Drawing.Color.Aquamarine;
			this.label9.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.label9.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.label9.ForeColor = global::System.Drawing.Color.White;
			this.label9.Location = new global::System.Drawing.Point(274, 144);
			this.label9.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label9.Name = "label9";
			this.label9.Size = new global::System.Drawing.Size(86, 19);
			this.label9.TabIndex = 19;
			this.label9.Text = "Spammer";
			this.label9.Click += new global::System.EventHandler(this.label9_Click);
			this.label10.AutoSize = true;
			this.label10.BackColor = global::System.Drawing.Color.Aquamarine;
			this.label10.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.label10.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.label10.ForeColor = global::System.Drawing.Color.White;
			this.label10.Location = new global::System.Drawing.Point(274, 176);
			this.label10.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label10.Name = "label10";
			this.label10.Size = new global::System.Drawing.Size(130, 19);
			this.label10.TabIndex = 20;
			this.label10.Text = "SpeedBridge";
			this.label10.Click += new global::System.EventHandler(this.label10_Click);
			this.label11.AutoSize = true;
			this.label11.BackColor = global::System.Drawing.Color.Aquamarine;
			this.label11.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.label11.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.label11.ForeColor = global::System.Drawing.Color.White;
			this.label11.Location = new global::System.Drawing.Point(180, 338);
			this.label11.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label11.Name = "label11";
			this.label11.Size = new global::System.Drawing.Size(53, 19);
			this.label11.TabIndex = 21;
			this.label11.Text = "Mods";
			this.label11.Click += new global::System.EventHandler(this.label11_Click);
			base.AutoScaleDimensions = new global::System.Drawing.SizeF(6f, 13f);
			base.AutoScaleMode = global::System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = global::System.Drawing.Color.White;
			base.ClientSize = new global::System.Drawing.Size(420, 366);
			base.Controls.Add(this.label11);
			base.Controls.Add(this.label10);
			base.Controls.Add(this.label9);
			base.Controls.Add(this.label8);
			base.Controls.Add(this.speedvalue);
			base.Controls.Add(this.label7);
			base.Controls.Add(this.label6);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.zoomKey);
			base.Controls.Add(this.zoomLabel);
			base.Controls.Add(this.exit);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.panel4);
			base.Controls.Add(this.panel3);
			base.Controls.Add(this.panel2);
			base.Controls.Add(this.flowLayoutPanel1);
			base.Controls.Add(this.panel1);
			this.Cursor = global::System.Windows.Forms.Cursors.Default;
			base.FormBorderStyle = global::System.Windows.Forms.FormBorderStyle.None;
			base.Icon = (global::System.Drawing.Icon)componentResourceManager.GetObject("$this.Icon");
			base.Margin = new global::System.Windows.Forms.Padding(2, 2, 2, 2);
			base.Name = "Form1";
			this.Text = "Octo bedrock";
			base.Load += new global::System.EventHandler(this.Form1_Load);
			base.MouseDown += new global::System.Windows.Forms.MouseEventHandler(this.Form1_MouseDown);
			base.ResumeLayout(false);
			base.PerformLayout();
		}

		// Token: 0x04000006 RID: 6
		private global::System.ComponentModel.IContainer components = null;

		// Token: 0x04000007 RID: 7
		private global::System.Windows.Forms.Panel panel1;

		// Token: 0x04000008 RID: 8
		private global::System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;

		// Token: 0x04000009 RID: 9
		private global::System.Windows.Forms.Panel panel2;

		// Token: 0x0400000A RID: 10
		private global::System.Windows.Forms.Panel panel3;

		// Token: 0x0400000B RID: 11
		private global::System.Windows.Forms.Panel panel4;

		// Token: 0x0400000C RID: 12
		private global::System.Windows.Forms.Label label1;

		// Token: 0x0400000D RID: 13
		private global::System.Windows.Forms.Label label2;

		// Token: 0x0400000E RID: 14
		private global::System.Windows.Forms.Label exit;

		// Token: 0x0400000F RID: 15
		private global::System.Windows.Forms.Label zoomLabel;

		// Token: 0x04000010 RID: 16
		private global::System.Windows.Forms.ComboBox zoomKey;

		// Token: 0x04000011 RID: 17
		private global::System.Windows.Forms.Label label3;

		// Token: 0x04000012 RID: 18
		private global::System.Windows.Forms.Label label4;

		// Token: 0x04000013 RID: 19
		private global::System.Windows.Forms.Label label5;

		// Token: 0x04000014 RID: 20
		private global::System.Windows.Forms.Label label6;

		// Token: 0x04000015 RID: 21
		private global::System.Windows.Forms.ComboBox speedvalue;

		// Token: 0x04000016 RID: 22
		private global::System.Windows.Forms.Label label7;

		// Token: 0x04000017 RID: 23
		private global::System.Windows.Forms.Label label8;

		// Token: 0x04000018 RID: 24
		private global::System.Windows.Forms.Timer memTick;

		// Token: 0x04000019 RID: 25
		private global::System.Windows.Forms.Label label9;

		// Token: 0x0400001A RID: 26
		private global::System.Windows.Forms.Label label10;

		// Token: 0x0400001B RID: 27
		private global::System.Windows.Forms.Label label11;
	}
}
