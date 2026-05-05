using System;
using System.Windows.Forms;

namespace ṧ
{
	// Token: 0x02000005 RID: 5
	internal class CORE
	{
		// Token: 0x06000044 RID: 68 RVA: 0x00002340 File Offset: 0x00000540
		internal static void boss()
		{
			Version version = Environment.OSVersion.Version;
			bool flag = (version.Major == 5 && version.Minor == 2) || version.Major == 10;
			bool flag2 = !flag;
			if (flag2)
			{
				MessageBox.Show("Error: This PC spots a Wrong windows. this pc doesnt work in any windows so im sparing you! Correct windows can let you run it. so cannot execute this program.\n\nIt only works on:\nWindows 10\nWindows 11\nWindows XP 64x", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
				Environment.Exit(0);
			}
		}
	}
}
