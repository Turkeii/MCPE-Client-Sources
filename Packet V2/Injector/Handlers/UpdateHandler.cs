using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PacketClient.Handlers
{
    internal class UpdateHandler
    {
        public static WebClient webClient = new WebClient();
        public static Version GetVersion() => Assembly.GetExecutingAssembly().GetName().Version;

        public static void CheckForUpdate()
        {
            var latest = webClient.DownloadString("https://raw.githubusercontent.com/PacketDeveloper/Website/main/download/version.txt");
            if (Version.Parse(latest) > GetVersion())
            {
                if (MessageBox.Show("New update available! Do you want to update now?", null, MessageBoxButtons.YesNo) == DialogResult.Yes)
                    Update();
            }
        }

        public static void Update()
        {
            var path = Assembly.GetExecutingAssembly().Location;

            try
            {
                Directory.GetAccessControl(Path.GetDirectoryName(path));
            }
            catch
            {
                MessageBox.Show("The updater has no permission to access the injectors directory!");
                return;
            }

            File.Move(path, Path.ChangeExtension(path, "old"));
            new WebClient().DownloadFile("https://github.com/PacketDeveloper/Website/raw/main/download/PacketClient.exe", path);

            MessageBox.Show("Update is finished!");
            Process.Start(path);

            Process.GetCurrentProcess().Kill();
        }
    }
}
