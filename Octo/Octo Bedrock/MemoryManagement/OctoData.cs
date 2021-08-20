using System;
using System.IO;
using System.Linq;

namespace Octo_Gamma.MemoryManagement
{
	// Token: 0x0200001D RID: 29
	internal class OctoData
	{
		// Token: 0x06000094 RID: 148 RVA: 0x00005880 File Offset: 0x00003A80
		public static void WriteData(string newText, int Module)
		{
			string text = OctoData.path + "/userinfo.octodata";
			int num = 3 * Module - 1;
			string[] array = File.ReadAllLines(text);
			array[num - 1] = newText;
			File.WriteAllLines(text, array);
		}

		// Token: 0x06000095 RID: 149 RVA: 0x000058BC File Offset: 0x00003ABC
		public static string ReadData(int Module)
		{
			int num = 3 * Module - 1;
			return File.ReadLines(OctoData.path + "/userinfo.octodata").Skip(num - 1).Take(1).First<string>();
		}

		// Token: 0x04000075 RID: 117
		public static string path = Directory.GetCurrentDirectory();
	}
}
