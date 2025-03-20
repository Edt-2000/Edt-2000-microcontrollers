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

class Presets {
    static items = [
        null,
        {
            name: "meer power",
            description: "donker beginnen - langzaam Z - daarna X | Strobeled | Powerbar brightness 0 -> 255",
            channels: [
                Object.assign(new InvokerPreset(), {
                    channel: 0,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 155,
                    colors: [Colors.Red, Colors.White],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new InvokerPreset(), {
                    channel: 1,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 155,
                    colors: [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime],
                    fade: Constants.FadeTypes.oneByOne
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
                    speed: "{speed}",
                    //speed: 255
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 1,
                    animation: "strobo",
                    title: "MEERPOWER text",
                    texts: ["MEER POWER"],
                    variant: 4,
                    flashCount: 1,
                    colors: [Colors.White, Colors.Blue, Colors.Green],
                    brightness: "{modifier}",
                    speed: 240
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 4,
                    animation: "strobo",
                    title: "MEERPOWER strobo",
                    colors: [Colors.White],
                    brightness: "{modifier}",
                    speed: "{speed}"
                }),
                // strobo op en neer
            ]
        },
        {
            name: "parttimepowerranger",
            description: "Channel 0 + 1 partial pulses | Repeater 4 = flash slow / Repeater 5 = flash fast | Repeater 6 + 7 = chases | Strobeled hero moment",
            channels: [
                Object.assign(new InvokerPreset(), {
                    channel: 0,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 250,
                    colors: [Colors.Red, Colors.Yellow, Colors.Blue, Colors.Pink],
                    fade: Constants.FadeTypes.oneByOne
                }),
                Object.assign(new InvokerPreset(), {
                    channel: 1,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 250,
                    colors: [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime],
                    fade: Constants.FadeTypes.oneByOne
                }),
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
                Object.assign(new RepeaterPreset(), {
                    channel: 5,
                    animation: Constants.AnimationTypes.allDoublePulse,
                    modifier: 51,
                    repeat: 213,
                    colors: [Colors.Rainbow],
                    fade: Constants.FadeTypes.pulse
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 6,
                    animation: Constants.AnimationTypes.allSingleChaseLeft,
                    modifier: 125,
                    repeat: 125,
                    colors: [Colors.Red, Colors.Yellow, Colors.Blue, Colors.Pink],
                    fade: Constants.FadeTypes.pulse
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 7,
                    animation: Constants.AnimationTypes.allSingleChaseRight,
                    modifier: 125,
                    repeat: 125,
                    colors: [Colors.Red, Colors.Yellow, Colors.Blue, Colors.Pink],
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
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 1,
                    animation: "strobo",
                    title: "PARTTIME",
                    texts: ["PARTTIME", "POWERRANGER"], // part + time / power + ranger 
                    variant: 4,
                    flashCount: 10,
                    colors: [Colors.Specific, Colors.Rainbow],
                    speed: 250
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 4,
                    animation: "singlePulse",
                    title: "Red",
                    colors: [Colors.Red],
                    brightness: 255,
                    speed: 65,
                    fade: 1
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 5,
                    animation: "singlePulse",
                    title: "Black",
                    colors: [Colors.White],
                    brightness: 255,
                    speed: 65,
                    fade: 1
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 6,
                    animation: "singlePulse",
                    title: "Yellow",
                    colors: [Colors.Yellow],
                    brightness: 255,
                    speed: 65,
                    fade: 1
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 7,
                    animation: "singlePulse",
                    title: "Pink",
                    colors: [Colors.Pink],
                    brightness: 255,
                    speed: 65,
                    fade: 1
                }),
            ]
        },
        {
            name: "binnen",
            description: "` tijdens tellen | repeater 4 = constant | repeater 5 = stress | repeater 6 + 7 = chases | Strobeled aan | Powerbar aan",
            channels: [
                Object.assign(new InvokerPreset(), {
                    channel: 0,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 250,
                    colors: [Colors.Red, Colors.Yellow, Colors.Blue, Colors.Pink],
                    fade: Constants.FadeTypes.oneByOne
                }),
                Object.assign(new InvokerPreset(), {
                    channel: 1,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 250,
                    colors: [Colors.Yellow],
                    fade: Constants.FadeTypes.sparkle
                }),
                Object.assign(new InvokerPreset(), {
                    channel: 2,
                    animation: Constants.AnimationTypes.strobo,
                    modifier: 239,
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
                Object.assign(new RepeaterPreset(), {
                    channel: 5,
                    animation: Constants.AnimationTypes.allDoublePulse,
                    modifier: 51,
                    repeat: 213,
                    colors: [Colors.Yellow],
                    fade: Constants.FadeTypes.sparkle
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 6,
                    animation: Constants.AnimationTypes.allDoubleChaseDown,
                    modifier: 125,
                    repeat: 125,
                    colors: [Colors.Yellow],
                    fade: Constants.FadeTypes.sparkle
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 7,
                    animation: Constants.AnimationTypes.allDoubleChaseUp,
                    modifier: 125,
                    repeat: 125,
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
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 4,
                    animation: "strobo",
                    title: "FLASH",
                    colors: [Colors.White],
                    speed: 1
                })
            ]
        },
        {
            name: "schuren in de fik",
            description: "Z tijdens couplet | strobo + channel 2 M + powerbar strobe | X afwisseling | Strobeled aan",
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
                    channel: 1,
                    animation: Constants.AnimationTypes.allSinglePulse,
                    modifier: 107,
                    speed: 17,
                    colors: [Colors.Red, Colors.Blue],
                    fade: Constants.FadeTypes.fadeAll
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
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 4,
                    animation: "strobo",
                    title: "STROBO",
                    colors: [Colors.White],
                    speed: 220
                })
            ]
        },
        {
            name: "neuken",
            description: "Repeat 6 + 7 = bounce | Repeat 4 + 5 = up down | Strobo | Strobeled aan | Powerbar aan",
            channels: [
                Object.assign(new InvokerPreset(), {
                    channel: 0,
                    animation: Constants.AnimationTypes.allSingleChaseLeft,
                    modifier: 45,
                    colors: [Colors.Pink],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new InvokerPreset(), {
                    channel: 1,
                    animation: Constants.AnimationTypes.allSingleChaseRight,
                    modifier: 45,
                    colors: [Colors.Pink],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new InvokerPreset(), {
                    channel: 2,
                    animation: Constants.AnimationTypes.strobo,
                    modifier: 238,
                    colors: [Colors.Pink],
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 4,
                    animation: Constants.AnimationTypes.allSingleChaseDown,
                    modifier: 143,
                    repeat: 145,
                    colors: [Colors.Pink],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 5,
                    animation: Constants.AnimationTypes.allSingleChaseUp,
                    modifier: 143,
                    repeat: 145,
                    colors: [Colors.Pink],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 6,
                    animation: Constants.AnimationTypes.allSingleChaseLeft,
                    modifier: 143,
                    repeat: 45,
                    colors: [Colors.Pink],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 7,
                    animation: Constants.AnimationTypes.allSingleChaseRight,
                    modifier: 143,
                    repeat: 45,
                    colors: [Colors.Pink],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 0,
                    animation: "strobo",
                    title: "NEUKEN",
                    texts: ["NEUKEN"],
                    variant: 4,
                    colors: [Colors.Pink],
                    speed: 245
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 4,
                    animation: "strobo",
                    title: "STROBO",
                    colors: [Colors.Pink],
                    speed: 220
                })
            ]
        },
        {
            name: "poetin",
            description: "Repeater 4 = stress | Repeater 5 = champignon | Repeater 6 + 7 = bounce | Strobeled strobo | Powerbar LSD",
            channels: [
                Object.assign(new InvokerPreset(), {
                    channel: 0,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 250,
                    colors: [Colors.Red, Colors.Orange, Colors.Yellow, Colors.Lime, Colors.Green, Colors.SeaGreen, Colors.Turquoise, Colors.Blue, Colors.Purple, Colors.Pink],
                    fade: Constants.FadeTypes.oneByOne
                }),
                Object.assign(new InvokerPreset(), {
                    channel: 1,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 250,
                    colors: [Colors.Rainbow],
                    fade: Constants.FadeTypes.oneByOne
                }),
                Object.assign(new InvokerPreset(), {
                    channel: 2,
                    animation: Constants.AnimationTypes.strobo,
                    modifier: 238,
                    colors: [Colors.Rainbow],
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 4,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 193,
                    repeat: 243,
                    colors: [Colors.Red, Colors.Orange, Colors.Yellow, Colors.Lime, Colors.Green, Colors.SeaGreen, Colors.Turquoise, Colors.Blue, Colors.Purple, Colors.Pink],
                    fade: Constants.FadeTypes.pulse
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 5,
                    animation: Constants.AnimationTypes.allPartialSinglePulse,
                    modifier: 41,
                    repeat: 197,
                    colors: [Colors.Red, Colors.Orange, Colors.Yellow, Colors.Lime, Colors.Green, Colors.SeaGreen, Colors.Turquoise, Colors.Blue, Colors.Purple, Colors.Pink],
                    fade: Constants.FadeTypes.fadeAll
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 6,
                    animation: Constants.AnimationTypes.allSingleChaseLeft,
                    modifier: 143,
                    repeat: 45,
                    colors: [Colors.Rainbow],
                    fade: Constants.FadeTypes.pulse
                }),
                Object.assign(new RepeaterPreset(), {
                    channel: 7,
                    animation: Constants.AnimationTypes.allSingleChaseRight,
                    modifier: 143,
                    repeat: 45,
                    colors: [Colors.Rainbow],
                    fade: Constants.FadeTypes.pulse
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 0,
                    animation: "lsd",
                    title: "LSD"
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 1,
                    animation: "strobo",
                    title: "STROBO",
                    colors: [Colors.Rainbow],
                    speed: 220
                }),
                Object.assign(new SenderPreset(), {
                    channel: 1,
                    index: 4,
                    animation: "strobo",
                    title: "STROBO",
                    colors: [Colors.Rainbow],
                    speed: 220
                })
            ]
        },
    ]
};

// class Presets {
//     static items = [
//         null,
//         {
//             name: "meer power",
//             description: "donker beginnen - langzaam Z - daarna X",
//             channels: [
//                 Object.assign(new InvokerPreset(), {
//                     channel: 0,
//                     animation: Constants.AnimationTypes.allPartialSinglePulse,
//                     modifier: 155,
//                     colors: [Colors.Red, Colors.White],
//                     fade: Constants.FadeTypes.fadeAll
//                 }),
//                 Object.assign(new InvokerPreset(), {
//                     channel: 1,
//                     animation: Constants.AnimationTypes.allPartialSinglePulse,
//                     modifier: 155,
//                     colors: [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime],
//                     fade: Constants.FadeTypes.oneByOne
//                 }),
//                 Object.assign(new ConfiguratorPreset(), {
//                     channel: 3,
//                     color: Colors.Red
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "strobo",
//                     title: "MEERPOWER strobo",
//                     variant: 2,
//                     flashCount: 1,
//                     colors: [Colors.White],
//                     brightness: "{modifier}",
//                     speed: "{speed}",
//                     //speed: 255
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 1,
//                     animation: "strobo",
//                     title: "MEERPOWER text",
//                     texts: ["MEER POWER"],
//                     variant: 4,
//                     flashCount: 1,
//                     colors: [Colors.White, Colors.Blue, Colors.Green],
//                     brightness: "{modifier}",
//                     speed: 240
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "strobo",
//                     title: "MEERPOWER strobo",
//                     colors: [Colors.White],
//                     brightness: 255,// "{modifier}",
//                     speed: 192, // "{speed}",
//                     //speed: 255
//                 }),
//                 // strobo op en neer
//             ]
//         },
//         {
//             name: "code monkeys",
//             description: "",
//             channels: [
//                 Object.assign(new InvokerPreset(), {
//                     channel: 0,
//                     animation: Constants.AnimationTypes.allPartialSinglePulse,
//                     modifier: 211,
//                     colors: [Colors.Green, Colors.White],
//                     fade: Constants.FadeTypes.oneByOne
//                 }),
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 4,
//                     animation: Constants.AnimationTypes.allPartialSinglePulse,
//                     modifier: 31,
//                     repeat: 229,
//                     colors: [Colors.Green, Colors.White],
//                     fade: Constants.FadeTypes.fadeAll
//                 }),
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 5,
//                     animation: Constants.AnimationTypes.allPartialSinglePulse,
//                     modifier: 9,
//                     repeat: 213,
//                     colors: [Colors.Blue],
//                     fade: Constants.FadeTypes.oneByOne
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "glitchText",
//                     title: "CODEMONKEYS",
//                     texts: ["CODEMONKEYS"],
//                     variant: 1,
//                     flashCount: 1,
//                     colors: [Colors.Specific],
//                     speed: 250
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 1,
//                     animation: "fadeText",
//                     title: "DANCE",
//                     texts: ["DANCE"],
//                     variant: 3,
//                     colors: [Colors.Specific],
//                     speed: 91 // TODO
//                 })
//                 // dance in code monkey kleuren
//             ]
//         },
            // {
            //     name: "cabrioletta",
            //     description: "Repeater 4 = tijdens alles | Repeater 5 = tijdens gas (100 - 255) | Z = tijdens cabrioletta | Strobeled tijdens gas | Powerbar tijdens couplet + hero moment",
            //     channels: [
            //         Object.assign(new InvokerPreset(), {
            //             channel: 0,
            //             animation: Constants.AnimationTypes.allSinglePulse,
            //             modifier: 128,
            //             colors: [Colors.Red],
            //             fade: Constants.FadeTypes.oneByOne
            //         }),
            //         Object.assign(new RepeaterPreset(), {
            //             channel: 4,
            //             animation: Constants.AnimationTypes.allSingleChaseUp,
            //             modifier: 81,
            //             repeat: 151,
            //             colors: [Colors.Red, Colors.White],
            //             fade: Constants.FadeTypes.none
            //         }),
            //         Object.assign(new RepeaterPreset(), {
            //             channel: 5,
            //             animation: Constants.AnimationTypes.allSingleChaseDown,
            //             modifier: 100,
            //             repeat: 1,
            //             colors: [Colors.Red],
            //             fade: Constants.FadeTypes.pulse
            //         }),
            //         Object.assign(new SenderPreset(), {
            //             channel: 1,
            //             index: 0,
            //             animation: "cabrio",
            //             variant: 0,
            //             title: "CABRIO 1",
            //             colors: [Colors.Orange],
            //             speed: 100
            //         }),
            //         Object.assign(new SenderPreset(), {
            //             channel: 1,
            //             index: 1,
            //             animation: "cabrio",
            //             variant: 1,
            //             title: "CABRIO 2",
            //             colors: [Colors.SeaGreen],
            //             speed: 300
            //         }),
            //         Object.assign(new SenderPreset(), {
            //             channel: 1,
            //             index: 4,
            //             animation: "doublePulse",
            //             title: "Red",
            //             colors: [Colors.Red, Colors.Black],
            //             percentage: 20,
            //             speed: 0
            //         }),
            //         Object.assign(new SenderPreset(), {
            //             channel: 1,
            //             index: 5,
            //             animation: "doublePulse",
            //             title: "Red",
            //             colors: [Colors.Red, Colors.Black],
            //             percentage: 40,
            //             speed: 0
            //         }),
            //         Object.assign(new SenderPreset(), {
            //             channel: 1,
            //             index: 6,
            //             animation: "doublePulse",
            //             title: "Red",
            //             colors: [Colors.Red, Colors.Black],
            //             percentage: 80,
            //             speed: 0
            //         }),
            //         Object.assign(new SenderPreset(), {
            //             channel: 1,
            //             index: 7,
            //             animation: "doublePulse",
            //             title: "Red",
            //             colors: [Colors.Red, Colors.Black],
            //             percentage: 127,
            //             speed: 0,
            //         }),
            //     ]
            // },
//         {
//             name: "binnen",
//             description: "",
//             channels: [
//                 Object.assign(new InvokerPreset(), {
//                     channel: 2,
//                     animation: Constants.AnimationTypes.strobo,
//                     modifier: 213,
//                     colors: [Colors.Rainbow]
//                 }),
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 4,
//                     animation: Constants.AnimationTypes.allPartialSinglePulse,
//                     modifier: 177,
//                     repeat: 189,
//                     colors: [Colors.Yellow],
//                     fade: Constants.FadeTypes.sparkle
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "noise",
//                     title: "BINNEN",
//                     colors: [Colors.Yellow, Colors.Yellow, Colors.White],
//                     speed: 30
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "strobo",
//                     title: "FLASH",
//                     colors: [Colors.White],
//                     speed: 1
//                 })
//             ]
//         },
//         {
//             name: "parttimepowerranger",
//             description: "",
//             channels: [
//                 Object.assign(new InvokerPreset(), {
//                     channel: 2,
//                     animation: Constants.AnimationTypes.strobo,
//                     modifier: 213,
//                     colors: [Colors.Rainbow]
//                 }),
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 4,
//                     animation: Constants.AnimationTypes.allPartialSinglePulse,
//                     modifier: 51,
//                     repeat: 213,
//                     colors: [Colors.Rainbow],
//                     fade: Constants.FadeTypes.pulse
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "strobo",
//                     title: "PARTTIME",
//                     variant: 3,
//                     flashCount: 2,
//                     colors: [Colors.Rainbow],
//                     speed: 255
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 1,
//                     animation: "strobo",
//                     title: "PARTTIME",
//                     texts: ["PARTTIME", "POWERRANGER"], // part + time / power + ranger
//                     variant: 4,
//                     flashCount: 10,
//                     colors: [Colors.Specific, Colors.Rainbow],
//                     speed: 250
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "singlePulse",
//                     title: "Red",
//                     colors: [Colors.Red],
//                     brightness: 255,// "{modifier}",
//                     speed: 65, // "{speed}",
//                     fade: 1
//                     //speed: 255
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 5,
//                     animation: "singlePulse",
//                     title: "Black",
//                     colors: [Colors.White],
//                     brightness: 255,// "{modifier}",
//                     speed: 65, // "{speed}",
//                     fade: 1
//                     //speed: 255
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 6,
//                     animation: "singlePulse",
//                     title: "Yellow",
//                     colors: [Colors.Yellow],
//                     brightness: 255,// "{modifier}",
//                     speed: 65, // "{speed}",
//                     fade: 1
//                     //speed: 255
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 7,
//                     animation: "singlePulse",
//                     title: "Pink",
//                     colors: [Colors.Pink],
//                     brightness: 255,// "{modifier}",
//                     speed: 65, // "{speed}",
//                     fade: 1
//                     //speed: 255
//                 }),
//             ]
//         },
//         {
//             name: "lava lava",
//             description: "",
//             channels: [
//                 Object.assign(new InvokerPreset(), {
//                     channel: 2,
//                     animation: Constants.AnimationTypes.fire,
//                     modifier: 5
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "fire",
//                     title: "FIRE",
//                     speed: 5,
//                     brightness: "{modifier}", // TODO max 1/3
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "fire",
//                     title: "FIRE",
//                     speed: 5,
//                     brightness: "{modifier}", // TODO max 1/3
//                 })
//             ]
//         },
//         {
//             name: "bek op asfalt",
//             description: "",
//             channels: [
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 4,
//                     animation: Constants.AnimationTypes.allDoublePulse,
//                     modifier: 75,
//                     repeat: 23,
//                     colors: [Colors.Turquoise, Colors.Pink],
//                     fade: Constants.FadeTypes.fadeAll
//                 }),
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 5,
//                     animation: Constants.AnimationTypes.allSingleChaseLeft,
//                     modifier: 255,
//                     repeat: 111,
//                     colors: [Colors.Turquoise, Colors.Pink],
//                     fade: Constants.FadeTypes.fadeAll
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "scrollText",
//                     title: "BEK OP ASFALT 1",
//                     texts: ["BEK", "ASFALT", "HARD VAN"],
//                     variant: 2,
//                     colors: [Colors.Pink, Colors.Blue, Colors.Red], // 1 extra kleur
//                     speed: 100
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 1,
//                     animation: "fadeText",
//                     title: "BEK OP ASFALT 2",
//                     texts: ["HARD", "VAN"],
//                     variant: 2,
//                     colors: [Colors.Blue, Colors.Pink],
//                     speed: 255
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "singlePulse",
//                     title: "Red",
//                     colors: [Colors.Red],
//                     brightness: 255,
//                     speed: 64,
//                     fade: 1
//                     //speed: 255
//                 }),
//             ]
//         },
//         {
//             name: "cabrioletta",
//             description: "",
//             channels: [
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 4,
//                     animation: Constants.AnimationTypes.allSingleChaseUp,
//                     modifier: 81,
//                     repeat: 151,
//                     colors: [Colors.Red, Colors.White],
//                     fade: Constants.FadeTypes.none
//                 }),
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 5,
//                     animation: Constants.AnimationTypes.allSingleChaseDown,
//                     modifier: 255,
//                     repeat: 1,
//                     colors: [Colors.Red],
//                     fade: Constants.FadeTypes.pulse
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "cabrio",
//                     variant: 0,
//                     title: "CABRIO 1",
//                     colors: [Colors.Orange],
//                     speed: 100
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 1,
//                     animation: "cabrio",
//                     variant: 1,
//                     title: "CABRIO 2",
//                     colors: [Colors.SeaGreen],
//                     speed: 300
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "doublePulse",
//                     title: "Red",
//                     colors: [Colors.Red, Colors.Black],
//                     percentage: 20,// "{modifier}",
//                     speed: 0, // "{speed}",
//                     //speed: 255
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 5,
//                     animation: "doublePulse",
//                     title: "Red",
//                     colors: [Colors.Red, Colors.Black],
//                     percentage: 40,// "{modifier}",
//                     speed: 0, // "{speed}",
//                     //speed: 255
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 6,
//                     animation: "doublePulse",
//                     title: "Red",
//                     colors: [Colors.Red, Colors.Black],
//                     percentage: 80,// "{modifier}",
//                     speed: 0, // "{speed}",
//                     //speed: 255
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 7,
//                     animation: "doublePulse",
//                     title: "Red",
//                     colors: [Colors.Red, Colors.Black],
//                     percentage: 127,// "{modifier}",
//                     speed: 0, // "{speed}",
//                     //speed: 255
//                 }),
//             ]
//         },
//         {
//             name: "schuren in de fik",
//             description: "",
//             channels: [
//                 Object.assign(new InvokerPreset(), {
//                     channel: 0,
//                     animation: Constants.AnimationTypes.allDoublePulse,
//                     modifier: 107,
//                     speed: 17,
//                     colors: [Colors.Red, Colors.Blue],
//                     fade: Constants.FadeTypes.sparkle
//                 }),
//                 Object.assign(new InvokerPreset(), {
//                     channel: 2,
//                     animation: Constants.AnimationTypes.strobo,
//                     modifier: 237,
//                     colors: [Colors.Red, Colors.Blue],
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "strobo",
//                     title: "SCHUREN",
//                     variant: 1,
//                     flashCount: 4,
//                     colors: [Colors.Red, Colors.Blue],
//                     speed: 240
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "strobo",
//                     title: "STROBO",
//                     colors: [Colors.White],
//                     speed: 220
//                 })
//             ]
//         },
//         {
//             name: "technokoning",
//             description: "",
//             channels: [
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 4,
//                     animation: Constants.AnimationTypes.allSingleChaseRight,
//                     modifier: 63,
//                     repeat: 169,
//                     colors: [Colors.Green],
//                     fade: Constants.FadeTypes.sparkle
//                 }),
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 5,
//                     animation: Constants.AnimationTypes.allPartialSinglePulse,
//                     modifier: 31,
//                     repeat: 229,
//                     colors: [Colors.Green, Colors.White],
//                     fade: Constants.FadeTypes.fadeAll
//                 }),
//                 Object.assign(new ConfiguratorPreset(), {
//                     channel: 3,
//                     config: "random-3"
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "noise",
//                     title: "NOISE",
//                     colors: [Colors.Blue, Colors.Green, Colors.White],
//                     brightness: 128,
//                     speed: 32
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 1,
//                     animation: "matrix",
//                     title: "MATRIX",
//                     colors: [Colors.White, Colors.Green],
//                     speed: 11
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "noise",
//                     title: "NOISE",
//                     colors: [Colors.White],
//                     speed: 20
//                 }),
//             ]
//         },
//         {
//             name: "harder dan jij",
//             description: "",
//             channels: [
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 4,
//                     animation: Constants.AnimationTypes.allSinglePulse,
//                     modifier: 45,
//                     repeat: 55,
//                     colors: [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime],
//                     fade: Constants.FadeTypes.fadeAll
//                 }),
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 5,
//                     animation: Constants.AnimationTypes.allSinglePulse,
//                     modifier: 175,
//                     repeat: 100,
//                     colors: [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime],
//                     fade: Constants.FadeTypes.oneByOne
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "strobo",
//                     title: "HARDER",
//                     texts: ["HARDER", "DAN", "JIJ"],
//                     variant: 4,
//                     colors: [Colors.Red],
//                     speed: 1
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 1,
//                     animation: "lsd",
//                     title: "LSD"
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "strobo",
//                     title: "STROBO",
//                     colors: [Colors.Rainbow],
//                     speed: 220
//                 })
//             ]
//         },
//         {
//             name: "intens",
//             description: "",
//             channels: [
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 4,
//                     animation: Constants.AnimationTypes.onePartialSinglePulse,
//                     modifier: 65,
//                     repeat: 179,
//                     colors: [Colors.Orange],
//                     fade: Constants.FadeTypes.oneByOne
//                 }),
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 5,
//                     animation: Constants.AnimationTypes.onePartialSinglePulse,
//                     modifier: 65,
//                     repeat: 179,
//                     colors: [Colors.Pink],
//                     fade: Constants.FadeTypes.oneByOne
//                 }),
//                 Object.assign(new ConfiguratorPreset(), {
//                     channel: 3,
//                     config: "center-2"
//                 }),
//                 Object.assign(new InvokerPreset(), {
//                     channel: 2,
//                     animation: Constants.AnimationTypes.noise,
//                     modifier: 69
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "fadeText",
//                     title: "INTENS",
//                     texts: ["!!!!!!!!!"],
//                     font: 1,
//                     variant: 1,
//                     colors: [Colors.Orange, Colors.Pink],
//                     speed: 32
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 1,
//                     animation: "fadeText",
//                     title: "ADEM IN/UIT",
//                     texts: ["ADEM IN", "ADEM UIT"],
//                     variant: 1,
//                     colors: [Colors.SeaGreen, Colors.Yellow],
//                     speed: 128
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 2,
//                     animation: "strobo",
//                     title: "VOEL NIKS",
//                     texts: ["VOEL", "NIKS"], // centreertruuk met tekst niet zichtbaar
//                     variant: 4,
//                     flashCount: 3,
//                     colors: [Colors.White],
//                     speed: 245
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "strobo",
//                     title: "STROBO",
//                     colors: [Colors.Orange],
//                     speed: 220
//                 })
//             ]
//         },
//         {
//             name: "neuken",
//             description: "",
//             channels: [
//                 Object.assign(new InvokerPreset(), {
//                     channel: 0,
//                     animation: Constants.AnimationTypes.allSingleChaseLeft,
//                     modifier: 45,
//                     colors: [Colors.Pink],
//                     fade: Constants.FadeTypes.fadeAll
//                 }),
//                 Object.assign(new InvokerPreset(), {
//                     channel: 2,
//                     animation: Constants.AnimationTypes.strobo,
//                     modifier: 128,
//                     colors: [Colors.Pink],
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "strobo",
//                     title: "NEUKEN",
//                     texts: ["NEUKEN"],
//                     variant: 4,
//                     colors: [Colors.Pink],
//                     speed: 245
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "strobo",
//                     title: "STROBO",
//                     colors: [Colors.Pink],
//                     speed: 220
//                 })
//             ]
//         },
//         {
//             name: "alles gejat",
//             description: "",
//             channels: [
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "strobo",
//                     title: "ALLES GEJAT",
//                     texts: ["ALLES", "GEJAT"], // centreertruuk met tekst niet zichtbaar
//                     variant: 4,
//                     flashCount: 10,
//                     colors: [Colors.Orange, Colors.Green],
//                     speed: 240
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "singlePulse",
//                     title: "Orange",
//                     colors: [Colors.Orange],
//                     percentage: 20,
//                     speed: 120,
//                     fade: 3,
//                     //speed: 255
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 5,
//                     animation: "singlePulse",
//                     title: "Green",
//                     colors: [Colors.Green],
//                     percentage: 20,
//                     speed: 120,
//                     fade: 3,
//                     //speed: 255
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 6,
//                     animation: "strobo",
//                     title: "GIGI",
//                     colors: [Colors.White],
//                     speed: 1
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 7,
//                     animation: "singlePulse",
//                     title: "BASE",
//                     colors: [Colors.Pink],
//                     speed: 30,
//                     fade: 1
//                 })]
//         },
//         {
//             name: "poetin",
//             description: "",
//             channels: [
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "lsd",
//                     title: "LSD"
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "strobo",
//                     title: "STROBO",
//                     colors: [Colors.Rainbow],
//                     speed: 220
//                 })
//             ]
//         },
//         {
//             name: "kermis/instaparty",
//             description: "",
//             channels: [
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "lsd",
//                     title: "LSD"
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "strobo",
//                     title: "STROBO",
//                     colors: [Colors.Rainbow],
//                     speed: 220
//                 })
//             ]
//         },
//         {
//             name: "kerst",
//             description: "",
//             channels: [
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 4,
//                     animation: Constants.AnimationTypes.allSingleChaseLeft,
//                     modifier: 147,
//                     repeat: 85,
//                     colors: [Colors.Green],
//                     fade: Constants.FadeTypes.none
//                 }),
//                 Object.assign(new RepeaterPreset(), {
//                     channel: 5,
//                     animation: Constants.AnimationTypes.allSinglePulse,
//                     modifier: 161,
//                     repeat: 123,
//                     colors: [Colors.Red],
//                     fade: Constants.FadeTypes.none
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 0,
//                     animation: "strobo",
//                     title: "KERST 1",
//                     variant: 1,
//                     flashCount: 1,
//                     colors: [Colors.Red, Colors.Green],
//                     speed: 245
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 1,
//                     animation: "glitchText",
//                     title: "KERST 2",
//                     texts: ["STROBO", "COPS"],
//                     variant: 2,
//                     displayAllTexts: true,
//                     colors: [Colors.Red, Colors.Green, Colors.White],
//                     speed: 50
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 4,
//                     animation: "strobo",
//                     title: "STROBO",
//                     colors: [Colors.Green],
//                     speed: 220
//                 }),
//                 Object.assign(new SenderPreset(), {
//                     channel: 1,
//                     index: 5,
//                     animation: "strobo",
//                     title: "STROBO",
//                     colors: [Colors.Red],
//                     speed: 220
//                 })
//             ]
//         }
//     ]
// };