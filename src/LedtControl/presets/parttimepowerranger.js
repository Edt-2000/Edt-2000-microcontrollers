Songs.parttimepowerranger = {
    name: "parttimepowerranger",
    description: "Channel 0 + 1 partial pulses | Repeater 4 = flash slow / Repeater 5 = flash fast | Repeater 6 + 7 = chases | Strobeled hero moment",
    channels: [
        Object.assign(new ConfiguratorPreset(), {
            channel: 3,
            config: "random-3"
        }),
        
        Object.assign(new InvokerPreset(), {
            channel: 0,
            animation: Constants.AnimationTypes.allPartialSinglePulse,
            modifier: 250,
            colors: [Colors.Red, Colors.Yellow, Colors.Blue, Colors.Pink],
            fade: Constants.FadeTypes.oneByOne
        }),
        Object.assign(new InvokerPreset(), {
            channel: 1,
            animation: Constants.AnimationTypes.allPartialSinglePulse,
            modifier: 250,
            colors: [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime],
            fade: Constants.FadeTypes.oneByOne
        }),
        Object.assign(new InvokerPreset(), {
            channel: 2,
            animation: Constants.AnimationTypes.strobo,
            modifier: 213,
            colors: [Colors.Red, Colors.Yellow, Colors.Blue, Colors.Pink]
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 4,
            animation: Constants.AnimationTypes.allPartialSinglePulse,
            modifier: 51,
            repeat: 213,
            colors: [Colors.Rainbow],
            fade: Constants.FadeTypes.pulse
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 5,
            animation: Constants.AnimationTypes.allDoublePulse,
            modifier: 51,
            repeat: 213,
            colors: [Colors.Rainbow],
            fade: Constants.FadeTypes.pulse
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 6,
            animation: Constants.AnimationTypes.allSingleChaseLeft,
            modifier: 125,
            repeat: 125,
            colors: [Colors.Red, Colors.Yellow, Colors.Blue, Colors.Pink],
            fade: Constants.FadeTypes.pulse
        }),
        Object.assign(new RepeaterPreset(), {
            channel: 7,
            animation: Constants.AnimationTypes.allSingleChaseRight,
            modifier: 125,
            repeat: 125,
            colors: [Colors.Red, Colors.Yellow, Colors.Blue, Colors.Pink],
            fade: Constants.FadeTypes.pulse
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 0,
            animation: "strobo",
            title: "PARTTIME",
            variant: 3,
            flashCount: 2,
            colors: [Colors.Rainbow],
            speed: 255
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 1,
            animation: "strobo",
            title: "PARTTIME",
            texts: ["PARTTIME", "POWERRANGER"], // part + time / power + ranger 
            variant: 4,
            flashCount: 10,
            colors: [Colors.Specific, Colors.Rainbow],
            speed: 250
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 4,
            animation: "singlePulse",
            title: "Red",
            colors: [Colors.Red],
            brightness: 255,
            speed: 65,
            fade: 1
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 5,
            animation: "singlePulse",
            title: "Black",
            colors: [Colors.White],
            brightness: 255,
            speed: 65,
            fade: 1
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 6,
            animation: "singlePulse",
            title: "Yellow",
            colors: [Colors.Yellow],
            brightness: 255,
            speed: 65,
            fade: 1
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 7,
            animation: "singlePulse",
            title: "Pink",
            colors: [Colors.Pink],
            brightness: 255,
            speed: 65,
            fade: 1
        }),
    ]
};
