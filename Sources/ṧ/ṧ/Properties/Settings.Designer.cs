using System;
using System.CodeDom.Compiler;
using System.Configuration;
using System.Runtime.CompilerServices;

namespace ṧ.Properties
{
	// Token: 0x02000015 RID: 21
	[CompilerGenerated]
	[GeneratedCode("Microsoft.VisualStudio.Editors.SettingsDesigner.SettingsSingleFileGenerator", "11.0.0.0")]
	internal sealed partial class Settings : ApplicationSettingsBase
	{
		// Token: 0x17000006 RID: 6
		// (get) Token: 0x060000A1 RID: 161 RVA: 0x00003B78 File Offset: 0x00001D78
		public static Settings Default
		{
			get
			{
				return Settings.defaultInstance;
			}
		}

		// Token: 0x04000040 RID: 64
		private static Settings defaultInstance = (Settings)SettingsBase.Synchronized(new Settings());
	}
}
