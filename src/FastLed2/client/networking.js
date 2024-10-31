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

    socket.onmessage = function (event) {
        var eventData = JSON.parse(event.data);

        if (eventData instanceof Array) {
            for (let element of animationElements) {
                if (element.dataset.channel) {
                    var midiData = eventData[element.dataset.channel];
                    element.onMessage(midiData);
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
