﻿using System.Text.Json;
using EdtWebSockEDT.Midi;

namespace EdtWebSockEDT;

public class MidiBackgroundService : BackgroundService
{
    private readonly Kontrol _kontrol = new();
    private readonly WebSocketHandler _webSocketHandler;
    private readonly SemaphoreSlim _semaphore = new(1);
    private readonly JsonSerializerOptions _options = new()
    {
        PropertyNamingPolicy = JsonNamingPolicy.CamelCase
    };

    public MidiBackgroundService(
        WebSocketHandler webSocketHandler)
    {
        _webSocketHandler = webSocketHandler;
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        var handler = HandleMidiMessageAsync;

        await _kontrol.InitAsync(handler);

        await Task.Delay(-1, stoppingToken);
    }

    private async Task HandleMidiMessageAsync(Channel[] states)
    {
        if (await _semaphore.WaitAsync(0))
        {
            var data = JsonSerializer.Serialize(states, _options);

            await _webSocketHandler.SendAsync("control", data);

            _semaphore.Release();
        }
    }
}