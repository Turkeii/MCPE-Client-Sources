using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using Octo_Gamma.MemoryManagement;

namespace Octo_Gamma.Modules
{
	// Token: 0x0200000C RID: 12
	internal class AutoSpeedBridge
	{
		// Token: 0x06000043 RID: 67
		[DllImport("user32.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Auto)]
		public static extern void mouse_event(uint dwFlags, uint dx, uint dy, uint cButtons, uint dwExtraInfo);

		// Token: 0x06000044 RID: 68 RVA: 0x00004EB4 File Offset: 0x000030B4
		public static void tick()
		{
			KeyPressing.Keyboard.KeyDown(KeyPressing.Keyboard.ScanCodeShort.KEY_W);
			KeyPressing.Keyboard.KeyUp(KeyPressing.Keyboard.ScanCodeShort.KEY_W);
			uint x = (uint)Cursor.Position.X;
			uint y = (uint)Cursor.Position.Y;
			AutoSpeedBridge.mouse_event(24U, x, y, 0U, 0U);
		}

		// Token: 0x06000045 RID: 69 RVA: 0x00004EFA File Offset: 0x000030FA
		public static void Enable()
		{
		}

		// Token: 0x06000046 RID: 70 RVA: 0x00004EFD File Offset: 0x000030FD
		public static void Disable()
		{
			KeyPressing.Keyboard.KeyUp(KeyPressing.Keyboard.ScanCodeShort.KEY_W);
		}

		// Token: 0x0400003E RID: 62
		private BlinkDashHotKey hook = new BlinkDashHotKey();

		// Token: 0x0400003F RID: 63
		private const int MOUSEEVENTF_LEFTDOWN = 2;

		// Token: 0x04000040 RID: 64
		private const int MOUSEEVENTF_LEFTUP = 4;

		// Token: 0x04000041 RID: 65
		private const int MOUSEEVENTF_RIGHTDOWN = 8;

		// Token: 0x04000042 RID: 66
		private const int MOUSEEVENTF_RIGHTUP = 16;

		// Token: 0x04000043 RID: 67
		public static bool enabled = false;

		// Token: 0x04000044 RID: 68
		public static bool active = false;

		// Token: 0x04000045 RID: 69
		public static string pointer = speed.pointer;
	}
}
