namespace EdtWebSockEDT;

public class StatusBackgroundService : BackgroundService
{
    private readonly StatusHandler _handler;

    public StatusBackgroundService(StatusHandler handler, WebSocketHandler webSocketHandler)
    {
        _handler = handler;
        _handler.Init(webSocketHandler);
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        do
        {
            _handler.SendStatus();

            await Task.Delay(1000, stoppingToken);
        }
        while (!stoppingToken.IsCancellationRequested);
    }
}
