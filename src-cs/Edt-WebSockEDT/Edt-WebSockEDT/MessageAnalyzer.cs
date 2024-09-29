using System.Text.Json;

namespace EdtWebSockEDT;

public class MessageAnalyzer
{
    private readonly Dictionary<string, object> _previousMessage = new();

    public MessageAnalysis AnalyzeMessage(string type, string data)
    {
        if (type != "led")
        {
            return new MessageAnalysis(data, []);
        }

        var json = JsonSerializer.Deserialize<Dictionary<string, JsonElement>>(data);
        if (json == null)
        {
            return new MessageAnalysis(data, []);
        }

        var colors = new List<(string, Color)>();

        foreach (var key in json.Keys.Where(x => x != "animation").ToArray())
        {
            object? value = json[key] switch
            {
                { ValueKind: JsonValueKind.String } @string => @string.GetString(),
                { ValueKind: JsonValueKind.Number } number => number.GetInt32(),
                { ValueKind: JsonValueKind.Array } array => array.Deserialize<int[]>(),
                _ => null
            };

            if (key.StartsWith("color") && value is int[] { Length: 3 } colorArray)
            {
                colors.Add((key, new Color(colorArray[0], colorArray[1], colorArray[2])));
            }

            if (value == null || (_previousMessage.TryGetValue(key, out var previousValue) && IsEqual(previousValue, value)))
            {
                json.Remove(key);
            }
            else
            {
                _previousMessage[key] = value;
            }
        }

        return new MessageAnalysis(data, [.. colors]);
    }

    private bool IsEqual(object a, object b)
        => (a, b) switch
        {
            (string string1, string string2) => string1.Equals(string2),
            (int int1, int int2) => int1 == int2,
            (IEnumerable<int> array1, IEnumerable<int> array2) => array1.SequenceEqual(array2),
            _ => false
        };

    public record MessageAnalysis(string MessageToSend, (string colorId, Color color)[] Colors);

    public record Color(int H, int S, int V);
}
