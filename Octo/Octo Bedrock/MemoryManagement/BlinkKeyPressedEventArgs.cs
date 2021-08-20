using System;
using System.Windows.Forms;

namespace Octo_Gamma.MemoryManagement
{
	// Token: 0x02000019 RID: 25
	public class BlinkKeyPressedEventArgs : EventArgs
	{
		// Token: 0x06000084 RID: 132 RVA: 0x0000566D File Offset: 0x0000386D
		internal BlinkKeyPressedEventArgs(ModifierKeys modifier, Keys key)
		{
			this._modifier = modifier;
			this._key = key;
		}

		// Token: 0x17000004 RID: 4
		// (get) Token: 0x06000085 RID: 133 RVA: 0x00005688 File Offset: 0x00003888
		public ModifierKeys Modifier
		{
			get
			{
				return this._modifier;
			}
		}

		// Token: 0x17000005 RID: 5
		// (get) Token: 0x06000086 RID: 134 RVA: 0x000056A0 File Offset: 0x000038A0
		public Keys Key
		{
			get
			{
				return this._key;
			}
		}

		// Token: 0x04000068 RID: 104
		private ModifierKeys _modifier;

		// Token: 0x04000069 RID: 105
		private Keys _key;
	}
}
