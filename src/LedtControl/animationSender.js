class AnimationSender extends AnimationElementBase {
    units = null;
    colors = [];
    texts = [];
    singleShot = true;

    speed = 0;
    usesSpeed = false;
    speedName = '';

    modifier = 0;
    usesModifier = false;
    modifierName = '';

    constructor() {
        super();
    }

    connectedCallback() {
        const key = this.dataset.key;

        this.id = `sender-${this.dataset.channel}-${key}`;

        if (this.dataset.deviceType) {
            this.units = this.dataset.deviceType.split(',');
        }

        this.initialize();

        window.addEventListener("keydown", (e) => {
            if (!e.repeat && e.code === key) {
                e.preventDefault();
                this.onKeyDown();
            }
        });

        this.drawState();
    }

    initialize() {
        if (this.dataset.color) {
            this.colors = this.dataset.color.split(',').map(c => Colors[c]);
            delete this.dataset.color;
        }
        if (this.dataset.text) {
            this.texts = this.dataset.text.split(',');
            delete this.dataset.text;
        }

        let speedProperty = Object.keys(this.dataset).find(k => this.dataset[k] == "{speed}");
        this.speedName = speedProperty;
        this.usesSpeed = !!speedProperty;

        let modifierProperty = Object.keys(this.dataset).find(k => this.dataset[k] == "{modifier}");
        this.modifierName = modifierProperty;
        this.usesModifier = !!modifierProperty;

        this.singleShot = !(this.usesSpeed || this.usesModifier);
    }

    onSelectUpdate(s) {
        let newModifier = 1 + (s * 2);
        this.modifier = newModifier;

        this.drawAndSend();
    }

    onIntensityUpdate(i) {
        let newSpeed = 1 + (i * 2);
        this.speed = newSpeed;

        this.drawAndSend();
    }

    onButtonPress(s, m, r) {

    }

    drawAndSend() {
        this.animationProbablyActive = !this.singleShot && this.webSocketHandler.previousSender == this;

        let shouldSend = this.animationProbablyActive;

        if (shouldSend) {
            this.sendMessage(false);
        }

        this.drawState();
    }

    onPreset(preset) {
        if (!(preset instanceof SenderPreset)) {
            return;
        }

        if (preset.index != this.dataset.index) {
            return;
        }

        this.dataset.underPreset = true;

        this.dataset.animation = preset.animation;
        this.dataset.title = preset.title;
        this.dataset.displayAllTexts = preset.displayAllTexts;
        this.dataset.font = preset.font;
        this.dataset.variant = preset.variant;
        this.dataset.flashCount = preset.flashCount;
        this.dataset.brightness = preset.brightness;
        this.dataset.speed = preset.speed;

        this.texts = preset.texts;
        this.colors = preset.colors;

        this.initialize();

        this.drawState();
    }

    resetPresetState() {
        this.dataset.underPreset = false;
        this.onReset();
    }

    onReset() {
        if (!this.dataset.index) {
            return;
        }

        delete this.dataset.animation;
        delete this.dataset.title;
        delete this.dataset.modifier;
        delete this.dataset.speed;
        delete this.dataset.text;
        delete this.dataset.displayAllTexts;
        delete this.dataset.font;
        delete this.dataset.variant;
        delete this.dataset.flashCount;
        delete this.dataset.color;
        delete this.dataset.brightness;
        delete this.dataset.speed;

        this.initialize();

        this.drawState();
    }

    sendMessage(sendFullMessage) {
        let message = {
            units: this.units
        };

        if (sendFullMessage) {
            message.colorCount = Math.max(1, this.colors.length);

            if (getElement(this.colors, 0)) {
                message.color1 = getElement(this.colors, 0).toArray();
            }
            if (getElement(this.colors, 1)) {
                message.color2 = getElement(this.colors, 1).toArray();
            }
            if (getElement(this.colors, 2)) {
                message.color3 = getElement(this.colors, 2).toArray();
            }

            for (let i = 0; i < this.texts.length; i++) {
                message[`text${i + 1}`] = this.texts[i];
            }

            Object.assign(message, this.dataset);

            delete message['key'];
            delete message['title'];
            delete message['deviceType'];
            delete message['index'];
            delete message['underPreset'];
        }

        if (this.usesSpeed) {
            message[this.speedName] = this.speed;
        }
        if (this.usesModifier) {
            message[this.modifierName] = this.modifier;
        }

        this.drawState();

        this.webSocketHandler.send(this, message);
    }

    onKeyDown() {
        this.sendMessage(true);
    }

    drawState() {

        let html = `<div><h2 class="type">${this.dataset.key}</h2>`;

        if (this.dataset.title != null) {
            html += `<h2 class="animation">${this.dataset.title}</h2>`;
        }

        if (this.usesSpeed) {
            html += this.createValueHtml(this.speed, spaceCapitals(this.speedName));
        }

        if (this.usesModifier) {
            html += this.createValueHtml(this.modifier, spaceCapitals(this.modifierName));
        }

        html += '</div>';

        this.innerHTML = html;
    }
}

customElements.define('animation-sender', AnimationSender);
