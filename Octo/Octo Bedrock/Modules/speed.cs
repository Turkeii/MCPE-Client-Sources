using System;
using Octo_Gamma.Memory_Management;

namespace Octo_Gamma.Modules
{
	// Token: 0x02000011 RID: 17
	internal class speed
	{
		// Token: 0x06000059 RID: 89 RVA: 0x00005209 File Offset: 0x00003409
		public static void tick()
		{
		}

		// Token: 0x0600005A RID: 90 RVA: 0x0000520C File Offset: 0x0000340C
		public static void Enable(string speedvalue)
		{
			MemoryHandler.m.FreezeValue(speed.pointer, "float", speedvalue, "");
		}

		// Token: 0x0600005B RID: 91 RVA: 0x0000522A File Offset: 0x0000342A
		public static void Disable()
		{
			MemoryHandler.m.UnfreezeValue(speed.pointer);
			MemoryHandler.m.WriteMemory(speed.pointer, "float", "0.1000000015", "", null);
		}

		// Token: 0x04000057 RID: 87
		public static bool enabled = false;

		// Token: 0x04000058 RID: 88
		public static string pointer = "Minecraft.Windows.exe+0x03A3A658,0x10,0x18,0xB0,0x478,0x18,0x1F8,0x9C";
	}
}
