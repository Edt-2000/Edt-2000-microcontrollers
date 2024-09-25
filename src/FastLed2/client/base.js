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

class Animation {
    name = "";
    selectable = true;

    generateMessage(state) {}
}

class AllSingleAnimation extends Animation {
    constructor() {
        super();
        this.name = "allSingle";
    }

    generateMessage(state) {
        let colorSet = state.getColorSet();

        let message = {
            animation: this.name,
            color1: getElement(colorSet, state.Tick).toArray(),
            fade: state.getFade(),
            speed: state.Modifier
        };

        return message;
    }
}

class PartialSingleAnimation extends Animation {
    constructor() {
        super();
        this.name = "partialSingle";
    }

    generateMessage(state) {
        let colorSet = state.getColorSet();

        let message = {
            animation: this.name,
            color1: getElement(colorSet, state.Tick).toArray(),
            fade: state.getFade(),
            speed: 30,
            percentage: state.Modifier
        };

        return message;
    }
}

class AllDoubleAnimation extends Animation {
    constructor() {
        super();
        this.name = "allDouble";
    }

    generateMessage(state) {
        let colorSet = state.getColorSet();

        // use the same colors every tick if there are only 2
        let tick = colorSet.length == 2 ? 0 : state.Tick;

        let message = {
            animation: this.name,
            color1: getElement(colorSet, tick).toArray(),
            color2: getElement(colorSet, tick + 1).toArray(),
            fade: state.getFade(),
            speed: Math.min(255, state.Speed * 3),
            percentage: state.Modifier
        };

        return message;
    }
}

class AllSingleChaseAnimation extends Animation {
    constructor() {
        super();
        this.name = "allSingleChase";
    }

    generateMessage(state) {
        let colorSet = state.getColorSet();

        let message = {
            animation: this.name,
            color1: getElement(colorSet, state.Tick).toArray(),
            fade: state.getFade(),
            speed: state.Modifier
        };

        return message;
    }
}

class AllDoubleChaseAnimation extends Animation {
    constructor() {
        super();
        this.name = "allDoubleChase";
    }

    generateMessage(state) {
        let colorSet = state.getColorSet();

        let tick = colorSet.length == 2 ? 0 : state.Tick;

        let message = {
            animation: this.name,
            color1: getElement(colorSet, tick).toArray(),
            color2: getElement(colorSet, tick + 1).toArray(),
            fade: state.getFade(),
            speed: state.Modifier
        };

        return message;
    }
}

class StroboAnimation extends Animation {
    constructor() {
        super();
        this.name = "strobo";
        this.selectable = false;
    }

    generateMessage(state) {
        let colorSet = state.getColorSet();

        let message = {
            animation: this.name,
            color1: getElement(colorSet, state.Tick).toArray(),
            speed: state.Speed
        };

        return message;
    }
}

class StopAnimation extends Animation {
    constructor() {
        super();
        this.name = "stop";
        this.selectable = false;
    }

    generateMessage(state) {
        let message = {
            animation: this.name
        };

        return message;
    }
}

class Constants {
    static Animations = [
        new AllSingleAnimation(), 
        new AllDoubleAnimation(), 
        new PartialSingleAnimation(),
        new AllSingleChaseAnimation(),
        new AllDoubleChaseAnimation(),
        new StroboAnimation(),
        new StopAnimation()
    ];
    static ColorSets = [
        [Colors.Red, Colors.White],
        [Colors.Red, Colors.Blue],
        [Colors.Turquoise, Colors.Pink],
        [Colors.Pink],
        [Colors.Green, Colors.Orange],
        [Colors.Green, Colors.White],
        [Colors.Red, Colors.Orange],
        [Colors.Red, Colors.Orange, Colors.Yellow, Colors.Lime, Colors.Green, Colors.SeaGreen, Colors.Turquoise, Colors.Blue, Colors.Purple, Colors.Pink],
        [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime],
        [Colors.Rainbow],
        [Colors.White]
    ];
    static Fades = ['none', 'fadeAll', 'oneByOne', 'sparkle'];
}

class AnimationState {
    // animations
    Modifier = 0;
    Speed = 0;
    Animation = 0;
    Color = null;
    ColorSet = 0;
    Fade = 0;
    
    // timings
    RepeatTime = 0;
    Tick = -1;

    getAnimation() { return Constants.Animations[this.Animation]; }
    nextAnimation() {
        this.Animation++;
        if (this.Animation >= Constants.Animations.length) {
            this.Animation = 0;
        }
        if (!this.getAnimation().selectable) {
            this.nextAnimation();
        }
    }
    getColorSet() { return this.Color ? [this.Color] : Constants.ColorSets[this.ColorSet]; }
    nextColorSet() {
        this.ColorSet++;
        if (this.ColorSet >= Constants.ColorSets.length) {
            this.ColorSet = 0;
        }
    }
    getFade() { return this.Fade; }
    nextFade() {
        this.Fade++;
        if (this.Fade >= Constants.Fades.length) {
            this.Fade = 0;
        }
    }

    updateTick() { this.Tick = this.Tick + 1; }
    reset() {
        this.Tick = -1;
    }
}
