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
//Module
using AimbotCheat;
using HitboxCheat;

namespace _Moon_V1_official.Arraylist
{
    public partial class Arraylist : Form
    {

        ez ez = new ez();
        

        //Module
        Aimbot aimbot = new Aimbot();
        Hitbox hitbox = new Hitbox();

        public Arraylist()
        {
            InitializeComponent();
        }

        private void Arraylist_Load(object sender, EventArgs e)
        {
            ez.SetInvi(this);
            ez.ClickThrough(this);
            ez.StartLoop(10, "Minecraft", this);

            //Start Timers
            timer_aimbot.Start();
            
        }

        private void label12_Click(object sender, EventArgs e)
        {

        }

        private void label_reach_Click(object sender, EventArgs e)
        {

        }
        //Aimbot
        private void timer_aimbot_Tick(object sender, EventArgs e)
        {
            if(label_aimbot.Visible == true)
            {
                aimbot.RunAimbot();
                
            }
        }
        //Hitbox
        private void timer_hitbox_Tick(object sender, EventArgs e)
        {
            ClickGui cg = new ClickGui();
            if(label_Hitbox.Visible == true)
            {
                hitbox.set(cg.trackBar_hitbox_withe.Value, cg.trackBar_hitbox_high.Value);
            }
            else
            {
                hitbox.unset();
            }
        }
    }
}
