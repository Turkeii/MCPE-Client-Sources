using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Octo_Gamma.MemoryManagement
{
	// Token: 0x0200001A RID: 26
	public sealed class HotkeyManager : IDisposable
	{
		// Token: 0x06000087 RID: 135
		[DllImport("user32.dll")]
		private static extern bool RegisterHotKey(IntPtr hWnd, int id, uint fsModifiers, uint vk);

		// Token: 0x06000088 RID: 136
		[DllImport("user32.dll")]
		private static extern bool UnregisterHotKey(IntPtr hWnd, int id);

		// Token: 0x06000089 RID: 137 RVA: 0x000056B8 File Offset: 0x000038B8
		public HotkeyManager()
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

		// Token: 0x0600008A RID: 138 RVA: 0x000056E8 File Offset: 0x000038E8
		public void RegisterHotKey(ModifierKeys modifier, Keys key)
		{
			HotkeyManager._currentId++;
			bool flag = !HotkeyManager.RegisterHotKey(this._window.Handle, HotkeyManager._currentId, (uint)modifier, (uint)key);
			if (flag)
			{
				throw new InvalidOperationException("Couldn’t register the hot key.");
			}
		}

		// Token: 0x0600008B RID: 139 RVA: 0x0000572B File Offset: 0x0000392B
		public void UnRegisterHotKey()
		{
			HotkeyManager.UnregisterHotKey(this._window.Handle, HotkeyManager._currentId);
			HotkeyManager._currentId--;
		}

		// Token: 0x14000002 RID: 2
		// (add) Token: 0x0600008C RID: 140 RVA: 0x00005750 File Offset: 0x00003950
		// (remove) Token: 0x0600008D RID: 141 RVA: 0x00005788 File Offset: 0x00003988
		public event EventHandler<KeyPressedEventArgs> KeyPressed;

		// Token: 0x0600008E RID: 142 RVA: 0x000057C0 File Offset: 0x000039C0
		public void Dispose()
		{
			for (int i = HotkeyManager._currentId; i > 0; i--)
			{
				HotkeyManager.UnregisterHotKey(this._window.Handle, i);
			}
			this._window.Dispose();
		}

		// Token: 0x0400006A RID: 106
		private HotkeyManager.Window _window = new HotkeyManager.Window();

		// Token: 0x0400006B RID: 107
		public static int _currentId = 1;

		// Token: 0x02000021 RID: 33
		private class Window : NativeWindow, IDisposable
		{
			// Token: 0x060000A2 RID: 162 RVA: 0x00005AE7 File Offset: 0x00003CE7
			public Window()
			{
				this.CreateHandle(new CreateParams());
			}

			// Token: 0x060000A3 RID: 163 RVA: 0x00005B00 File Offset: 0x00003D00
			protected override void WndProc(ref Message m)
			{
				base.WndProc(ref m);
				bool flag = m.Msg == HotkeyManager.Window.WM_HOTKEY;
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

			// Token: 0x14000004 RID: 4
			// (add) Token: 0x060000A4 RID: 164 RVA: 0x00005B74 File Offset: 0x00003D74
			// (remove) Token: 0x060000A5 RID: 165 RVA: 0x00005BAC File Offset: 0x00003DAC
			public event EventHandler<KeyPressedEventArgs> KeyPressed;

			// Token: 0x060000A6 RID: 166 RVA: 0x00005BE1 File Offset: 0x00003DE1
			public void Dispose()
			{
				this.DestroyHandle();
			}

			// Token: 0x04000079 RID: 121
			private static int WM_HOTKEY = 786;
		}
	}
}
