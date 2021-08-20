using System;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using Octo_Gamma.MemoryManagement;
using Octo_Gamma.Memory_Management;
using Octo_Gamma.Modules;

namespace Octo_Gamma
{
	// Token: 0x02000002 RID: 2
	public partial class Form1 : Form
	{
		// Token: 0x06000001 RID: 1
		[DllImport("USER32.DLL", CharSet = CharSet.Unicode)]
		public static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

		// Token: 0x06000002 RID: 2
		[DllImport("USER32.DLL")]
		public static extern bool SetForegroundWindow(IntPtr hWnd);

		// Token: 0x06000003 RID: 3
		[DllImport("user32.dll")]
		public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);

		// Token: 0x06000004 RID: 4
		[DllImport("user32.dll")]
		public static extern bool ReleaseCapture();

		// Token: 0x06000005 RID: 5 RVA: 0x00002048 File Offset: 0x00000248
		private void Form1_MouseDown(object sender, MouseEventArgs e)
		{
			bool flag = e.Button == MouseButtons.Left;
			if (flag)
			{
				Form1.ReleaseCapture();
				Form1.SendMessage(base.Handle, 161, 2, 0);
			}
		}

		// Token: 0x06000006 RID: 6 RVA: 0x00002084 File Offset: 0x00000284
		public Form1()
		{
			this.InitializeComponent();
			this.hook.KeyPressed += this.hook_KeyPressed;
			this.blink.KeyPressed += this.blink_KeyPressed;
			this.blink.RegisterHotKey(Octo_Gamma.MemoryManagement.ModifierKeys.None, Keys.Capital);
			string a = OctoData.ReadData(1);
			bool flag = a == "C";
			if (flag)
			{
				this.hook.RegisterHotKey(Octo_Gamma.MemoryManagement.ModifierKeys.None, Keys.C);
			}
			else
			{
				bool flag2 = a == "X";
				if (flag2)
				{
					this.hook.RegisterHotKey(Octo_Gamma.MemoryManagement.ModifierKeys.None, Keys.X);
				}
				else
				{
					bool flag3 = a == "Z";
					if (flag3)
					{
						this.hook.RegisterHotKey(Octo_Gamma.MemoryManagement.ModifierKeys.None, Keys.Z);
					}
				}
			}
		}

		// Token: 0x06000007 RID: 7 RVA: 0x00002172 File Offset: 0x00000372
		private void Form1_Load(object sender, EventArgs e)
		{
			MemoryHandler.m.OpenProcess("Minecraft.Windows");
		}

		// Token: 0x06000008 RID: 8 RVA: 0x00002185 File Offset: 0x00000385
		private void flowLayoutPanel1_MouseClick(object sender, MouseEventArgs e)
		{
		}

		// Token: 0x06000009 RID: 9 RVA: 0x00002188 File Offset: 0x00000388
		private void label2_MouseClick(object sender, MouseEventArgs e)
		{
			bool enabled = fullbright.enabled;
			if (enabled)
			{
				fullbright.enabled = false;
				fullbright.Disable();
			}
			else
			{
				fullbright.enabled = true;
				fullbright.Enable();
			}
		}

		// Token: 0x0600000A RID: 10 RVA: 0x000021BD File Offset: 0x000003BD
		private void exit_Click(object sender, EventArgs e)
		{
			base.Close();
		}

		// Token: 0x0600000B RID: 11 RVA: 0x000021C8 File Offset: 0x000003C8
		private void hook_KeyPressed(object sender, KeyPressedEventArgs e)
		{
			bool enabled = zoom.enabled;
			if (enabled)
			{
				zoom.enabled = false;
				zoom.Disable();
			}
			else
			{
				zoom.enabled = true;
				zoom.Enable();
			}
		}

		// Token: 0x0600000C RID: 12 RVA: 0x00002200 File Offset: 0x00000400
		private void blink_KeyPressed(object sender, KeyPressedEventArgs e)
		{
			bool enabled = AutoSpeedBridge.enabled;
			if (enabled)
			{
				bool flag = !AutoSpeedBridge.active;
				if (flag)
				{
					AutoSpeedBridge.active = true;
				}
				else
				{
					AutoSpeedBridge.active = false;
					AutoSpeedBridge.Disable();
				}
			}
		}

		// Token: 0x0600000D RID: 13 RVA: 0x00002240 File Offset: 0x00000440
		private void zoomKey_SelectedIndexChanged(object sender, EventArgs e)
		{
			this.hook.UnRegisterHotKey();
			bool flag = this.zoomKey.Text == "C";
			if (flag)
			{
				this.hook.RegisterHotKey(Octo_Gamma.MemoryManagement.ModifierKeys.None, Keys.C);
				OctoData.WriteData("C", 1);
			}
			else
			{
				bool flag2 = this.zoomKey.Text == "X";
				if (flag2)
				{
					this.hook.RegisterHotKey(Octo_Gamma.MemoryManagement.ModifierKeys.None, Keys.X);
					OctoData.WriteData("X", 1);
				}
				else
				{
					bool flag3 = this.zoomKey.Text == "Z";
					if (flag3)
					{
						this.hook.RegisterHotKey(Octo_Gamma.MemoryManagement.ModifierKeys.None, Keys.Z);
						OctoData.WriteData("Z", 1);
					}
				}
			}
		}

		// Token: 0x0600000E RID: 14 RVA: 0x00002300 File Offset: 0x00000500
		private void label3_Click(object sender, EventArgs e)
		{
			bool enabled = phase.enabled;
			if (enabled)
			{
				phase.enabled = false;
				phase.Disable();
			}
			else
			{
				phase.enabled = true;
				phase.Enable();
			}
		}

		// Token: 0x0600000F RID: 15 RVA: 0x00002338 File Offset: 0x00000538
		private void label5_Click(object sender, EventArgs e)
		{
			bool enabled = nofall.enabled;
			if (enabled)
			{
				nofall.enabled = false;
				nofall.Disable();
			}
			else
			{
				nofall.enabled = true;
				nofall.Enable();
			}
		}

		// Token: 0x06000010 RID: 16 RVA: 0x00002370 File Offset: 0x00000570
		private void label4_Click(object sender, EventArgs e)
		{
			bool enabled = airjump.enabled;
			if (enabled)
			{
				airjump.enabled = false;
				airjump.Disable();
			}
			else
			{
				airjump.enabled = true;
				airjump.Enable();
			}
		}

		// Token: 0x06000011 RID: 17 RVA: 0x000023A8 File Offset: 0x000005A8
		private void label6_Click(object sender, EventArgs e)
		{
			bool enabled = autosprint.enabled;
			if (enabled)
			{
				autosprint.enabled = false;
				autosprint.Disable();
			}
			else
			{
				autosprint.enabled = true;
				autosprint.Enable();
			}
		}

		// Token: 0x06000012 RID: 18 RVA: 0x000023E0 File Offset: 0x000005E0
		private void label7_Click(object sender, EventArgs e)
		{
			bool enabled = speed.enabled;
			if (enabled)
			{
				speed.enabled = false;
				speed.Disable();
			}
			else
			{
				bool flag = this.speedvalue.Text == "Slow";
				if (flag)
				{
					speed.enabled = true;
					speed.Enable("0.05");
				}
				else
				{
					bool flag2 = this.speedvalue.Text == "Fast";
					if (flag2)
					{
						speed.enabled = true;
						speed.Enable("1");
					}
					else
					{
						bool flag3 = this.speedvalue.Text == "Very Fast";
						if (flag3)
						{
							speed.enabled = true;
							speed.Enable("3");
						}
						else
						{
							bool flag4 = this.speedvalue.Text == "Basic";
							if (flag4)
							{
								speed.enabled = true;
								speed.Enable("0.5");
							}
							else
							{
								speed.enabled = true;
								speed.Enable("0.5");
							}
						}
					}
				}
			}
		}

		// Token: 0x06000013 RID: 19 RVA: 0x000024DC File Offset: 0x000006DC
		private void label8_Click(object sender, EventArgs e)
		{
			bool enabled = freecam.enabled;
			if (enabled)
			{
				freecam.enabled = false;
				freecam.Disable();
			}
			else
			{
				freecam.enabled = true;
				freecam.Enable();
			}
		}

		// Token: 0x06000014 RID: 20 RVA: 0x00002514 File Offset: 0x00000714
		private void label8_Click_1(object sender, EventArgs e)
		{
			bool enabled = triggerbot.enabled;
			if (enabled)
			{
				triggerbot.enabled = false;
			}
			else
			{
				triggerbot.enabled = true;
			}
		}

		// Token: 0x06000015 RID: 21 RVA: 0x0000253D File Offset: 0x0000073D
		private void memTick_Tick(object sender, EventArgs e)
		{
			MemoryHandler.tick();
		}

		// Token: 0x06000016 RID: 22 RVA: 0x00002548 File Offset: 0x00000748
		private void label9_Click(object sender, EventArgs e)
		{
			bool enabled = spammer.enabled;
			if (enabled)
			{
				spammer.enabled = false;
			}
			else
			{
				spammer.enabled = true;
				IntPtr foregroundWindow = Form1.FindWindow("ApplicationFrameInputSinkWindow", "ApplicationFrameHost");
				Form1.SetForegroundWindow(foregroundWindow);
				KeyPressing.Keyboard.KeyDown(KeyPressing.Keyboard.ScanCodeShort.ESCAPE);
				KeyPressing.Keyboard.KeyUp(KeyPressing.Keyboard.ScanCodeShort.ESCAPE);
				KeyPressing.Keyboard.KeyDown(KeyPressing.Keyboard.ScanCodeShort.KEY_T);
				KeyPressing.Keyboard.KeyUp(KeyPressing.Keyboard.ScanCodeShort.KEY_T);
			}
		}

		// Token: 0x06000017 RID: 23 RVA: 0x000025A8 File Offset: 0x000007A8
		private void label10_Click(object sender, EventArgs e)
		{
			bool enabled = AutoSpeedBridge.enabled;
			if (enabled)
			{
				AutoSpeedBridge.enabled = false;
			}
			else
			{
				AutoSpeedBridge.enabled = true;
			}
		}

		// Token: 0x06000018 RID: 24 RVA: 0x000025D1 File Offset: 0x000007D1
		private void label11_Click(object sender, EventArgs e)
		{
			this.ModsForm.Show();
		}

		// Token: 0x04000001 RID: 1
		private ModForm ModsForm = new ModForm();

		// Token: 0x04000002 RID: 2
		private HotkeyManager hook = new HotkeyManager();

		// Token: 0x04000003 RID: 3
		private BlinkDashHotKey blink = new BlinkDashHotKey();

		// Token: 0x04000004 RID: 4
		public const int WM_NCLBUTTONDOWN = 161;

		// Token: 0x04000005 RID: 5
		public const int HT_CAPTION = 2;
	}
}
