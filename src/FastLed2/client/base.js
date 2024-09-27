class HSV {
    H = 0;
    S = 0;
    V = 0;

    constructor(h, s, v) {
        this.H = h;
        this.S = s ?? 255;
        this.V = v ?? 255;
    }

    toHsl() {
        let vFactor = this.S == 0 ? 100.0 : 50.0;
        return `hsl(${((360.0 * this.H) / 255.0)} ${((100.0 * this.S) / 255.0)}% ${((vFactor * this.V) / 255.0)}%)`
    }
    toArray() {
        return [this.H, this.S, this.V];
    }
    isRainbow() {
        return this.S === 10;
    }
}

class Leds {
    static All = 255;

    static _leds = [1, 2, 4, 8, 16, 32, 64, 128];

    static _index = 8;

    static random() {
        if (this._index == 8) {
            // TODO: configurable?
            // this._leds.sort(() => Math.random() - 0.5);
            this._index = 0;
        }
        
        return this._leds[this._index++];
    }
}

class Colors {
    static Black = new HSV(0, 0, 0);
    static Red = new HSV(0);
    static Orange = new HSV(18);
    static Yellow = new HSV(58);
    static Lime = new HSV(85);
    static Green = new HSV(95);
    static SeaGreen = new HSV(105);
    static Turquoise = new HSV(129);
    static Blue = new HSV(158);
    static Purple = new HSV(183);
    static Pink = new HSV(238);
    static White = new HSV(0, 0, 255);

    // magic colors
    static Rainbow = new HSV(0, 10, 0);
}

function getElement(array, index) {
    if (array.length === 0) {
        return null;
    }

    return array[index % array.length];
}

function spaceCapitals(text)  {
    return text.replace(/([A-Z])/g, ' $1').trim();
}

function leftPad(value, length) {
    return value.toString().padStart(length, '0');
}

function getAngle(angle) {
    if (angle == 0) {
        return 'Down';
    }
    else if (angle == 64) {
        return 'Left';
    }
    else if (angle == 128) {
        return 'Up';
    }
    else {
        return 'Right';
    }
}

function arrayEquals(a, b) {
    if (a === b) return true;
    if (a == null || b == null) return false;
    if (a.length !== b.length) return false;

    for (let i = 0; i < a.length; ++i) {
        if (a[i] !== b[i]) return false;
    }
    return true;
}

class AnimationElementBase extends HTMLElement {
    constructor() {
        super();
    }

    setWebSocketHandler(webSocketHandler) {
        this.webSocketHandler = webSocketHandler;
    }

    createSettingHtml(value, disabled) {
        return `<p class="text-setting${disabled ? ' disabled' : ''}">${value}</p>`;
    }
    
    createValueHtml(value, description, disabled) {
        let setting = 100 * (value / 255.0);
        return `<p class="value-setting${disabled ? ' disabled' : ''}" style="background: linear-gradient(90deg, var(--settingHighlight) 0%, var(--settingHighlight) ${setting}%, var(--setting) ${setting}%, var(--setting) 100%);">${description}</p>`;
    }

    createColorSetHtml(colorSetIndex, disabled) {
        let colorSet = Constants.ColorSets[colorSetIndex];
        return this.createColorsHtml(colorSet, disabled);
    }

    createColorsHtml(colors, disabled) {
        let colorStyle = '';

        if (colors.length == 1 && colors[0].isRainbow())  {
            colorStyle = `background: linear-gradient(in hsl longer hue 90deg, red 0 0);`;
        }
        else {
            let colorLength = colors.length;
            let gradient = colors.map((color, index) => `${color.toHsl()} ${(100 * index / colorLength)}%, ${color.toHsl()} ${(100 * (index + 1) / colorLength)}%`).join(', ');
            colorStyle = `background: linear-gradient(90deg, ${gradient});`;
        }

        return `<p class="color-setting${disabled ? ' disabled' : ''}" style="${colorStyle}">&nbsp;</p>`;
    }
}

class WebSocketHandler {
    previousMessage = {};
    previousSender = null;

    constructor(ws) {
        this.ws = ws;
    }

    send(sender, message) {
        this.previousSender = sender;

        let previousMessageLocal = structuredClone(this.previousMessage);
        let messageClone = structuredClone(message);

        let keys = Object.keys(message).filter(x => x !== "animation");
        for (let key of keys) {
            if (message[key] === previousMessageLocal[key] ||
                (message[key] instanceof Array && arrayEquals(message[key], previousMessageLocal[key]))) {
                delete message[key];
            }
        }

        if (Object.keys(message).length == 0) {
            return;
        }

        this.ws.send(JSON.stringify(message));

        this.previousMessage = messageClone;
    }
}
