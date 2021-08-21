using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Memory;
using sdkcheat;

namespace HitboxCheat
{
    class Hitbox
    {
        Mem m = new Mem();
        SDK sdk = new SDK();

        public void set(float withe, float high)
        {
            m.OpenProcess("Minecraft.Windows");
            List<string> entitysw = sdk.getentitylist("4EC");
            List<string> entitysh = sdk.getentitylist("4F0");

            for (int i = 0; i < 100; i++)
            {
                if (i == 0 ) { goto end; }
                //m.WriteMemory(entitysh[i], "float", high.ToString());
                //m.WriteMemory(entitysw[i], "float", withe.ToString());
                m.FreezeValue(entitysh[i], "float", high.ToString());
                m.FreezeValue(entitysw[i], "float", withe.ToString());

            end:;
            }

        }
        public void unset()
        {
            m.OpenProcess("Minecraft.Windows");
            List<string> entitysw = sdk.getentitylist("4EC");
            List<string> entitysh = sdk.getentitylist("4F0");

            for (int i = 0; i < 100; i++)
            {
                if (i == 0) { goto end; }
                //m.WriteMemory(entitysh[i], "float", high.ToString());
                //m.WriteMemory(entitysw[i], "float", withe.ToString());
                m.UnfreezeValue(entitysh[i]);
                m.UnfreezeValue(entitysw[i]);

            end:;
            }
        }

    }
}
