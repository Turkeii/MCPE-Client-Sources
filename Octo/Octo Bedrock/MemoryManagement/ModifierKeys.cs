using System;

namespace Octo_Gamma.MemoryManagement
{
	// Token: 0x0200001C RID: 28
	[Flags]
	public enum ModifierKeys : uint
	{
		// Token: 0x04000070 RID: 112
		None = 0U,
		// Token: 0x04000071 RID: 113
		Alt = 1U,
		// Token: 0x04000072 RID: 114
		Control = 2U,
		// Token: 0x04000073 RID: 115
		Shift = 4U,
		// Token: 0x04000074 RID: 116
		Win = 8U
	}
}
