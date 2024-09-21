using System.Text.Json.Serialization;

namespace EdtWebSockEDT.Midi;

public class RegularChannel : Channel
{
    [JsonPropertyName("i")]
    public int Intensity { get; set; }

    [JsonPropertyName("s")]
    public int Select { get; set; }

    [JsonPropertyName("m")]
    public Mode Mode { get; set; }

    public override void SetIntensity(byte intensity)
    {
        Intensity = intensity;
    }

    public override void SetSelect(int? absoluteSelect, int? delta)
    {
        if (absoluteSelect.HasValue)
        {
            Select = absoluteSelect.Value;
        }
        else if (delta.HasValue)
        {
            Select += delta.Value;
        }

        Select = Math.Clamp(Select, 0, 127);
    }

    public override Mode GetMode()
    {
        return Mode;
    }

    public override void SetMode(Mode mode)
    {
        Mode = (Mode & mode) > 0 ? Mode & ~mode : Mode | mode;
    }

    public override void ButtonUp() { }
}
