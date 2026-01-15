Songs.technokoning = {
    name: "technokoning",
    description: "Repeater 4 + 5 | Repeater 6 + 7",
    channels: [
        Object.assign(new ConfiguratorPreset(), {
            channel: 3,
            config: "random-3"
        }),
        
        Object.assign(new InvokerPreset(), {
            channel: 0,
            animation: Constants.AnimationTypes.allSinglePulse,
            modifier: 155,
            colors: [Colors.Blue],
            fade: Constants.FadeTypes.oneByOne
        }),
        Object.assign(new InvokerPreset(), {
            channel: 1,
            animation: Constants.AnimationTypes.onePartialSinglePulse,
            modifier: 155,
            colors: [Colors.Green, Colors.White],
            fade: Constants.FadeTypes.oneByOne
        }),
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
            animation: Constants.AnimationTypes.allSingleChaseLeft,
            modifier: 6,
            repeat: 16,
            colors: [Colors.Blue],
            fade: Constants.FadeTypes.sparkle
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 6,
            animation: Constants.AnimationTypes.allPartialSinglePulse,
            modifier: 31,
            repeat: 229,
            colors: [Colors.Green, Colors.White],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 7,
            animation: Constants.AnimationTypes.allPartialSinglePulse,
            modifier: 6,
            repeat: 110,
            colors: [Colors.Blue],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 0,
            animation: "noise",
            title: "NOISE",
            colors: [Colors.Blue, Colors.Green, Colors.White],
            brightness: 128,
            speed: 32
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 1,
            animation: "matrix",
            title: "MATRIX",
            colors: [Colors.White, Colors.Green],
            speed: 11
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 4,
            animation: "noise",
            title: "NOISE",
            colors: [Colors.White],
            speed: 20
        }),
    ]
};
