using HoI_Ultimate_Bravery.Classes;
using HoI_Ultimate_Bravery.Classes.Ideas;
using HoI_Ultimate_Bravery.Utils;
using System.Runtime.InteropServices;
using System.Text.Json;

namespace HoI_Ultimate_Bravery
{
    internal static class Program
    {
        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool AllocConsole();
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            AllocConsole();

            Mod vanilla = new Mod();
            Mod milleniumDawn = new Mod();

            vanilla.unitsType = UnitsType;

            Console.ReadLine();
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            // ApplicationConfiguration.Initialize();
            // Application.Run(new Form1());
        }
    }
}