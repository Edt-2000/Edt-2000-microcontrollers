class Preset {
    name = "";

    channels = [];
}

class ChannelPreset {
    channel = 0;
}

class InvokerPreset extends ChannelPreset {
    modifier = 0;
    speed = 0;
    animation = null;
    colors = [];
    fade = null;
}

class ConfiguratorPreset extends ChannelPreset {
    color = null;
    config = null;
}

class RepeaterPreset extends ChannelPreset {
    modifier = 0;
    repeat = 0;
    animation = null;
    colors = [];
    fade = null;
}

class SenderPreset extends ChannelPreset {
    index = 0;
    animation = null;
    title = null;
    texts = [];
    displayAllTexts = false;
    font = 0;
    variant = 0;
    flashCount = 1;
    colors = [];
    brightness = 255;
    speed = 1;
}
