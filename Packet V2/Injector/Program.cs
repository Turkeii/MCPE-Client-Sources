using System.Windows.Forms;
using DiscordRPC;
using System;
using PacketClient.Handlers;

namespace PacketClient
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            RPCHandler.Initialize();
            RPCHandler.Setup();

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
