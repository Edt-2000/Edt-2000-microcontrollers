Songs.cabrioletta = {
    name: "cabrioletta",
    description: "Repeater 4 = tijdens alles | Repeater 5 = tijdens gas (100 - 255) | Z = tijdens cabrioletta | Strobeled tijdens gas | Powerbar tijdens couplet + hero moment",
    channels: [
        Object.assign(new InvokerPreset(), {
            channel: 0,
            animation: Constants.AnimationTypes.allSinglePulse,
            modifier: 128,
            colors: [Colors.Red],
            fade: Constants.FadeTypes.oneByOne
        }),
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
            modifier: 100,
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
            colors: [Colors.Orange],
            speed: 100
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 1,
            animation: "cabrio",
            variant: 1,
            title: "CABRIO 2",
            colors: [Colors.SeaGreen],
            speed: 300
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 4,
            animation: "doublePulse",
            title: "Red",
            colors: [Colors.Red, Colors.Black],
            percentage: 20,
            speed: 0
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 5,
            animation: "doublePulse",
            title: "Red",
            colors: [Colors.Red, Colors.Black],
            percentage: 40,
            speed: 0
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 6,
            animation: "doublePulse",
            title: "Red",
            colors: [Colors.Red, Colors.Black],
            percentage: 80,
            speed: 0
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 7,
            animation: "doublePulse",
            title: "Red",
            colors: [Colors.Red, Colors.Black],
            percentage: 127,
            speed: 0,
        }),
    ]
};
