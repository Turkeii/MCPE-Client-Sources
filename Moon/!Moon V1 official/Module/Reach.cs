using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Memory;

namespace ReachCheat
{
    class Reach
    {
        Mem m = new Mem();

        public void set(float withe)
        {
            m.OpenProcess("Minecraft.Windows");
            m.WriteMemory("Minecraft.Windows.exe+3500ED0", "float", withe.ToString());
        }
    }
}
