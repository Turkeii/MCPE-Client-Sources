using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using Octo_Gamma.Memory_Management;

namespace Octo_Gamma.Modules
{
	// Token: 0x02000010 RID: 16
	internal class triggerbot
	{
		// Token: 0x06000055 RID: 85
		[DllImport("user32.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Auto)]
		public static extern void mouse_event(uint dwFlags, uint dx, uint dy, uint cButtons, uint dwExtraInfo);

		// Token: 0x06000056 RID: 86 RVA: 0x0000519C File Offset: 0x0000339C
		public static void tick()
		{
			bool flag = MemoryHandler.m.ReadInt(triggerbot.pointer, "") != 0;
			if (flag)
			{
				uint x = (uint)Cursor.Position.X;
				uint y = (uint)Cursor.Position.Y;
				triggerbot.mouse_event(6U, x, y, 0U, 0U);
			}
		}

		// Token: 0x04000051 RID: 81
		private const int MOUSEEVENTF_LEFTDOWN = 2;

		// Token: 0x04000052 RID: 82
		private const int MOUSEEVENTF_LEFTUP = 4;

		// Token: 0x04000053 RID: 83
		private const int MOUSEEVENTF_RIGHTDOWN = 8;

		// Token: 0x04000054 RID: 84
		private const int MOUSEEVENTF_RIGHTUP = 16;

		// Token: 0x04000055 RID: 85
		public static bool enabled = false;

		// Token: 0x04000056 RID: 86
		public static string pointer = "Minecraft.Windows.exe+0x036B3650,0x0,0x270,0x30,0x0,0x38,0x494";
	}
}
