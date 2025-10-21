class Songs {}

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

class FastLedUnits {
    static _modes = [
        ['unit1', 'unit2', 'spectacle', 'dmx'],
        ['unit1'],
        ['unit2'],
        ['spectacle'],
        ['unit1', 'unit2', 'dmx']
    ];
    static _activeMode = 0;

    static getUnits() { return this._modes[this._activeMode]; }
    static nextConfig() {
        this._activeMode++;
        if (this._activeMode >= this._modes.length) {
            this._activeMode = 0;
        }
    }
}

class Leds {
    static All = 255;
    static Config = 0;

    static _modes = ['linear-1', 'random-1', 'linear-2', 'center-2', 'random-2', 'linear-3', 'random-3', 'center-4'];
    static _leds = [1, 2, 4, 8, 16, 32, 64, 128];
    static _activeLeds = [... this._leds];
    static _centerLeds = [8, 16, 4, 32, 2, 64, 1, 128];
    static _index = 8;

    static getLeds() {
        return this._getLeds(1);
    }

    static _getLeds(currentCount) {
        let type = this._modes[this.Config].split('-');

        let ledCount = parseInt(type[1]);
        if (currentCount > ledCount) {
            return 0;
        }
        
        let isRandom = type[0] === 'random';
        let isCenter = type[0] === 'center';
        
        if (this._index == 8) {
            if (isRandom) {
                this._activeLeds.sort(() => Math.random() - 0.5);
            }
            this._index = 0;
        }

        let array = isRandom ? this._activeLeds : isCenter ? this._centerLeds : this._leds;

        return array[this._index++] + this._getLeds(currentCount + 1);
    }

    static getConfig() { return this._modes[this.Config]; }
    static setConfig(config) {
        this.Config = Math.max(0, this._modes.indexOf(config));
    }
    static nextConfig() {
        this.Config++;
        this._index = 8;
        if (this.Config >= this._modes.length) {
            this.Config = 0;
        }
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
    static Specific = new HSV(0, 20, 0);
}

function getElement(array, index) {
    if (array.length === 0) {
        return null;
    }

    return array[index % array.length];
}

function spaceCapitals(text) {
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

    onPreset(preset) {}

    resetPresetState() {
        this.dataset.underPreset = false;
    }

    onReset() {}

    createSettingHtml(value, disabled, button, active) {
        return `<p class="text-setting${disabled ? ' disabled' : ''}${active ? ' active' : ''}" ${this.createButtonHtml(button)}>${value}</p>`;
    }

    createValueHtml(value, description, disabled, button) {
        let setting = Math.round(100 * (value / 255.0));
        return `<p class="value-setting${disabled ? ' disabled' : ''}" ${this.createButtonHtml(button)} data-value="${value}" style="background: linear-gradient(90deg, var(--settingHighlight) 0%, var(--settingHighlight) ${setting}%, var(--setting) ${setting}%, var(--setting) 100%);">${description}</p>`;
    }

    createColorSetHtml(colorSetIndex, disabled, button) {
        let colorSet = Constants.ColorSets[colorSetIndex];
        return this.createColorsHtml(colorSet, disabled, button, colorSetIndex);
    }

    createColorsHtml(colors, disabled, button, colorSetIndex) {
        let colorStyle = '';

        if (colors.length == 1 && colors[0].isRainbow()) {
            colorStyle = `background: linear-gradient(in hsl longer hue 90deg, red 0 100%);`;
        }
        else {
            let colorLength = colors.length;
            let gradient = colors.map((color, index) => `${color.toHsl()} ${(100 * index / colorLength)}%, ${color.toHsl()} ${(100 * (index + 1) / colorLength)}%`).join(', ');
            colorStyle = `background: linear-gradient(90deg, ${gradient});`;
        }

        return `<p data-value="${colorSetIndex != undefined ? `${colorSetIndex}/${Constants.ColorSets.length}` : ''}" class="color-setting${disabled ? ' disabled' : ''}" ${this.createButtonHtml(button)} style="${colorStyle}">&nbsp;</p>`;
    }

    createButtonHtml(button) {
        return button == null ? "" : `data-button="${button}"`;
    }
}

class WebSocketHandler {
    previousSender = null;

    constructor(ws) {
        this.ws = ws;
    }

    send(sender, message) {
        this.previousSender = sender;
        this.ws.send(JSON.stringify(message));
    }
}
