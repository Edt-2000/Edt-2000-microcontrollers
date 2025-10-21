Songs.allesgejat = {
    name: "alles gejat",
    description: "",
    channels: [
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
