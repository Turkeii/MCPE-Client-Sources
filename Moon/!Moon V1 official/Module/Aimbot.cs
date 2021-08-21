using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Memory;
using sdkcheat;
using System.Threading;


namespace AimbotCheat
{
    class Aimbot
    {
        Mem m = new Mem();
        SDK sdk = new SDK();


        public void RunAimbot()
        {
            m.OpenProcess("Minecraft.Windows");

            List<string> dxentitylist = sdk.getentitylist("4D8");
            List<string> dyentitylist = sdk.getentitylist("4D0");
            List<string> dzentitylist = sdk.getentitylist("4D4");


            float dxself = m.ReadFloat(sdk.LocalPlayer("4D8"));
            float dyself = m.ReadFloat(sdk.LocalPlayer("4D0"));
            float dzself = m.ReadFloat(sdk.LocalPlayer("4D4"));


            float dxentity = m.ReadFloat(dxentitylist[sdk.GetNearestEntity()]);
            float dyentity = m.ReadFloat(dyentitylist[sdk.GetNearestEntity()]);
            float dzentity = m.ReadFloat(dzentitylist[sdk.GetNearestEntity()]);

            

            float dx = dxself - dxentity;  // Z
            float dy = dyself - dyentity;  // X
            float dz = dzself - dzentity; // Y

            double angleYaw = Math.Atan2(dy, dx) * 3.14 / Math.PI;
            double distance = Math.Sqrt(dx * dx + dy * dy);
            double anglePitch = Math.Atan2(dz, distance) * -3.14 / Math.PI;

            m.WriteMemory(sdk.ViewMatrix("x"), "float", angleYaw.ToString());
            m.WriteMemory(sdk.ViewMatrix("y"), "float", anglePitch.ToString());
            

        }

        

        private static void abthread()
        {
            Mem m = new Mem();
            SDK sdk = new SDK();

            m.OpenProcess("Minecraft.Windows");

            List<string> dxentitylist = sdk.getentitylist("4D8");
            List<string> dyentitylist = sdk.getentitylist("4D0");
            List<string> dzentitylist = sdk.getentitylist("4D4");


            float dxself = m.ReadFloat(sdk.LocalPlayer("4D8"));
            float dyself = m.ReadFloat(sdk.LocalPlayer("4D0"));
            float dzself = m.ReadFloat(sdk.LocalPlayer("4D4"));


            float dxentity = m.ReadFloat(dxentitylist[1]);
            float dyentity = m.ReadFloat(dyentitylist[1]);
            float dzentity = m.ReadFloat(dzentitylist[1]);



            float dx = dxself - dxentity;  // Z
            float dy = dyself - dyentity;  // X
            float dz = dzself - dzentity; // Y

            double angleYaw = Math.Atan2(dy, dx) * 3.14 / Math.PI;
            double distance = Math.Sqrt(dx * dx + dy * dy);
            double anglePitch = Math.Atan2(dz, distance) * -3.14 / Math.PI;

            m.WriteMemory(sdk.ViewMatrix("x"), "float", angleYaw.ToString());
            m.WriteMemory(sdk.ViewMatrix("y"), "float", anglePitch.ToString());


        }

    }

    
}
