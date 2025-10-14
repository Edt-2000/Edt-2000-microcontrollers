namespace Edt_DmxEDTitor;

public class Config
{
    public required Device[] Dmx { get; set; }

    public class Device
    {
        public required string Type { get; set; }
        public required int Address { get; set; }
        public int? MinimumBrightness { get; set; }
        public int? MaximumBrightness { get; set; }
    }
}
