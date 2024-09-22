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
}

class Colors {
    static Black = new HSV(0, 0, 0);
    static Red = new HSV(0);
    static Amber = new HSV(11);
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
}

class Constants {
    static Animations = ['allSingle', 'allDouble', 'partialSingle', 'allChase']
    static ColorSets = [
        [Colors.Red, Colors.White],
        [Colors.Red, Colors.Blue],
        [Colors.Turquoise, Colors.Pink],
        [Colors.Pink],
        [Colors.Green, Colors.Amber],
        [Colors.Green, Colors.White],
        [Colors.Red, Colors.Amber],
        [Colors.Red, Colors.Amber, Colors.Orange, Colors.Yellow, Colors.Lime, Colors.Green, Colors.SeaGreen, Colors.Turquoise, Colors.Blue, Colors.Purple, Colors.Pink],
        [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime, Colors.Amber]
    ]
    static Fades = ['none', 'fadeAll', 'oneByOne', 'sparkle']
}

class AnimationRepeaterState {
    Percentage = 0;
    Speed = 0;
    RepeatTime = 0;
    Animation = 0;
    ColorSet = 0;
    Fade = 0;

    getAnimation() { return Constants.Animations[this.Animation]; }
    nextAnimation() {
        this.Animation++;
        if (this.Animation >= Constants.Animations.length) {
            this.Animation = 0;
        }
    }
    getColorSet(animationIndex) {
        let set = Constants.ColorSets[this.ColorSet];
        if (set.length == 1) {
            return [set[0], set[0]];
        }
        else if (set.length > 2) {
            return [getElement(set, animationIndex), getElement(set, animationIndex + 1)];
        }
        else {
            let animation = this.getAnimation();

            if (animation == 'allDouble') {
                return set;
            }
            else {
                return [getElement(set, animationIndex), getElement(set, animationIndex + 1)];
            }
        }
    }
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

    reset() {
        this.Fade = -1;
        this.Percentage = 0;
        this.Speed = 0;
    }
}

function ease(input) {
    //y = (1 - (1 - (x / 255))^3) * 255
    return ((1 - Math.pow(1 - (input / 127.0), 3)) * 127.0);
}

function getElement(array, index) {
    if (array.length === 0) {
        return null;
    }

    return array[index % array.length];
}

function arrayEquals(a, b) {
    if (a === b) return true;
    if (a == null || b == null) return false;
    if (a.length !== b.length) return false;

    for (var i = 0; i < a.length; ++i) {
        if (a[i] !== b[i]) return false;
    }
    return true;
}

class AnimationRepeater extends HTMLElement {
    state = new AnimationRepeaterState();
    animationState = new AnimationRepeaterState();
    animationStep = 0;
    animationIndex = 0;

    constructor() {
        super();
    }

    connectedCallback() {
        this.shadow = this.attachShadow({ mode: "open" });
        this.drawState();

        const keys = this.dataset.key.split(',');

        window.addEventListener("keydown", (e) => {
            if (keys.includes(e.code) && !e.repeat) {
                this.onKeyDown();
            }
        });
        window.addEventListener("keyup", (e) => {
            console.log(e);

            if (keys.includes(e.code)) {
                this.onKeyUp();
            }
        });
    }

    setWebsocket(ws) {
        this.ws = ws;
    }

    onMessage(message) {
        if (message.bS) {
            this.state.nextAnimation();
        }
        if (message.bM) {
            this.state.nextColorSet();
        }
        if (message.bR) {
            this.state.nextFade();
        }
        this.state.Percentage = 1 + (message.s * 2);
        this.state.Speed = 1 + (message.i * 2);
        this.state.RepeatTime = ease(message.i);

        this.drawState();
    }

    sendMessage(firstMessage) {
        if (--this.animationStep < this.state.RepeatTime) {
            this.animationStep = 127;
        }
        else if (!firstMessage) {
            return;
        }


        let previousColorSet = this.state.getColorSet(this.animationIndex);

        this.animationIndex++;

        let colorSet = this.state.getColorSet(this.animationIndex);

        let message = {
            animation: this.state.getAnimation()
        };

        if (firstMessage || !arrayEquals(previousColorSet, colorSet)) {
            message.color1 = getElement(colorSet, 0).toArray();
            message.color2 = getElement(colorSet, 1).toArray();
        }

        if (this.animationState.Fade != this.state.Fade) {
            message.fade = this.state.getFade();
            this.animationState.Fade = this.state.Fade;
        }
        if (this.animationState.Percentage != this.state.Percentage) {
            message.percentage = this.state.Percentage;
            this.animationState.Percentage = this.state.Percentage;
        }
        if (this.animationState.Speed != this.state.Speed) {
            message.speed = this.state.Speed;
            this.animationState.Speed = this.state.Speed;
        }

        this.ws.send(JSON.stringify(message));
    }

    drawState() {
        const colorSet = Constants.ColorSets[this.state.ColorSet];
        const animation = Constants.Animations[this.state.Animation];
        const fade = Constants.Fades[this.state.Fade];

        let colorHtml = colorSet.map((color, index) => `<p style="background-color: ${color.toHsl()}">Color ${index}</p>`).join('');

        this.shadow.innerHTML = `<div>
            <fieldset>
                <legend>Repeater ${this.dataset.channel}</legend>

                <p>Animation: ${animation}</p>
                <progress max="255" value="${this.state.Speed}"></progress>
                <progress max="255" value="${this.state.Percentage}"></progress>
                <p>Fade: ${fade}</p>
                ${colorHtml}
            </fieldset>
        </div>`
    }

    onKeyDown() {
        if (this.animationInterval == null) {
            this.sendMessage(true);
            this.animationInterval = window.setInterval(() => this.sendMessage(), 10);
        }
    }

    onKeyUp() {
        window.clearInterval(this.animationInterval);
        this.animationInterval = null;

        this.animationState.reset();
    }
}

customElements.define('animation-repeater', AnimationRepeater);
