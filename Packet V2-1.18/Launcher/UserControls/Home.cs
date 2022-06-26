using PacketLauncher.Handlers;
using System;
using System.Threading;
using System.Windows.Forms;

namespace PacketLauncher.UserControls
{
    public partial class Home : UserControl
    {
        public Home()
        {
            InitializeComponent();
        }

        private void SetStatus(string status, int progress)
        {
            Status.Text = status;
            Progress.Value = progress;
        }

        private async void Inject_Click(object sender, EventArgs e)
        {
            SetStatus("Checking for Directory", 1);
            UpdateHandler.CheckForDirectory();
            SetStatus("Installing Pack", 2);
            InstallHandler.InstallPack();
            SetStatus("Installing Client", 3);
            await UpdateHandler.InstallClient();
            SetStatus("Injecting...", 4);
            InjectionHandler.InjectClient();
            SetStatus("Injected!", 5); 
        }
    }
}
