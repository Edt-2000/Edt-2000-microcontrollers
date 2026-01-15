Songs.allesgejat = {
    name: "alles gejat",
    description: "",
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
            colors: [Colors.Green, Colors.Orange],
            fade: Constants.FadeTypes.oneByOne
        }),
        Object.assign(new InvokerPreset(), {
            channel: 1,
            animation: Constants.AnimationTypes.allPartialSinglePulse,
            modifier: 80,
            colors: [Colors.White],
            fade: Constants.FadeTypes.pulse
        }),
        
        Object.assign(new RepeaterPreset(), {
            channel: 4,
            animation: Constants.AnimationTypes.allDoublePulse,
            modifier: 127,
            repeat: 15,
            colors: [Colors.Green, Colors.Orange],
            fade: Constants.FadeTypes.oneByOne
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 5,
            animation: Constants.AnimationTypes.onePartialSinglePulse,
            modifier: 47,
            repeat: 255,
            colors: [Colors.White],
            fade: Constants.FadeTypes.pulse
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 6,
            animation: Constants.AnimationTypes.oneSinglePulse,
            modifier: 9,
            repeat: 213,
            colors: [Colors.Pink],
            fade: Constants.FadeTypes.oneByOne
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 7,
            animation: Constants.AnimationTypes.oneSingleChaseRight,
            modifier: 49,
            repeat: 255,
            colors: [Colors.Pink],
            fade: Constants.FadeTypes.fadeAll
        }),

        // powerbar effects
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 0,
            animation: "strobo",
            title: "ALLES GEJAT",
            texts: ["ALLES", "GEJAT"], // centreertruuk met tekst niet zichtbaar
            variant: 4,
            flashCount: 10,
            colors: [Colors.Orange, Colors.Green],
            speed: 240
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 4,
            animation: "singlePulse",
            title: "Orange",
            colors: [Colors.Orange],
            percentage: 20,
            speed: 120,
            fade: 3,
            //speed: 255
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 5,
            animation: "singlePulse",
            title: "Green",
            colors: [Colors.Green],
            percentage: 20,
            speed: 120,
            fade: 3,
            //speed: 255
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 6,
            animation: "strobo",
            title: "GIGI",
            colors: [Colors.White],
            speed: 1
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 7,
            animation: "singlePulse",
            title: "BASE",
            colors: [Colors.Pink],
            speed: 30,
            fade: 1
        })
    ]
};
