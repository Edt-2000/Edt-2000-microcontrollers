using System.Net.WebSockets;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
using Edt_DmxEDTitor;

var settings = new JsonSerializerOptions
{
    PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
    DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingDefault
};

do
{
    Console.WriteLine("Available files");
    Console.WriteLine();

    var files = Directory.EnumerateFiles("../../../Profiles").ToArray();

    for (var i = 0; i < files.Length; i++)
    {
        var file = Path.GetFileName(files[i]);

        if (file.StartsWith("_"))
        {
            continue;
        }

        Console.WriteLine($"[{i}]: {file}");
    }

    Console.WriteLine();
    Console.WriteLine("Load file:");

    var input = Console.ReadLine();
    var fileIndex = int.Parse(string.IsNullOrWhiteSpace(input) ? "0" : input.Trim());

    var jsonFile = File.ReadAllText(files[fileIndex]);

    var config = JsonSerializer.Deserialize<Config>(jsonFile, settings);

    var parsedJsonFile = JsonSerializer.Serialize(config, settings);
    var message = new ReadOnlyMemory<byte>(Encoding.UTF8.GetBytes(parsedJsonFile));

    using var ws = new ClientWebSocket();

    Console.WriteLine("Connecting..");

    await ws.ConnectAsync(new Uri("ws://10.0.0.50:80/ws"), default);

    await Task.Delay(2000);

    Console.WriteLine("Connected!");
    Console.WriteLine("Sending..");

    await ws.SendAsync(message, WebSocketMessageType.Text, true, default);

    Console.WriteLine("Sent!");
    Console.WriteLine();
}
while (true);

