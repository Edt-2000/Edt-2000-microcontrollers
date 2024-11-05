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
    text = null;
    font = 0;
    variant = 0;
    flashCount = 1;
    colors = [];
    brightness = 255;
    speed = 1;
}

class Presets {

    static items = [
        null,
        { 
            name: "meer power",
            channels: [
                Object.assign(new InvokerPreset(), {
                    channel: 0,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 155,
                    colors: [Colors.Red, Colors.White],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new ConfiguratorPreset(), {
                    channel: 3,
                    color: Colors.Red
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 0,
                    animation: "strobo",
                    title: "MEERPOWER strobo",
                    variant: 2,
                    flashCount: 1,
                    colors: [Colors.White],
                    brightness: "{modifier}",
                    speed: 200
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 1,
                    animation: "strobo",
                    title: "MEERPOWER text",
                    text: "MEER POWER",
                    variant: 4,
                    flashCount: 1,
                    colors: [Colors.White, Colors.Blue, Colors.Green],
                    brightness: "{modifier}",
                    speed: 240
                })
            ]
        },
        { 
            name: "code monkeys",
            channels: [
                Object.assign(new InvokerPreset(), {
                    channel: 0,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 211,
                    colors: [Colors.Green, Colors.White],
                    fade: Constants.FadeTypes.oneByOne
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 4,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 31,
                    repeat: 229,
                    colors: [Colors.Green, Colors.White],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 5,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 9,
                    repeat: 213,
                    colors: [Colors.Blue],
                    fade: Constants.FadeTypes.oneByOne
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 0,
                    animation: "glitchText",
                    title: "CODEMONKEYS",
                    text: "CODEMONKEYS",
                    variant: 1,
                    flashCount: 1,
                    colors: [Colors.Specific],
                    speed: 250
                })
            ]
        },
        {
            name: "binnen",
            channels: [
                Object.assign(new InvokerPreset(), {
                    channel: 2,
                    animation: Constants.AnimationTypes.strobo,
                    modifier: 213,
                    colors: [Colors.Rainbow]
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 5,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 177,
                    repeat: 189,
                    colors: [Colors.Yellow],
                    fade: Constants.FadeTypes.sparkle
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 0,
                    animation: "noise",
                    title: "BINNEN",
                    colors: [Colors.Yellow, Colors.Yellow, Colors.White],
                    speed: 30
                })
            ]
        }
    ]
};