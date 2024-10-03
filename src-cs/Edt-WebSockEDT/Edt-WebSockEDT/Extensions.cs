namespace EdtWebSockEDT;

public static class Extensions
{
    public static object ToMainframeMessage(this MessageAnalyzer.Color[] colors)
        => new
        {
            type = "fastLedMultiColor",
            payload = colors.Select(x => new { h = x.H, s = x.S, b = x.V }).ToArray()
        };

    public static T? GetElement<T>(this T[] values, int index)
    {
        if (values.Length == 0)
        {
            return default;
        }

        return values[index % values.Length];
    }
}
