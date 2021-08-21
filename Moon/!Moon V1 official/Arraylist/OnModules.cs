
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace onmodulesclass
{
    class OnModules
    {
        //Combo
        bool Reach = false;
        bool Hitbox = false;
        bool Instantbreak = false;
        bool Noknockback = false;
        bool Infinityblockreach = false;

        //Visuals
        bool Zoom = true;
        bool Rainbowsky = false;
        bool Fulllight = false;
        bool Stopvisualtime = false;

        //Mov
        bool Speed = false;
        bool Airjump = false;
        bool Highjump = false;
        bool Pglide = false;
        bool Glide = false;
        bool PositionFreeze = false;
        bool Infinityjump = false;
        bool Airwalk = false;
        bool Phase = false;
        bool Speedsneak = false;

        //Exploits
        bool Nofall = false;
        bool Flydamagebypass = false;
        bool Antivoid = false;
        bool Norender = false;
        bool Scaffold = false;
        bool Fakegamemode = false;

        //Settings
        bool Keystrokes = false;
        bool TabGui = false;

        public void togglemodule(string modul)
        {
            if(modul == "Reach")
            {
                Reach = !Reach;
            }
            else if(modul == "Hitbox")
            {
                Hitbox = !Hitbox;
            }
            else if (modul == "Instantbreak")
            {
                Instantbreak = !Instantbreak;
            }
            else if (modul == "Noknockback")
            {
                Noknockback = !Noknockback;
            }
            else if (modul == "Infinityblockreach")
            {
                Infinityblockreach = !Infinityblockreach;
            }
            else if (modul == "Zoom")
            {
                Zoom = !Zoom;
            }
            else if (modul == "Rainbowsky")
            {
                Rainbowsky = !Rainbowsky;
            }
            else if (modul == "Fulllight")
            {
                Fulllight = !Fulllight;
            }
            else if (modul == "Stopvisualtime")
            {
                Stopvisualtime = !Stopvisualtime;
            }
            else if (modul == "Speed")
            {
                Speed = !Speed;
            }
            else if (modul == "Airjump")
            {
                Airjump = !Airjump;
            }
            else if (modul == "Highjump")
            {
                Highjump = !Highjump;
            }
            else if (modul == "Pglide")
            {
                Pglide = !Pglide;
            }
            else if (modul == "Glide")
            {
                Glide = !Glide;
            }
            else if (modul == "Positionfreeze")
            {
                PositionFreeze = !PositionFreeze;
            }
            else if (modul == "Infinityjump")
            {
                Infinityjump = !Infinityjump;
            }
            else if (modul == "Airwalk")
            {
                Airwalk = !Airwalk;
            }
            else if (modul == "Phase")
            {
                Phase = !Phase;
            }
            else if (modul == "Speedsneak")
            {
                Speedsneak = !Speedsneak;
            }
            else if (modul == "Nofall")
            {
                Nofall = !Nofall;
            }
            else if (modul == "Flydamagebypass")
            {
                Flydamagebypass = !Flydamagebypass;
            }
            else if (modul == "Antivoid")
            {
                Antivoid = !Antivoid;
            }
            //Norender
            //scaffold 
            //etc...
        }

    }
}
