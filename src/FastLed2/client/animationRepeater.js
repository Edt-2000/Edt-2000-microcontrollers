class HSV {
    H = 0;
    S = 0;
    V = 0;

    constructor(h, s, v) {
        this.H = h;
        this.S = s;
        this.V = v;
    }

    toHsl() {
        return `hsl(${((360.0 * this.H) / 255.0)} ${((100.0 * this.S) / 255.0)}% ${((50.0 * this.V) / 255.0)}%)`
    }
}

class AnimationRepeater extends HTMLElement {
    animations = ['allSingle', 'allDouble', 'partialSingle']
    colorSets = [
        [new HSV(0, 255, 255), new HSV(0, 0, 255)],
        [new HSV(0, 255, 255), new HSV(158, 255, 255)]
    ]
    fades = ['none', 'fadeAll', 'oneByOne', 'sparkle']
    state = {
        percentage: 0,
        speed: 0,
        animation: 0,
        colorSet: 0,
        fade: 0
    };

    constructor() {
        super();
    }

    onMessage(message) {
        if (message.bS) {
            this.state.animation++;
            if (this.state.animation >= this.animations.length) {
                this.state.animation = 0;
            }
        }
        if (message.bM) {
            this.state.colorSet++;
            if (this.state.colorSet >= this.colorSets.length) {
                this.state.colorSet = 0;
            }
        }
        if (message.bR) {
            this.state.fade++;
            if (this.state.fade >= this.fades.length) {
                this.state.fade = 0;
            }
        }
        this.state.percentage = message.s;
        this.state.speed = message.i;

        this.drawState();
    }

    connectedCallback() {
        this.shadow = this.attachShadow({ mode: "open" });
        this.drawState();
    }

    drawState() {
        const colorSet = this.colorSets[this.state.colorSet];
        const animation = this.animations[this.state.animation];
        const fade = this.fades[this.state.fade];

        this.shadow.innerHTML = `<div>
            <fieldset>
                <legend>Repeater ${this.dataset.channel}</legend>

                <p>Animation: ${animation}</p>
                <progress max="127" value="${this.state.speed}"></progress>
                <progress max="127" value="${this.state.percentage}"></progress>
                <p>Fade: ${fade}</p>
                <p style="background-color: ${colorSet[0].toHsl()}">Color 1</p>
                <p style="background-color: ${colorSet[1].toHsl()}">Color 2</p>
            </fieldset>
        </div>`
    }
}

customElements.define('animation-repeater', AnimationRepeater);
