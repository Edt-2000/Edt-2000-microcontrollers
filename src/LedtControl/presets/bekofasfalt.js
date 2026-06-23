Songs.bekopasfalt = {
    name: "bek op asfalt",
    description: "repeater 6 + 7 voor rustige stukjes, repeater 4 + 5 voor erbij",
    channels: [
        Object.assign(new ConfiguratorPreset(), {
            channel: 3,
            config: "random-1"
        }),

        Object.assign(new InvokerPreset(), {
            channel: 0,
            animation: Constants.AnimationTypes.allDoublePulse,
            modifier: 211,
            speed: 1,
            colors: [Colors.Turquoise],
            fade: Constants.FadeTypes.oneByOne
        }),
        Object.assign(new InvokerPreset(), {
            channel: 1,
            animation: Constants.AnimationTypes.allPartialSinglePulse,
            modifier: 80,
            colors: [Colors.Turquoise],
            fade: Constants.FadeTypes.pulse
        }),

        Object.assign(new RepeaterPreset(), {
            channel: 4,
            animation: Constants.AnimationTypes.allDoublePulse,
            modifier: 75,
            repeat: 23,
            colors: [Colors.Turquoise, Colors.Turquoise],
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
            texts: ["BEK", "ASFALT", "HARD VAN"],
            variant: 2,
            colors: [Colors.Pink, Colors.Blue, Colors.Red], // 1 extra kleur
            speed: 100
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 1,
            animation: "fadeText",
            title: "BEK OP ASFALT 2",
            texts: ["HARD", "VAN"],
            variant: 2,
            colors: [Colors.Blue, Colors.Pink],
            speed: 255
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 4,
            animation: "singlePulse",
            title: "Red",
            colors: [Colors.Red],
            brightness: 255,
            speed: 64,
            fade: 1
            //speed: 255
        }),
    ]
};
