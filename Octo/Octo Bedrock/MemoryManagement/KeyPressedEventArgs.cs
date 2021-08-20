using System;
using System.Windows.Forms;

namespace Octo_Gamma.MemoryManagement
{
	// Token: 0x0200001B RID: 27
	public class KeyPressedEventArgs : EventArgs
	{
		// Token: 0x06000091 RID: 145 RVA: 0x00005835 File Offset: 0x00003A35
		internal KeyPressedEventArgs(ModifierKeys modifier, Keys key)
		{
			this._modifier = modifier;
			this._key = key;
		}

		// Token: 0x17000006 RID: 6
		// (get) Token: 0x06000092 RID: 146 RVA: 0x00005850 File Offset: 0x00003A50
		public ModifierKeys Modifier
		{
			get
			{
				return this._modifier;
			}
		}

		// Token: 0x17000007 RID: 7
		// (get) Token: 0x06000093 RID: 147 RVA: 0x00005868 File Offset: 0x00003A68
		public Keys Key
		{
			get
			{
				return this._key;
			}
		}

		// Token: 0x0400006D RID: 109
		private ModifierKeys _modifier;

		// Token: 0x0400006E RID: 110
		private Keys _key;
	}
}
