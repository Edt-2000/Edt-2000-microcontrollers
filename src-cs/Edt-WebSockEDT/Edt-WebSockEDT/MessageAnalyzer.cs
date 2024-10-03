using System.Text.Json;
using System.Text.Json.Serialization;

namespace EdtWebSockEDT;

public class MessageAnalyzer
{
    private readonly Dictionary<string, object> _previousMessage = new();
    private readonly JsonSerializerOptions _jsonOptions = new JsonSerializerOptions
    {
        DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull
    };

    public MessageAnalysis AnalyzeMessage(string type, string data)
    {
        if (type != Constants.WebSocketLed)
        {
            return new MessageAnalysis(data, []);
        }

        var colors = new List<Color>();

        var message = JsonSerializer.Deserialize<Message>(data, _jsonOptions);
        if (message == null)
        {
            return new MessageAnalysis(data, []);
        }

        if (message.ColorSet is int[][] colorSet)
        {
            foreach (var color in colorSet)
            {
                colors.Add(new Color(color[0], color[1], color[2]));
            }

            if (message.ColorIndex is int colorIndex)
            {
                message.ExtraProperties["color1"] = message.ColorSet.GetElement(colorIndex);
                message.ExtraProperties["color2"] = message.ColorSet.GetElement(colorIndex + 1);

                message.ColorIndex = null;
            }

            message.ColorSet = null;
        }

        //var json = JsonSerializer.Deserialize<Dictionary<string, JsonElement>>(data);
        //if (json == null)
        //{
        //    return new MessageAnalysis(data, []);
        //}

        foreach (var key in message.ExtraProperties.Keys.ToArray())
        {
            // TODO: this should handle object too
            if (message.ExtraProperties[key] is JsonElement jsonElement)
            {
                object? value = jsonElement switch
                {
                    { ValueKind: JsonValueKind.String } @string => @string.GetString(),
                    { ValueKind: JsonValueKind.Number } number => number.GetInt32(),
                    { ValueKind: JsonValueKind.Array } array => array.Deserialize<int[][]>(),
                    _ => null
                };

                if (value == null || (_previousMessage.TryGetValue(key, out var previousValue) && IsEqual(previousValue, value)))
                {
                    message.ExtraProperties.Remove(key);
                }
                else
                {
                    _previousMessage[key] = value;
                }
            }
        }

        var newMessage = JsonSerializer.Serialize(message, _jsonOptions);

        return new MessageAnalysis(newMessage, [.. colors]);
    }

    private static bool IsEqual(object a, object b)
        => (a, b) switch
        {
            (string string1, string string2) => string1.Equals(string2),
            (int int1, int int2) => int1 == int2,
            (IEnumerable<int> array1, IEnumerable<int> array2) => array1.SequenceEqual(array2),
            _ => false
        };

    public record MessageAnalysis(
        string MessageToSend,
        Color[] Colors);

    public record Color(int H, int S, int V);

    public record Message
    {
        [JsonPropertyName("animation")]
        public string? Animation { get; set; }

        [JsonPropertyName("colorSet")]
        public int[][]? ColorSet { get; set; }

        [JsonPropertyName("colorIndex")]
        public int? ColorIndex { get; set; }

        [JsonExtensionData]
        public Dictionary<string, object?> ExtraProperties { get; set; } = [];
    }
}
