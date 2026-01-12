Songs.harderdanjij = {
    name: "harder dan jij",
    description: "",
    channels: [
        Object.assign(new RepeaterPreset(), {
            channel: 4,
            animation: Constants.AnimationTypes.allSinglePulse,
            modifier: 45,
            repeat: 55,
            colors: [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 5,
            animation: Constants.AnimationTypes.allSinglePulse,
            modifier: 175,
            repeat: 100,
            colors: [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime],
            fade: Constants.FadeTypes.oneByOne
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 0,
            animation: "strobo",
            title: "HARDER",
            texts: ["HARDER", "DAN", "JIJ"],
            variant: 4,
            colors: [Colors.Red],
            speed: 1
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 1,
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
