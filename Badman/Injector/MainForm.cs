using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Security.AccessControl;
using System.Security.Principal;

namespace BadmanInjector
{
    public partial class MainForm : Form
    {
        [DllImport("kernel32.dll")]
        public static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("kernel32", CharSet = CharSet.Ansi, ExactSpelling = true, SetLastError = true)]
        static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress,
            uint dwSize, uint flAllocationType, uint flProtect);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out UIntPtr lpNumberOfBytesWritten);

        [DllImport("kernel32.dll")]
        static extern IntPtr CreateRemoteThread(IntPtr hProcess,
            IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);

        [System.Runtime.InteropServices.DllImport("wininet.dll")]
        private extern static bool InternetGetConnectedState(out int Description, int ReservedValue);

        public static bool OnlineCheck()
        {
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create("https://github.com/");
            request.Timeout = 15000;
            request.Method = "HEAD";
            try
            {
                using (HttpWebResponse response = (HttpWebResponse)request.GetResponse())
                {
                    return response.StatusCode == HttpStatusCode.OK;
                }
            }
            catch (WebException)
            {
                return false;
            }
        }
        public static bool InternetCheck()
        {
            int desc;
            bool internetcheckone = InternetGetConnectedState(out desc, 0);
            bool internetchecktwo = OnlineCheck();

            if (internetcheckone == true && internetchecktwo == true)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public static void applyAppPackages(string DLLPath)
        {
            FileInfo InfoFile = new FileInfo(DLLPath);
            FileSecurity fSecurity = InfoFile.GetAccessControl();
            fSecurity.AddAccessRule(new FileSystemAccessRule(new SecurityIdentifier("S-1-15-2-1"), FileSystemRights.FullControl, InheritanceFlags.None, PropagationFlags.NoPropagateInherit, AccessControlType.Allow));
            InfoFile.SetAccessControl(fSecurity);
        }

        private Color hoverTextColor = Color.FromArgb(62, 109, 181);

        public Color HoverTextColor
        {
            get => hoverTextColor;
            set => hoverTextColor = value;
        }

        private Color downTextColor = Color.FromArgb(25, 71, 138);

        public Color DownTextColor
        {
            get => downTextColor;
            set => downTextColor = value;
        }

        private Color hoverBackColor = Color.FromArgb(66, 66, 66);

        public Color HoverBackColor
        {
            get => hoverBackColor;
            set => hoverBackColor = value;
        }

        private Color downBackColor = Color.FromArgb(88, 88, 88);

        public Color DownBackColor
        {
            get => downBackColor;
            set => downBackColor = value;
        }

        private Color normalBackColor = Color.FromArgb(44, 44, 44);

        public Color NormalBackColor
        {
            get => normalBackColor;
            set => normalBackColor = value;
        }

        public enum MouseState
        {
            Normal,
            Hover,
            Down
        }

        protected void SetLabelColors(Control control, MouseState state)
        {
            if (!ContainsFocus)
            {
                return;
            }

            Color textColor = ActiveTextColor;
            Color backColor = NormalBackColor;

            switch (state)
            {
                case MouseState.Hover:
                    textColor = HoverTextColor;
                    backColor = HoverBackColor;
                    break;
                case MouseState.Down:
                    textColor = DownTextColor;
                    backColor = DownBackColor;
                    break;
            }

            control.ForeColor = textColor;
            control.BackColor = backColor;
        }

        protected void SetLabelBackgroundOnly(Control control, MouseState state)
        {
            if (!ContainsFocus)
            {
                return;
            }

            Color textColor = ActiveTextColor;
            Color backColor = NormalBackColor;

            switch (state)
            {
                case MouseState.Hover:
                    backColor = HoverBackColor;
                    break;
                case MouseState.Down:
                    backColor = DownBackColor;
                    break;
            }

            control.ForeColor = textColor;
            control.BackColor = backColor;
        }

        public MainForm()
        {
            InitializeComponent();

            Activated += MainForm_Activated;
            Deactivate += MainForm_Deactivate;

            foreach (Label control in new[] { HomePageTab, DevInjectPageTab, HelpPageTab, MinimizeLabel, CloseLabel })
            {
                control.MouseEnter += (s, e) => SetLabelColors((Control)s, MouseState.Hover);
                control.MouseLeave += (s, e) => SetLabelColors((Control)s, MouseState.Normal);
                control.MouseDown += (s, e) => SetLabelColors((Control)s, MouseState.Down);
            }

            foreach (Label control in new[] { InjectButton, LocateDllButton, InjectDllButton })
            {
                control.MouseEnter += (s, e) => SetLabelBackgroundOnly((Control)s, MouseState.Hover);
                control.MouseLeave += (s, e) => SetLabelBackgroundOnly((Control)s, MouseState.Normal);
                control.MouseDown += (s, e) => SetLabelBackgroundOnly((Control)s, MouseState.Down);
            }

            TitleLabel.Text = Text;
            TextChanged += (s, e) => TitleLabel.Text = Text;

            Font marlett = new Font("Marlett", 8.5f);

            MinimizeLabel.Font = marlett;
            CloseLabel.Font = marlett;

            Font InjectFontSize = new Font("Segoe UI", 15.5f);

            InjectButton.Font = InjectFontSize;

            CloseLabel.MouseClick += (s, e) => Close(e);
            InitialValues();
        }

        const int PROCESS_CREATE_THREAD = 0x0002;
        const int PROCESS_QUERY_INFORMATION = 0x0400;
        const int PROCESS_VM_OPERATION = 0x0008;
        const int PROCESS_VM_WRITE = 0x0020;
        const int PROCESS_VM_READ = 0x0010;

        // used for memory allocation
        const uint MEM_COMMIT = 0x00001000;
        const uint MEM_RESERVE = 0x00002000;
        const uint PAGE_READWRITE = 4;

        string DllPath;

        static bool alreadyAttemptedInject = false;
        private void InitialValues() // sets values needed first
        {
            ProgressBar.Width = 0;
        }


        public static void InjectDLL(string DownloadedDllFilePath, Control label, Control panel, Control Form1)//creates the function and the controls so it can modify values outside of it
        {
            Form1.Refresh(); // refreshes the form
            Process[] targetProcessIndex = Process.GetProcessesByName("Minecraft.Windows"); //gets the prosss from the prosseslisy
            if (targetProcessIndex.Length > 0) //if the prosses list is more then 0 it means its active
            {
                applyAppPackages(DownloadedDllFilePath); //runs the function apply app packeges allowing the dll to inject without administrater

                Process targetProcess = Process.GetProcessesByName("Minecraft.Windows")[0];//gets the prosses now that it knows minecraft is open
                IntPtr procHandle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, false, targetProcess.Id); // creates a handle so it can do shiz

                IntPtr loadLibraryAddr = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA"); //loads library a due to every app using it       this is how it actully injects

                IntPtr allocMemAddress = VirtualAllocEx(procHandle, IntPtr.Zero, (uint)((DownloadedDllFilePath.Length + 1) * Marshal.SizeOf(typeof(char))), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); //makes some space in the memory to hold the dll

                UIntPtr bytesWritten; // byteswritten value L
                WriteProcessMemory(procHandle, allocMemAddress, Encoding.Default.GetBytes(DownloadedDllFilePath), (uint)((DownloadedDllFilePath.Length + 1) * Marshal.SizeOf(typeof(char))), out bytesWritten); // basicly copys the dll to the memory that just got made
                CreateRemoteThread(procHandle, IntPtr.Zero, 0, loadLibraryAddr, allocMemAddress, 0, IntPtr.Zero); //loads the dll with dloadlibrarya into the prosses

                alreadyAttemptedInject = false; 

                label.Text = ("Injected Badman!"); // changes the text valuse so the user knows its done
                Form1.Refresh(); // refreshes the page so the user can see /|\
            }
            else
            {
                if (!alreadyAttemptedInject) // if its 0 and it has failed to inject then minecraft aint open
                {
                    alreadyAttemptedInject = true;
                    panel.Width = 0;
                    label.Text = "Error Injection Failed";
                    Form1.Refresh();
                    MessageBox.Show("Open Minecraft First Bro");
                }
                else // this means they a fking idiot and trying to idn inject it into minecraft java or smt
                {
                    panel.Width = 0;
                    label.Text = "Not Injected";
                    Form1.Refresh();
                    MessageBox.Show("You Kinda Need Minecraft Bedrock To Inject... idiot"); //stuped
                    alreadyAttemptedInject = false;
                }
            }
        }

        // start of window movement
        bool drag = false;
        Point start_point = new Point(0, 0);
        private void TitleLabel_MouseDown(object sender, MouseEventArgs e)
        {

            drag = true; //drag is your variable flag.
            start_point = new Point(e.X, e.Y);
        }

        private void TitleLabel_MouseMove(object sender, MouseEventArgs e)
        {
            if (drag)
            {
                Point p = PointToScreen(e.Location);
                this.Location = new Point(p.X - start_point.X, p.Y - start_point.Y);
            }
        }

        private void TitleLabel_MouseUp(object sender, MouseEventArgs e)
        {
            drag = false;
        }
        // end of window movement

        private void Close(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                Close(); //closes lol
            }
        }
        //button color shiz
        private Color activeBorderColor = Color.FromArgb(43, 87, 154);

        public Color ActiveBorderColor
        {
            get => activeBorderColor;
            set => activeBorderColor = value;
        }

        private Color inactiveBorderColor = Color.FromArgb(131, 131, 131);

        public Color InactiveBorderColor
        {
            get => inactiveBorderColor;
            set => inactiveBorderColor = value;
        }

        private void MainForm_Deactivate(object sender, EventArgs e)
        {
            SetBorderColor(InactiveBorderColor);
            SetTextColor(InactiveTextColor);
        }

        private void MainForm_Activated(object sender, EventArgs e)
        {
            SetBorderColor(ActiveBorderColor);
            SetTextColor(ActiveTextColor);
        }

        private Color activeTextColor = Color.FromArgb(255, 255, 255);

        public Color ActiveTextColor
        {
            get => activeTextColor;
            set => activeTextColor = value;
        }

        private Color inactiveTextColor = Color.FromArgb(177, 177, 177);

        public Color InactiveTextColor
        {
            get => inactiveTextColor;
            set => inactiveTextColor = value;
        }

        protected void SetBorderColor(Color color)
        {
            TopBorderPanel.BackColor = color;
            LeftBorderPanel.BackColor = color;
            RightBorderPanel.BackColor = color;
            BottomBorderPanel.BackColor = color;
        }

        protected void SetTextColor(Color color)
        {
            TitleLabel.ForeColor = color;
            MinimizeLabel.ForeColor = color;
            CloseLabel.ForeColor = color;
        }

        private DateTime titleClickTime = DateTime.MinValue;
        private Point titleClickPosition = Point.Empty;
        //button functions for changing the tabs
        private void HomePageTab_Click(object sender, EventArgs e)
        {
            TabControl.SelectedIndex = 0;  //home page
        }

        private void DevInjectPageTab_Click(object sender, EventArgs e)
        {
            TabControl.SelectedIndex = 1;  //Dev page
        }

        private void HelpPageTab_Click(object sender, EventArgs e)
        {
            TabControl.SelectedIndex = 2;  //Help page
        }
        //minimise lol
        private void MinimizeLabel_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }
        //inject lol
        private void InjectButton_Click(object sender, EventArgs e)
        {
            InjectButton.BackColor = Color.FromArgb(44, 44, 44);
            bool internet = InternetCheck();
            if (internet == true)
            {
                Process[] targetProcessIndex = Process.GetProcessesByName("Minecraft.Windows"); //gets the prosss from the prosseslisy
                if (targetProcessIndex.Length > 0) //if the prosses list is more then 0 it means its active
                {
                    string Title = "Badman Injector"; // sets the useragent's title
                    WebClient webClient = new WebClient(); // new webclient kinda self explanitory
                    webClient.Headers.Add(HttpRequestHeader.UserAgent, Title);
                    webClient.Proxy = null;
                    string DownloadUrl = ("https://github.com/BadMan-Client/BadMan-Releases/releases/latest/download/BadManPublic.dll"); // gets the dll 
                    string DownloadedDllFilePath = Path.GetTempPath() + "/BadManPublic.dll"; //gets the temp path and merges it with the dll name
                    startDownload(DownloadUrl, DownloadedDllFilePath); //runs the cool af download function
                }
                else
                {
                    ProgressBar.Width = 0;
                    Infolabel.Text = "Error, Injection Failed"; // you can probly understand this section fine
                    this.Refresh();
                    MessageBox.Show("Open Minecraft First BRO");
                }
            }
            else
            {
                ProgressBar.Width = 0;
                Infolabel.Text = "Error Injection Failed. No Internet"; // you can probly understand this section fine
                Refresh();
                MessageBox.Show("     Cannot Connect To Server\n       Check Your Connection");
            }
        }
        private void startDownload(string toDownload, string saveLocation) // starts the download loop on a new thread so the gui doesnt oof
        {
            Thread thread = new Thread(() =>
            {
                WebClient client = new WebClient();
                client.DownloadProgressChanged += new DownloadProgressChangedEventHandler(client_DownloadProgressChanged);
                client.DownloadFileCompleted += new AsyncCompletedEventHandler(client_DownloadFileCompleted);
                client.DownloadFileAsync(new Uri(toDownload), saveLocation);
            });
            thread.Start();
        }

        void client_DownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e) //runs every time the download has changed
        {
            this.BeginInvoke((MethodInvoker)delegate
            {
                double BytesDownloaded = double.Parse(e.BytesReceived.ToString()); // gets how much data has been downloaded
                double TotalBytes = double.Parse(e.TotalBytesToReceive.ToString());//gets total ammount
                double percentage = BytesDownloaded / TotalBytes * 100; //makes it divisible by 100 so it can be a %
                Infolabel.Text = "Downloading " + Convert.ToInt32(percentage) + "%  -  " + Convert.ToInt32(BytesDownloaded / 1024 / 1024) + " / " + Convert.ToInt32(TotalBytes / 1024 / 1024) + " mb"; //gets the %, ammount downloaded and ammount total rounded to mbs
                double PanelPercent = Math.Round(2.7 * percentage, 0); //takes 2.7 and multiplys it by the current %     devide the with *270 by *100 and plug it in if you ever change the %bar size
                ProgressBar.Width = int.Parse(Math.Truncate(PanelPercent).ToString()); // takes the value on the line above and makes the progress bar = to the current value
            });
        }

        void client_DownloadFileCompleted(object sender, AsyncCompletedEventArgs e)
        {
            this.BeginInvoke((MethodInvoker)delegate
            {
                InjectDLL(Path.GetTempPath() + "/BadManPublic.dll", Infolabel, ProgressBar, this); //runs the function inject dll with the temp path being merged with the dll name, the seccond will carry the lable over so the function can modify the labe, the third will bring the progress bar so it can change the with and lastly the "this" so it can do things like this.refresh();
            });
        }

        private void LocateDllButton_Click(object sender, EventArgs e)
        {
            LocateDllButton.BackColor = Color.FromArgb(44, 44, 44);
            OpenFileDialog FileIn = new OpenFileDialog();
            if (FileIn.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                if (FileIn.SafeFileName.ToLower().EndsWith(".dll"))
                {
                    DllPath = FileIn.FileName;
                    DevInfoText.Text = "Dll Selected";
                    Refresh();
                }
                else
                {
                    DevInfoText.Text = "No Dll Selected";
                    Refresh();
                }
            }
        }

        private void InjectDllButton_Click(object sender, EventArgs e)
        {
            InjectDllButton.BackColor = Color.FromArgb(44, 44, 44);
            InjectDLL(DllPath, this.DevInfoText, this.uselessthingjustneededfortheinjectfunction, this);
        }
    }
}
