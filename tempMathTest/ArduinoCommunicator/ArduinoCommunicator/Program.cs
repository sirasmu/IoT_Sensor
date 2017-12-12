using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Rssdp;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;

namespace ArduinoCommunicator
{
    class Program
    {
        static void Main(string[] args)
        {

            var ips = SearchForDevices("192.168.1.112", "upnp-dev:device:DistanceSensorWiFiClient").Result;
            foreach(var ip in ips)
                Console.WriteLine("{0}:{1}", ip.Address, ip.Port);


            var theip = ips.FirstOrDefault();
            int c = 0;
            while(theip != null)
            {
                using (TcpClient client = new TcpClient())
                {
                    client.Connect(theip);
                    using (StreamWriter writer = new StreamWriter(client.GetStream()))
                    {
                        writer.Write("Hello, World!");
                        writer.Flush();
                        using (StreamReader reader = new StreamReader(client.GetStream()))
                        {
                            string str = reader.ReadToEnd();
                            if (str.Contains('\n'))
                                throw new Exception();
                            Console.Write(str);
                        }
                        Console.WriteLine(c++);
                        //Console.ReadLine();
                    }
                }
            }
            Console.WriteLine("Done");
            Console.Read();
        }
        public static async Task<IEnumerable<IPEndPoint>> SearchForDevices(string localIp, string st)
        {
            using (var deviceLocator = new SsdpDeviceLocator(localIp))
            {
                var foundDevices = await deviceLocator.SearchAsync();
                return (await Task.WhenAll(foundDevices.Select(async dev =>
                {
                    IEnumerable<string> vals;
                    if (dev.ResponseHeaders.TryGetValues("ST", out vals) && vals.Contains(st))
                    {
                        IPAddress adr;
                        if (IPAddress.TryParse(dev.DescriptionLocation.Host, out adr))
                            return new IPEndPoint(adr, dev.DescriptionLocation.Port);
                        else
                        {
                            try
                            {
                                var ips = await Dns.GetHostAddressesAsync(dev.DescriptionLocation.Host);
                                if (ips.Length > 0)
                                    return new IPEndPoint(ips[0], dev.DescriptionLocation.Port);
                            }
                            catch (Exception)
                            { }
                        }
                    }
                    else if(vals != null)
                        Console.WriteLine(string.Join(" ", vals));
                    return null;
                }))).Where(ip => ip != null);
            }
        }
    }
}
