using iRacingSdkWrapper;
using iRacingSimulator;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimServerCLI
{
    class Program
    {
        static void Main(string[] args)
        {
            Sim.Instance.SessionInfoUpdated += OnSessionInfoUpdated;
            Sim.Instance.TelemetryUpdated += OnTelemetryUpdated;
            Sim.Instance.RaceEvent += OnRaceEvent;
            Sim.Instance.Start();

            Console.WriteLine("Press enter to quit");
            Console.ReadLine();
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
