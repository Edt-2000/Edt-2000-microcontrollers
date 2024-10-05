using System.Text.Json;
using System.Text.Json.Serialization;

namespace EdtWebSockEDT;

public class MessageAnalyzer
{
    private readonly Dictionary<string, object> _previousMessage = new();

    public MessageAnalysis AnalyzeMessage(string type, string data)
    {
        if (type != Constants.WebSocketLed)
        {
            return new MessageAnalysis(data, [type], []);
        }

        var colors = new List<Color>();
        var units = new List<string>();

        var json = JsonSerializer.Deserialize<Dictionary<string, JsonElement>>(data);
        if (json == null)
        {
            return new MessageAnalysis(data, [], []);
        }

        foreach (var key in json.Keys.Where(x => x != "animation").ToArray())
        {
            object? value = json[key] switch
            {
                JsonElement { ValueKind: JsonValueKind.String } @string => @string.GetString(),
                JsonElement { ValueKind: JsonValueKind.Number } number => number.GetInt32(),
                JsonElement { ValueKind: JsonValueKind.Array } array => array.Deserialize<int[]>(),
                _ => null
            };

            if (value == null || (_previousMessage.TryGetValue(key, out var previousValue) && IsEqual(previousValue, value)))
            {
                json.Remove(key);
            }
            else
            {
                _previousMessage[key] = value;
            }

            if (key == "units" && value is int unit)
            {
                json.Remove("units");

                if (unit == 1 || unit == 3)
                {
                    units.Add("unit1");
                }
                if (unit == 2 || unit == 3)
                {
                    units.Add("unit2");
                }

                // TODO: this should be part of units
                units.Add("spectacle");
            }
        }

        var newMessage = JsonSerializer.Serialize(json);

        return new MessageAnalysis(newMessage, [.. units], [.. colors]);
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
        string[] UnitToSentTo,
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
