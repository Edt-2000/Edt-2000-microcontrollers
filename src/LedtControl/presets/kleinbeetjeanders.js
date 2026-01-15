Songs.kleinbeetjeanders = {
    name: "klein beetje anders",
    description: "2 kleuren voor tijdens djvt toontje - ",
    channels: [
        Object.assign(new ConfiguratorPreset(), {
            channel: 3,
            config: "random-3"
        }),
        
        Object.assign(new InvokerPreset(), {
            channel: 0,
            animation: Constants.AnimationTypes.allDoubleChaseUp,
            modifier: 127,
            speed: 16,
            colors: [Colors.Turquoise, Colors.Pink],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new InvokerPreset(), {
            channel: 1,
            animation: Constants.AnimationTypes.allDoublePulse,
            modifier: 127,
            speed: 16,
            colors: [Colors.Turquoise, Colors.Pink],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 4,
            animation: Constants.AnimationTypes.allSingleChaseLeft,
            modifier: 60,
            repeat: 213,
            colors: [Colors.Turquoise, Colors.Pink],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 5,
            animation: Constants.AnimationTypes.allSingleChaseRight,
            modifier: 60,
            repeat: 213,
            colors: [Colors.Turquoise, Colors.Pink],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 6,
            animation: Constants.AnimationTypes.allSinglePulse,
            modifier: 200,
            repeat: 255,
            colors: [Colors.Turquoise],
            fade: Constants.FadeTypes.pulse
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 7,
            animation: Constants.AnimationTypes.allSinglePulse,
            modifier: 200,
            repeat: 255,
            colors: [Colors.Pink],
            fade: Constants.FadeTypes.pulse
        })
    ]
};
