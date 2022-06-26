using PacketLauncher.Handlers;
using System;
using System.Windows.Forms;

namespace PacketLauncher.UserControls
{
    public partial class Development : UserControl
    {
        public string FileToInjectDir;

        public Development()
        {
            InitializeComponent();
        }

        private void Locate_Click(object sender, EventArgs e)
        {
            UpdateHandler.CheckForDirectory();
            OpenFileDialog FileIn = new OpenFileDialog
            {
                Filter = "dll |*.dll"
            };
            if (FileIn.ShowDialog() == DialogResult.OK)
            {
                if (FileIn.SafeFileName.ToLower().EndsWith(".dll"))
                {
                    FileToInjectDir = FileIn.FileName;
                }
                else
                {
                    MessageBox.Show("You did not specify a DLL!", "Locating Error");
                }
            }
        }

        private void Inject_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(FileToInjectDir))
                InjectionHandler.InjectDLL(FileToInjectDir);
            else
                MessageBox.Show("File not selected/specified", "Injection Error");
        }
    }
}
