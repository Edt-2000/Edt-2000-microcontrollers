using System.Diagnostics;
using System.IO.Ports;
using EdtSpedtometer;


var currentTimestamp = Stopwatch.GetTimestamp();
var results = new List<TimeSpan>();

var sender = new WebSocketSender();
// var sender = new UdpSender();

await sender.InitializeAsync();

using var serial = new SerialPort("COM6", 115200, Parity.None, 8, StopBits.One);
serial.DataReceived += Serial_DataReceived;
serial.Open();

do
{
    var animation = new AnimationAndSettingsMessage("blink")
    {
        Brightness = 10,
        Color1 = (Random.Shared.Next(255), 255, 255),
        Color2 = (0, 255, 255)
    };

    currentTimestamp = Stopwatch.GetTimestamp();

    await sender.SendAsync(animation);

    await Task.Delay(1);
}
while (true);

void Serial_DataReceived(object sender, SerialDataReceivedEventArgs e)
{
    var delta = Stopwatch.GetElapsedTime(currentTimestamp);

    results.Add(delta);

    var data = results.Select(x => x.TotalMicroseconds);
    var average = data.Average();
    var sumOfSquaresOfDifferences = data.Select(val => (val - average) * (val - average)).Sum();
    var sd = Math.Sqrt(sumOfSquaresOfDifferences / results.Count);

    Console.WriteLine($"Took {delta}\t-\t{average:0}, {sd:0}");

    serial.ReadExisting();
}
