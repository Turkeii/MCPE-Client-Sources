using System;
using Octo_Gamma.Memory_Management;

namespace Octo_Gamma.Modules
{
	// Token: 0x02000015 RID: 21
	internal class zoom
	{
		// Token: 0x0600006D RID: 109 RVA: 0x000053F2 File Offset: 0x000035F2
		public static void tick()
		{
		}

		// Token: 0x0600006E RID: 110 RVA: 0x000053F8 File Offset: 0x000035F8
		public static void Enable()
		{
			zoom.prevFov = MemoryHandler.m.ReadFloat(zoom.pointer, "", true).ToString();
			MemoryHandler.m.WriteMemory(zoom.pointer, "float", "0", "", null);
		}

		// Token: 0x0600006F RID: 111 RVA: 0x00005448 File Offset: 0x00003648
		public static void Disable()
		{
			MemoryHandler.m.WriteMemory(zoom.pointer, "float", zoom.prevFov, "", null);
		}

		// Token: 0x04000060 RID: 96
		public static bool enabled = false;

		// Token: 0x04000061 RID: 97
		public static string pointer = "Minecraft.Windows.exe+0x0369BD40,0x20,0x910,0x1A8,0xB30,0x1A8,120,0x1E8";

		// Token: 0x04000062 RID: 98
		private static string prevFov;
	}
}
