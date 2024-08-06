using System;

namespace EdtKontrol.Midi;

public class KontrolEventArgs : EventArgs
{
    internal KontrolEventArgs(int channel, ChannelState state)
    {
        Channel = channel;
        ChannelState = state;
    }

    public int Channel { get; set; }
    public ChannelState ChannelState { get; set; }
}
