namespace EdtWebSockEDT;

public static class Extensions
{
    public static object ToMainframeMessage(this (string colorId, MessageAnalyzer.Color color)[] colors)
    {
        /*
         * {
         *      "type": "colorPalette",
         *      "payload": [
         *          {
         *              "h": 0-255,
         *              "s": 0-255,
         *              "b": 0-255
         *          }
         *      ]
         * }
         * 
         * 
         */

        return new
        {
            type = "fastLedMultiColor",
            payload = colors.Select(x => new { h = x.color.H, s = x.color.S, b = x.color.V }).ToArray()
        };
    }
}
