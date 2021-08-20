using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using Octo_Gamma.MemoryManagement;

namespace Octo_Gamma
{
	// Token: 0x02000004 RID: 4
	public partial class UserLicenceAgreement : Form
	{
		// Token: 0x06000027 RID: 39 RVA: 0x000046A2 File Offset: 0x000028A2
		public UserLicenceAgreement()
		{
			this.InitializeComponent();
		}

		// Token: 0x06000028 RID: 40 RVA: 0x000046BC File Offset: 0x000028BC
		private void button1_Click(object sender, EventArgs e)
		{
			OctoData.WriteData("true", 2);
			Form1 form = new Form1();
			form.Show();
			base.Close();
		}

		// Token: 0x06000029 RID: 41 RVA: 0x000046EA File Offset: 0x000028EA
		private void UserLicenceAgreement_Load(object sender, EventArgs e)
		{
		}
	}
}
