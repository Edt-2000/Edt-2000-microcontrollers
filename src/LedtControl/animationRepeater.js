class AnimationRepeater extends AnimationElementBase {
    state = new AnimationState();
    previousAnimation = 0;
    animationIndex = 0;

    constructor() {
        super();
    }

    connectedCallback() {
        const keys = this.dataset.key.split(',');

        this.initialize();

        window.addEventListener("keydown", (e) => {
            if (!e.repeat && keys.includes(e.code)) {
                e.preventDefault();
                this.onKeyDown();
            }
        });

        window.addEventListener("keyup", (e) => {
            if (keys.includes(e.code)) {
                e.preventDefault();
                this.onKeyUp();
            }
        });

        this.channel = parseInt(this.dataset.channel);

        this.drawState();
    }

    initialize() {
        this.id = `invoker-${this.dataset.channel}-${this.dataset.key}`;

        let state = localStorage.getItem(this.id);
        if (state) {
            Object.assign(this.state, JSON.parse(state));
        }
    }

    onMessage(message) {
        if (message.bS) {
            this.state.nextAnimation(this.channel);
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

        localStorage.setItem(this.id, JSON.stringify(this.state));
    }

    onPreset(preset) {
        if (!(preset instanceof RepeaterPreset)) {
            return;
        }

        this.dataset.underPreset = true;
        
        this.state.setAnimation(preset.animation);
        this.state.setColorSet(preset.colors);
        this.state.setFade(preset.fade);
        this.state.Modifier = preset.modifier;
        this.state.Speed = preset.repeat;
        this.state.RepeatTime = (145 - (preset.repeat / 2)) * 3;

        this.drawState();
    }

    onReset() {
        this.initialize();

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

        this.webSocketHandler.send(this, message);
    }

    drawState() {
        const animation = Constants.Animations[this.state.Animation];
        const allowedAnimations = Constants.Animations.filter(x => x.selectable.includes(this.channel));
        const animationName = spaceCapitals(animation.name);
        const fade = spaceCapitals(Constants.Fades[this.state.Fade]);

        this.innerHTML = `<div>
            <h2 class="type">Repeater ${this.dataset.channel}</h2>
            <h2 class="animation">${leftPad(allowedAnimations.indexOf(animation) + 1, 2)}/${allowedAnimations.length}</h2>
            ${this.createSettingHtml(animationName, false, 's')}
            ${this.createValueHtml(this.state.Speed, "Repeat")}
            ${this.createValueHtml(this.state.Modifier, spaceCapitals(animation.modifierDescription))}
            ${this.createColorSetHtml(this.state.ColorSet, false, 'm')}
            ${this.createSettingHtml(fade, false, 'r')}
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

        this.state.reset();
    }
}

customElements.define('animation-repeater', AnimationRepeater);
