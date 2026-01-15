Songs.lavalava = {
    name: "lava lava",
    description: "",
    channels: [
        Object.assign(new ConfiguratorPreset(), {
            channel: 3,
            config: "random-3"
        }),
        
        Object.assign(new InvokerPreset(), {
            channel: 2,
            animation: Constants.AnimationTypes.fire,
            modifier: 5
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 0,
            animation: "fire",
            title: "FIRE",
            speed: 5,
            brightness: "{modifier}", // TODO max 1/3
        }),
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 4,
            animation: "fire",
            title: "FIRE",
            speed: 5,
            brightness: "{modifier}", // TODO max 1/3
        })
    ]
};
