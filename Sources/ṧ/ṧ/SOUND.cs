using System;
using System.IO;
using System.Media;
using System.Text;

namespace ṧ
{
	// Token: 0x02000012 RID: 18
	internal class SOUND
	{
		// Token: 0x06000092 RID: 146 RVA: 0x00003744 File Offset: 0x00001944
		private static byte[] getBytes(string text)
		{
			return Encoding.ASCII.GetBytes(text);
		}

		// Token: 0x06000093 RID: 147 RVA: 0x00003763 File Offset: 0x00001963
		public void beat()
		{
		}

		// Token: 0x06000094 RID: 148 RVA: 0x00003768 File Offset: 0x00001968
		internal static void bn()
		{
			Random random = new Random();
			int num = 16;
			short value = 1;
			short num2 = 16;
			short num3 = 2;
			int num4 = 24000;
			int num5 = num4 * SOUND.speed;
			int value2 = num4 * (int)num3 * (int)(num2 / 8);
			short value3 = num3 * (num2 / 8);
			int num6 = num5 * (int)num3 * (int)(num2 / 8);
			int value4 = 4 + (8 + num) + (8 + num6);
			string text = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "beat.wav");
			bool flag = File.Exists(text);
			if (flag)
			{
				File.Delete(text);
			}
			FileStream output = new FileStream(text, FileMode.Create);
			using (BinaryWriter binaryWriter = new BinaryWriter(output))
			{
				binaryWriter.Write(SOUND.getBytes("RIFF"));
				binaryWriter.Write(value4);
				binaryWriter.Write(SOUND.getBytes("WAVE"));
				binaryWriter.Write(SOUND.getBytes("fmt"));
				binaryWriter.Write(32);
				binaryWriter.Write(num);
				binaryWriter.Write(value);
				binaryWriter.Write(num3);
				binaryWriter.Write(num4);
				binaryWriter.Write(value2);
				binaryWriter.Write(value3);
				binaryWriter.Write(num2);
				binaryWriter.Write(SOUND.getBytes("data"));
				binaryWriter.Write(num6);
				byte[] buffer = new byte[4];
				binaryWriter.Write(buffer);
				for (int i = 0; i < 300; i++)
				{
					bool flag2 = SOUND.style == 0;
					float num7;
					if (flag2)
					{
						num7 = (float)random.Next(20, 220);
					}
					else
					{
						bool flag3 = SOUND.style == 1;
						if (flag3)
						{
							num7 = (float)random.Next(40, 400);
						}
						else
						{
							num7 = (float)random.Next(10, 200);
						}
					}
					for (int j = 0; j < num5 / 300; j++)
					{
						binaryWriter.Write(Convert.ToInt16(32767 * Math.Sign(Math.Sin(25.132741228718345 * (double)num7 / (double)num4 * (double)j))));
						binaryWriter.Write(Convert.ToInt16(32767 * Math.Sign(Math.Sin(31.41592653589793 * (double)num7 / (double)num4 * (double)j))));
					}
				}
			}
			using (SoundPlayer soundPlayer = new SoundPlayer(text))
			{
				soundPlayer.PlayLooping();
			}
		}

		// Token: 0x04000039 RID: 57
		public static int style = 0;

		// Token: 0x0400003A RID: 58
		public static int speed = 60;
	}
}
