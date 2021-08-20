using System;
using Octo_Gamma.Memory_Management;

namespace Octo_Gamma.Modules
{
	// Token: 0x02000013 RID: 19
	internal class airjump
	{
		// Token: 0x06000063 RID: 99 RVA: 0x000052CB File Offset: 0x000034CB
		public static void tick()
		{
		}

		// Token: 0x06000064 RID: 100 RVA: 0x000052CE File Offset: 0x000034CE
		public static void Enable()
		{
			MemoryHandler.m.FreezeValue(airjump.pointer, "int", "16777473", "");
			nofall.Enable();
		}

		// Token: 0x06000065 RID: 101 RVA: 0x000052F6 File Offset: 0x000034F6
		public static void Disable()
		{
			MemoryHandler.m.UnfreezeValue(airjump.pointer);
			nofall.Disable();
		}

		// Token: 0x0400005B RID: 91
		public static bool enabled = false;

		// Token: 0x0400005C RID: 92
		public static string pointer = "Minecraft.Windows.exe+0x036A2248,0x8,0x38,0xC8,0x88,0x50,0x0,0x1C0";
	}
}
