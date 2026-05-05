namespace ṧ
{
	// Token: 0x02000009 RID: 9
	public partial class Form1 : global::System.Windows.Forms.Form
	{
		// Token: 0x06000063 RID: 99 RVA: 0x000027CC File Offset: 0x000009CC
		protected override void Dispose(bool disposing)
		{
			bool flag = disposing && this.components != null;
			if (flag)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}

		// Token: 0x06000064 RID: 100 RVA: 0x00002804 File Offset: 0x00000A04
		private void InitializeComponent()
		{
			this.components = new global::System.ComponentModel.Container();
			global::System.ComponentModel.ComponentResourceManager componentResourceManager = new global::System.ComponentModel.ComponentResourceManager(typeof(global::ṧ.Form1));
			this.pictureBox1 = new global::System.Windows.Forms.PictureBox();
			this.pictureBox2 = new global::System.Windows.Forms.PictureBox();
			this.label1 = new global::System.Windows.Forms.Label();
			this.label2 = new global::System.Windows.Forms.Label();
			this.button1 = new global::System.Windows.Forms.Button();
			this.button2 = new global::System.Windows.Forms.Button();
			this.timer1 = new global::System.Windows.Forms.Timer(this.components);
			this.timer2 = new global::System.Windows.Forms.Timer(this.components);
			this.timer3 = new global::System.Windows.Forms.Timer(this.components);
			((global::System.ComponentModel.ISupportInitialize)this.pictureBox1).BeginInit();
			((global::System.ComponentModel.ISupportInitialize)this.pictureBox2).BeginInit();
			base.SuspendLayout();
			this.pictureBox1.Image = (global::System.Drawing.Image)componentResourceManager.GetObject("pictureBox1.Image");
			this.pictureBox1.Location = new global::System.Drawing.Point(12, 12);
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new global::System.Drawing.Size(107, 92);
			this.pictureBox1.SizeMode = global::System.Windows.Forms.PictureBoxSizeMode.StretchImage;
			this.pictureBox1.TabIndex = 0;
			this.pictureBox1.TabStop = false;
			this.pictureBox1.Click += new global::System.EventHandler(this.pictureBox1_Click);
			this.pictureBox2.Image = (global::System.Drawing.Image)componentResourceManager.GetObject("pictureBox2.Image");
			this.pictureBox2.Location = new global::System.Drawing.Point(861, 12);
			this.pictureBox2.Name = "pictureBox2";
			this.pictureBox2.Size = new global::System.Drawing.Size(107, 92);
			this.pictureBox2.SizeMode = global::System.Windows.Forms.PictureBoxSizeMode.StretchImage;
			this.pictureBox2.TabIndex = 1;
			this.pictureBox2.TabStop = false;
			this.label1.AutoSize = true;
			this.label1.Font = new global::System.Drawing.Font("Microsoft Sans Serif", 36f, global::System.Drawing.FontStyle.Regular, global::System.Drawing.GraphicsUnit.Point, 0);
			this.label1.Location = new global::System.Drawing.Point(298, 22);
			this.label1.Name = "label1";
			this.label1.Size = new global::System.Drawing.Size(374, 82);
			this.label1.TabIndex = 2;
			this.label1.Text = "HOLD UP!";
			this.label2.AutoSize = true;
			this.label2.Font = new global::System.Drawing.Font("Microsoft Sans Serif", 10f, global::System.Drawing.FontStyle.Regular, global::System.Drawing.GraphicsUnit.Point, 0);
			this.label2.Location = new global::System.Drawing.Point(83, 137);
			this.label2.Name = "label2";
			this.label2.Size = new global::System.Drawing.Size(837, 150);
			this.label2.TabIndex = 3;
			this.label2.Text = componentResourceManager.GetString("label2.Text");
			this.button1.Location = new global::System.Drawing.Point(12, 350);
			this.button1.Name = "button1";
			this.button1.Size = new global::System.Drawing.Size(223, 66);
			this.button1.TabIndex = 4;
			this.button1.Text = "EXECUTE";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new global::System.EventHandler(this.button1_Click);
			this.button2.Location = new global::System.Drawing.Point(748, 350);
			this.button2.Name = "button2";
			this.button2.Size = new global::System.Drawing.Size(220, 66);
			this.button2.TabIndex = 5;
			this.button2.Text = "EXIT";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new global::System.EventHandler(this.button2_Click);
			this.timer1.Tick += new global::System.EventHandler(this.timer1_Tick);
			this.timer2.Tick += new global::System.EventHandler(this.timer2_Tick);
			this.timer3.Tick += new global::System.EventHandler(this.timer3_Tick);
			base.AutoScaleDimensions = new global::System.Drawing.SizeF(9f, 20f);
			base.AutoScaleMode = global::System.Windows.Forms.AutoScaleMode.Font;
			base.ClientSize = new global::System.Drawing.Size(980, 428);
			base.Controls.Add(this.button2);
			base.Controls.Add(this.button1);
			base.Controls.Add(this.label2);
			base.Controls.Add(this.label1);
			base.Controls.Add(this.pictureBox2);
			base.Controls.Add(this.pictureBox1);
			base.MaximizeBox = false;
			base.MinimizeBox = false;
			base.Name = "Form1";
			base.ShowIcon = false;
			base.ShowInTaskbar = false;
			this.Text = "EXE.EXE.EXE.EXE.EXE.EXE.EXE";
			base.FormClosing += new global::System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
			((global::System.ComponentModel.ISupportInitialize)this.pictureBox1).EndInit();
			((global::System.ComponentModel.ISupportInitialize)this.pictureBox2).EndInit();
			base.ResumeLayout(false);
			base.PerformLayout();
		}

		// Token: 0x04000012 RID: 18
		private global::System.ComponentModel.IContainer components = null;

		// Token: 0x04000013 RID: 19
		private global::System.Windows.Forms.PictureBox pictureBox1;

		// Token: 0x04000014 RID: 20
		private global::System.Windows.Forms.PictureBox pictureBox2;

		// Token: 0x04000015 RID: 21
		private global::System.Windows.Forms.Label label1;

		// Token: 0x04000016 RID: 22
		private global::System.Windows.Forms.Label label2;

		// Token: 0x04000017 RID: 23
		private global::System.Windows.Forms.Button button1;

		// Token: 0x04000018 RID: 24
		private global::System.Windows.Forms.Button button2;

		// Token: 0x04000019 RID: 25
		private global::System.Windows.Forms.Timer timer1;

		// Token: 0x0400001A RID: 26
		private global::System.Windows.Forms.Timer timer2;

		// Token: 0x0400001B RID: 27
		private global::System.Windows.Forms.Timer timer3;
	}
}
