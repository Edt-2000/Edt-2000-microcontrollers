namespace Core.Midi;

public class StateChannel
{
    public int Intensity { get; private set; }

    public int Select { get; private set; }

    public bool SPressed { get; set; }

    public bool MPressed { get; set; }

    public bool RPressed { get; set; }

    public void SetIntensity(byte intensity)
    {
        Intensity = intensity;
    }

    public void SetSelect(int? absoluteSelect, int? delta)
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

    public Mode GetMode()
    {
        return (SPressed ? Mode.One : 0)
            | (MPressed ? Mode.Two : 0)
            | (RPressed ? Mode.Four : 0);
    }

    public void SetMode(Mode mode)
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
            RPressed = true;
        }
    }

    public void ButtonUp()
    {
        SPressed = false;
        MPressed = false;
        RPressed = false;
    }
}
