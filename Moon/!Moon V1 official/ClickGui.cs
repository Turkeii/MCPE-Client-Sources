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
using Gma.System.MouseKeyHook;
using onmodulesclass;
using Memory;
using sdkcheat;

//Using Cheats
using AimbotCheat;
using AirjumpCheat;
using ReachCheat;
using HitboxCheat;

namespace _Moon_V1_official
{
    public partial class ClickGui : Form
    {
        //imports
        ez ez = new ez();

        Mem m = new Mem();
        SDK sdk = new SDK();

        //Make Panels moveable
        private Point MouseDownLocationCombo;
        private Point MouseDownLocationVisuals;
        private Point MouseDownLocationMov;
        private Point MouseDownLocationExploits;
        private Point MouseDownLocationSettings;

        //Manage Modules
        Aimbot aimbot = new Aimbot();
        Airjump airjump = new Airjump();
        Reach reach = new Reach();
        Hitbox hitbox = new Hitbox();

        //Configure Hotkeys

        //Hotkeys
        bool GetClickGuiHotkey = false;
        Keys clickguikey = Keys.Insert;

        bool GetReachHotkey = false;
        Keys reachkey;

        bool GetHitboxHotkey = false;
        Keys hitboxkey;

        bool GetInstantbreakHotkey = false;
        Keys instantbreakkey;

        bool GetNoknockbackHotkey = false;
        Keys noknockbackkey;

        bool GetInfiblockreachHotkey = false;
        Keys infiblockreachkey;

        bool GetTriggerbotHotkey = false;
        Keys triggerbotkey = Keys.F18;

        bool GetAimbotHotkey = false;
        Keys aimbotkey;

        //Visuals

        bool GetZoomHotkey = false;
        Keys zoomkey = Keys.C;

        bool GetRainbowskyHotkey = false;
        Keys rainbowsky;

        bool GetFulllightHotkey = false;
        Keys fulllightkey;

        bool GetStopvisualtimeHotkey = false;
        Keys stopvisualtime;

        bool GetCompassHotkey = false;
        Keys compasshotkey;

        bool GetEntitydisplayHotkey = false;
        Keys entitydisplaykey;

        //Mov

        bool GetSpeedHotkey = false;
        Keys speedkey;

        bool GetAirjumpHotkey = false;
        Keys airjumpkey;

        bool GetHighjumpHotkey = false;
        Keys highjumpkey;

        bool GetPglideHotkey = false;
        Keys pglidekey;

        bool GetGlideHotkey = false;
        Keys glidekey;

        bool GetPositionfreezeHotkey = false;
        Keys positionfreezekey;

        bool GetAirwalkHotkey = false;
        Keys airwalkkey;

        bool GetInfinityHotkey = false;
        Keys infinitykey;

        bool GetPhaseHotkey = false;
        Keys phasekey;

        bool GetSpeedsneakHotkey = false;
        Keys speedsneakkey;

        //Exploits

        bool GetNofallHotkey = false;
        Keys nofallkey;

        bool GetFlydamagebypassHotkey = false;
        Keys flydamagebypasskey;

        bool GetAntivoidHotkey = false;
        Keys antivoidkey;

        bool GetNorenderHotkey = false;
        Keys norenderkey;

        bool GetScaffoldHotkey = false;
        Keys scaffoldkey;

        bool GetTargetstraffeHotkey = false;
        Keys targetstraffekey;

        bool GetFakeGodmodeHotkey = false;
        Keys fakegodmodekey;

        //Settings

        bool GetKeystrokesHotkey = false;
        Keys keystrokeskey;

        bool GetTabguiHotkey = false;
        Keys tabguikey;

        bool GetWatermarkHotkey = false;
        Keys watermarkHotkey;

        bool GetArraylistHotkey = false;
        Keys arraylistkey;

        


        //For array list!
        OnModules arrayon = new OnModules();
        Arraylist.Arraylist arryl = new Arraylist.Arraylist();

        //Overlay / Watermark
        Arraylist.MainOverlay moverly = new Arraylist.MainOverlay();

        //TabGui tbgui = new TabGui();





        public ClickGui()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
            //Start the Overlay!
            CheckForIllegalCrossThreadCalls = false;
            ez.SetInvi(this);
            ez.StartLoop(10, "Minecraft", this);

            //Manage hotkeys
            var hook = Hook.GlobalEvents();
            hook.KeyDown += Hook_KeyDown;
            
            hook.KeyUp += Hook_KeyUp;

            //Start Array list
            arryl.Show();
            //Start Overlay
            moverly.Show();

            //Start Tabgui
            //tbgui.Show();


            //Run Timers
            timer_aimbot.Start();

        }
       
        //KeyUp
        private void Hook_KeyUp(object sender, KeyEventArgs e)
        {
            //SetHotkeyfor the ClickGui
            if (GetClickGuiHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    clickguikey = e.KeyCode;
                    button_clickgui_hotkey.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetClickGuiHotkey = false;
            }
            //SetHotkeyfor the Reach
            else if (GetReachHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    reachkey = e.KeyCode;
                    button_reach_hotkey.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetReachHotkey = false;
            }
            //SetHotkeyfor the Hitbox
            else if (GetHitboxHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    hitboxkey = e.KeyCode;
                    button_hitbox_hotkey.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetHitboxHotkey = false;
            }
            //SetHotkeyfor the Instantbreak
            else if (GetInstantbreakHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    instantbreakkey = e.KeyCode;
                    button_instantbreak_hotkey.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetInstantbreakHotkey = false;
            }
            //SetHotkeyfor the Noknockback
            else if (GetNoknockbackHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    noknockbackkey = e.KeyCode;
                    button_noknockback_hotkey.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetNoknockbackHotkey = false;
            }
            //SetHotkey for Infinityblockreach!
            else if (GetInfiblockreachHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    infiblockreachkey = e.KeyCode;
                    button_Infinityblockreach_hotkey.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetInfiblockreachHotkey = false;
            }
            //SetHotkey for Triggerbot
            else if (GetTriggerbotHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    triggerbotkey = e.KeyCode;
                    button_triggerbot_hotkey.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetTriggerbotHotkey = false;
            }
            //SetHotkey for Aimbot
            else if (GetAimbotHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    aimbotkey = e.KeyCode;
                    button_aimbot_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetAimbotHotkey = false;
            }

            //SetHotkey for Zoom
            else if (GetZoomHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    zoomkey = e.KeyCode;
                    button_zoom_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetZoomHotkey = false;
            }
            //SetHotkey for Rainbowsky
            else if (GetRainbowskyHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    rainbowsky = e.KeyCode;
                    button_rainbowsky_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetRainbowskyHotkey = false;
            }
            //SetHotkey for Fulllight
            else if (GetFulllightHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    fulllightkey = e.KeyCode;
                    button_fulllight_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetFulllightHotkey = false;
            }
            //SetHotkey for StopVisualTime
            else if (GetStopvisualtimeHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    stopvisualtime = e.KeyCode;
                    button_stopvisualtime_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetStopvisualtimeHotkey = false;
            }
            //SetHotkey for Speed
            else if (GetSpeedHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    speedkey = e.KeyCode;
                    button_speed_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetSpeedHotkey = false;
            }
            //SetHotkey for Airjump
            else if (GetAirjumpHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    airjumpkey = e.KeyCode;
                    button_airjump_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetAirjumpHotkey = false;
            }
            //SetHotkey for Highjump
            else if (GetHighjumpHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    highjumpkey = e.KeyCode;
                    button_highjump_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetHighjumpHotkey = false;
            }
            //SetHotkey for PGlide
            else if (GetPglideHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    pglidekey = e.KeyCode;
                    button_highjump_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetPglideHotkey = false;
            }
            //SetHotkey for Glide
            else if (GetGlideHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    glidekey = e.KeyCode;
                    button_glide_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetGlideHotkey = false;
            }
            //SetHotkey for Positionfrezze
            else if (GetPositionfreezeHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    positionfreezekey = e.KeyCode;
                    button_positionfreeze_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetPositionfreezeHotkey = false;
            }
            //SetHotkey for Airwalk
            else if (GetAirwalkHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    airwalkkey = e.KeyCode;
                    button_airwalk_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetAirwalkHotkey = false;
            }
            //SetHotkey for Phase
            else if (GetPhaseHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    phasekey = e.KeyCode;
                    button_phase_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetPhaseHotkey = false;
            }
            //SetHotkey for SpeedSneak
            else if (GetSpeedsneakHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    speedkey = e.KeyCode;
                    button_speedsneak_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetSpeedsneakHotkey = false;
            }
            //SetHotkey for NoFall
            else if (GetNofallHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    nofallkey = e.KeyCode;
                    button_nofall_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetNofallHotkey = false;
            }
            //SetHotkey for FlyDamageBypass
            else if (GetFlydamagebypassHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    flydamagebypasskey = e.KeyCode;
                    button_flydamagebypass_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetFlydamagebypassHotkey = false;
            }
            //SetHotkey for AntiVoid
            else if (GetAntivoidHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    antivoidkey = e.KeyCode;
                    button_antivoid_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetAntivoidHotkey = false;
            }
            //SetHotkey for Norender
            else if (GetNorenderHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    norenderkey = e.KeyCode;
                    button_norender_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetNorenderHotkey = false;
            }
            //SetHotkey for Scaffold
            else if (GetScaffoldHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    scaffoldkey = e.KeyCode;
                    button_scaffold_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetScaffoldHotkey = false;
            }
            //SetHotkey for FakeGamemode
            else if (GetFakeGodmodeHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    fakegodmodekey = e.KeyCode;
                    button_fakegamemode_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetFakeGodmodeHotkey = false;
            }
            //SetHotkey for Targetstraffe
            else if (GetTargetstraffeHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    targetstraffekey = e.KeyCode;
                    button_targetstraffe_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetTargetstraffeHotkey = false;
            }
            //SetHotkey for Keystrokes
            else if (GetKeystrokesHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    keystrokeskey = e.KeyCode;
                    button_keystrokes_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
               GetKeystrokesHotkey = false;
            }
            //SetHotkey for Tabgui
            else if (GetTabguiHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    tabguikey = e.KeyCode;
                    button_tabgui_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetTabguiHotkey = false;
            }
            //SetHotkey for Arraylist
            else if (GetArraylistHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    arraylistkey = e.KeyCode;
                    button_arraylist_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetArraylistHotkey = false;
            }
            //SetHotkey for Watermark
            else if (GetWatermarkHotkey == true)
            {
                if (e.KeyCode != Keys.Escape)
                {
                    watermarkHotkey = e.KeyCode;
                    button_watermark_h.Text = "Hotkey: " + e.KeyCode.ToString();
                }
                GetWatermarkHotkey = false;
            }

        }



        //KeyDown
        bool clickgui_shown = true;
        
        private void Hook_KeyDown(object sender, KeyEventArgs e)
        {
            //open/close ClickGui
            if(e.KeyCode == clickguikey)
            {
                clickgui_shown = !clickgui_shown;

                this.Visible = !this.Visible;
                
            }
            

            //Run Reach
            if (e.KeyCode == reachkey)
            {
                reachon = !reachon;
                if (reachon) { reach.set(trackBar_reach.Value); } else { reach.set(3f); }
               panel_reach.Visible = panel_reach.Visible;
               arryl.label_reach.Visible = !arryl.label_reach.Visible;
            }
            //Run Hitbox
            if (e.KeyCode == hitboxkey)
            {
                if (hitboxon)
                {
                    hitboxon = !hitboxon;
                    hitbox.set(trackBar_hitbox_withe.Value, trackBar_hitbox_high.Value);
                }
                panel_hitbox.Visible = panel_hitbox.Visible;
                arryl.label_Hitbox.Visible = !arryl.label_Hitbox.Visible;
            }
            //Run Instantbreak
            if (e.KeyCode == instantbreakkey)
            {
                panel_instantbreak.Visible = panel_instantbreak.Visible;
                arryl.label_instantbreak.Visible = !arryl.label_instantbreak.Visible;
            }
            //Run Noknockback
            if (e.KeyCode == hitboxkey)
            {
                panel_noknockback.Visible = panel_noknockback.Visible;
                arryl.label_Noknockback.Visible = !arryl.label_Noknockback.Visible;
            }
            //Run InfinityblockReach
            if (e.KeyCode == infinitykey)
            {
                panel_Infinityblockreach.Visible = panel_Infinityblockreach.Visible;
                arryl.label_infinityblockreach.Visible = !arryl.label_infinityblockreach.Visible;
            }
            //Run Twriggerbot
            if (e.KeyCode == triggerbotkey)
            {
                panel_triggerbot.Visible = panel_triggerbot.Visible;
                arryl.label_triggerbot.Visible = !arryl.label_triggerbot.Visible;
            }
            //Run Aimbot
            if (e.KeyCode == aimbotkey)
            {
                panel_aimbot.Visible = panel_aimbot.Visible;
                arryl.label_aimbot.Visible = !arryl.label_aimbot.Visible;
            }

                        //Visuals

            //Run Zoom
            if (e.KeyCode == zoomkey)
            {
                panel_zoom.Visible = panel_zoom.Visible;
                arryl.label_zoom.Visible = !arryl.label_zoom.Visible;
            }
            //Run Rainbowsky
            if (e.KeyCode == rainbowsky)
            {
               panel_rainbowsky.Visible = panel_rainbowsky.Visible;
               arryl.label_rainbowsky.Visible = !arryl.label_rainbowsky.Visible;
            }
            //Run Fulllight
            if (e.KeyCode == fulllightkey)
            {
                panel_fulllight.Visible = panel_fulllight.Visible;
                arryl.label_fulllight.Visible = !arryl.label_fulllight.Visible;
            }
            //Run StopVisualTime
            if (e.KeyCode == stopvisualtime)
            {
                panel_StopVisualTime.Visible = panel_StopVisualTime.Visible;
                arryl.label_stopvisualtime.Visible = !arryl.label_stopvisualtime.Visible;
            }
            //Run EntityDisplay
            if (e.KeyCode == entitydisplaykey)
            {
               panel_entitydisplay.Visible = panel_entitydisplay.Visible;
                arryl.label_entitydisplay.Visible = !arryl.label_entitydisplay.Visible;
            }
            //Run Compass
            if (e.KeyCode == compasshotkey)
            {
                panel_StopVisualTime.Visible = panel_StopVisualTime.Visible;
                arryl.label_kompass.Visible = !arryl.label_kompass.Visible;
            }
                                    //Mov

            //Run Speed
            if (e.KeyCode == speedkey)
            {
                panel_speed.Visible = panel_speed.Visible;
                arryl.label_speed.Visible = !arryl.label_speed.Visible;
            }
            //Run Airjump
            if (e.KeyCode == airjumpkey)
            {
                airjumpon = !airjumpon;
                if (airjumpon) { airjump.AirJumpon(); } else { airjump.AirJumpoff(); }
                panel_airjump.Visible = panel_airjump.Visible;
                arryl.label_airjump.Visible = !arryl.label_airjump.Visible;
            }
            //Run HighJump
            if (e.KeyCode == highjumpkey)
            {
                panel_highjump.Visible = panel_highjump.Visible;
                arryl.label_highjump.Visible = !arryl.label_highjump.Visible;
            }
            //Run PGlide
            if (e.KeyCode == pglidekey)
            {
                panel_pglide.Visible = panel_pglide.Visible;
                arryl.label_pglide.Visible = !arryl.label_pglide.Visible;
            }
            //Run Glide
            if (e.KeyCode == glidekey)
            {
                panel_glide.Visible = panel_glide.Visible;
                arryl.label_glide.Visible = !arryl.label_glide.Visible;
            }
            //Run Positionfreeze
            if (e.KeyCode == positionfreezekey)
            {
                panel_positionfreeze.Visible = panel_positionfreeze.Visible;
                arryl.label_positionfreeze.Visible = !arryl.label_positionfreeze.Visible;
            }
            //Run InfinintyJumop
            if (e.KeyCode == infinitykey)
            {
                panel_infinityjump.Visible = panel_infinityjump.Visible;
                arryl.label_infinityjump.Visible = !arryl.label_infinityjump.Visible;
            }
            //Run Airwalk
            if (e.KeyCode == airwalkkey)
            {
                panel_airwalk.Visible = panel_airwalk.Visible;
                arryl.label_airwalk.Visible = !arryl.label_airwalk.Visible;
            }
            //Run Phase
            if (e.KeyCode == phasekey)
            {
                panel_phase.Visible = panel_phase.Visible;
                arryl.label_phase.Visible = !arryl.label_phase.Visible;
            }
            //Run SpeedSneak
            if (e.KeyCode == speedsneakkey)
            {
                panel_speedsneak.Visible = panel_speedsneak.Visible;
                arryl.label_speedsneak.Visible = !arryl.label_speedsneak.Visible;
            }
                        
                            //Exploits

            //Run Nofall
            if (e.KeyCode == nofallkey)
            {
                panel_nofall.Visible = panel_nofall.Visible;
                arryl.label_nofall.Visible = !arryl.label_nofall.Visible;
            }
            //Run FlyDamageBypass
            if (e.KeyCode == flydamagebypasskey)
            {
                panel_FlyDamageBypass.Visible = panel_FlyDamageBypass.Visible;
                arryl.label_flydamagebypass.Visible = !arryl.label_flydamagebypass.Visible;
            }
            //Run Antivoid
            if (e.KeyCode == antivoidkey)
            {
                panel_antivoid.Visible = panel_antivoid.Visible;
                arryl.label_antivoid.Visible = !arryl.label_antivoid.Visible;
            }
            //Run Scaffold
            if (e.KeyCode == scaffoldkey)
            {
                panel_scaffold.Visible = panel_scaffold.Visible;
                arryl.label_scaffold.Visible = !arryl.label_scaffold.Visible;
            }
            //Run Norender
            if (e.KeyCode == norenderkey)
            {
                panel_norender.Visible = panel_norender.Visible;
                arryl.label_norender.Visible = !arryl.label_norender.Visible;
            }
            //Run FakeGamemode
            if (e.KeyCode == fakegodmodekey)
            {
                panel_fakegamemode.Visible = panel_fakegamemode.Visible;
                arryl.label_fakegamemode.Visible = !arryl.label_fakegamemode.Visible;
            }
            //Run Targetstraffe
            if (e.KeyCode == targetstraffekey)
            {
               panel_targetstraffe.Visible = panel_targetstraffe.Visible;
                arryl.label_targetstraffe.Visible = !arryl.label_targetstraffe.Visible;
            }




        }


        //Reach
        bool reachon = false;
        private void button_reach_Click(object sender, EventArgs e)
        {
            reachon = !reachon;
            if (reachon) { reach.set(trackBar_reach.Value); } else { reach.set(3f); }
            panel_reach.Visible = !panel_reach.Visible;
            

            //Send to the Array list
            arryl.label_reach.Visible = !arryl.label_reach.Visible;
            

            
        }
        //Hitbox Button
        bool hitboxon = false;
        private void button_hitbox_Click(object sender, EventArgs e)
        {
            hitboxon = !hitboxon;
            if (hitboxon)
            {
                hitbox.set(trackBar_hitbox_withe.Value, trackBar_hitbox_high.Value);
            }
            else
            {
                hitbox.unset();
            }
            panel_hitbox.Visible = !panel_hitbox.Visible;
            arryl.label_Hitbox.Visible = !arryl.label_Hitbox.Visible;
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            panel_instantbreak.Visible = !panel_instantbreak.Visible;
            arryl.label_instantbreak.Visible = !arryl.label_instantbreak.Visible;

        }
        //NoKnockback Button
        private void button4_Click(object sender, EventArgs e)
        {
            panel_noknockback.Visible = !panel_noknockback.Visible;
            arryl.label_Noknockback.Visible = !arryl.label_Noknockback.Visible;
        }
        //InfinityBlockReach Button
        private void button_Infinityblockreach_Click(object sender, EventArgs e)
        {
            panel_Infinityblockreach.Visible = !panel_Infinityblockreach.Visible;
            arryl.label_infinityblockreach.Visible = !arryl.label_infinityblockreach.Visible;
        }
        //Triggerbot Button
        private void button_triggerbot_Click(object sender, EventArgs e)
        {
            panel_triggerbot.Visible = !panel_triggerbot.Visible;
            arryl.label_triggerbot.Visible = !arryl.label_triggerbot.Visible;
        }
        //AutoclickerButton
        private void button_AutoClicker_Click(object sender, EventArgs e)
        {
            panel_AutoClicker.Visible = !panel_AutoClicker.Visible;
        }

        //Visuals;

        //Zoom
        private void button13_Click(object sender, EventArgs e)
        {
            panel_zoom.Visible = !panel_zoom.Visible;
            arryl.label_zoom.Visible = !arryl.label_zoom.Visible;
        }
        //Rainbowsky
        private void button_rainbowsky_Click(object sender, EventArgs e)
        {
            panel_rainbowsky.Visible = !panel_rainbowsky.Visible;
            arryl.label_rainbowsky.Visible = !arryl.label_rainbowsky.Visible;
        }
        //Fulllight
        private void button16_Click(object sender, EventArgs e)
        {
            panel_fulllight.Visible = !panel_fulllight.Visible;
            arryl.label_fulllight.Visible = !arryl.label_fulllight.Visible;
        }
        //StopVisualTime
        private void button18_Click(object sender, EventArgs e)
        {
            panel_StopVisualTime.Visible = !panel_StopVisualTime.Visible;
            arryl.label_stopvisualtime.Visible = !arryl.label_stopvisualtime.Visible;
        }
        //Speed
        private void button_speed_Click(object sender, EventArgs e)
        {
            panel_speed.Visible = !panel_speed.Visible;
            arryl.label_speed.Visible = !arryl.label_speed.Visible;
        }
        //Airjump
        bool airjumpon = false;
        private void button_airjump_Click(object sender, EventArgs e)
        {
            airjumpon = !airjumpon;
            if(airjumpon == true)
            {
                airjump.AirJumpon();
            }
            else
            {
                airjump.AirJumpoff();   
            }
            panel_airjump.Visible = !panel_airjump.Visible;
            arryl.label_airjump.Visible = !arryl.label_airjump.Visible;
            
        }
        //HithJump
        private void button_highjump_Click(object sender, EventArgs e)
        {
            panel_highjump.Visible = !panel_highjump.Visible;
            arryl.label_highjump.Visible = !arryl.label_highjump.Visible;
        }
        //PGlide
        private void button_pglide_Click(object sender, EventArgs e)
        {
            panel_pglide.Visible = !panel_pglide.Visible;
            arryl.label_pglide.Visible = !arryl.label_pglide.Visible;
        }
        //Glide
        private void button_glide_Click(object sender, EventArgs e)
        {
            panel_glide.Visible = !panel_glide.Visible;
            arryl.label_glide.Visible = !arryl.label_glide.Visible;
        }
        //Positionfreeze
        private void button_positionfreeze_Click(object sender, EventArgs e)
        {
            panel_positionfreeze.Visible = !panel_positionfreeze.Visible;
            arryl.label_positionfreeze.Visible = !arryl.label_positionfreeze.Visible;
        }
        //InfinityJump
        private void button_infinityjump_Click(object sender, EventArgs e)
        {
            panel_infinityjump.Visible = !panel_infinityjump.Visible;
            arryl.label_infinityjump.Visible = !arryl.label_infinityjump.Visible;
        }
        //airwalk
        private void button_airwalk_Click(object sender, EventArgs e)
        {
            panel_airwalk.Visible = !panel_airwalk.Visible;
            arryl.label_airwalk.Visible = !arryl.label_airwalk.Visible;
        }
        //Phase
        private void button_phase_Click(object sender, EventArgs e)
        {
            panel_phase.Visible = !panel_phase.Visible;
            arryl.label_phase.Visible = !arryl.label_phase.Visible;
        }
        //Speedsneak
        private void button21_Click(object sender, EventArgs e)
        {
            panel_speedsneak.Visible = !panel_speedsneak.Visible;
        }
        
        //Combopanelmove 1
        private void panel2_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                MouseDownLocationCombo = e.Location;
            }
        }
        //Combopanelmove 2
        private void panel2_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                panel_combo.Left = e.X + panel_combo.Left - MouseDownLocationCombo.X;
                panel_combo.Top = e.Y + panel_combo.Top - MouseDownLocationCombo.Y;

            }
        }
        //Visualpanelmov 1
        private void panel3_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                MouseDownLocationVisuals = e.Location;
            }
        }
        //Visualpanelmov 2
        private void panel3_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                panel_visuals.Left = e.X + panel_visuals.Left - MouseDownLocationVisuals.X;
                panel_visuals.Top = e.Y + panel_visuals.Top - MouseDownLocationVisuals.Y;

            }
        }

        //Movpanelmov 1
        private void panel8_MouseDown_1(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                MouseDownLocationMov = e.Location;
            }
        }
        //Movpanelmov 2
        private void panel8_MouseMove_1(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                panel1.Left = e.X + panel1.Left - MouseDownLocationMov.X;
                panel1.Top = e.Y + panel1.Top - MouseDownLocationMov.Y;

            }
        }
        //Exploitspanelmov 1
        private void panel5_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                MouseDownLocationExploits = e.Location;
            }
        }
        //Exploitspanelmov 2
        private void panel5_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                panel_exploits.Left = e.X + panel_exploits.Left - MouseDownLocationExploits.X;
                panel_exploits.Top = e.Y + panel_exploits.Top - MouseDownLocationExploits.Y;

            }
        }
        //NoFall
        private void button23_Click(object sender, EventArgs e)
        {
            panel_nofall.Visible = !panel_nofall.Visible;
            arryl.label_nofall.Visible = !arryl.label_nofall.Visible;
        }
        //Flydamagebypass
        private void button_FlyDamageBypass_Click(object sender, EventArgs e)
        {
            panel_FlyDamageBypass.Visible = !panel_FlyDamageBypass.Visible;
            arryl.label_flydamagebypass.Visible = !arryl.label_flydamagebypass.Visible;
        }
        //Antivoid
        private void button_antivoid_Click(object sender, EventArgs e)
        {
            panel_antivoid.Visible = !panel_antivoid.Visible;
            arryl.label_antivoid.Visible = !arryl.label_antivoid.Visible;
        }
        //Norender
        private void button_norender_Click(object sender, EventArgs e)
        {
            panel_norender.Visible = !panel_norender.Visible;
            arryl.label_norender.Visible = !arryl.label_norender.Visible;
        }
        //Scaffold
        private void button_scaffold_Click(object sender, EventArgs e)
        {
            panel_scaffold.Visible = !panel_scaffold.Visible;
            arryl.label_scaffold.Visible = !arryl.label_scaffold.Visible;
        }
        //Keystrokes
        private void button30_Click(object sender, EventArgs e)
        {
            panel_keystrokes.Visible = !panel_keystrokes.Visible;
        }
        //ClickGui
        private void button_clickgui_Click(object sender, EventArgs e)
        {
            panel_clickgui.Visible = !panel_clickgui.Visible;
        }
        //TabGui
        private void button_tabgui_Click(object sender, EventArgs e)
        {
            panel_tabgui.Visible = !panel_tabgui.Visible;
            TabGui tbgui = new TabGui();
            tbgui.Show();
        }
        //ClickGui/Hotkey
        private void button_clickgui_hotkey_Click(object sender, EventArgs e)
        {
            GetClickGuiHotkey = true;

            button_clickgui_hotkey.Text = "Press Key!";
        }
        //Settingspanelmoveable
        private void panel6_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                MouseDownLocationSettings = e.Location;
            }
        }

        private void panel6_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                panel_settings.Left = e.X + panel_settings.Left - MouseDownLocationSettings.X;
                panel_settings.Top = e.Y + panel_settings.Top - MouseDownLocationSettings.Y;

            }
        }
        //Arraylist on/off
        private void button_arraylist_Click(object sender, EventArgs e)
        {
            arryl.Visible = !arryl.Visible;
        }
        //Watermark on/off
        private void button_watermark_Click(object sender, EventArgs e)
        {
            moverly.Visible = !moverly.Visible;
        }
        //reach Hotkey
        private void button_reach_hotkey_Click(object sender, EventArgs e)
        {
            GetReachHotkey = true;
            button_reach_hotkey.Text = "Press Key!";
        }

        private void button_hitbox_hotkey_Click(object sender, EventArgs e)
        {
            GetHitboxHotkey = true;
            button_hitbox_hotkey.Text = "Press Key!";
        }

        private void button_instantbreak_hotkey_Click(object sender, EventArgs e)
        {
            GetInstantbreakHotkey = true;
            button_instantbreak_hotkey.Text = "Press Key!";
        }

        private void button_noknockback_hotkey_Click(object sender, EventArgs e)
        {
            GetNoknockbackHotkey = true;
            button_noknockback_hotkey.Text = "Press Key!";
        }

        private void button_Infinityblockreach_hotkey_Click(object sender, EventArgs e)
        {
            GetInfiblockreachHotkey = true;
            button_Infinityblockreach_hotkey.Text = "Press Key!";
        }

        private void button_triggerbot_hotkey_Click(object sender, EventArgs e)
        {
            GetTriggerbotHotkey = true;
            button_triggerbot_hotkey.Text = "Press Key!";
        }

        private void button_zoom_h_Click(object sender, EventArgs e)
        {
            GetZoomHotkey = true;
            button_zoom_h.Text = "Press Key!";
        }

        private void button_rainbowsky_h_Click(object sender, EventArgs e)
        {
            GetRainbowskyHotkey = true;
            button_rainbowsky_h.Text = "Press Key!";
        }

        private void button_fulllight_h_Click(object sender, EventArgs e)
        {
            GetFulllightHotkey = true;
            button_fulllight_h.Text = "Press Key!";
        }

        private void button_stopvisualtime_h_Click(object sender, EventArgs e)
        {
            GetStopvisualtimeHotkey = true;
            button_stopvisualtime_h.Text = "Press Key!";
        }

        private void button_speed_h_Click(object sender, EventArgs e)
        {
            GetSpeedHotkey = true;
            button_speed_h.Text = "Press Key!";
        }

        private void button_airjump_h_Click(object sender, EventArgs e)
        {
            GetAirjumpHotkey = true;
            button_airjump_h.Text = "Press Key!";
        }

        private void button_highjump_h_Click(object sender, EventArgs e)
        {
            GetHighjumpHotkey = true;
            button_highjump_h.Text = "Press Key!";
        }

        private void button_pglide_h_Click(object sender, EventArgs e)
        {
            GetPglideHotkey = true;
            button_pglide_h.Text = "Press Key!";
        }

        private void button_glide_h_Click(object sender, EventArgs e)
        {
            GetGlideHotkey = true;
            button_glide_h.Text = "Press Key!";
        }

        private void button_positionfreeze_h_Click(object sender, EventArgs e)
        {
            GetPositionfreezeHotkey = true;
            button_positionfreeze_h.Text = "Press Key!";
        }

        private void button_infinijump_h_Click(object sender, EventArgs e)
        {
            GetInfinityHotkey = true;
            button_infinijump_h.Text = "Press Key";
        }

        private void button_airwalk_h_Click(object sender, EventArgs e)
        {
            GetAirwalkHotkey = true;
            button_airwalk_h.Text = "Press Key!";

        }

        private void button_phase_h_Click(object sender, EventArgs e)
        {
            GetPhaseHotkey = true;
            button_phase_h.Text = "Press Key!";
        }

        private void button_speedsneak_h_Click(object sender, EventArgs e)
        {
            GetSpeedsneakHotkey = true;
            button_speedsneak_h.Text = "Press Key!";
        }

        private void button_nofall_h_Click(object sender, EventArgs e)
        {
            GetNofallHotkey = true;
            button_nofall_h.Text = "Press Key!";

        }

        private void button_flydamagebypass_h_Click(object sender, EventArgs e)
        {
            GetFlydamagebypassHotkey = true;
            button_flydamagebypass_h.Text = "Press Key!";
        }

        private void button_antivoid_h_Click(object sender, EventArgs e)
        {
            GetAntivoidHotkey = true;
            button_antivoid_h.Text = "Press key!";
        }

        private void button_norender_h_Click(object sender, EventArgs e)
        {
            GetNorenderHotkey = true;
            button_norender_h.Text = "Press Key!";
        }

        private void button_scaffold_h_Click(object sender, EventArgs e)
        {
            GetScaffoldHotkey = true;
            button_scaffold_h.Text = "Press Key!";
        }

        private void button_fakegamemode_h_Click(object sender, EventArgs e)
        {
            GetFakeGodmodeHotkey = true;
            button_fakegamemode_h.Text = "Press Key!";
        }

        private void button_keystrokes_h_Click(object sender, EventArgs e)
        {
            GetKeystrokesHotkey = true;
            button_keystrokes_h.Text = "Press Key!";
        }

        private void button_tabgui_h_Click(object sender, EventArgs e)
        {
            GetTabguiHotkey = false;
            button_tabgui_h.Text = "Press Key!";
        }

        private void button_arraylist_h_Click(object sender, EventArgs e)
        {
            GetArraylistHotkey = true;
            button_arraylist_h.Text = "Press Key!";
        }

        private void button_watermark_h_Click(object sender, EventArgs e)
        {
            GetWatermarkHotkey = false;
            button_watermark_h.Text = "Press Key!";
            
        }
        bool timerisrunning = false;
        private void button_aimbot_Click(object sender, EventArgs e)
        {
         
            panel_aimbot.Visible = !panel_aimbot.Visible;
            arryl.label_aimbot.Visible = !arryl.label_aimbot.Visible;
        }

        private void button_entitydisplay_Click(object sender, EventArgs e)
        {
            panel_entitydisplay.Visible = !panel_entitydisplay.Visible;
            arryl.label_entitydisplay.Visible = !arryl.label_entitydisplay.Visible;
        }

        private void button_kompass_Click(object sender, EventArgs e)
        {
            panel_kompass.Visible = !panel_kompass.Visible;
            arryl.label_kompass.Visible = !arryl.label_kompass.Visible;
        }

        private void button_tragtetstraffe_Click(object sender, EventArgs e)
        {
            panel_targetstraffe.Visible = !panel_targetstraffe.Visible;
            arryl.label_targetstraffe.Visible = !arryl.label_targetstraffe.Visible;
        }

        private void button_aimbot_h_Click(object sender, EventArgs e)
        {
            GetAimbotHotkey = true;
            button_aimbot_h.Text = "Press Key!";
        }

        private void button_entitydisplay_h_Click(object sender, EventArgs e)
        {
            GetEntitydisplayHotkey = true;
            button_entitydisplay_h.Text = "Press Key!";
        }

        private void button_kompass_h_Click(object sender, EventArgs e)
        {
            GetCompassHotkey = true;
            button_kompass_h.Text = "Press Key!";
        }

        private void button_targetstraffe_h_Click(object sender, EventArgs e)
        {
            GetTriggerbotHotkey = true;
            button_targetstraffe_h.Text = "Press Key!";
        }

        private void button_scaffold_Click_1(object sender, EventArgs e)
        {
            arryl.label_scaffold.Visible = !arryl.label_scaffold.Visible;
            panel_scaffold.Visible = !panel_scaffold.Visible;
        }

        //The Timer for the Aimbot :Y
        
        private void timer_aimbot_Tick(object sender, EventArgs e)
        {
            
        }

        private void trackBar_reach_Scroll(object sender, EventArgs e)
        {
            reach.set(trackBar_reach.Value);
        }
    }
}
