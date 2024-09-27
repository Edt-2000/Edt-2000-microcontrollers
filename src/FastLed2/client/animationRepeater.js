class AnimationRepeater extends AnimationElementBase {
    state = new AnimationState();
    previousAnimation = 0;
    animationIndex = 0;

    constructor() {
        super();
    }

    connectedCallback() {
        const keys = this.dataset.key.split(',');

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
            ${this.createSettingHtml(animationName)}
            ${this.createValueHtml(this.state.Speed, "Repeat")}
            ${this.createValueHtml(this.state.Modifier, spaceCapitals(animation.modifierDescription))}
            ${this.createColorSetHtml(this.state.ColorSet)}
            ${this.createSettingHtml(fade)}
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
