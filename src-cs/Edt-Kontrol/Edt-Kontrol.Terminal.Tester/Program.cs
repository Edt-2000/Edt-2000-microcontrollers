using System.Net;
using Edt_Kontrol.OSC;

var sender = new UdpSender(IPAddress.Parse("10.0.0.99"), 12345);

do
{
    Console.WriteLine("Enter OSC message (/{address} {1 or more ints}: '/SP 123' ): ");

    try
    {
        var input = Console.ReadLine();

        if (!string.IsNullOrEmpty(input))
        {
            var chunks = input.Split(' ');

            if (chunks.Length > 1)
            {
                var address = chunks[0];

                var data = chunks[1..].Select(int.Parse).Cast<object>().ToArray();

                var message = new OscMessage(address, data);

                await sender.SendAsync(message);
            }
        }
    }
    catch (Exception ex)
    {
        Console.WriteLine(ex.Message);
    }
}
while (true);
