Songs.kerst = {
    name: "kerst",
    description: "",
    channels: [
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
