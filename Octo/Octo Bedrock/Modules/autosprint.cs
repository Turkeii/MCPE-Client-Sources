using System;
using Octo_Gamma.Memory_Management;

namespace Octo_Gamma.Modules
{
	// Token: 0x0200000D RID: 13
	internal class autosprint
	{
		// Token: 0x06000049 RID: 73 RVA: 0x00004F34 File Offset: 0x00003134
		public static void tick()
		{
		}

		// Token: 0x0600004A RID: 74 RVA: 0x00004F37 File Offset: 0x00003137
		public static void Enable()
		{
			MemoryHandler.m.FreezeValue(autosprint.pointer, "float", "0.1299999952", "");
		}

		// Token: 0x0600004B RID: 75 RVA: 0x00004F59 File Offset: 0x00003159
		public static void Disable()
		{
			MemoryHandler.m.UnfreezeValue(autosprint.pointer);
		}

		// Token: 0x04000046 RID: 70
		public static bool enabled = false;

		// Token: 0x04000047 RID: 71
		public static string pointer = speed.pointer;
	}
}
