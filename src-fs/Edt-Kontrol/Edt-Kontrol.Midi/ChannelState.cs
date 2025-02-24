using System;

namespace EdtKontrol.Midi;

public struct ChannelState
{
    public Mode Mode { get; set; }
    public int Intensity { get; set; }
    public int IntensityLog => Log(Intensity);
    public int Select { get; set; }
    public int SelectLog => Log(Select);

    public int ButtonPresses { get; set; }

    private static int Log(int input)
    {
        return (int)(26.21 * Math.Log(input + 1));
    }
}
