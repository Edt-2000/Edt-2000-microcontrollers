namespace EdtWebSockEDT;

public class WebSocketBackgroundService : BackgroundService
{
    private readonly WebSocketHandler _handler;

    public WebSocketBackgroundService(WebSocketHandler handler)
    {
        _handler = handler;
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        do
        {
            await _handler.MaintainWebSocketsAsync();

            await Task.Delay(1000, stoppingToken);
        }
        while (!stoppingToken.IsCancellationRequested);
    }
}
