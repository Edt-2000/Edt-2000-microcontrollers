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

// TODO: rename percentage to modifier
// TODO: make animations a real class that handles:
// - color set calculations (based on index + set choosen)
// - duration of fade based on modifier for single animations
// - duration of fade based on modifier for chase animations

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
            
            // TODO: this should be abstracted away by moving some stuff into an Animation class
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

class AnimationRepeater extends HTMLElement {
    state = new AnimationRepeaterState();
    animationState = new AnimationRepeaterState();
    previousAnimation = 0;
    animationIndex = 0;

    constructor() {
        super();
    }

    connectedCallback() {
        this.drawState();

        const keys = this.dataset.key.split(',');

        window.addEventListener("keydown", (e) => {
            if (keys.includes(e.code) && !e.repeat) {
                this.onKeyDown();
            }
        });
        window.addEventListener("keyup", (e) => {
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
        this.state.RepeatTime = (145 - message.i) * 3;

        this.drawState();
    }

    sendMessage(firstMessage) {
        let now = performance.now();
        let diff = now - this.previousAnimation;
        
        if (!firstMessage && diff < this.state.RepeatTime) {
            return;
        }
        this.previousAnimation = now;

        let previousColorSet = this.state.getColorSet(this.animationIndex);
        this.animationIndex++;
        let colorSet = this.state.getColorSet(this.animationIndex);

        let message = {
            animation: this.state.getAnimation()
        };

        if (firstMessage || !arrayEquals(previousColorSet, colorSet) || this.animationState.ColorSet != this.state.ColorSet) {
            message.color1 = getElement(colorSet, 0).toArray();
            message.color2 = getElement(colorSet, 1).toArray();
            this.animationState.ColorSet = this.state.ColorSet;
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
            message.speed = Math.max(20, this.state.Speed);
            this.animationState.Speed = this.state.Speed;
        }

        this.ws.send(JSON.stringify(message));
    }

    drawState() {
        const colorSet = Constants.ColorSets[this.state.ColorSet];
        const animation = spaceCapitals(Constants.Animations[this.state.Animation]);
        const fade = spaceCapitals(Constants.Fades[this.state.Fade]);

        let colors = colorSet.length;
        let gradient = colorSet.map((color, index) => `${color.toHsl()} ${(100 * index / colors)}%, ${color.toHsl()} ${(100 * (index + 1) / colors)}%`).join(', ');
        let colorStyle = `background: linear-gradient(90deg, ${gradient});`;

        let speed = 100 * (this.state.Speed / 255.0);
        let percentage = 100 * (this.state.Percentage / 255.0);

        this.innerHTML = `<div class="repeater">
            
            <h2 class="type">Repeater ${this.dataset.channel}</h2>

            <p class="text-setting">${animation}</p>
            <p class="value-setting" style="background: linear-gradient(90deg, var(--settingHighlight) 0%, var(--settingHighlight) ${speed}%, var(--setting) ${speed}%, var(--setting) 100%);">Speed</p>
            <p class="value-setting" style="background: linear-gradient(90deg, var(--settingHighlight) 0%, var(--settingHighlight) ${percentage}%, var(--setting) ${percentage}%, var(--setting) 100%);">Percentage</p>
            <p class="color-setting" style="${colorStyle}">&nbsp;</p>
            <p class="text-setting">${fade}</p>
        </div>`
    }

    onKeyDown() {
        if (this.animationInterval == null) {
            this.sendMessage(true);
            this.animationInterval = window.setInterval(() => this.sendMessage(), 0);
        }
    }

    onKeyUp() {
        window.clearInterval(this.animationInterval);
        this.animationInterval = null;

        this.animationState.reset();
    }
}

customElements.define('animation-repeater', AnimationRepeater);
