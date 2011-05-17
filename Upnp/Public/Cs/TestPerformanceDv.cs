using System;
using Zapp.Core;
using Zapp.Device;

namespace Zapp.Device
{
    class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("TestPerformanceDvCs - starting ('q' to quit)");
            InitParams initParams = new InitParams();
            using (Library lib = Library.Create(initParams))
            {
                lib.StartDv();
                DeviceBasic device = new DeviceBasic();
                while (Console.ReadKey(true).KeyChar != 'q') ;
                device.Dispose();
            }
        }
    }
}
