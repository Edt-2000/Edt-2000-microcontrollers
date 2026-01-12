let socket;

let statusElement = document.querySelector('#networking');
let resetElement = document.querySelector('#storage');
let devicesElement = document.querySelector('#devices');

resetElement.onclick = function () {
    if (confirm('Reset?')) {
        localStorage.clear();
        location.reload();
    }
}

function setupSocket() {
    console.log("Starting WebSocket..");

    socket = new WebSocket('ws://localhost:5151/control');

    let handler = new WebSocketHandler(socket);

    const animationElements = document.querySelectorAll("animation-configurator, animation-invoker, animation-repeater, animation-sender");
    for (let element of animationElements) {
        element.setWebSocketHandler(handler);
    }
    socket.onopen = function (event) {
        console.log("WebSocket connected!");
        statusElement.className = "connected";
    };

    document.querySelector("animation-presets").setPresetReceivers(animationElements);

    socket.onmessage = function (event) {
        let eventData = JSON.parse(event.data);

        if (eventData.devices != null) {
            devicesElement.innerHTML = Object.entries(eventData.devices).sort((a,b) => a[0] > b[0]).map(([device, status]) => `<span class="${status}">${device}</span>`).join("");
        }
        else {
            let index = eventData.index;

            for (let element of animationElements) {
                if (element.dataset.channel == index) {
                    switch (eventData.updateType) {
                        case "select": element.onSelectUpdate(eventData.value); break;
                        case "intensity": element.onIntensityUpdate(eventData.value); break;
                        case "button": element.onButtonPress(eventData.value == 1, eventData.value == 2, eventData.value == 4); break;
                    }
                }
            }
        }
    };

    socket.onclose = function (event) {
        console.log("WebSocket disconnected!");

        statusElement.className = "disconnnected";

        setTimeout(setupSocket, 1000);
    };

    statusElement.className = "";
}

setupSocket();
