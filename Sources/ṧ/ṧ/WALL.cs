using System;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.InteropServices;
using ṧ.Properties;

namespace ṧ
{
	// Token: 0x02000013 RID: 19
	internal class WALL
	{
		// Token: 0x06000097 RID: 151 RVA: 0x00003A38 File Offset: 0x00001C38
		internal static void cha()
		{
			string text = Path.Combine(Path.GetTempPath(), "wallpaper.bmp");
			Resources.background.Save(text, ImageFormat.Bmp);
			WALL.SystemParametersInfo(20, 0, text, 3);
		}

		// Token: 0x06000098 RID: 152
		[DllImport("user32.dll", SetLastError = true)]
		private static extern bool SystemParametersInfo(int uAction, int uParam, string lpvParam, int fuWinIni);

		// Token: 0x0400003B RID: 59
		private const int SPI_SETDESKWALLPAPER = 20;

		// Token: 0x0400003C RID: 60
		private const int SPIF_UPDATEINIFILE = 1;

		// Token: 0x0400003D RID: 61
		private const int SPIF_SENDCHANGE = 2;
	}
}
