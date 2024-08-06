open EdtKontrol.Midi
open System
open System.Threading
open System.Threading.Tasks
open System.Net.WebSockets
open System.Text
open System.Text.Json
open System.Text.Json.Serialization

let uri = new Uri("ws://10.0.0.25:80/ws")

let mutable states = [| 0;0;0;0;0;0;0;0; |]

type Color = (int * int * int)

type Message =
    { Animation: string option
      Color1: Color option
      Color2: Color option
      Color3: Color option
      Color4: Color option
      Color5: Color option
      Led: int option
      ColorIndex: int option
      Speed: int option
      Brightness: int option
      Size: int option }

let emptyMessage =
    { Animation = None
      Color1 = None
      Color2 = None
      Color3 = None
      Color4 = None
      Color5 = None
      Led = None
      ColorIndex = None
      Speed = None
      Brightness = None
      Size = None }

type ValueTupleConverter<'a>() = 
    inherit JsonConverter<'a * 'a * 'a>()

    override x.Read(reader: byref<Utf8JsonReader>, typeToConvert: Type, options: JsonSerializerOptions) = raise(new NotImplementedException())
    override x.Write(writer: Utf8JsonWriter, value: 'a * 'a * 'a, options: JsonSerializerOptions) =
        match value with 
        | (value1, value2, value3) -> JsonSerializer.Serialize<'a array>(writer, [| value1; value2; value3 |], options)

let settings =
    JsonSerializerOptions(
        DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull,
        WriteIndented = false,
        PropertyNamingPolicy = JsonNamingPolicy.CamelCase
    )
settings.Converters.Add(ValueTupleConverter<int>())

let sendMessage<'T> (client: ClientWebSocket) (message: 'T) =
    let json = JsonSerializer.Serialize(message, settings)
    let payload = Encoding.UTF8.GetBytes(json).AsMemory()

    task {
        try
            do! client.SendAsync(payload, WebSocketMessageType.Binary, true, CancellationToken.None)
        with _ -> ()
    }

let kontrol = new Kontrol()

let socket = new ClientWebSocket()

let sendSinglePulseMessage (client) (led, color, speed) =
    let message =
        { emptyMessage with
            Animation = Some("singlePulse")
            Color1 = Some(Color(color, 255, 255))
            Led = Some(led)
            Speed = Some(speed) }

    sendMessage client message

let sendSinglePulse (client) (channel, state: ChannelState) = 
    sendSinglePulseMessage client (channel, state.Select * 2, 255)

let handleChannel (client) (channel) =
    let task = 
        match channel with
        | 0 -> sendSinglePulse client (0, kontrol.Channels[channel])
        | 1 -> sendSinglePulse client (1, kontrol.Channels[channel])
        | _ -> Task.FromResult<unit>()
    task.Wait()

let handleKey (client) (key) =
    let task =
        match key with
        | ConsoleKey.Z -> sendSinglePulseMessage client (0, kontrol.Channels[7].Select * 2, kontrol.Channels[7].Intensity)
        | _ -> Task.FromResult<unit>()
    task.Wait()

let timeChannel (channel) (next) =
    if kontrol.Channels[channel].Intensity > 0 && states[channel] > (127 - kontrol.Channels[channel].IntensityLog) then
        next() |> ignore
        states[channel] <- 0
    else
        states[channel] <- states[channel] + 1

let keyTask (callback: ConsoleKey -> unit) =
    while true do
        let key = Console.ReadKey(true)

        callback key.Key

let initTask =
    task {
        do! kontrol.InitAsync()

        let handleChannel (channel) = timeChannel channel (fun () -> handleChannel socket channel)

        let timers = [
            new Timer((fun (_) -> handleChannel 0), None, 0, 10), 
            new Timer((fun (_) -> handleChannel 1), None, 0, 10)
        ]

        do! socket.ConnectAsync(uri, CancellationToken.None)

        do! Task.Run(fun () -> keyTask (handleKey socket))

        // do! Task.Delay(-1) |> Async.AwaitTask
    }

initTask |> Async.AwaitTask |> Async.RunSynchronously
