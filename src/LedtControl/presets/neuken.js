Songs.neuken = {
    name: "neuken",
    description: "Repeat 6 + 7 = bounce | Repeat 4 + 5 = up down | Strobo | Strobeled aan | Powerbar aan",
    channels: [
        Object.assign(new InvokerPreset(), {
            channel: 0,
            animation: Constants.AnimationTypes.allSingleChaseLeft,
            modifier: 45,
            colors: [Colors.Pink],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new InvokerPreset(), {
            channel: 1,
            animation: Constants.AnimationTypes.allSingleChaseRight,
            modifier: 45,
            colors: [Colors.Pink],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new InvokerPreset(), {
            channel: 2,
            animation: Constants.AnimationTypes.strobo,
            modifier: 238,
            colors: [Colors.Pink],
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 4,
            animation: Constants.AnimationTypes.allSingleChaseDown,
            modifier: 143,
            repeat: 145,
            colors: [Colors.Pink],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 5,
            animation: Constants.AnimationTypes.allSingleChaseUp,
            modifier: 143,
            repeat: 145,
            colors: [Colors.Pink],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 6,
            animation: Constants.AnimationTypes.allSingleChaseLeft,
            modifier: 143,
            repeat: 45,
            colors: [Colors.Pink],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 7,
            animation: Constants.AnimationTypes.allSingleChaseRight,
            modifier: 143,
            repeat: 45,
            colors: [Colors.Pink],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 0,
            animation: "strobo",
            title: "NEUKEN",
            texts: ["NEUKEN"],
            variant: 4,
            colors: [Colors.Pink],
            speed: 245
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 4,
            animation: "strobo",
            title: "STROBO",
            colors: [Colors.Pink],
            speed: 220
        })
    ]
};
