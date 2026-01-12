Songs.kermisinstaparty = {
    name: "kermis/instaparty",
    description: "",
    channels: [
        Object.assign(new SenderPreset(), {
            channel: 1,
            index: 0,
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