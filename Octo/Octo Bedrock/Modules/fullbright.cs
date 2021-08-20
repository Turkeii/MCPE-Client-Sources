using System;
using Octo_Gamma.Memory_Management;

namespace Octo_Gamma.Modules
{
	// Token: 0x02000016 RID: 22
	internal class fullbright
	{
		// Token: 0x06000072 RID: 114 RVA: 0x00005486 File Offset: 0x00003686
		public static void tick()
		{
		}

		// Token: 0x06000073 RID: 115 RVA: 0x00005489 File Offset: 0x00003689
		public static void Enable()
		{
			MemoryHandler.m.WriteMemory(fullbright.pointer, "float", "100", "", null);
		}

		// Token: 0x06000074 RID: 116 RVA: 0x000054AC File Offset: 0x000036AC
		public static void Disable()
		{
			MemoryHandler.m.WriteMemory(fullbright.pointer, "float", "1", "", null);
		}

		// Token: 0x04000063 RID: 99
		public static bool enabled = false;

		// Token: 0x04000064 RID: 100
		public static string pointer = "Minecraft.Windows.exe+0x0369C400,0x30,0xC88,0x70,0x60,0x10,0x138,0x1E8";
	}
}
