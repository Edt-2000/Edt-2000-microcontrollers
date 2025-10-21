using System.Collections.Concurrent;
using System.Text.Json;
using System.Text.Json.Serialization;
using Core;
using EdtWebSockEDT.Status;

namespace EdtWebSockEDT;

public class StatusHandler : IStatusReporter
{
    private readonly ConcurrentDictionary<string, DateTime> _devices = new();
    private WebSocketHandler? _webSocketHandler;
    private readonly JsonSerializerOptions _options = new()
    {
        PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
        Converters =
        {
            new JsonStringEnumConverter(JsonNamingPolicy.CamelCase)
        }
    };

    public void Init(WebSocketHandler webSocketHandler)
    {
        _webSocketHandler = webSocketHandler;
    }

    public void ReportStatus(string device, bool isOk)
    {
        _devices[device] = isOk ? DateTime.UtcNow : DateTime.MinValue;
    }

    public void SendStatus()
    {
        var message = new StatusMessage(_devices.ToDictionary(x => x.Key, x => x.Value switch
        {
            _ when x.Value == DateTime.MinValue => StatusType.Failed,
            _ when x.Value < DateTime.UtcNow.AddSeconds(-30) => StatusType.Warning,
            _ => StatusType.Ok
        }));

        var data = JsonSerializer.Serialize(message, _options);
        _webSocketHandler?.Send(Constants.WebSocketControl, data);
    }
}
