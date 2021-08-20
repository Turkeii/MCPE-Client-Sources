using System;
using System.Windows.Forms;
using Octo_Gamma.MemoryManagement;

namespace Octo_Gamma
{
	// Token: 0x02000005 RID: 5
	internal static class Program
	{
		// Token: 0x0600002C RID: 44 RVA: 0x00004904 File Offset: 0x00002B04
		[STAThread]
		private static void Main()
		{
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			bool flag = OctoData.ReadData(2) == "false";
			if (flag)
			{
				Application.Run(new UserLicenceAgreement());
			}
			else
			{
				Application.Run(new Form1());
			}
		}
	}
}
