using iRacingSdkWrapper;
using iRacingSimulator;
using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimServerCLI
{
    class Program
    {
        static void Main(string[] args)
        {
            CommTest();
            Console.WriteLine("Press enter to quit");
            Console.ReadLine();
        }

        private static void CommTest()
        {
            SerialPort sp = new SerialPort();
            sp.PortName = "COM3";
            sp.BaudRate = 9600;
            var toContinue = true;
            sp.Open();
            try
            {
                do
                {
                    Console.WriteLine("Enter Message");
                    var message = Console.ReadLine();
                    if (message.ToLower() == "q")
                    {
                        toContinue = false;
                    }
                    else
                    {
                        sp.WriteLine(message + "\n");
                    }
                } while (toContinue);
            }
            finally
            {
                sp.Close();
            }
        }

        private void SimTest()
        {
            Sim.Instance.SessionInfoUpdated += OnSessionInfoUpdated;
            Sim.Instance.TelemetryUpdated += OnTelemetryUpdated;
            Sim.Instance.RaceEvent += OnRaceEvent;
            Sim.Instance.Start();

        }

        private static void OnRaceEvent(object sender, Sim.RaceEventArgs e)
        {
            //throw new NotImplementedException();
        }

        private static void OnTelemetryUpdated(object sender, SdkWrapper.TelemetryUpdatedEventArgs e)
        {
            Console.WriteLine(e.TelemetryInfo.Speed);
        }

        private static void OnSessionInfoUpdated(object sender, SdkWrapper.SessionInfoUpdatedEventArgs e)
        {
            //throw new NotImplementedException();
        }
    }
}
