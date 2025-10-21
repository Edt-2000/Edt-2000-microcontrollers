Songs.codemonkeys = {
    name: "code monkeys",
    description: "",
    channels: [
        Object.assign(new InvokerPreset(), {
            channel: 0,
            animation: Constants.AnimationTypes.allPartialSinglePulse,
            modifier: 211,
            colors: [Colors.Green, Colors.White],
            fade: Constants.FadeTypes.oneByOne
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 4,
            animation: Constants.AnimationTypes.allPartialSinglePulse,
            modifier: 31,
            repeat: 229,
            colors: [Colors.Green, Colors.White],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 5,
            animation: Constants.AnimationTypes.allPartialSinglePulse,
            modifier: 9,
            repeat: 213,
            colors: [Colors.Blue],
            fade: Constants.FadeTypes.oneByOne
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 0,
            animation: "glitchText",
            title: "CODEMONKEYS",
            texts: ["CODEMONKEYS"],
            variant: 1,
            flashCount: 1,
            colors: [Colors.Specific],
            speed: 250
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 1,
            animation: "fadeText",
            title: "DANCE",
            texts: ["DANCE"],
            variant: 3,
            colors: [Colors.Specific],
            speed: 91 // TODO
        })
        // dance in code monkey kleuren
    ]
};
