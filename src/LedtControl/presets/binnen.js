Songs.binnen = {
    name: "binnen",
    description: "` tijdens tellen | repeater 4 = constant | repeater 5 = stress | repeater 6 + 7 = chases | Strobeled aan | Powerbar aan",
    channels: [
        Object.assign(new ConfiguratorPreset(), {
            channel: 3,
            config: "random-3"
        }),
        
        Object.assign(new InvokerPreset(), {
            channel: 0,
            animation: Constants.AnimationTypes.allPartialSinglePulse,
            modifier: 250,
            colors: [Colors.Yellow],
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
            colors: [Colors.Yellow, Colors.White]
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

        // powerbar effects
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
};
