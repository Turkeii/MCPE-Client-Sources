using System;
using System.Threading;
using Memory;
using Octo_Gamma.Modules;

namespace Octo_Gamma.Memory_Management
{
	// Token: 0x02000008 RID: 8
	internal class MemoryHandler
	{
		// Token: 0x06000034 RID: 52 RVA: 0x000049FC File Offset: 0x00002BFC
		public static void tick()
		{
			bool enabled = triggerbot.enabled;
			if (enabled)
			{
				triggerbot.tick();
			}
			bool enabled2 = spammer.enabled;
			if (enabled2)
			{
				spammer.tick();
			}
			bool active = AutoSpeedBridge.active;
			if (active)
			{
				AutoSpeedBridge.tick();
			}
			Thread.Sleep(10);
		}

		// Token: 0x04000035 RID: 53
		public static Mem m = new Mem();
	}
}
