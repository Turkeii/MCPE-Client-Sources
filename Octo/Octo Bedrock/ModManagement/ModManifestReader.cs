using System;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace Octo_Gamma.ModManagement
{
	// Token: 0x0200000A RID: 10
	internal class ModManifestReader
	{
		// Token: 0x0600003A RID: 58 RVA: 0x00004B0C File Offset: 0x00002D0C
		public static string ReadData(int Module, string ModDir)
		{
			int num = 3 * Module - 1;
			return File.ReadLines(ModDir + "\\manifest.omm").Skip(num - 1).Take(1).First<string>();
		}

		// Token: 0x0600003B RID: 59 RVA: 0x00004B48 File Offset: 0x00002D48
		public static void ReadManifests(Label mod1Title, Label mod2Title, Label mod3Title, Label mod1Button, Label mod2Button, Label mod3Button)
		{
			ModManager.getMods();
			bool flag = ModManager.Mod1Dir != "";
			if (flag)
			{
				mod1Title.Text = ModManifestReader.ReadData(1, ModManager.Mod1Dir);
				bool flag2 = ModManifestReader.ReadData(2, ModManager.Mod1Dir) != "N/A";
				if (flag2)
				{
					ModModuleManager.loadModule(mod1Button, ModManager.Mod1Dir + "\\" + ModManifestReader.ReadData(2, ModManager.Mod1Dir));
					ModManifestReader.Mod1ModuleDir = ModManager.Mod1Dir + "\\" + ModManifestReader.ReadData(2, ModManager.Mod1Dir);
				}
			}
			else
			{
				bool flag3 = ModManager.Mod2Dir != "";
				if (flag3)
				{
					mod2Title.Text = ModManifestReader.ReadData(1, ModManager.Mod2Dir);
					bool flag4 = ModManifestReader.ReadData(2, ModManager.Mod2Dir) != "N/A";
					if (flag4)
					{
						ModModuleManager.loadModule(mod2Button, ModManager.Mod2Dir + "\\" + ModManifestReader.ReadData(2, ModManager.Mod2Dir));
						ModManifestReader.Mod2ModuleDir = ModManager.Mod2Dir + "\\" + ModManifestReader.ReadData(2, ModManager.Mod2Dir);
					}
				}
				else
				{
					bool flag5 = ModManager.Mod3Dir != "";
					if (flag5)
					{
						mod3Title.Text = ModManifestReader.ReadData(1, ModManager.Mod3Dir);
						bool flag6 = ModManifestReader.ReadData(2, ModManager.Mod3Dir) != "N/A";
						if (flag6)
						{
							ModModuleManager.loadModule(mod3Button, ModManager.Mod3Dir + "\\" + ModManifestReader.ReadData(2, ModManager.Mod3Dir));
							ModManifestReader.Mod3ModuleDir = ModManager.Mod3Dir + "\\" + ModManifestReader.ReadData(2, ModManager.Mod3Dir);
						}
					}
				}
			}
		}

		// Token: 0x0400003A RID: 58
		public static string path = Directory.GetCurrentDirectory();

		// Token: 0x0400003B RID: 59
		public static string Mod1ModuleDir;

		// Token: 0x0400003C RID: 60
		public static string Mod2ModuleDir;

		// Token: 0x0400003D RID: 61
		public static string Mod3ModuleDir;
	}
}
