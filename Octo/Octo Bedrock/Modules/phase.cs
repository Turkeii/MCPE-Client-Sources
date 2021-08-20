using System;
using Octo_Gamma.Memory_Management;

namespace Octo_Gamma.Modules
{
	// Token: 0x02000014 RID: 20
	internal class phase
	{
		// Token: 0x06000068 RID: 104 RVA: 0x0000532A File Offset: 0x0000352A
		public static void tick()
		{
		}

		// Token: 0x06000069 RID: 105 RVA: 0x00005330 File Offset: 0x00003530
		public static void Enable()
		{
			phase.ypos = MemoryHandler.m.ReadFloat(phase.pointer, "", true) + 2f;
			MemoryHandler.m.WriteMemory(phase.pointer, "float", phase.ypos.ToString(), "", null);
		}

		// Token: 0x0600006A RID: 106 RVA: 0x00005384 File Offset: 0x00003584
		public static void Disable()
		{
			phase.ypos = MemoryHandler.m.ReadFloat(phase.pointer, "", true) - 2f;
			MemoryHandler.m.WriteMemory(phase.pointer, "float", phase.ypos.ToString(), "", null);
		}

		// Token: 0x0400005D RID: 93
		public static bool enabled = false;

		// Token: 0x0400005E RID: 94
		public static string pointer = "Minecraft.Windows.exe+0x03A3A5B8,0x10,0x18,0x80,0xBC0,0x5E8,0x100,0x49C";

		// Token: 0x0400005F RID: 95
		public static float ypos;
	}
}
