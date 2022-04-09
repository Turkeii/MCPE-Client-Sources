using PacketClient.Handlers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PacketClient
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            UpdateHandler.CheckForUpdate();

            InjectionHandler.injectionStagedEvent += stagedChange;

            InjectionHandler.injectionStagedEvent.Invoke(null, new InjectEventArgs(""));

            HomePage.BringToFront();

            PacketTrayIcon.InitializeLifetimeService();
        }

        private void stagedChange(object sender, InjectEventArgs e) => label1.Text = e.injectionStage; // Allow updating injector state via injection event handler

        private void OutlineFocused_Tick(object sender, EventArgs e)
        {
            if (ActiveForm == this)
            {
                var focusedColor = Color.FromArgb(255, 255, 255);
                panel2.BackColor = focusedColor;
                panel3.BackColor = focusedColor;
                panel4.BackColor = focusedColor;
                panel5.BackColor = focusedColor;
            }

            if (ActiveForm != this)
            {
                var unfocusedColor = Color.FromArgb(64, 64, 64);
                panel2.BackColor = unfocusedColor;
                panel3.BackColor = unfocusedColor;
                panel4.BackColor = unfocusedColor;
                panel5.BackColor = unfocusedColor;
            }

            subStageText.Text = label1.Text;
        }

        Color originalFade = Color.FromArgb(152, 158, 161); // Color.FromArgb(152, 158, 161);
        private Point _mouseDownLocation;

        private void HoverEvent(object sender, EventArgs e)
        {
            var label = sender as Control;
            label.ForeColor = originalFade;
        }

        private void BlinkEvent(object sender, EventArgs e)
        {
            var label = sender as Control;
            label.ForeColor = Color.White;
        }

        private void panel7_MouseDown(object sender, MouseEventArgs e)
        {
            _mouseDownLocation = e.Location;
        }

        private void panel7_MouseMove(object sender, MouseEventArgs e)
        {
            switch (e.Button)
            {
                case MouseButtons.Left:
                    Left = e.X + Left - _mouseDownLocation.X;
                    Top = e.Y + Top - _mouseDownLocation.Y;
                    break;
            }
        }

        private void label5_Click(object sender, EventArgs e) => Application.Exit();
        private void label6_Click(object sender, EventArgs e) => Hide(); //WindowState = FormWindowState.Minimized;

        private void button1_Click(object sender, EventArgs e)
        {
            InjectionHandler.injectionStagedEvent.Invoke(null, new InjectEventArgs("no fuck u"));
        }

        private void label3_Click(object sender, EventArgs e) => HomePage.BringToFront();
        private void label2_Click(object sender, EventArgs e) => DevelopmentPage.BringToFront();
        private void label4_Click(object sender, EventArgs e) => SettingsPage.BringToFront();

        string path;
        private void button4_Click(object sender, EventArgs e)
        {
            OpenFileDialog FileIn = new OpenFileDialog();
            if (FileIn.ShowDialog() == DialogResult.OK)
            {
                if (FileIn.SafeFileName.ToLower().EndsWith(".dll"))
                {
                    path = FileIn.FileName;
                }
                else
                {
                    InjectionHandler.injectionStagedEvent.Invoke(null, new InjectEventArgs("You did not select a DLL!"));
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (path == null)
            {
                InjectionHandler.injectionStagedEvent.Invoke(null, new InjectEventArgs("You did not specify a DLL!"));
            }
            else
            {
                InjectionHandler.InjectDLL(path, "Minecraft.Windows");
            }
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e) => Process.GetCurrentProcess().Kill();
        private void toolStripMenuItem2_Click(object sender, EventArgs e) => Show();

        private void locateDLLToolStripMenuItem_Click(object sender, EventArgs e) => button4_Click(sender, e);

        private void injectDLLToolStripMenuItem_Click(object sender, EventArgs e) => button2_Click(sender, e);

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            var checkbox = sender as CheckBox;
            if (!checkbox.Checked)
                RPCHandler.WipePresence();
            else RPCHandler.Setup();
        }
    }
}
