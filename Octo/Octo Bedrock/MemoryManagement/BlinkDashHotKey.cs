using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Octo_Gamma.MemoryManagement
{
	// Token: 0x02000018 RID: 24
	public sealed class BlinkDashHotKey : IDisposable
	{
		// Token: 0x0600007A RID: 122
		[DllImport("user32.dll")]
		private static extern bool RegisterHotKey(IntPtr hWnd, int id, uint fsModifiers, uint vk);

		// Token: 0x0600007B RID: 123
		[DllImport("user32.dll")]
		private static extern bool UnregisterHotKey(IntPtr hWnd, int id);

		// Token: 0x0600007C RID: 124 RVA: 0x000054F3 File Offset: 0x000036F3
		public BlinkDashHotKey()
		{
			this._window.KeyPressed += delegate(object sender, KeyPressedEventArgs args)
			{
				bool flag = this.KeyPressed != null;
				if (flag)
				{
					this.KeyPressed(this, args);
				}
			};
		}

		// Token: 0x0600007D RID: 125 RVA: 0x00005520 File Offset: 0x00003720
		public void RegisterHotKey(ModifierKeys modifier, Keys key)
		{
			BlinkDashHotKey._currentId++;
			bool flag = !BlinkDashHotKey.RegisterHotKey(this._window.Handle, BlinkDashHotKey._currentId, (uint)modifier, (uint)key);
			if (flag)
			{
				throw new InvalidOperationException("Couldn’t register the hot key.");
			}
		}

		// Token: 0x0600007E RID: 126 RVA: 0x00005563 File Offset: 0x00003763
		public void UnRegisterHotKey()
		{
			BlinkDashHotKey.UnregisterHotKey(this._window.Handle, BlinkDashHotKey._currentId);
			BlinkDashHotKey._currentId--;
		}

		// Token: 0x14000001 RID: 1
		// (add) Token: 0x0600007F RID: 127 RVA: 0x00005588 File Offset: 0x00003788
		// (remove) Token: 0x06000080 RID: 128 RVA: 0x000055C0 File Offset: 0x000037C0
		public event EventHandler<KeyPressedEventArgs> KeyPressed;

		// Token: 0x06000081 RID: 129 RVA: 0x000055F8 File Offset: 0x000037F8
		public void Dispose()
		{
			for (int i = BlinkDashHotKey._currentId; i > 0; i--)
			{
				BlinkDashHotKey.UnregisterHotKey(this._window.Handle, i);
			}
			this._window.Dispose();
		}

		// Token: 0x04000065 RID: 101
		private BlinkDashHotKey.Window _window = new BlinkDashHotKey.Window();

		// Token: 0x04000066 RID: 102
		public static int _currentId = 1;

		// Token: 0x02000020 RID: 32
		private class Window : NativeWindow, IDisposable
		{
			// Token: 0x0600009C RID: 156 RVA: 0x000059D7 File Offset: 0x00003BD7
			public Window()
			{
				this.CreateHandle(new CreateParams());
			}

			// Token: 0x0600009D RID: 157 RVA: 0x000059F0 File Offset: 0x00003BF0
			protected override void WndProc(ref Message m)
			{
				base.WndProc(ref m);
				bool flag = m.Msg == BlinkDashHotKey.Window.WM_HOTKEY;
				if (flag)
				{
					Keys key = (Keys)((int)m.LParam >> 16 & 65535);
					ModifierKeys modifier = (ModifierKeys)((int)m.LParam & 65535);
					bool flag2 = this.KeyPressed != null;
					if (flag2)
					{
						this.KeyPressed(this, new KeyPressedEventArgs(modifier, key));
					}
				}
			}

			// Token: 0x14000003 RID: 3
			// (add) Token: 0x0600009E RID: 158 RVA: 0x00005A64 File Offset: 0x00003C64
			// (remove) Token: 0x0600009F RID: 159 RVA: 0x00005A9C File Offset: 0x00003C9C
			public event EventHandler<KeyPressedEventArgs> KeyPressed;

			// Token: 0x060000A0 RID: 160 RVA: 0x00005AD1 File Offset: 0x00003CD1
			public void Dispose()
			{
				this.DestroyHandle();
			}

			// Token: 0x04000077 RID: 119
			private static int WM_HOTKEY = 786;
		}
	}
}
