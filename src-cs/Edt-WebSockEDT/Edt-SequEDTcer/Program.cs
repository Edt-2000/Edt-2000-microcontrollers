using System.Threading.Channels;
using Core.Midi;
using Edt_SequEDTcer;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;

var builder = new HostApplicationBuilder();

builder.Services.AddSingleton(new Kontrol(new NullReporter()));

builder.Services.AddHostedService<MidiBackgroundService>();

var channel = Channel.CreateUnbounded<Message>();

builder.Services.AddSingleton(channel.Reader);
builder.Services.AddSingleton(channel.Writer);

builder.Services.AddHostedService<SenderService>();

var app = builder.Build();
await app.RunAsync();
