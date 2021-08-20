namespace Octo_Gamma
{
	// Token: 0x02000004 RID: 4
	public partial class UserLicenceAgreement : global::System.Windows.Forms.Form
	{
		// Token: 0x0600002A RID: 42 RVA: 0x000046F0 File Offset: 0x000028F0
		protected override void Dispose(bool disposing)
		{
			bool flag = disposing && this.components != null;
			if (flag)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}

		// Token: 0x0600002B RID: 43 RVA: 0x00004728 File Offset: 0x00002928
		private void InitializeComponent()
		{
			global::System.ComponentModel.ComponentResourceManager componentResourceManager = new global::System.ComponentModel.ComponentResourceManager(typeof(global::Octo_Gamma.UserLicenceAgreement));
			this.textBox1 = new global::System.Windows.Forms.TextBox();
			this.button1 = new global::System.Windows.Forms.Button();
			base.SuspendLayout();
			this.textBox1.Font = new global::System.Drawing.Font("Microsoft Sans Serif", 9f);
			this.textBox1.Location = new global::System.Drawing.Point(-4, 1);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new global::System.Drawing.Size(340, 248);
			this.textBox1.TabIndex = 0;
			this.textBox1.Text = componentResourceManager.GetString("textBox1.Text");
			this.button1.Location = new global::System.Drawing.Point(118, 255);
			this.button1.Name = "button1";
			this.button1.Size = new global::System.Drawing.Size(75, 23);
			this.button1.TabIndex = 1;
			this.button1.Text = "I accept";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new global::System.EventHandler(this.button1_Click);
			base.AutoScaleDimensions = new global::System.Drawing.SizeF(8f, 16f);
			base.AutoScaleMode = global::System.Windows.Forms.AutoScaleMode.Font;
			base.ClientSize = new global::System.Drawing.Size(336, 278);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.textBox1);
			base.Name = "UserLicenceAgreement";
			this.Text = "User Licence agreement";
			base.Load += new global::System.EventHandler(this.UserLicenceAgreement_Load);
			base.ResumeLayout(false);
			base.PerformLayout();
		}

		// Token: 0x0400002F RID: 47
		private global::System.ComponentModel.IContainer components = null;

		// Token: 0x04000030 RID: 48
		private global::System.Windows.Forms.TextBox textBox1;

		// Token: 0x04000031 RID: 49
		private global::System.Windows.Forms.Button button1;
	}
}
