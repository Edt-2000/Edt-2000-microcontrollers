Songs.intens = {
    name: "intens",
    description: "Repeater 4 / 5 - Noise",
    channels: [
        Object.assign(new ConfiguratorPreset(), {
            channel: 3,
            config: "center-2"
        }),
        
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
        Object.assign(new InvokerPreset(), {
            channel: 2,
            animation: Constants.AnimationTypes.noise,
            modifier: 69
        }),

        // powerbar effects
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 0,
            animation: "fadeText",
            title: "INTENS",
            texts: ["!!!!!!!!!"],
            font: 1,
            variant: 1,
            colors: [Colors.Orange, Colors.Pink],
            speed: 32
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 1,
            animation: "fadeText",
            title: "ADEM IN/UIT",
            texts: ["ADEM IN", "ADEM UIT"],
            variant: 1,
            colors: [Colors.SeaGreen, Colors.Yellow],
            speed: 128
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 2,
            animation: "strobo",
            title: "VOEL NIKS",
            texts: ["VOEL", "NIKS"], // centreertruuk met tekst niet zichtbaar
            variant: 4,
            flashCount: 3,
            colors: [Colors.White],
            speed: 245
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 4,
            animation: "strobo",
            title: "STROBO",
            colors: [Colors.Orange],
            speed: 220
        })
    ]
};
