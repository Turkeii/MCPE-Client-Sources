using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace _Moon_V1_official
{
    public partial class TabGui : Form
    {
        public TabGui()
        {
            InitializeComponent();
        }

        public ClickGui Clickgui = new ClickGui();

        private void TabGui_Load(object sender, EventArgs e)
        {
            iscgopen.RunWorkerAsync();
        }

        private void iscgopen_DoWork(object sender, DoWorkEventArgs e)
        {
            
            while (true)
            {
                if (Clickgui.Visible == true)
                {
                    try
                    {
                        this.Hide();
                    }
                    catch { }
                }
                else
                {
                    try
                    {
                        this.Show();
                        /*if (true) //  <--- kommt später rein ob Tabgui = open!
                        {
                            this.Show();
                        }*/
                    }
                    catch { };
                }
                Thread.Sleep(10);
            }
        }
    }
}
