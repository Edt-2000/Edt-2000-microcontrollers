Songs.schurenindefik = {
    name: "schuren in de fik",
    description: "Z tijdens couplet | strobo + channel 2 M + powerbar strobe | X afwisseling | Strobeled aan",
    channels: [
        Object.assign(new ConfiguratorPreset(), {
            channel: 3,
            config: "random-3"
        }),
        
        Object.assign(new InvokerPreset(), {
            channel: 0,
            animation: Constants.AnimationTypes.allDoublePulse,
            modifier: 107,
            speed: 17,
            colors: [Colors.Red, Colors.Blue],
            fade: Constants.FadeTypes.sparkle
        }),
        Object.assign(new InvokerPreset(), {
            channel: 1,
            animation: Constants.AnimationTypes.allSinglePulse,
            modifier: 107,
            speed: 17,
            colors: [Colors.Red, Colors.Blue],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new InvokerPreset(), {
            channel: 2,
            animation: Constants.AnimationTypes.strobo,
            modifier: 237,
            colors: [Colors.Red, Colors.Blue],
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 0,
            animation: "strobo",
            title: "SCHUREN",
            variant: 1,
            flashCount: 4,
            colors: [Colors.Red, Colors.Blue],
            speed: 240
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 4,
            animation: "strobo",
            title: "STROBO",
            colors: [Colors.White],
            speed: 220
        })
    ]
};
