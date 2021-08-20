using System;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using Octo_Gamma.Memory_Management;

namespace Octo_Gamma.ModManagement
{
	// Token: 0x0200000B RID: 11
	internal class ModModuleManager
	{
		// Token: 0x0600003E RID: 62 RVA: 0x00004D08 File Offset: 0x00002F08
		public static string ReadData(int Module, string Dir)
		{
			int num = 3 * Module - 1;
			return File.ReadLines(Dir).Skip(num - 1).Take(1).First<string>();
		}

		// Token: 0x0600003F RID: 63 RVA: 0x00004D39 File Offset: 0x00002F39
		public static void loadModule(Label ModButton, string ModuleDir)
		{
			ModButton.Show();
			ModButton.Text = ModModuleManager.ReadData(1, ModuleDir);
		}

		// Token: 0x06000040 RID: 64 RVA: 0x00004D54 File Offset: 0x00002F54
		public static void enableModule(string ModuleDir)
		{
			string text = ModModuleManager.ReadData(2, ModuleDir);
			bool flag = ModModuleManager.ReadData(4, ModuleDir) == "Freeze";
			if (flag)
			{
				MemoryHandler.m.FreezeValue(text, ModModuleManager.ReadData(3, ModuleDir), ModModuleManager.ReadData(5, ModuleDir), "");
			}
			else
			{
				bool flag2 = ModModuleManager.ReadData(4, ModuleDir) == "UnFreeze";
				if (flag2)
				{
					MemoryHandler.m.UnfreezeValue(text);
				}
				else
				{
					bool flag3 = ModModuleManager.ReadData(4, ModuleDir) == "Set";
					if (flag3)
					{
						MemoryHandler.m.WriteMemory(text, ModModuleManager.ReadData(3, ModuleDir), ModModuleManager.ReadData(5, ModuleDir), "", null);
					}
				}
			}
		}

		// Token: 0x06000041 RID: 65 RVA: 0x00004E00 File Offset: 0x00003000
		public static void disableModule(string ModuleDir)
		{
			string text = ModModuleManager.ReadData(2, ModuleDir);
			bool flag = ModModuleManager.ReadData(6, ModuleDir) == "Freeze";
			if (flag)
			{
				MemoryHandler.m.FreezeValue(text, ModModuleManager.ReadData(3, ModuleDir), ModModuleManager.ReadData(7, ModuleDir), "");
			}
			else
			{
				bool flag2 = ModModuleManager.ReadData(6, ModuleDir) == "UnFreeze";
				if (flag2)
				{
					MemoryHandler.m.UnfreezeValue(text);
				}
				else
				{
					bool flag3 = ModModuleManager.ReadData(6, ModuleDir) == "Set";
					if (flag3)
					{
						MemoryHandler.m.WriteMemory(text, ModModuleManager.ReadData(3, ModuleDir), ModModuleManager.ReadData(7, ModuleDir), "", null);
					}
				}
			}
		}
	}
}
