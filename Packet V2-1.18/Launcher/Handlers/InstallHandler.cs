using System;
using System.ComponentModel;
using System.IO;
using System.Net;
using System.Threading;
using System.Windows.Forms;

namespace PacketLauncher.Handlers
{
    internal class InstallHandler
    {
        public static string ResourcePackDir = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData) + @"\Packages\Microsoft.MinecraftUWP_8wekyb3d8bbwe\LocalState\games\com.mojang\resource_packs\";

        public static bool CheckValidDirectory()
        {
            if (!Directory.Exists(ResourcePackDir))
            {
                MessageBox.Show("Resource Pack folder not found, installing pack to current folder", "Directory Error");
                return false;
            }
            return true;
        }

        public static void DownloadFileThreaded(string url, string path)
        {
            new Thread(() =>
            {
                WebClient webClient = new WebClient();
                webClient.DownloadFileAsync(new Uri(path), url);
            }).Start();
        }


        private static void PackComplete(object sender, AsyncCompletedEventArgs e)
        {
            try
            {
                System.IO.Compression.ZipFile.ExtractToDirectory(ResourcePackDir + "PacketRP.zip", ResourcePackDir + "PacketRP");
                Thread.Sleep(5);
                File.Delete(ResourcePackDir + "PacketRP.zip");
            } catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Pack Error [2]");
            }
        }
        public static void InstallPack()
        {
            try
            {
                if (!Directory.Exists(ResourcePackDir + "PacketRP"))
                {
                    new Thread(() =>
                {
                    WebClient webClient = new WebClient();
                    webClient.DownloadFileCompleted += new AsyncCompletedEventHandler(PackComplete);
                    webClient.DownloadFileAsync(new Uri("https://github.com/FadedKow/Assets/raw/main/Other/PacketRP.zip"), ResourcePackDir + "PacketRP.zip");
                }).Start();
                }
            } catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Pack Error [1]");
            }
        }

    }
}
