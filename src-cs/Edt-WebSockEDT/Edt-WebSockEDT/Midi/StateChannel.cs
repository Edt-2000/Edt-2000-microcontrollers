using System.Text.Json.Serialization;

namespace EdtWebSockEDT.Midi;

public class StateChannel : Channel
{
    [JsonPropertyName("i")]
    public int Intensity { get; set; }

    [JsonPropertyName("s")]
    public int Select { get; set; }

    [JsonPropertyName("bS")]
    public bool SPressed { get; set; }

    [JsonPropertyName("bM")]
    public bool MPressed { get; set; }

    [JsonPropertyName("bR")]
    public bool RPRessed { get; set; }

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
        return (SPressed ? Mode.One : 0)
            | (MPressed ? Mode.Two : 0)
            | (RPRessed ? Mode.Four : 0);
    }

    public override void SetMode(Mode mode)
    {
        if (mode == Mode.One)
        {
            SPressed = true;
        }
        if (mode == Mode.Two)
        {
            MPressed = true;
        }
        if (mode == Mode.Four)
        {
            RPRessed = true;
        }
    }

    public override void ButtonUp()
    {
        SPressed = false;
        MPressed = false;
        RPRessed = false;
    }
}
