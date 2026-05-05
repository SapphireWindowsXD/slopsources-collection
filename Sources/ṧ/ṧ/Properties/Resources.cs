using System;
using System.CodeDom.Compiler;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Globalization;
using System.IO;
using System.Resources;
using System.Runtime.CompilerServices;

namespace ṧ.Properties
{
	// Token: 0x02000014 RID: 20
	[GeneratedCode("System.Resources.Tools.StronglyTypedResourceBuilder", "17.0.0.0")]
	[DebuggerNonUserCode]
	[CompilerGenerated]
	internal class Resources
	{
		// Token: 0x0600009A RID: 154 RVA: 0x00003A7B File Offset: 0x00001C7B
		internal Resources()
		{
		}

		// Token: 0x17000001 RID: 1
		// (get) Token: 0x0600009B RID: 155 RVA: 0x00003A88 File Offset: 0x00001C88
		[EditorBrowsable(EditorBrowsableState.Advanced)]
		internal static ResourceManager ResourceManager
		{
			get
			{
				bool flag = Resources.resourceMan == null;
				if (flag)
				{
					ResourceManager resourceManager = new ResourceManager("ṧ.Properties.Resources", typeof(Resources).Assembly);
					Resources.resourceMan = resourceManager;
				}
				return Resources.resourceMan;
			}
		}

		// Token: 0x17000002 RID: 2
		// (get) Token: 0x0600009C RID: 156 RVA: 0x00003AD0 File Offset: 0x00001CD0
		// (set) Token: 0x0600009D RID: 157 RVA: 0x00003AE7 File Offset: 0x00001CE7
		[EditorBrowsable(EditorBrowsableState.Advanced)]
		internal static CultureInfo Culture
		{
			get
			{
				return Resources.resourceCulture;
			}
			set
			{
				Resources.resourceCulture = value;
			}
		}

		// Token: 0x17000003 RID: 3
		// (get) Token: 0x0600009E RID: 158 RVA: 0x00003AF0 File Offset: 0x00001CF0
		internal static Bitmap background
		{
			get
			{
				object @object = Resources.ResourceManager.GetObject("background", Resources.resourceCulture);
				return (Bitmap)@object;
			}
		}

		// Token: 0x17000004 RID: 4
		// (get) Token: 0x0600009F RID: 159 RVA: 0x00003B20 File Offset: 0x00001D20
		internal static UnmanagedMemoryStream beat
		{
			get
			{
				return Resources.ResourceManager.GetStream("beat", Resources.resourceCulture);
			}
		}

		// Token: 0x17000005 RID: 5
		// (get) Token: 0x060000A0 RID: 160 RVA: 0x00003B48 File Offset: 0x00001D48
		internal static Icon DEATH
		{
			get
			{
				object @object = Resources.ResourceManager.GetObject("DEATH", Resources.resourceCulture);
				return (Icon)@object;
			}
		}

		// Token: 0x0400003E RID: 62
		private static ResourceManager resourceMan;

		// Token: 0x0400003F RID: 63
		private static CultureInfo resourceCulture;
	}
}
