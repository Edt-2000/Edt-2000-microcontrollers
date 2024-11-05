let socket;

let statusElement = document.querySelector('#networking');
let resetElement = document.querySelector('#storage');
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

        let index = eventData.index;

        for (let element of animationElements) {
            if (element.dataset.channel == index) {
                element.onMessage(eventData.channel);
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
