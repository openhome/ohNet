using System;
using System.Net;

using Zapp;

    class Program
    {
        public static void Main(string[] args)
        {
            bool enabled = true;

            Soundcard soundcard = new Soundcard("TestSoundcard", 1, IPAddress.Any, 1, false, enabled);

            while (true)
            {
                ConsoleKeyInfo key = Console.ReadKey(true);

                if (key.KeyChar == 'q')
                {
                    break;
                }

                if (key.KeyChar == 'e')
                {
                    if (enabled)
                    {
                        enabled = false;
                        Console.WriteLine("Disabled");
                    }
                    else
                    {
                        enabled = true;
                        Console.WriteLine("Enabled");
                    }

                    soundcard.SetEnabled(enabled);
                    
                    continue;
                }
            }

            soundcard.Dispose();
        }
    }
