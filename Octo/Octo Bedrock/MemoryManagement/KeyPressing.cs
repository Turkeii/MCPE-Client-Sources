using System;
using System.Runtime.InteropServices;

namespace Octo_Gamma.MemoryManagement
{
	// Token: 0x02000017 RID: 23
	internal class KeyPressing
	{
		// Token: 0x06000077 RID: 119
		[DllImport("USER32.DLL", CharSet = CharSet.Unicode)]
		public static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

		// Token: 0x06000078 RID: 120
		[DllImport("USER32.DLL")]
		public static extern bool SetForegroundWindow(IntPtr hWnd);

		// Token: 0x0200001F RID: 31
		public class Keyboard
		{
			// Token: 0x06000098 RID: 152 RVA: 0x00005910 File Offset: 0x00003B10
			public static void KeyDown(KeyPressing.Keyboard.ScanCodeShort a)
			{
				KeyPressing.Keyboard.INPUT[] array = new KeyPressing.Keyboard.INPUT[1];
				KeyPressing.Keyboard.INPUT input = default(KeyPressing.Keyboard.INPUT);
				input.type = 1U;
				input.U.ki.wScan = a;
				input.U.ki.dwFlags = KeyPressing.Keyboard.KEYEVENTF.SCANCODE;
				array[0] = input;
				KeyPressing.Keyboard.SendInput(1U, array, KeyPressing.Keyboard.INPUT.Size);
			}

			// Token: 0x06000099 RID: 153 RVA: 0x00005970 File Offset: 0x00003B70
			public static void KeyUp(KeyPressing.Keyboard.ScanCodeShort a)
			{
				KeyPressing.Keyboard.INPUT[] array = new KeyPressing.Keyboard.INPUT[1];
				KeyPressing.Keyboard.INPUT input = default(KeyPressing.Keyboard.INPUT);
				input.type = 1U;
				input.U.ki.wScan = a;
				input.U.ki.dwFlags = KeyPressing.Keyboard.KEYEVENTF.KEYUP;
				array[0] = input;
				KeyPressing.Keyboard.SendInput(1U, array, KeyPressing.Keyboard.INPUT.Size);
			}

			// Token: 0x0600009A RID: 154
			[DllImport("user32.dll")]
			internal static extern uint SendInput(uint nInputs, [MarshalAs(UnmanagedType.LPArray)] [In] KeyPressing.Keyboard.INPUT[] pInputs, int cbSize);

			// Token: 0x02000022 RID: 34
			public struct INPUT
			{
				// Token: 0x17000008 RID: 8
				// (get) Token: 0x060000A8 RID: 168 RVA: 0x00005BF8 File Offset: 0x00003DF8
				public static int Size
				{
					get
					{
						return Marshal.SizeOf(typeof(KeyPressing.Keyboard.INPUT));
					}
				}

				// Token: 0x0400007B RID: 123
				public uint type;

				// Token: 0x0400007C RID: 124
				public KeyPressing.Keyboard.InputUnion U;
			}

			// Token: 0x02000023 RID: 35
			[StructLayout(LayoutKind.Explicit)]
			public struct InputUnion
			{
				// Token: 0x0400007D RID: 125
				[FieldOffset(0)]
				internal KeyPressing.Keyboard.MOUSEINPUT mi;

				// Token: 0x0400007E RID: 126
				[FieldOffset(0)]
				internal KeyPressing.Keyboard.KEYBDINPUT ki;

				// Token: 0x0400007F RID: 127
				[FieldOffset(0)]
				internal KeyPressing.Keyboard.HARDWAREINPUT hi;
			}

			// Token: 0x02000024 RID: 36
			public struct MOUSEINPUT
			{
				// Token: 0x04000080 RID: 128
				internal int dx;

				// Token: 0x04000081 RID: 129
				internal int dy;

				// Token: 0x04000082 RID: 130
				internal KeyPressing.Keyboard.MouseEventDataXButtons mouseData;

				// Token: 0x04000083 RID: 131
				internal KeyPressing.Keyboard.MOUSEEVENTF dwFlags;

				// Token: 0x04000084 RID: 132
				internal uint time;

				// Token: 0x04000085 RID: 133
				internal UIntPtr dwExtraInfo;
			}

			// Token: 0x02000025 RID: 37
			[Flags]
			public enum MouseEventDataXButtons : uint
			{
				// Token: 0x04000087 RID: 135
				Nothing = 0U,
				// Token: 0x04000088 RID: 136
				XBUTTON1 = 1U,
				// Token: 0x04000089 RID: 137
				XBUTTON2 = 2U
			}

			// Token: 0x02000026 RID: 38
			[Flags]
			public enum MOUSEEVENTF : uint
			{
				// Token: 0x0400008B RID: 139
				ABSOLUTE = 32768U,
				// Token: 0x0400008C RID: 140
				HWHEEL = 4096U,
				// Token: 0x0400008D RID: 141
				MOVE = 1U,
				// Token: 0x0400008E RID: 142
				MOVE_NOCOALESCE = 8192U,
				// Token: 0x0400008F RID: 143
				LEFTDOWN = 2U,
				// Token: 0x04000090 RID: 144
				LEFTUP = 4U,
				// Token: 0x04000091 RID: 145
				RIGHTDOWN = 8U,
				// Token: 0x04000092 RID: 146
				RIGHTUP = 16U,
				// Token: 0x04000093 RID: 147
				MIDDLEDOWN = 32U,
				// Token: 0x04000094 RID: 148
				MIDDLEUP = 64U,
				// Token: 0x04000095 RID: 149
				VIRTUALDESK = 16384U,
				// Token: 0x04000096 RID: 150
				WHEEL = 2048U,
				// Token: 0x04000097 RID: 151
				XDOWN = 128U,
				// Token: 0x04000098 RID: 152
				XUP = 256U
			}

			// Token: 0x02000027 RID: 39
			public struct KEYBDINPUT
			{
				// Token: 0x04000099 RID: 153
				internal KeyPressing.Keyboard.VirtualKeyShort wVk;

				// Token: 0x0400009A RID: 154
				internal KeyPressing.Keyboard.ScanCodeShort wScan;

				// Token: 0x0400009B RID: 155
				internal KeyPressing.Keyboard.KEYEVENTF dwFlags;

				// Token: 0x0400009C RID: 156
				internal int time;

				// Token: 0x0400009D RID: 157
				internal UIntPtr dwExtraInfo;
			}

			// Token: 0x02000028 RID: 40
			[Flags]
			public enum KEYEVENTF : uint
			{
				// Token: 0x0400009F RID: 159
				EXTENDEDKEY = 1U,
				// Token: 0x040000A0 RID: 160
				KEYUP = 2U,
				// Token: 0x040000A1 RID: 161
				SCANCODE = 8U,
				// Token: 0x040000A2 RID: 162
				UNICODE = 4U
			}

			// Token: 0x02000029 RID: 41
			public enum VirtualKeyShort : short
			{
				// Token: 0x040000A4 RID: 164
				LBUTTON = 1,
				// Token: 0x040000A5 RID: 165
				RBUTTON,
				// Token: 0x040000A6 RID: 166
				CANCEL,
				// Token: 0x040000A7 RID: 167
				MBUTTON,
				// Token: 0x040000A8 RID: 168
				XBUTTON1,
				// Token: 0x040000A9 RID: 169
				XBUTTON2,
				// Token: 0x040000AA RID: 170
				BACK = 8,
				// Token: 0x040000AB RID: 171
				TAB,
				// Token: 0x040000AC RID: 172
				CLEAR = 12,
				// Token: 0x040000AD RID: 173
				RETURN,
				// Token: 0x040000AE RID: 174
				SHIFT = 16,
				// Token: 0x040000AF RID: 175
				CONTROL,
				// Token: 0x040000B0 RID: 176
				MENU,
				// Token: 0x040000B1 RID: 177
				PAUSE,
				// Token: 0x040000B2 RID: 178
				CAPITAL,
				// Token: 0x040000B3 RID: 179
				KANA,
				// Token: 0x040000B4 RID: 180
				HANGUL = 21,
				// Token: 0x040000B5 RID: 181
				JUNJA = 23,
				// Token: 0x040000B6 RID: 182
				FINAL,
				// Token: 0x040000B7 RID: 183
				HANJA,
				// Token: 0x040000B8 RID: 184
				KANJI = 25,
				// Token: 0x040000B9 RID: 185
				ESCAPE = 27,
				// Token: 0x040000BA RID: 186
				CONVERT,
				// Token: 0x040000BB RID: 187
				NONCONVERT,
				// Token: 0x040000BC RID: 188
				ACCEPT,
				// Token: 0x040000BD RID: 189
				MODECHANGE,
				// Token: 0x040000BE RID: 190
				SPACE,
				// Token: 0x040000BF RID: 191
				PRIOR,
				// Token: 0x040000C0 RID: 192
				NEXT,
				// Token: 0x040000C1 RID: 193
				END,
				// Token: 0x040000C2 RID: 194
				HOME,
				// Token: 0x040000C3 RID: 195
				LEFT,
				// Token: 0x040000C4 RID: 196
				UP,
				// Token: 0x040000C5 RID: 197
				RIGHT,
				// Token: 0x040000C6 RID: 198
				DOWN,
				// Token: 0x040000C7 RID: 199
				SELECT,
				// Token: 0x040000C8 RID: 200
				PRINT,
				// Token: 0x040000C9 RID: 201
				EXECUTE,
				// Token: 0x040000CA RID: 202
				SNAPSHOT,
				// Token: 0x040000CB RID: 203
				INSERT,
				// Token: 0x040000CC RID: 204
				DELETE,
				// Token: 0x040000CD RID: 205
				HELP,
				// Token: 0x040000CE RID: 206
				KEY_0,
				// Token: 0x040000CF RID: 207
				KEY_1,
				// Token: 0x040000D0 RID: 208
				KEY_2,
				// Token: 0x040000D1 RID: 209
				KEY_3,
				// Token: 0x040000D2 RID: 210
				KEY_4,
				// Token: 0x040000D3 RID: 211
				KEY_5,
				// Token: 0x040000D4 RID: 212
				KEY_6,
				// Token: 0x040000D5 RID: 213
				KEY_7,
				// Token: 0x040000D6 RID: 214
				KEY_8,
				// Token: 0x040000D7 RID: 215
				KEY_9,
				// Token: 0x040000D8 RID: 216
				KEY_A = 65,
				// Token: 0x040000D9 RID: 217
				KEY_B,
				// Token: 0x040000DA RID: 218
				KEY_C,
				// Token: 0x040000DB RID: 219
				KEY_D,
				// Token: 0x040000DC RID: 220
				KEY_E,
				// Token: 0x040000DD RID: 221
				KEY_F,
				// Token: 0x040000DE RID: 222
				KEY_G,
				// Token: 0x040000DF RID: 223
				KEY_H,
				// Token: 0x040000E0 RID: 224
				KEY_I,
				// Token: 0x040000E1 RID: 225
				KEY_J,
				// Token: 0x040000E2 RID: 226
				KEY_K,
				// Token: 0x040000E3 RID: 227
				KEY_L,
				// Token: 0x040000E4 RID: 228
				KEY_M,
				// Token: 0x040000E5 RID: 229
				KEY_N,
				// Token: 0x040000E6 RID: 230
				KEY_O,
				// Token: 0x040000E7 RID: 231
				KEY_P,
				// Token: 0x040000E8 RID: 232
				KEY_Q,
				// Token: 0x040000E9 RID: 233
				KEY_R,
				// Token: 0x040000EA RID: 234
				KEY_S,
				// Token: 0x040000EB RID: 235
				KEY_T,
				// Token: 0x040000EC RID: 236
				KEY_U,
				// Token: 0x040000ED RID: 237
				KEY_V,
				// Token: 0x040000EE RID: 238
				KEY_W,
				// Token: 0x040000EF RID: 239
				KEY_X,
				// Token: 0x040000F0 RID: 240
				KEY_Y,
				// Token: 0x040000F1 RID: 241
				KEY_Z,
				// Token: 0x040000F2 RID: 242
				LWIN,
				// Token: 0x040000F3 RID: 243
				RWIN,
				// Token: 0x040000F4 RID: 244
				APPS,
				// Token: 0x040000F5 RID: 245
				SLEEP = 95,
				// Token: 0x040000F6 RID: 246
				NUMPAD0,
				// Token: 0x040000F7 RID: 247
				NUMPAD1,
				// Token: 0x040000F8 RID: 248
				NUMPAD2,
				// Token: 0x040000F9 RID: 249
				NUMPAD3,
				// Token: 0x040000FA RID: 250
				NUMPAD4,
				// Token: 0x040000FB RID: 251
				NUMPAD5,
				// Token: 0x040000FC RID: 252
				NUMPAD6,
				// Token: 0x040000FD RID: 253
				NUMPAD7,
				// Token: 0x040000FE RID: 254
				NUMPAD8,
				// Token: 0x040000FF RID: 255
				NUMPAD9,
				// Token: 0x04000100 RID: 256
				MULTIPLY,
				// Token: 0x04000101 RID: 257
				ADD,
				// Token: 0x04000102 RID: 258
				SEPARATOR,
				// Token: 0x04000103 RID: 259
				SUBTRACT,
				// Token: 0x04000104 RID: 260
				DECIMAL,
				// Token: 0x04000105 RID: 261
				DIVIDE,
				// Token: 0x04000106 RID: 262
				F1,
				// Token: 0x04000107 RID: 263
				F2,
				// Token: 0x04000108 RID: 264
				F3,
				// Token: 0x04000109 RID: 265
				F4,
				// Token: 0x0400010A RID: 266
				F5,
				// Token: 0x0400010B RID: 267
				F6,
				// Token: 0x0400010C RID: 268
				F7,
				// Token: 0x0400010D RID: 269
				F8,
				// Token: 0x0400010E RID: 270
				F9,
				// Token: 0x0400010F RID: 271
				F10,
				// Token: 0x04000110 RID: 272
				F11,
				// Token: 0x04000111 RID: 273
				F12,
				// Token: 0x04000112 RID: 274
				F13,
				// Token: 0x04000113 RID: 275
				F14,
				// Token: 0x04000114 RID: 276
				F15,
				// Token: 0x04000115 RID: 277
				F16,
				// Token: 0x04000116 RID: 278
				F17,
				// Token: 0x04000117 RID: 279
				F18,
				// Token: 0x04000118 RID: 280
				F19,
				// Token: 0x04000119 RID: 281
				F20,
				// Token: 0x0400011A RID: 282
				F21,
				// Token: 0x0400011B RID: 283
				F22,
				// Token: 0x0400011C RID: 284
				F23,
				// Token: 0x0400011D RID: 285
				F24,
				// Token: 0x0400011E RID: 286
				NUMLOCK = 144,
				// Token: 0x0400011F RID: 287
				SCROLL,
				// Token: 0x04000120 RID: 288
				LSHIFT = 160,
				// Token: 0x04000121 RID: 289
				RSHIFT,
				// Token: 0x04000122 RID: 290
				LCONTROL,
				// Token: 0x04000123 RID: 291
				RCONTROL,
				// Token: 0x04000124 RID: 292
				LMENU,
				// Token: 0x04000125 RID: 293
				RMENU,
				// Token: 0x04000126 RID: 294
				BROWSER_BACK,
				// Token: 0x04000127 RID: 295
				BROWSER_FORWARD,
				// Token: 0x04000128 RID: 296
				BROWSER_REFRESH,
				// Token: 0x04000129 RID: 297
				BROWSER_STOP,
				// Token: 0x0400012A RID: 298
				BROWSER_SEARCH,
				// Token: 0x0400012B RID: 299
				BROWSER_FAVORITES,
				// Token: 0x0400012C RID: 300
				BROWSER_HOME,
				// Token: 0x0400012D RID: 301
				VOLUME_MUTE,
				// Token: 0x0400012E RID: 302
				VOLUME_DOWN,
				// Token: 0x0400012F RID: 303
				VOLUME_UP,
				// Token: 0x04000130 RID: 304
				MEDIA_NEXT_TRACK,
				// Token: 0x04000131 RID: 305
				MEDIA_PREV_TRACK,
				// Token: 0x04000132 RID: 306
				MEDIA_STOP,
				// Token: 0x04000133 RID: 307
				MEDIA_PLAY_PAUSE,
				// Token: 0x04000134 RID: 308
				LAUNCH_MAIL,
				// Token: 0x04000135 RID: 309
				LAUNCH_MEDIA_SELECT,
				// Token: 0x04000136 RID: 310
				LAUNCH_APP1,
				// Token: 0x04000137 RID: 311
				LAUNCH_APP2,
				// Token: 0x04000138 RID: 312
				OEM_1 = 186,
				// Token: 0x04000139 RID: 313
				OEM_PLUS,
				// Token: 0x0400013A RID: 314
				OEM_COMMA,
				// Token: 0x0400013B RID: 315
				OEM_MINUS,
				// Token: 0x0400013C RID: 316
				OEM_PERIOD,
				// Token: 0x0400013D RID: 317
				OEM_2,
				// Token: 0x0400013E RID: 318
				OEM_3,
				// Token: 0x0400013F RID: 319
				OEM_4 = 219,
				// Token: 0x04000140 RID: 320
				OEM_5,
				// Token: 0x04000141 RID: 321
				OEM_6,
				// Token: 0x04000142 RID: 322
				OEM_7,
				// Token: 0x04000143 RID: 323
				OEM_8,
				// Token: 0x04000144 RID: 324
				OEM_102 = 226,
				// Token: 0x04000145 RID: 325
				PROCESSKEY = 229,
				// Token: 0x04000146 RID: 326
				PACKET = 231,
				// Token: 0x04000147 RID: 327
				ATTN = 246,
				// Token: 0x04000148 RID: 328
				CRSEL,
				// Token: 0x04000149 RID: 329
				EXSEL,
				// Token: 0x0400014A RID: 330
				EREOF,
				// Token: 0x0400014B RID: 331
				PLAY,
				// Token: 0x0400014C RID: 332
				ZOOM,
				// Token: 0x0400014D RID: 333
				NONAME,
				// Token: 0x0400014E RID: 334
				PA1,
				// Token: 0x0400014F RID: 335
				OEM_CLEAR
			}

			// Token: 0x0200002A RID: 42
			public enum ScanCodeShort : short
			{
				// Token: 0x04000151 RID: 337
				LBUTTON,
				// Token: 0x04000152 RID: 338
				RBUTTON = 0,
				// Token: 0x04000153 RID: 339
				CANCEL = 70,
				// Token: 0x04000154 RID: 340
				MBUTTON = 0,
				// Token: 0x04000155 RID: 341
				XBUTTON1 = 0,
				// Token: 0x04000156 RID: 342
				XBUTTON2 = 0,
				// Token: 0x04000157 RID: 343
				BACK = 14,
				// Token: 0x04000158 RID: 344
				TAB,
				// Token: 0x04000159 RID: 345
				CLEAR = 76,
				// Token: 0x0400015A RID: 346
				RETURN = 28,
				// Token: 0x0400015B RID: 347
				SHIFT = 42,
				// Token: 0x0400015C RID: 348
				CONTROL = 29,
				// Token: 0x0400015D RID: 349
				MENU = 56,
				// Token: 0x0400015E RID: 350
				PAUSE = 0,
				// Token: 0x0400015F RID: 351
				CAPITAL = 58,
				// Token: 0x04000160 RID: 352
				KANA = 0,
				// Token: 0x04000161 RID: 353
				HANGUL = 0,
				// Token: 0x04000162 RID: 354
				JUNJA = 0,
				// Token: 0x04000163 RID: 355
				FINAL = 0,
				// Token: 0x04000164 RID: 356
				HANJA = 0,
				// Token: 0x04000165 RID: 357
				KANJI = 0,
				// Token: 0x04000166 RID: 358
				ESCAPE,
				// Token: 0x04000167 RID: 359
				CONVERT = 0,
				// Token: 0x04000168 RID: 360
				NONCONVERT = 0,
				// Token: 0x04000169 RID: 361
				ACCEPT = 0,
				// Token: 0x0400016A RID: 362
				MODECHANGE = 0,
				// Token: 0x0400016B RID: 363
				SPACE = 57,
				// Token: 0x0400016C RID: 364
				PRIOR = 73,
				// Token: 0x0400016D RID: 365
				NEXT = 81,
				// Token: 0x0400016E RID: 366
				END = 79,
				// Token: 0x0400016F RID: 367
				HOME = 71,
				// Token: 0x04000170 RID: 368
				LEFT = 75,
				// Token: 0x04000171 RID: 369
				UP = 72,
				// Token: 0x04000172 RID: 370
				RIGHT = 77,
				// Token: 0x04000173 RID: 371
				DOWN = 80,
				// Token: 0x04000174 RID: 372
				SELECT = 0,
				// Token: 0x04000175 RID: 373
				PRINT = 0,
				// Token: 0x04000176 RID: 374
				EXECUTE = 0,
				// Token: 0x04000177 RID: 375
				SNAPSHOT = 84,
				// Token: 0x04000178 RID: 376
				INSERT = 82,
				// Token: 0x04000179 RID: 377
				DELETE,
				// Token: 0x0400017A RID: 378
				HELP = 99,
				// Token: 0x0400017B RID: 379
				KEY_0 = 11,
				// Token: 0x0400017C RID: 380
				KEY_1 = 2,
				// Token: 0x0400017D RID: 381
				KEY_2,
				// Token: 0x0400017E RID: 382
				KEY_3,
				// Token: 0x0400017F RID: 383
				KEY_4,
				// Token: 0x04000180 RID: 384
				KEY_5,
				// Token: 0x04000181 RID: 385
				KEY_6,
				// Token: 0x04000182 RID: 386
				KEY_7,
				// Token: 0x04000183 RID: 387
				KEY_8,
				// Token: 0x04000184 RID: 388
				KEY_9,
				// Token: 0x04000185 RID: 389
				KEY_A = 30,
				// Token: 0x04000186 RID: 390
				KEY_B = 48,
				// Token: 0x04000187 RID: 391
				KEY_C = 46,
				// Token: 0x04000188 RID: 392
				KEY_D = 32,
				// Token: 0x04000189 RID: 393
				KEY_E = 18,
				// Token: 0x0400018A RID: 394
				KEY_F = 33,
				// Token: 0x0400018B RID: 395
				KEY_G,
				// Token: 0x0400018C RID: 396
				KEY_H,
				// Token: 0x0400018D RID: 397
				KEY_I = 23,
				// Token: 0x0400018E RID: 398
				KEY_J = 36,
				// Token: 0x0400018F RID: 399
				KEY_K,
				// Token: 0x04000190 RID: 400
				KEY_L,
				// Token: 0x04000191 RID: 401
				KEY_M = 50,
				// Token: 0x04000192 RID: 402
				KEY_N = 49,
				// Token: 0x04000193 RID: 403
				KEY_O = 24,
				// Token: 0x04000194 RID: 404
				KEY_P,
				// Token: 0x04000195 RID: 405
				KEY_Q = 16,
				// Token: 0x04000196 RID: 406
				KEY_R = 19,
				// Token: 0x04000197 RID: 407
				KEY_S = 31,
				// Token: 0x04000198 RID: 408
				KEY_T = 20,
				// Token: 0x04000199 RID: 409
				KEY_U = 22,
				// Token: 0x0400019A RID: 410
				KEY_V = 47,
				// Token: 0x0400019B RID: 411
				KEY_W = 17,
				// Token: 0x0400019C RID: 412
				KEY_X = 45,
				// Token: 0x0400019D RID: 413
				KEY_Y = 21,
				// Token: 0x0400019E RID: 414
				KEY_Z = 44,
				// Token: 0x0400019F RID: 415
				LWIN = 91,
				// Token: 0x040001A0 RID: 416
				RWIN,
				// Token: 0x040001A1 RID: 417
				APPS,
				// Token: 0x040001A2 RID: 418
				SLEEP = 95,
				// Token: 0x040001A3 RID: 419
				NUMPAD0 = 82,
				// Token: 0x040001A4 RID: 420
				NUMPAD1 = 79,
				// Token: 0x040001A5 RID: 421
				NUMPAD2,
				// Token: 0x040001A6 RID: 422
				NUMPAD3,
				// Token: 0x040001A7 RID: 423
				NUMPAD4 = 75,
				// Token: 0x040001A8 RID: 424
				NUMPAD5,
				// Token: 0x040001A9 RID: 425
				NUMPAD6,
				// Token: 0x040001AA RID: 426
				NUMPAD7 = 71,
				// Token: 0x040001AB RID: 427
				NUMPAD8,
				// Token: 0x040001AC RID: 428
				NUMPAD9,
				// Token: 0x040001AD RID: 429
				MULTIPLY = 55,
				// Token: 0x040001AE RID: 430
				ADD = 78,
				// Token: 0x040001AF RID: 431
				SEPARATOR = 0,
				// Token: 0x040001B0 RID: 432
				SUBTRACT = 74,
				// Token: 0x040001B1 RID: 433
				DECIMAL = 83,
				// Token: 0x040001B2 RID: 434
				DIVIDE = 53,
				// Token: 0x040001B3 RID: 435
				F1 = 59,
				// Token: 0x040001B4 RID: 436
				F2,
				// Token: 0x040001B5 RID: 437
				F3,
				// Token: 0x040001B6 RID: 438
				F4,
				// Token: 0x040001B7 RID: 439
				F5,
				// Token: 0x040001B8 RID: 440
				F6,
				// Token: 0x040001B9 RID: 441
				F7,
				// Token: 0x040001BA RID: 442
				F8,
				// Token: 0x040001BB RID: 443
				F9,
				// Token: 0x040001BC RID: 444
				F10,
				// Token: 0x040001BD RID: 445
				F11 = 87,
				// Token: 0x040001BE RID: 446
				F12,
				// Token: 0x040001BF RID: 447
				F13 = 100,
				// Token: 0x040001C0 RID: 448
				F14,
				// Token: 0x040001C1 RID: 449
				F15,
				// Token: 0x040001C2 RID: 450
				F16,
				// Token: 0x040001C3 RID: 451
				F17,
				// Token: 0x040001C4 RID: 452
				F18,
				// Token: 0x040001C5 RID: 453
				F19,
				// Token: 0x040001C6 RID: 454
				F20,
				// Token: 0x040001C7 RID: 455
				F21,
				// Token: 0x040001C8 RID: 456
				F22,
				// Token: 0x040001C9 RID: 457
				F23,
				// Token: 0x040001CA RID: 458
				F24 = 118,
				// Token: 0x040001CB RID: 459
				NUMLOCK = 69,
				// Token: 0x040001CC RID: 460
				SCROLL,
				// Token: 0x040001CD RID: 461
				LSHIFT = 42,
				// Token: 0x040001CE RID: 462
				RSHIFT = 54,
				// Token: 0x040001CF RID: 463
				LCONTROL = 29,
				// Token: 0x040001D0 RID: 464
				RCONTROL = 29,
				// Token: 0x040001D1 RID: 465
				LMENU = 56,
				// Token: 0x040001D2 RID: 466
				RMENU = 56,
				// Token: 0x040001D3 RID: 467
				BROWSER_BACK = 106,
				// Token: 0x040001D4 RID: 468
				BROWSER_FORWARD = 105,
				// Token: 0x040001D5 RID: 469
				BROWSER_REFRESH = 103,
				// Token: 0x040001D6 RID: 470
				BROWSER_STOP,
				// Token: 0x040001D7 RID: 471
				BROWSER_SEARCH = 101,
				// Token: 0x040001D8 RID: 472
				BROWSER_FAVORITES,
				// Token: 0x040001D9 RID: 473
				BROWSER_HOME = 50,
				// Token: 0x040001DA RID: 474
				VOLUME_MUTE = 32,
				// Token: 0x040001DB RID: 475
				VOLUME_DOWN = 46,
				// Token: 0x040001DC RID: 476
				VOLUME_UP = 48,
				// Token: 0x040001DD RID: 477
				MEDIA_NEXT_TRACK = 25,
				// Token: 0x040001DE RID: 478
				MEDIA_PREV_TRACK = 16,
				// Token: 0x040001DF RID: 479
				MEDIA_STOP = 36,
				// Token: 0x040001E0 RID: 480
				MEDIA_PLAY_PAUSE = 34,
				// Token: 0x040001E1 RID: 481
				LAUNCH_MAIL = 108,
				// Token: 0x040001E2 RID: 482
				LAUNCH_MEDIA_SELECT,
				// Token: 0x040001E3 RID: 483
				LAUNCH_APP1 = 107,
				// Token: 0x040001E4 RID: 484
				LAUNCH_APP2 = 33,
				// Token: 0x040001E5 RID: 485
				OEM_1 = 39,
				// Token: 0x040001E6 RID: 486
				OEM_PLUS = 13,
				// Token: 0x040001E7 RID: 487
				OEM_COMMA = 51,
				// Token: 0x040001E8 RID: 488
				OEM_MINUS = 12,
				// Token: 0x040001E9 RID: 489
				OEM_PERIOD = 52,
				// Token: 0x040001EA RID: 490
				OEM_2,
				// Token: 0x040001EB RID: 491
				OEM_3 = 41,
				// Token: 0x040001EC RID: 492
				OEM_4 = 26,
				// Token: 0x040001ED RID: 493
				OEM_5 = 43,
				// Token: 0x040001EE RID: 494
				OEM_6 = 27,
				// Token: 0x040001EF RID: 495
				OEM_7 = 40,
				// Token: 0x040001F0 RID: 496
				OEM_8 = 0,
				// Token: 0x040001F1 RID: 497
				OEM_102 = 86,
				// Token: 0x040001F2 RID: 498
				PROCESSKEY = 0,
				// Token: 0x040001F3 RID: 499
				PACKET = 0,
				// Token: 0x040001F4 RID: 500
				ATTN = 0,
				// Token: 0x040001F5 RID: 501
				CRSEL = 0,
				// Token: 0x040001F6 RID: 502
				EXSEL = 0,
				// Token: 0x040001F7 RID: 503
				EREOF = 93,
				// Token: 0x040001F8 RID: 504
				PLAY = 0,
				// Token: 0x040001F9 RID: 505
				ZOOM = 98,
				// Token: 0x040001FA RID: 506
				NONAME = 0,
				// Token: 0x040001FB RID: 507
				PA1 = 0,
				// Token: 0x040001FC RID: 508
				OEM_CLEAR = 0
			}

			// Token: 0x0200002B RID: 43
			public struct HARDWAREINPUT
			{
				// Token: 0x040001FD RID: 509
				internal int uMsg;

				// Token: 0x040001FE RID: 510
				internal short wParamL;

				// Token: 0x040001FF RID: 511
				internal short wParamH;
			}
		}
	}
}
