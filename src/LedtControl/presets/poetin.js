Songs.poetin = {
    name: "poetin",
    description: "Repeater 4 = stress | Repeater 5 = champignon | Repeater 6 + 7 = bounce | Strobeled strobo | Powerbar LSD",
    channels: [
        Object.assign(new ConfiguratorPreset(), {
            channel: 3,
            config: "random-3"
        }),
        
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
};
