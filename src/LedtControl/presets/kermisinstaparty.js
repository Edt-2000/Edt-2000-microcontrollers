Songs.kermisinstaparty = {
    name: "kermis/instaparty",
    description: "alles is geoorloofd | gebruik spatiebalk om door kleuren heen lopen tijdens strobo",
    channels: [
        Object.assign(new ConfiguratorPreset(), {
            channel: 3,
            config: "random-3"
        }),
        
        Object.assign(new InvokerPreset(), {
            channel: 0,
            animation: Constants.AnimationTypes.allDoublePulse,
            modifier: 211,
            speed: 1,
            colors: [Colors.Rainbow],
            fade: Constants.FadeTypes.oneByOne
        }),
        Object.assign(new InvokerPreset(), {
            channel: 1,
            animation: Constants.AnimationTypes.allPartialSinglePulse,
            modifier: 80,
            colors: [Colors.Rainbow],
            fade: Constants.FadeTypes.sparkle
        }),
        Object.assign(new InvokerPreset(), {
            channel: 2,
            animation: Constants.AnimationTypes.strobo,
            modifier: 239,
            colors: [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime],
        }),

        Object.assign(new RepeaterPreset(), {
            channel: 4,
            animation: Constants.AnimationTypes.allDoublePulse,
            modifier: 127,
            repeat: 15,
            colors: [Colors.Rainbow],
            fade: Constants.FadeTypes.oneByOne
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 5,
            animation: Constants.AnimationTypes.onePartialSinglePulse,
            modifier: 47,
            repeat: 255,
            colors: [Colors.Rainbow],
            fade: Constants.FadeTypes.pulse
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 6,
            animation: Constants.AnimationTypes.oneSinglePulse,
            modifier: 9,
            repeat: 213,
            colors: [Colors.Rainbow],
            fade: Constants.FadeTypes.oneByOne
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 7,
            animation: Constants.AnimationTypes.oneSingleChaseRight,
            modifier: 49,
            repeat: 255,
            colors: [Colors.Rainbow],
            fade: Constants.FadeTypes.fadeAll
        }),

        // powerbar effects
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 0,
            animation: "lsd",
            title: "LSD"
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