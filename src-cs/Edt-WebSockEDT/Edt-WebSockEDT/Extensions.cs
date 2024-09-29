using System.Text.Json;

namespace EdtWebSockEDT;

public static class Extensions
{
    public static string ToJson(this (string colorId, MessageAnalyzer.Color color)[] colors)
    {
        var message = colors.ToDictionary();
        return JsonSerializer.Serialize(message);
    }
}
