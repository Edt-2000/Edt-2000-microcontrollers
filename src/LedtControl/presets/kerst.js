Songs.kerst = {
    name: "kerst",
    description: "Repeater 4 + 5 tegelijkertijd",
    channels: [
        Object.assign(new ConfiguratorPreset(), {
            channel: 3,
            config: "random-3"
        }),
        
        Object.assign(new InvokerPreset(), {
            channel: 0,
            animation: Constants.AnimationTypes.allDoublePulse,
            modifier: 127,
            speed: 45,
            colors: [Colors.Red, Colors.Green],
            fade: Constants.FadeTypes.pulse
        }),
        Object.assign(new InvokerPreset(), {
            channel: 1,
            animation: Constants.AnimationTypes.allSinglePulse,
            modifier: 127,
            speed: 255,
            colors: [Colors.Red, Colors.Green],
            fade: Constants.FadeTypes.fadeAll
        }),
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
        Object.assign(new RepeaterPreset(), {
            channel: 6,
            animation: Constants.AnimationTypes.allDoublePulse,
            modifier: 147,
            repeat: 191,
            colors: [Colors.Red, Colors.Green],
            fade: Constants.FadeTypes.pulse
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 7,
            animation: Constants.AnimationTypes.allSinglePulse,
            modifier: 31,
            repeat: 123,
            colors: [Colors.Red, Colors.Green],
            fade: Constants.FadeTypes.fadeAll
        }),

        // powerbar effects
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
            texts: ["STROBO", "COPS"],
            variant: 2,
            displayAllTexts: true,
            colors: [Colors.Red, Colors.Green, Colors.White],
            speed: 50
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 4,
            animation: "strobo",
            title: "STROBO",
            colors: [Colors.Green],
            speed: 220
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 5,
            animation: "strobo",
            title: "STROBO",
            colors: [Colors.Red],
            speed: 220
        })
    ]
};
