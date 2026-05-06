using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Media;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace xdde
{
    public partial class fullscreen : Form
    {
        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool SetForegroundWindow(IntPtr hWnd);

        [DllImport("user32.dll", SetLastError = true)]
        static extern int GetWindowLong(IntPtr hWnd, int nIndex);

        [DllImport("user32.dll", SetLastError = true)]
        static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);

        public fullscreen()
        {
            InitializeComponent();
            pictureBox1.Image = Properties.Resources.dumptruck;
            pictureBox1.SizeMode = PictureBoxSizeMode.Zoom;
            FormBorderStyle = FormBorderStyle.None;
            WindowState = FormWindowState.Maximized;
            SetStyle(ControlStyles.SupportsTransparentBackColor, value: true);
            TransparencyKey = BackColor;
            Opacity = 1;
            SetForegroundWindow(Handle);
            TopMost = true;
        }

        private void fullscreen_Load(object sender, EventArgs e)
        {
            SoundPlayer soundPlayer = new SoundPlayer(Properties.Resources.dumptruck_music);
            soundPlayer.PlayLooping();
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            int windowLong = GetWindowLong(Handle, -20);
            SetWindowLong(Handle, -20, windowLong | 0x80000 | 0x20);
        }

        private void fullscreen_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = true;
        }
    }
}