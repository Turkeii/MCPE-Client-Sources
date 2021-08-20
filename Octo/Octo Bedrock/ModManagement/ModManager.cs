using System;
using System.IO;

namespace Octo_Gamma.ModManagement
{
	// Token: 0x02000009 RID: 9
	internal class ModManager
	{
		// Token: 0x06000037 RID: 55 RVA: 0x00004A5C File Offset: 0x00002C5C
		public static void getMods()
		{
			FileInfo[] files = new DirectoryInfo(ModManager.path + "/Mods/").GetFiles("manifest.omm", SearchOption.AllDirectories);
			bool flag = files.Length != 0;
			if (flag)
			{
				ModManager.Mod1Dir = files[0].DirectoryName;
			}
			else
			{
				bool flag2 = files.Length > 1;
				if (flag2)
				{
					ModManager.Mod2Dir = files[1].DirectoryName;
				}
				else
				{
					bool flag3 = files.Length > 2;
					if (flag3)
					{
						ModManager.Mod3Dir = files[2].DirectoryName;
					}
				}
			}
		}

		// Token: 0x04000036 RID: 54
		public static string Mod1Dir = "";

		// Token: 0x04000037 RID: 55
		public static string Mod2Dir = "";

		// Token: 0x04000038 RID: 56
		public static string Mod3Dir = "";

		// Token: 0x04000039 RID: 57
		public static string path = Directory.GetCurrentDirectory();
	}
}
