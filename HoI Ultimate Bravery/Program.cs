using HoI_Ultimate_Bravery.Classes;
using HoI_Ultimate_Bravery.Utils;
using System.Text.Json;

namespace HoI_Ultimate_Bravery
{
    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            using var reader = new StreamReader("./Assets/Data/Files/Back-Up/ideas/GER.txt");
            Ideas result = ParadoxIdeasParser.ParseIdeas(reader);

            // Display as JSON for inspection
            // var json = JsonSerializer.Serialize(result, new JsonSerializerOptions { WriteIndented = true });
            Console.WriteLine("test");
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            Application.Run(new Form1());
        }
    }
}