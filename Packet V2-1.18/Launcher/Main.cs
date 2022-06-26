using System;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Reflection;
using System.Windows.Forms;
using PacketLauncher.Handlers;

namespace PacketLauncher
{
    public partial class Main : Form
    {
        public static Version GetVersion() => Assembly.GetExecutingAssembly().GetName().Version;
        public static WebClient webClient = new WebClient();
        public Main()
        {
            var version = webClient.DownloadString("https://raw.githubusercontent.com/PacketDeveloper/Website/main/download/version.txt"); // located at the bottom of AssemblyInfo.cs
            if (Version.Parse(version) > GetVersion()) if (MessageBox.Show("New update available! Do you want to update now?", null, MessageBoxButtons.YesNo) == DialogResult.Yes)
                UpdateLauncher();
            RPCHandler.Initialize();
            InitializeComponent();
            //Process.Start("https://discord.gg/aNVstg7j3j"); // will add back later but better
        }

        private void Home_Click(object sender, EventArgs e)
        {
            ControlDockPanel.Controls.Clear();
            ControlDockPanel.Controls.Add(new UserControls.Home());
        }

        private void Development_Click(object sender, EventArgs e)
        {
            ControlDockPanel.Controls.Clear();
            ControlDockPanel.Controls.Add(new UserControls.Development());
        }

        private void Settings_Click(object sender, EventArgs e)
        {
            ControlDockPanel.Controls.Clear();
            ControlDockPanel.Controls.Add(new UserControls.Settings());
        }

        public static void UpdateLauncher() // Credits: Horion
        {
            var path = Assembly.GetExecutingAssembly().Location;
            try {Directory.GetAccessControl(Path.GetDirectoryName(path));}
            catch {MessageBox.Show("Cannot access the launchers directory!"); return;}

            File.Move(path, Path.ChangeExtension(path, "old"));
            new WebClient().DownloadFile("https://github.com/PacketDeveloper/Website/raw/main/download/PacketClient.exe", path);
            MessageBox.Show("Update is finished!");
            Process.Start(path);

            Process.GetCurrentProcess().Kill();
        }

        private void Main_Load(object sender, EventArgs e)
        {
            ControlDockPanel.Controls.Clear();
            ControlDockPanel.Controls.Add(new UserControls.Home());
        }
    }
}
