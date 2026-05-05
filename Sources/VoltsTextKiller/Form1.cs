using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace VoltsTextKiller
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            string t = richTextBox1.Text;
            byte[] b = Encoding.UTF8.GetBytes(t);
            int w = 32, h = 32;
            byte[] pixelArray = new byte[w * h * 3];
            for (int i = 0; i < b.Length && i < pixelArray.Length; i++)
            {
                pixelArray[i] = b[i];
            }
            Bitmap bmp = new Bitmap(w, h, PixelFormat.Format24bppRgb);

            BitmapData bmpData = bmp.LockBits(
                                new Rectangle(0, 0, bmp.Width, bmp.Height),
                                ImageLockMode.WriteOnly, bmp.PixelFormat);
            Marshal.Copy(pixelArray, 0, bmpData.Scan0, pixelArray.Length);

            bmp.UnlockBits(bmpData);
            pictureBox1.Image = bmp;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            SaveFileDialog a = new SaveFileDialog();
            a.ShowDialog();
            pictureBox1.Image.Save(a.FileName);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            OpenFileDialog v = new OpenFileDialog();
            v.ShowDialog();
            Image img = Image.FromFile(v.FileName);
            Bitmap bmp = (Bitmap)img;
            int w = bmp.Width;
            int h = bmp.Height;
            byte[] pixelz = new byte[w * h * 3];
            BitmapData bmpd = bmp.LockBits(new Rectangle(0, 0, w, h), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            Marshal.Copy(bmpd.Scan0, pixelz, 0, pixelz.Length);
            bmp.UnlockBits(bmpd);
            int fn = Array.IndexOf(pixelz, (byte)0);
            string str;

            if (fn >= 0)
            {
                str = Encoding.UTF8.GetString(pixelz, 0, fn);
            }
            else
            {
                str = Encoding.UTF8.GetString(pixelz);
            }
            richTextBox1.Text = str;
        }
    }
}
