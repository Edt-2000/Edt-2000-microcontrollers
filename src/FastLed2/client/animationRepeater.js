class Animation {
    name = "";

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

class Constants {
    static Animations = [
        new AllSingleAnimation(), 
        new AllDoubleAnimation(), 
        new PartialSingleAnimation(),
        new AllSingleChaseAnimation(),
        new AllDoubleChaseAnimation()
    ];
    static ColorSets = [
        [Colors.Red, Colors.White],
        [Colors.Red, Colors.Blue],
        [Colors.Turquoise, Colors.Pink],
        [Colors.Pink],
        [Colors.Green, Colors.Amber],
        [Colors.Green, Colors.White],
        [Colors.Red, Colors.Amber],
        [Colors.Red, Colors.Amber, Colors.Orange, Colors.Yellow, Colors.Lime, Colors.Green, Colors.SeaGreen, Colors.Turquoise, Colors.Blue, Colors.Purple, Colors.Pink],
        [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime, Colors.Amber],
        [Colors.White]
    ];
    static Fades = ['none', 'fadeAll', 'oneByOne', 'sparkle'];
}

class AnimationRepeaterState {
    Modifier = 0;
    Speed = 0;
    RepeatTime = 0;
    Animation = 0;
    ColorSet = 0;
    Fade = 0;
    Tick = -1;

    getAnimation() { return Constants.Animations[this.Animation]; }
    nextAnimation() {
        this.Animation++;
        if (this.Animation >= Constants.Animations.length) {
            this.Animation = 0;
        }
    }
    getColorSet() { return Constants.ColorSets[this.ColorSet]; }
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

class AnimationRepeater extends HTMLElement {
    state = new AnimationRepeaterState();
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
        this.state.Modifier = 1 + (message.s * 2);
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

        this.state.updateTick();

        let animation = this.state.getAnimation();

        let message = animation.generateMessage(this.state);
        let previousMessageLocal = structuredClone(previousMessage);
        let messageClone = structuredClone(message);

        let keys = Object.keys(message).filter(x => x !== "animation");
        for (let key of keys) {
            if (message[key] === previousMessageLocal[key] ||
                (message[key] instanceof Array && arrayEquals(message[key], previousMessageLocal[key]))) {
                delete message[key];
            }
        }

        this.ws.send(JSON.stringify(message));

        previousMessage = messageClone;
    }

    drawState() {
        const colorSet = Constants.ColorSets[this.state.ColorSet];
        const animation = spaceCapitals(Constants.Animations[this.state.Animation].name);
        const fade = spaceCapitals(Constants.Fades[this.state.Fade]);

        let colors = colorSet.length;
        let gradient = colorSet.map((color, index) => `${color.toHsl()} ${(100 * index / colors)}%, ${color.toHsl()} ${(100 * (index + 1) / colors)}%`).join(', ');
        let colorStyle = `background: linear-gradient(90deg, ${gradient});`;

        let speed = 100 * (this.state.Speed / 255.0);
        let modifier = 100 * (this.state.Modifier / 255.0);

        this.innerHTML = `<div class="repeater">
            
            <h2 class="type">Repeater ${this.dataset.channel}</h2>

            <p class="text-setting">${animation}</p>
            <p class="value-setting" style="background: linear-gradient(90deg, var(--settingHighlight) 0%, var(--settingHighlight) ${speed}%, var(--setting) ${speed}%, var(--setting) 100%);">Speed</p>
            <p class="value-setting" style="background: linear-gradient(90deg, var(--settingHighlight) 0%, var(--settingHighlight) ${modifier}%, var(--setting) ${modifier}%, var(--setting) 100%);">Modifier</p>
            <p class="color-setting" style="${colorStyle}">&nbsp;</p>
            <p class="text-setting">${fade}</p>
        </div>`
    }

    onKeyDown() {
        if (this.animationInterval == null) {
            previousMessage = {};
            this.sendMessage(true);
            this.animationInterval = window.setInterval(() => this.sendMessage(), 0);
        }
    }

    onKeyUp() {
        window.clearInterval(this.animationInterval);
        this.animationInterval = null;

        this.state.reset();
    }
}

customElements.define('animation-repeater', AnimationRepeater);
