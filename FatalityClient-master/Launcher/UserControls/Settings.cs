using System;
using PacketLauncher.Handlers;
using System.Windows.Forms;

namespace PacketLauncher.UserControls
{
    public partial class Settings : UserControl
    {
        public Settings()
        {
            InitializeComponent();
        }

        private void Rpc_CheckedChanged(object sender, EventArgs e)
        {
            if (Rpc.Checked) RPCHandler.Setup();
            else RPCHandler.WipePresence();
        }

        private void RoundedCorners_CheckedChanged(object sender, EventArgs e)
        {
            Main mf = (Main)Application.OpenForms["Main"];
            if (RoundedCorners.Checked)
            {
                RoundnessSlider.Visible = true;
                mf.Elipse.BorderRadius = RoundnessSlider.Value;
            } else
            {
                mf.Elipse.BorderRadius = 0;
                RoundnessSlider.Visible = false;
            }
        }

        private void RoundnessSlider_Scroll(object sender, ScrollEventArgs e)
        {
            Main mf = (Main)Application.OpenForms["Main"];
            RoundnessLabel.Text = $"Value: <b>{RoundnessSlider.Value}</b>";
            mf.Elipse.BorderRadius = RoundnessSlider.Value;
        }
    }
}
