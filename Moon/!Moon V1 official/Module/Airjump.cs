using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Memory;

namespace AirjumpCheat
{
    class Airjump
    {
        Mem m = new Mem();

        public void AirJumpon()
        {
            m.OpenProcess("Minecraft.Windows");

            //0F B6 80 E0 01 00 00
            m.WriteMemory("Minecraft.Windows.exe+1053124", "bytes", "90 90 90 90 90 90 90");
        }
        public void AirJumpoff()
        {
            m.OpenProcess("Minecraft.Windows");
            m.WriteMemory("Minecraft.Windows.exe+1053124", "bytes", "0F B6 80 E0 01 00 00");
        }

    }
}
