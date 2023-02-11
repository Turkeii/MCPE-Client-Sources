using System;
using System.ComponentModel;
using System.IO;
using System.Net;
using System.Threading;
using System.Threading.Tasks;

namespace PacketLauncher.Handlers
{
    public class UpdateHandler
    {
        //public static readonly string AssetDirectory = $@"{Directory.GetCurrentDirectory()}\PacketAssets\";
        public static readonly string AssetDirectory = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData) + @"\PacketClient\";

        public static void CheckForDirectory()
        {
            if (!Directory.Exists(AssetDirectory))
            {
                Directory.CreateDirectory(AssetDirectory);
                Thread.Sleep(50);
            }
        }

        private static void FileCompleted(object sender, AsyncCompletedEventArgs e)
        {

        }

        public static void DownloadFile(string file, string location)
        {
            new Thread(() =>
            {
                WebClient webClient = new WebClient();
                webClient.DownloadFileAsync(new Uri(file), location);
            }).Start();
        }

        public static async Task InstallClient()
        {
            if (File.Exists(AssetDirectory + "PacketClient.dll"))
            {
                File.Delete(AssetDirectory + "PacketClient.dll");
                Thread.Sleep(150);
            }
            WebClient webClient = new WebClient();
            await webClient.DownloadFileTaskAsync(new Uri("https://github.com/PacketDeveloper/PacketClientDLLS/raw/main/PacketClient.dll"), AssetDirectory + "PacketClient.dll").ConfigureAwait(false);
        }
    }
}