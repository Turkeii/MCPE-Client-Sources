using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ezOverLay;

namespace _Moon_V1_official.Arraylist
{
    public partial class MainOverlay : Form
    {

        //Definigingedhajsebd ez xD!
        ez ez = new ez();
        public MainOverlay()
        {
            InitializeComponent();
        }

        private void MainOverlay_Load(object sender, EventArgs e)
        {
            ez.SetInvi(this);
            ez.ClickThrough(this);
            ez.StartLoop(10, "Minecraft", this);
        }
    }
}
