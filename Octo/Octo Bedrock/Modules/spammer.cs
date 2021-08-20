using System;
using System.Threading;
using Octo_Gamma.MemoryManagement;

namespace Octo_Gamma.Modules
{
	// Token: 0x0200000F RID: 15
	internal class spammer
	{
		// Token: 0x06000053 RID: 83 RVA: 0x0000513C File Offset: 0x0000333C
		public static void tick()
		{
			KeyPressing.Keyboard.KeyDown(KeyPressing.Keyboard.ScanCodeShort.KEY_B);
			KeyPressing.Keyboard.KeyUp(KeyPressing.Keyboard.ScanCodeShort.KEY_B);
			KeyPressing.Keyboard.KeyDown(KeyPressing.Keyboard.ScanCodeShort.KEY_O);
			KeyPressing.Keyboard.KeyUp(KeyPressing.Keyboard.ScanCodeShort.KEY_O);
			KeyPressing.Keyboard.KeyDown(KeyPressing.Keyboard.ScanCodeShort.KEY_I);
			KeyPressing.Keyboard.KeyUp(KeyPressing.Keyboard.ScanCodeShort.KEY_I);
			KeyPressing.Keyboard.KeyDown(KeyPressing.Keyboard.ScanCodeShort.RETURN);
			KeyPressing.Keyboard.KeyUp(KeyPressing.Keyboard.ScanCodeShort.RETURN);
			Thread.Sleep(30);
		}

		// Token: 0x04000050 RID: 80
		public static bool enabled;
	}
}
