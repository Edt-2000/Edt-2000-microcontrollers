using System.Text.Json.Serialization;

namespace EdtWebSockEDT.Midi;

[JsonDerivedType(typeof(RegularChannel))]
[JsonDerivedType(typeof(StateChannel))]
public abstract class Channel
{
    public abstract void SetIntensity(byte intensity);

    public abstract void SetSelect(int? absoluteSelect, int? delta);

    public abstract Mode GetMode();

    public abstract void SetMode(Mode mode);

    public abstract void ButtonUp();
}
