using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace ṧ
{
	// Token: 0x0200000E RID: 14
	internal class MOUSE
	{
		// Token: 0x06000087 RID: 135
		[DllImport("user32.dll", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Auto)]
		public static extern void mouse_event(uint dwFlags, uint dx, uint dy, uint cButtons, uint dwExtraInfo);

		// Token: 0x06000088 RID: 136 RVA: 0x00003388 File Offset: 0x00001588
		public static void DoMouseClick()
		{
			uint x = (uint)Cursor.Position.X;
			uint y = (uint)Cursor.Position.Y;
			MOUSE.mouse_event(6U, x, y, 0U, 0U);
		}

		// Token: 0x0400002C RID: 44
		private const int MOUSEEVENTF_LEFTDOWN = 2;

		// Token: 0x0400002D RID: 45
		private const int MOUSEEVENTF_LEFTUP = 4;

		// Token: 0x0400002E RID: 46
		private const int MOUSEEVENTF_RIGHTDOWN = 8;

		// Token: 0x0400002F RID: 47
		private const int MOUSEEVENTF_RIGHTUP = 16;
	}
}
