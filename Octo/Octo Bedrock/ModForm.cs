using System;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using Octo_Gamma.ModManagement;

namespace Octo_Gamma
{
	// Token: 0x02000003 RID: 3
	public partial class ModForm : Form
	{
		// Token: 0x0600001B RID: 27
		[DllImport("USER32.DLL")]
		public static extern bool SetForegroundWindow(IntPtr hWnd);

		// Token: 0x0600001C RID: 28
		[DllImport("user32.dll")]
		public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);

		// Token: 0x0600001D RID: 29
		[DllImport("user32.dll")]
		public static extern bool ReleaseCapture();

		// Token: 0x0600001E RID: 30 RVA: 0x00003978 File Offset: 0x00001B78
		public ModForm()
		{
			this.InitializeComponent();
			this.label3.Hide();
			this.label4.Hide();
			this.label5.Hide();
			ModManifestReader.ReadManifests(this.mod1Name, this.mod2Name, this.mod3Name, this.label3, this.label4, this.label5);
		}

		// Token: 0x0600001F RID: 31 RVA: 0x000039FE File Offset: 0x00001BFE
		private void exit_Click(object sender, EventArgs e)
		{
			base.Close();
		}

		// Token: 0x06000020 RID: 32 RVA: 0x00003A08 File Offset: 0x00001C08
		private void label11_Click(object sender, EventArgs e)
		{
			base.Hide();
		}

		// Token: 0x06000021 RID: 33 RVA: 0x00003A14 File Offset: 0x00001C14
		private void ModForm_MouseDown(object sender, MouseEventArgs e)
		{
			bool flag = e.Button == MouseButtons.Left;
			if (flag)
			{
				ModForm.ReleaseCapture();
				ModForm.SendMessage(base.Handle, 161, 2, 0);
			}
		}

		// Token: 0x06000022 RID: 34 RVA: 0x00003A50 File Offset: 0x00001C50
		private void label3_Click(object sender, EventArgs e)
		{
			bool flag = !this.mod1Enabled;
			if (flag)
			{
				ModModuleManager.enableModule(ModManifestReader.Mod1ModuleDir);
				this.mod1Enabled = true;
			}
			else
			{
				ModModuleManager.disableModule(ModManifestReader.Mod1ModuleDir);
				this.mod1Enabled = false;
			}
		}

		// Token: 0x06000023 RID: 35 RVA: 0x00003A98 File Offset: 0x00001C98
		private void label4_Click(object sender, EventArgs e)
		{
			bool flag = !this.mod2Enabled;
			if (flag)
			{
				ModModuleManager.enableModule(ModManifestReader.Mod2ModuleDir);
				this.mod2Enabled = true;
			}
			else
			{
				ModModuleManager.disableModule(ModManifestReader.Mod2ModuleDir);
				this.mod2Enabled = false;
			}
		}

		// Token: 0x06000024 RID: 36 RVA: 0x00003AE0 File Offset: 0x00001CE0
		private void label5_Click(object sender, EventArgs e)
		{
			bool flag = !this.mod3Enabled;
			if (flag)
			{
				ModModuleManager.enableModule(ModManifestReader.Mod3ModuleDir);
				this.mod3Enabled = true;
			}
			else
			{
				ModModuleManager.disableModule(ModManifestReader.Mod3ModuleDir);
				this.mod3Enabled = false;
			}
		}

		// Token: 0x0400001C RID: 28
		public const int WM_NCLBUTTONDOWN = 161;

		// Token: 0x0400001D RID: 29
		public const int HT_CAPTION = 2;

		// Token: 0x0400001E RID: 30
		public bool mod1Enabled = false;

		// Token: 0x0400001F RID: 31
		public bool mod2Enabled = false;

		// Token: 0x04000020 RID: 32
		public bool mod3Enabled = false;
	}
}
