using System.Text.Json;

namespace EdtWebSockEDT;

public class MessageAnalyzer
{
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

        foreach (var key in json.Keys.Where(x => x != "animation").OrderBy(x => x).ToArray())
        {
            object? value = json[key] switch
            {
                JsonElement { ValueKind: JsonValueKind.String } @string => @string.GetString(),
                JsonElement { ValueKind: JsonValueKind.Number } number => number.GetInt32(),
                JsonElement { ValueKind: JsonValueKind.Array } array when array.GetArrayLength() > 0 => array switch
                {
                    _ when array[0].ValueKind == JsonValueKind.Number => array.Deserialize<int[]>(),
                    _ => array.Deserialize<string[]>()
                },
                _ => null
            };

            if (key.StartsWith("color") && value is int[] { Length: 3 } color)
            {
                colors.Add(new Color(color[0], color[1], color[2]));
            }

            if (key == "units" && value is string[] jsonUnits)
            {
                json.Remove("units");

                units.AddRange(jsonUnits);
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
}
