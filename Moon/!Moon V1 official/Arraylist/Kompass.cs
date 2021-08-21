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
    public partial class Kompass : Form
    {
        ez ez = new ez();
        public Kompass()
        {
            InitializeComponent();
        }

        private void Kompass_Load(object sender, EventArgs e)
        {
            ez.SetInvi(this);
            ez.StartLoop(200, "Minecraft", this);
        }
    }
}
