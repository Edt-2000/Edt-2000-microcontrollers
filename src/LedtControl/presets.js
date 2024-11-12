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
    textSplitPosition = 0;
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
                    channel: 4,
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
        },
        {
            name: "parttimepowerranger",
            channels: [
                Object.assign(new InvokerPreset(), {
                    channel: 2,
                    animation: Constants.AnimationTypes.strobo,
                    modifier: 213,
                    colors: [Colors.Rainbow]
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 4,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 51,
                    repeat: 213,
                    colors: [Colors.Rainbow],
                    fade: Constants.FadeTypes.pulse
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 0,
                    animation: "strobo",
                    title: "PARTTIME",
                    variant: 3,
                    flashCount: 2,
                    colors: [Colors.Rainbow],
                    speed: 255
                })
            ]
        },
        {
            name: "lava lava",
            channels: [
                Object.assign(new InvokerPreset(), {
                    channel: 2,
                    animation: Constants.AnimationTypes.fire,
                    modifier: 5
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 0,
                    animation: "fire",
                    title: "FIRE",
                    speed: 5,
                    brightness: "{modifier}",
                })
            ]
        },
        {
            name: "bek op asfalt",
            channels: [
                Object.assign(new RepeaterPreset(), {
                    channel: 4,
                    animation: Constants.AnimationTypes.allDoublePulse,
                    modifier: 75,
                    repeat: 23,
                    colors: [Colors.Turquoise, Colors.Pink],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 5,
                    animation: Constants.AnimationTypes.allSingleChaseLeft,
                    modifier: 255,
                    repeat: 111,
                    colors: [Colors.Turquoise, Colors.Pink],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 0,
                    animation: "scrollText",
                    title: "BEK OP ASFALT 1",
                    text: "ASFALTBEK",
                    textSplitPosition: 6,
                    variant: 2,
                    colors: [Colors.Blue, Colors.Pink, Colors.Red],
                    speed: 1000
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 1,
                    animation: "fadeText",
                    title: "BEK OP ASFALT 2",
                    text: "HARD VAN",
                    variant: 2,
                    colors: [Colors.Blue, Colors.Pink],
                    speed: 255
                })
            ]
        },
        {
            name: "cabrioletta",
            channels: [
                Object.assign(new RepeaterPreset(), {
                    channel: 4,
                    animation: Constants.AnimationTypes.allSingleChaseUp,
                    modifier: 81,
                    repeat: 151,
                    colors: [Colors.Red, Colors.White],
                    fade: Constants.FadeTypes.none
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 5,
                    animation: Constants.AnimationTypes.allSingleChaseDown,
                    modifier: 255,
                    repeat: 1,
                    colors: [Colors.Red],
                    fade: Constants.FadeTypes.pulse
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 0,
                    animation: "cabrio",
                    variant: 0,
                    title: "CABRIO 1",
                    colors: [Colors.Turquoise],
                    speed: 100
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 1,
                    animation: "cabrio",
                    variant: 1,
                    title: "CABRIO 2",
                    colors: [Colors.Yellow],
                    speed: 300
                })
            ]
        },
        {
            name: "schuren in de fik",
            channels: [
                Object.assign(new InvokerPreset(), {
                    channel: 0,
                    animation: Constants.AnimationTypes.allDoublePulse,
                    modifier: 107,
                    speed: 17,
                    colors: [Colors.Red, Colors.Blue],
                    fade: Constants.FadeTypes.sparkle
                }),
                Object.assign(new InvokerPreset(), {
                    channel: 2,
                    animation: Constants.AnimationTypes.strobo,
                    modifier: 237,
                    colors: [Colors.Red, Colors.Blue],
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 0,
                    animation: "strobo",
                    title: "SCHUREN",
                    variant: 1,
                    flashCount: 4,
                    colors: [Colors.Red, Colors.Blue],
                    speed: 240
                })
            ]
        },
        {
            name: "technokoning",
            channels: [
                Object.assign(new RepeaterPreset(), {
                    channel: 4,
                    animation: Constants.AnimationTypes.allSingleChaseRight,
                    modifier: 63,
                    repeat: 169,
                    colors: [Colors.Green],
                    fade: Constants.FadeTypes.sparkle
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 5,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 31,
                    repeat: 229,
                    colors: [Colors.Green, Colors.White],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new ConfiguratorPreset(), {
                    channel: 3,
                    config: "random-3"
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 0,
                    animation: "noise",
                    title: "TECHNOKONING",
                    colors: [Colors.Blue, Colors.Green, Colors.White],
                    brightness: 128,
                    speed: 32
                })
            ]
        },
        {
            name: "harder dan jij",
            channels: [
                Object.assign(new RepeaterPreset(), {
                    channel: 4,
                    animation: Constants.AnimationTypes.allSinglePulse,
                    modifier: 45,
                    repeat: 55,
                    colors: [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 5,
                    animation: Constants.AnimationTypes.allSinglePulse,
                    modifier: 175,
                    repeat: 100,
                    colors: [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime],
                    fade: Constants.FadeTypes.oneByOne
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 0,
                    animation: "strobo",
                    title: "HARDER",
                    text: "HARDER",
                    variant: 4,
                    colors: [Colors.Red],
                    speed: 1
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 1,
                    animation: "lsd",
                    title: "LSD"
                })
            ]
        },
        {
            name: "intens",
            channels: [
                Object.assign(new RepeaterPreset(), {
                    channel: 4,
                    animation: Constants.AnimationTypes.onePartialSinglePulse,
                    modifier: 65,
                    repeat: 179,
                    colors: [Colors.Orange],
                    fade: Constants.FadeTypes.oneByOne
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 5,
                    animation: Constants.AnimationTypes.onePartialSinglePulse,
                    modifier: 65,
                    repeat: 179,
                    colors: [Colors.Pink],
                    fade: Constants.FadeTypes.oneByOne
                }),
                Object.assign(new ConfiguratorPreset(), {
                    channel: 3,
                    config: "center-2"
                }),
                Object.assign(new InvokerPreset(), {
                    channel: 2,
                    animation: Constants.AnimationTypes.noise,
                    modifier: 69
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 0,
                    animation: "fadeText",
                    title: "INTENS 1",
                    text: "!!!!!!!!!",
                    font: 1,
                    variant: 1,
                    colors: [Colors.Orange, Colors.Pink],
                    speed: 32
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 1,
                    animation: "strobo",
                    title: "INTENS 2",
                    text: "VOEL NIKS",
                    variant: 4,
                    colors: [Colors.White],
                    speed: 245
                })
            ]
        },
        {
            name: "neuken",
            channels: [
                Object.assign(new InvokerPreset(), {
                    channel: 0,
                    animation: Constants.AnimationTypes.allSingleChaseLeft,
                    modifier: 45,
                    colors: [Colors.Pink],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new InvokerPreset(), {
                    channel: 2,
                    animation: Constants.AnimationTypes.strobo,
                    modifier: 128,
                    colors: [Colors.Pink],
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 1,
                    animation: "strobo",
                    title: "NEUKEN",
                    text: "NEUKEN",
                    variant: 4,
                    colors: [Colors.Pink],
                    speed: 245
                })
            ]
        },
        {
            name: "alles gejat",
            channels: []
        },
        {
            name: "poetin",
            channels: []
        },
        {
            name: "kermis/instaparty",
            channels: []
        },
        {
            name: "kerst",
            channels: [
                Object.assign(new RepeaterPreset(), {
                    channel: 4,
                    animation: Constants.AnimationTypes.allSingleChaseLeft,
                    modifier: 147,
                    repeat: 85,
                    colors: [Colors.Green],
                    fade: Constants.FadeTypes.none
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 5,
                    animation: Constants.AnimationTypes.allSinglePulse,
                    modifier: 161,
                    repeat: 123,
                    colors: [Colors.Red],
                    fade: Constants.FadeTypes.none
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 0,
                    animation: "strobo",
                    title: "KERST 1",
                    variant: 1,
                    flashCount: 1,
                    colors: [Colors.Red, Colors.Green],
                    speed: 245
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 1,
                    animation: "glitchText",
                    title: "KERST 2",
                    text: "STROBOCOPS",
                    textSplitPosition: 6,
                    variant: 2,
                    colors: [Colors.Red, Colors.Green, Colors.White],
                    speed: 50
                })
            ]
        }
    ]
};