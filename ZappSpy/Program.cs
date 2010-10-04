using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;

namespace ZappSpy
{
    class Program
    {
        static void Main(string[] args)
        {
            using (ZappLibraryWrapper library = new ZappLibraryWrapper())
            using (UpnpDeviceFinder finder = new UpnpDeviceFinder(library, "7076436f-6e65-1063-8074-001cc0c0e64e"))
            {
                Console.WriteLine("Searching for devices...");
                System.Threading.Thread.Sleep(3100);
                foreach (var device in finder.Devices)
                {
                    Console.WriteLine(device.FriendlyName);
                    foreach (var service in device.Services)
                    {
                        Console.WriteLine("    {0}", service.ServiceId);
                        Console.WriteLine("      Actions:");
                        foreach (var action in service.Description.Actions)
                        {
                            Console.WriteLine(
                                "        {0}({1})",
                                action.Name,
                                string.Join(", ", (from arg in action.Arguments select arg.DirectionAsString + " " + arg.Name).ToArray()));
                        }
                        Console.WriteLine("      State variables:");
                        foreach (var variable in service.Description.StateVariables)
                        {
                            Console.WriteLine(
                                "        {0} : {1} = (default) {2}",
                                variable.Name,
                                variable.DataType,
                                variable.DefaultValue??"<null>");
                        }
                    }
                    foreach (var subdevice in device.EmbeddedDevices)
                    {
                        Console.WriteLine("    EMBEDDED DEVICE: {0}", subdevice.FriendlyName);
                    }
                }
            }
            Console.ReadLine();
        }
    }
}

