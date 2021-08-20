using System;
using Octo_Gamma.Memory_Management;

namespace Octo_Gamma.Modules
{
	// Token: 0x0200000E RID: 14
	internal class freecam
	{
		// Token: 0x0600004E RID: 78 RVA: 0x00004F87 File Offset: 0x00003187
		public static void tick()
		{
		}

		// Token: 0x0600004F RID: 79 RVA: 0x00004F8C File Offset: 0x0000318C
		public static void Enable()
		{
			freecam.xbytes = MemoryHandler.m.ReadBytes(freecam.xpointer, 4L, "");
			freecam.ybytes = MemoryHandler.m.ReadBytes(freecam.ypointer, 4L, "");
			freecam.zbytes = MemoryHandler.m.ReadBytes(freecam.zpointer, 4L, "");
			MemoryHandler.m.WriteBytes(freecam.xpointer, freecam.nop, "");
			MemoryHandler.m.WriteBytes(freecam.ypointer, freecam.nop, "");
			MemoryHandler.m.WriteBytes(freecam.zpointer, freecam.nop, "");
		}

		// Token: 0x06000050 RID: 80 RVA: 0x0000503C File Offset: 0x0000323C
		public static void Disable()
		{
			MemoryHandler.m.WriteBytes(freecam.xpointer, freecam.xbytes, "");
			MemoryHandler.m.WriteBytes(freecam.ypointer, freecam.ybytes, "");
			MemoryHandler.m.WriteBytes(freecam.zpointer, freecam.zbytes, "");
		}

		// Token: 0x04000048 RID: 72
		public static bool enabled = false;

		// Token: 0x04000049 RID: 73
		public static string xpointer = "Minecraft.Windows.exe+0x035866E0,0x130,0x0,0x8,0x1F0,0x0,0x138,0x480";

		// Token: 0x0400004A RID: 74
		public static string ypointer = "Minecraft.Windows.exe+0x035866E0,0x130,0x0,0x8,0x1F0,0x0,0x138,0x484";

		// Token: 0x0400004B RID: 75
		public static string zpointer = "Minecraft.Windows.exe+0x035866E0,0x130,0x0,0x8,0x1F0,0x0,0x138,0x488";

		// Token: 0x0400004C RID: 76
		private static byte[] xbytes = MemoryHandler.m.ReadBytes(freecam.xpointer, 4L, "");

		// Token: 0x0400004D RID: 77
		private static byte[] ybytes = MemoryHandler.m.ReadBytes(freecam.ypointer, 4L, "");

		// Token: 0x0400004E RID: 78
		private static byte[] zbytes = MemoryHandler.m.ReadBytes(freecam.zpointer, 4L, "");

		// Token: 0x0400004F RID: 79
		private static byte[] nop = new byte[]
		{
			144,
			144,
			144,
			144
		};
	}
}
