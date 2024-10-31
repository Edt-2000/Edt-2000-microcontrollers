class AnimationSender extends AnimationElementBase {
    units = null;
    colors = [];
    
    constructor() {
        super();
    }

    connectedCallback() {
        const key = this.dataset.key;

        this.id = `sender-${this.dataset.channel}-${key}`;

        if (this.dataset.deviceType) {
            this.units = this.dataset.deviceType.split(',');
        }
        if (this.dataset.color) {
            this.colors = this.dataset.color.split(',').map(c => Colors[c]);
            delete this.dataset.color;
        }

        window.addEventListener("keydown", (e) => {
            if (!e.repeat && e.code === key) {
                e.preventDefault();
                this.onKeyDown();
            }
        })

        this.drawState();
    }

    onMessage(message) {
    }

    sendMessage() {
        let message = {
            units: this.units,
            colorCount: Math.max(1, this.colors.length)
        };

        if (getElement(this.colors, 0)) {
            message.color1 = getElement(this.colors, 0).toArray();
        }
        if (getElement(this.colors, 1)) {
            message.color2 = getElement(this.colors, 1).toArray();
        }
        if (getElement(this.colors, 2)) {
            message.color3 = getElement(this.colors, 2).toArray();
        }

        Object.assign(message, this.dataset);

        delete message['key'];
        delete message['title'];
        delete message['deviceType'];

        this.drawState();

        this.webSocketHandler.send(this, message);
    }

    onKeyDown() {
        this.sendMessage();
    }

    drawState() {
        let html = `<div><h2 class="type">${this.dataset.key}</h2>`;
        html += `<h2 class="animation">${this.dataset.title}</h2>`;
        html += '</div>';

        this.innerHTML = html;
    }
}

customElements.define('animation-sender', AnimationSender);