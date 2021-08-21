using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Memory;
using sdkcheat;

namespace sdkcheat
{
    public class SDK
    {
        
        
        
        public const string EntityAddr = "Minecraft.Windows.exe+04020228,8,18,B8,378,58,";

        //Static Addresses
        public const string spinnme = "Minecraft.Windows.exe+2C0E76C";
        public const string W360 = "Minecraft.Windows.exe+35012F4";
        public const string W180 = "Minecraft.Windows.exe+3501270";
        public const string Reach = "Minecraft.Windows.exe+3500ED0";



        //Offsets
        public const string XCord = "4D0";
        public const string YCord = "4D4";
        public const string ZCord = "4D8";
        public const string YHitbox = "4EC";
        public const string XHitbox = "4F0";
        public const string XVec = "50C";
        public const string YVec = "510";
        public const string ZVec = "514";
        public const string YCam = "26636A4";
        public const string XCam = "26636A0";

        public string LocalPlayer(string offset)
        {
            return "Minecraft.Windows.exe+04020228,8,18,B8," + offset;
        }
        public string ViewMatrix(string wich)
        {
            if(wich == "y") { return "Minecraft.Windows.exe+03A144C8,28,168,0,14"; }
            else { return "Minecraft.Windows.exe+03A144C8,28,168,0,10"; }
        }




        public List<string> entitylist = new List<string>();
        public List<string> getentitylist(string offset)
        {
            string list1 = "Minecraft.Windows.exe+04020228,8,18,B8,378,58,";
            string list3 = ",";


            List<string> entitylist = new List<string>();
            int entinum = 0;
            bool pl8 = true;

            for (int i = 0; i < 999; i++)
            {

                if (pl8 = true)
                {
                    string _entity = list1 + entinum.ToString() + list3 + offset;
                    entinum = entinum + 8;
                    entitylist.Add(_entity);
                }
                else
                {
                    string _entity = list1 + entinum.ToString() + list3 + offset;
                    entinum = entinum + 2;
                    entitylist.Add(_entity);
                }
                pl8 = !pl8;


            }
            return entitylist;

        }
        Mem m = new Mem();
        public int GetNearestEntity()
        {
            
            m.OpenProcess("Minecraft.Windows");
            List<string> allentitysX = getentitylist("4D0");
            List<string> allentitysZ = getentitylist("4D8");
            
            float nearestdistance = 100f;
            int nearestplayer = 2;

            for(int i = 0; i < allentitysX.Count; i++)
            {
                if (i != 0 || i != 1)
                {
                    
                    float thisdistanceX = (m.ReadFloat(allentitysX[i]) - m.ReadFloat(LocalPlayer("4D0")));
                    float thisdistanceZ = (m.ReadFloat(allentitysZ[i]) - m.ReadFloat(LocalPlayer("4D8")));
                    float thisdistance = (float)Math.Sqrt(thisdistanceX * thisdistanceZ);

                    if (thisdistance < nearestdistance)
                    {
                        nearestdistance = thisdistance;
                        nearestplayer = i;
                    }

                }    
            }

            return nearestplayer;
        }

        

    }
}
