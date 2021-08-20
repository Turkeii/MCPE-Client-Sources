using System;
using Octo_Gamma.Memory_Management;

namespace Octo_Gamma.Modules
{
	// Token: 0x02000012 RID: 18
	internal class nofall
	{
		// Token: 0x0600005E RID: 94 RVA: 0x00005278 File Offset: 0x00003478
		public static void tick()
		{
		}

		// Token: 0x0600005F RID: 95 RVA: 0x0000527B File Offset: 0x0000347B
		public static void Enable()
		{
			MemoryHandler.m.FreezeValue(nofall.pointer, "int", "0", "");
		}

		// Token: 0x06000060 RID: 96 RVA: 0x0000529D File Offset: 0x0000349D
		public static void Disable()
		{
			MemoryHandler.m.UnfreezeValue(nofall.pointer);
		}

		// Token: 0x04000059 RID: 89
		public static bool enabled = false;

		// Token: 0x0400005A RID: 90
		public static string pointer = "Minecraft.Windows.exe+0x03A34C60,0x0,0x28,0x30,0x18,0x0,0x1BC";
	}
}
