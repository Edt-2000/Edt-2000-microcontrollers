namespace Core.Midi;

public record ChannelMessage(int Index, UpdateType UpdateType, int Value);
