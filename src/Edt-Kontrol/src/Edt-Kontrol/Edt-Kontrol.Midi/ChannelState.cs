namespace Edt_Kontrol.Midi
{
    public struct ChannelState
    {
        public int Mode { get; set; }
        public int Intensity { get; set; }
        public int Select { get; set; }

        public int ButtonPresses { get; set; }
    }
}
