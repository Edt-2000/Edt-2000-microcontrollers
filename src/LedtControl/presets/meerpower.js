Songs.meerpower = {
    name: "meer power",
    description: "donker beginnen - langzaam Z - daarna X | Strobeled | Powerbar brightness 0 -> 255 | Powerbar strobo speed 0 -> 255",
    channels: [
        Object.assign(new ConfiguratorPreset(), {
            channel: 3,
            config: "random-1"
        }),
        
        Object.assign(new InvokerPreset(), {
            channel: 0,
            animation: Constants.AnimationTypes.allPartialSinglePulse,
            modifier: 155,
            colors: [Colors.Red, Colors.White],
            fade: Constants.FadeTypes.fadeAll
        }),
        Object.assign(new InvokerPreset(), {
            channel: 1,
            animation: Constants.AnimationTypes.allPartialSinglePulse,
            modifier: 155,
            colors: [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime],
            fade: Constants.FadeTypes.oneByOne
        }),
        Object.assign(new ConfiguratorPreset(), {
            channel: 3,
            color: Colors.Red
        }),

        // powerbar effects
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 0,
            animation: "strobo",
            title: "MEERPOWER strobo",
            variant: 2,
            flashCount: 1,
            colors: [Colors.White],
            brightness: "{modifier}",
            speed: "{speed}",
            //speed: 255
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 1,
            animation: "strobo",
            title: "MEERPOWER text",
            texts: ["MEER POWER"],
            variant: 4,
            flashCount: 1,
            colors: [Colors.White, Colors.Blue, Colors.Green],
            brightness: "{modifier}",
            speed: 240
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 4,
            animation: "strobo",
            title: "MEERPOWER strobo",
            colors: [Colors.White],
            brightness: "{modifier}",
            speed: "{speed}"
        }),
        // strobo op en neer
    ]
};
