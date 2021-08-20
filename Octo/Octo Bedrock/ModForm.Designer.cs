namespace Octo_Gamma
{
	// Token: 0x02000003 RID: 3
	public partial class ModForm : global::System.Windows.Forms.Form
	{
		// Token: 0x06000025 RID: 37 RVA: 0x00003B28 File Offset: 0x00001D28
		protected override void Dispose(bool disposing)
		{
			bool flag = disposing && this.components != null;
			if (flag)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}

		// Token: 0x06000026 RID: 38 RVA: 0x00003B60 File Offset: 0x00001D60
		private void InitializeComponent()
		{
			this.label1 = new global::System.Windows.Forms.Label();
			this.panel4 = new global::System.Windows.Forms.Panel();
			this.panel3 = new global::System.Windows.Forms.Panel();
			this.panel2 = new global::System.Windows.Forms.Panel();
			this.panel1 = new global::System.Windows.Forms.Panel();
			this.label11 = new global::System.Windows.Forms.Label();
			this.label2 = new global::System.Windows.Forms.Label();
			this.mod1Name = new global::System.Windows.Forms.Label();
			this.mod2Name = new global::System.Windows.Forms.Label();
			this.mod3Name = new global::System.Windows.Forms.Label();
			this.label3 = new global::System.Windows.Forms.Label();
			this.label4 = new global::System.Windows.Forms.Label();
			this.label5 = new global::System.Windows.Forms.Label();
			base.SuspendLayout();
			this.label1.AutoSize = true;
			this.label1.BackColor = global::System.Drawing.Color.White;
			this.label1.Font = new global::System.Drawing.Font("Lucida Console", 22.2f, global::System.Drawing.FontStyle.Bold, global::System.Drawing.GraphicsUnit.Point, 0);
			this.label1.ForeColor = global::System.Drawing.Color.Aquamarine;
			this.label1.Location = new global::System.Drawing.Point(163, 9);
			this.label1.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label1.Name = "label1";
			this.label1.Size = new global::System.Drawing.Size(89, 30);
			this.label1.TabIndex = 12;
			this.label1.Text = "Octo";
			this.panel4.BackColor = global::System.Drawing.Color.Aquamarine;
			this.panel4.Location = new global::System.Drawing.Point(0, -15);
			this.panel4.Margin = new global::System.Windows.Forms.Padding(2);
			this.panel4.Name = "panel4";
			this.panel4.Size = new global::System.Drawing.Size(420, 21);
			this.panel4.TabIndex = 11;
			this.panel3.BackColor = global::System.Drawing.Color.Aquamarine;
			this.panel3.Location = new global::System.Drawing.Point(0, 364);
			this.panel3.Margin = new global::System.Windows.Forms.Padding(2);
			this.panel3.Name = "panel3";
			this.panel3.Size = new global::System.Drawing.Size(420, 21);
			this.panel3.TabIndex = 10;
			this.panel2.BackColor = global::System.Drawing.Color.Aquamarine;
			this.panel2.Location = new global::System.Drawing.Point(416, -27);
			this.panel2.Margin = new global::System.Windows.Forms.Padding(2);
			this.panel2.Name = "panel2";
			this.panel2.Size = new global::System.Drawing.Size(4, 414);
			this.panel2.TabIndex = 9;
			this.panel1.BackColor = global::System.Drawing.Color.Aquamarine;
			this.panel1.Location = new global::System.Drawing.Point(0, -9);
			this.panel1.Margin = new global::System.Windows.Forms.Padding(2);
			this.panel1.Name = "panel1";
			this.panel1.Size = new global::System.Drawing.Size(4, 381);
			this.panel1.TabIndex = 8;
			this.label11.AutoSize = true;
			this.label11.BackColor = global::System.Drawing.Color.Aquamarine;
			this.label11.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.label11.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.label11.ForeColor = global::System.Drawing.Color.White;
			this.label11.Location = new global::System.Drawing.Point(175, 338);
			this.label11.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label11.Name = "label11";
			this.label11.Size = new global::System.Drawing.Size(64, 19);
			this.label11.TabIndex = 22;
			this.label11.Text = "Close";
			this.label11.Click += new global::System.EventHandler(this.label11_Click);
			this.label2.AutoSize = true;
			this.label2.BackColor = global::System.Drawing.Color.White;
			this.label2.Font = new global::System.Drawing.Font("Lucida Console", 14f, global::System.Drawing.FontStyle.Bold);
			this.label2.ForeColor = global::System.Drawing.Color.Aquamarine;
			this.label2.Location = new global::System.Drawing.Point(11, 77);
			this.label2.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label2.Name = "label2";
			this.label2.Size = new global::System.Drawing.Size(153, 19);
			this.label2.TabIndex = 23;
			this.label2.Text = "Mods Active:";
			this.mod1Name.AutoSize = true;
			this.mod1Name.BackColor = global::System.Drawing.Color.White;
			this.mod1Name.Font = new global::System.Drawing.Font("Lucida Console", 10f, global::System.Drawing.FontStyle.Bold);
			this.mod1Name.ForeColor = global::System.Drawing.Color.Aquamarine;
			this.mod1Name.Location = new global::System.Drawing.Point(12, 105);
			this.mod1Name.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.mod1Name.Name = "mod1Name";
			this.mod1Name.Size = new global::System.Drawing.Size(16, 14);
			this.mod1Name.TabIndex = 24;
			this.mod1Name.Text = " ";
			this.mod2Name.AutoSize = true;
			this.mod2Name.BackColor = global::System.Drawing.Color.White;
			this.mod2Name.Font = new global::System.Drawing.Font("Lucida Console", 10f, global::System.Drawing.FontStyle.Bold);
			this.mod2Name.ForeColor = global::System.Drawing.Color.Aquamarine;
			this.mod2Name.Location = new global::System.Drawing.Point(12, 119);
			this.mod2Name.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.mod2Name.Name = "mod2Name";
			this.mod2Name.Size = new global::System.Drawing.Size(16, 14);
			this.mod2Name.TabIndex = 25;
			this.mod2Name.Text = " ";
			this.mod3Name.AutoSize = true;
			this.mod3Name.BackColor = global::System.Drawing.Color.White;
			this.mod3Name.Font = new global::System.Drawing.Font("Lucida Console", 10f, global::System.Drawing.FontStyle.Bold);
			this.mod3Name.ForeColor = global::System.Drawing.Color.Aquamarine;
			this.mod3Name.Location = new global::System.Drawing.Point(12, 133);
			this.mod3Name.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.mod3Name.Name = "mod3Name";
			this.mod3Name.Size = new global::System.Drawing.Size(16, 14);
			this.mod3Name.TabIndex = 26;
			this.mod3Name.Text = " ";
			this.label3.AutoSize = true;
			this.label3.BackColor = global::System.Drawing.Color.Aquamarine;
			this.label3.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.label3.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.label3.ForeColor = global::System.Drawing.Color.White;
			this.label3.Location = new global::System.Drawing.Point(291, 100);
			this.label3.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label3.Name = "label3";
			this.label3.Size = new global::System.Drawing.Size(53, 19);
			this.label3.TabIndex = 27;
			this.label3.Text = "Mod1";
			this.label3.Click += new global::System.EventHandler(this.label3_Click);
			this.label4.AutoSize = true;
			this.label4.BackColor = global::System.Drawing.Color.Aquamarine;
			this.label4.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.label4.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.label4.ForeColor = global::System.Drawing.Color.White;
			this.label4.Location = new global::System.Drawing.Point(291, 128);
			this.label4.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label4.Name = "label4";
			this.label4.Size = new global::System.Drawing.Size(53, 19);
			this.label4.TabIndex = 28;
			this.label4.Text = "Mod2";
			this.label4.Click += new global::System.EventHandler(this.label4_Click);
			this.label5.AutoSize = true;
			this.label5.BackColor = global::System.Drawing.Color.Aquamarine;
			this.label5.Cursor = global::System.Windows.Forms.Cursors.Hand;
			this.label5.Font = new global::System.Drawing.Font("Lucida Console", 14f);
			this.label5.ForeColor = global::System.Drawing.Color.White;
			this.label5.Location = new global::System.Drawing.Point(291, 156);
			this.label5.Margin = new global::System.Windows.Forms.Padding(2, 0, 2, 0);
			this.label5.Name = "label5";
			this.label5.Size = new global::System.Drawing.Size(53, 19);
			this.label5.TabIndex = 29;
			this.label5.Text = "Mod3";
			this.label5.Click += new global::System.EventHandler(this.label5_Click);
			base.AutoScaleDimensions = new global::System.Drawing.SizeF(6f, 13f);
			base.AutoScaleMode = global::System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = global::System.Drawing.Color.White;
			base.ClientSize = new global::System.Drawing.Size(420, 366);
			base.Controls.Add(this.label5);
			base.Controls.Add(this.label4);
			base.Controls.Add(this.label3);
			base.Controls.Add(this.mod3Name);
			base.Controls.Add(this.mod2Name);
			base.Controls.Add(this.mod1Name);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.label11);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.panel4);
			base.Controls.Add(this.panel3);
			base.Controls.Add(this.panel2);
			base.Controls.Add(this.panel1);
			base.FormBorderStyle = global::System.Windows.Forms.FormBorderStyle.None;
			this.MaximumSize = new global::System.Drawing.Size(420, 366);
			this.MinimumSize = new global::System.Drawing.Size(420, 366);
			base.Name = "ModForm";
			this.Text = "ModForm";
			base.MouseDown += new global::System.Windows.Forms.MouseEventHandler(this.ModForm_MouseDown);
			base.ResumeLayout(false);
			base.PerformLayout();
		}

		// Token: 0x04000021 RID: 33
		private global::System.ComponentModel.IContainer components = null;

		// Token: 0x04000022 RID: 34
		private global::System.Windows.Forms.Label label1;

		// Token: 0x04000023 RID: 35
		private global::System.Windows.Forms.Panel panel4;

		// Token: 0x04000024 RID: 36
		private global::System.Windows.Forms.Panel panel3;

		// Token: 0x04000025 RID: 37
		private global::System.Windows.Forms.Panel panel2;

		// Token: 0x04000026 RID: 38
		private global::System.Windows.Forms.Panel panel1;

		// Token: 0x04000027 RID: 39
		private global::System.Windows.Forms.Label label11;

		// Token: 0x04000028 RID: 40
		private global::System.Windows.Forms.Label label2;

		// Token: 0x04000029 RID: 41
		private global::System.Windows.Forms.Label mod1Name;

		// Token: 0x0400002A RID: 42
		private global::System.Windows.Forms.Label mod2Name;

		// Token: 0x0400002B RID: 43
		private global::System.Windows.Forms.Label mod3Name;

		// Token: 0x0400002C RID: 44
		private global::System.Windows.Forms.Label label3;

		// Token: 0x0400002D RID: 45
		private global::System.Windows.Forms.Label label4;

		// Token: 0x0400002E RID: 46
		private global::System.Windows.Forms.Label label5;
	}
}
