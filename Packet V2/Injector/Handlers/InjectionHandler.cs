using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security.AccessControl;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PacketClient.Handlers
{
    internal class InjectionHandler
    {
        public static EventHandler<InjectEventArgs> injectionStagedEvent;

        #region DllImport

        [DllImport("kernel32.dll")]
        static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("kernel32", CharSet = CharSet.Ansi, ExactSpelling = true, SetLastError = true)]
        static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out UIntPtr lpNumberOfBytesWritten);

        [DllImport("kernel32.dll")]
        static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);

        #endregion

        #region Access

        const int PROCESS_CREATE_THREAD = 0x2;
        const int PROCESS_QUERY_INFORMATION = 0x400;
        const int PROCESS_VM_OPERATION = 0x8;
        const int PROCESS_VM_WRITE = 0x20;
        const int PROCESS_VM_READ = 0x10;

        const uint MEM_COMMIT = 0x1000;
        const uint MEM_RESERVE = 0x2000;
        const uint PAGE_READWRITE = 4;

        #endregion

        public static void InjectDLL(string path, string proc) // "Minecraft.Windows"
        {
            injectionStagedEvent.Invoke(null, new InjectEventArgs("Finding process"));
            Process[] targetProcessIndex = Process.GetProcessesByName(proc);
            if (targetProcessIndex.Length > 0)
            {
                injectionStagedEvent.Invoke(null, new InjectEventArgs("Applying packages"));
                applyAllApplicationPackages(path);

                Process targetProcess = Process.GetProcessesByName(proc)[0];
                IntPtr procHandle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, false, targetProcess.Id);

                IntPtr loadLibraryAddr = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

                IntPtr allocMemAddress = VirtualAllocEx(procHandle, IntPtr.Zero, (uint)((path.Length + 1) * Marshal.SizeOf(typeof(char))), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

                injectionStagedEvent.Invoke(null, new InjectEventArgs("Injecting"));
                UIntPtr bytesWritten;
                WriteProcessMemory(procHandle, allocMemAddress, Encoding.Default.GetBytes(path), (uint)((path.Length + 1) * Marshal.SizeOf(typeof(char))), out bytesWritten);
                CreateRemoteThread(procHandle, IntPtr.Zero, 0, loadLibraryAddr, allocMemAddress, 0, IntPtr.Zero);

                injectionStagedEvent.Invoke(null, new InjectEventArgs("Injected!"));
            }
            else
            {
                injectionStagedEvent.Invoke(null, new InjectEventArgs("No Minecraft Found (Is it open?)"));
            }
        }
        public static void applyAllApplicationPackages(string path)
        {
            FileInfo InfoFile = new FileInfo(path);
            FileSecurity fSecurity = InfoFile.GetAccessControl();
            fSecurity.AddAccessRule(new FileSystemAccessRule(new SecurityIdentifier("S-1-15-2-1"), FileSystemRights.FullControl, InheritanceFlags.None, PropagationFlags.NoPropagateInherit, AccessControlType.Allow));
            InfoFile.SetAccessControl(fSecurity);
        }
    }

    class InjectEventArgs : EventArgs
    {
        public string injectionStage;
        public InjectEventArgs(string injectionStage)
        {
            this.injectionStage = injectionStage;
        }
    }
}
