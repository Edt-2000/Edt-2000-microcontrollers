namespace EdtSpedtometer.Messaging;

internal record SettingsMessage
{
    public string? Text { get; init; }
    public Color? Color1 { get; init; }
    public Color? Color2 { get; init; }
    public Color? Color3 { get; init; }
    public Color? Color4 { get; init; }
    public Color? Color5 { get; init; }
    public int? Speed { get; init; }
    public int? Brightness { get; init; }
    public int? Size { get; init; }
}
