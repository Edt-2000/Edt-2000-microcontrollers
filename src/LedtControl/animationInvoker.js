class AnimationInvoker extends AnimationElementBase {
    state = new AnimationState();
    singleShot = true;

    modifier = true;
    speed = true;
    animation = true;
    colorSet = true;
    fade = true;

    constructor() {
        super();
    }

    connectedCallback() {
        const key = this.dataset.key;

        this.initialize();

        window.addEventListener("keydown", (e) => {
            if (!this.singleShot && this.animationProbablyActive && e.code !== key) {
                this.animationProbablyActive = false;
                this.drawState();
            }

            if (!e.repeat && e.code === key) {
                e.preventDefault();
                this.onKeyDown();
            }
        });

        this.channel = parseInt(this.dataset.channel);

        this.drawState(false);   
    }

    initialize() {
        this.id = `invoker-${this.dataset.channel}-${this.dataset.key}`;

        let state = localStorage.getItem(this.id);
        if (state) {
            Object.assign(this.state, JSON.parse(state));
        }

        if (this.dataset.continuous) {
            this.singleShot = false;
            this.animationProbablyActive = false;
        }

        if (this.dataset.modifier) {
            this.modifier = false;
            if (this.dataset.modifier !== "false") {
                this.state.Modifier = parseInt(this.dataset.modifier);
            }
        }

        if (this.dataset.speed) {
            this.speed = false;
            if (this.dataset.speed !== "false") {
                this.state.Speed = parseInt(this.dataset.speed);
            }
        }

        if (this.dataset.animation) {
            this.animation = false;

            if (this.dataset.animation !== "false") {
                this.state.Animation = Constants.Animations.findIndex(x => x.name === this.dataset.animation);
            }
        }

        if (this.dataset.color) {
            this.colorSet = false;

            this.state.Color = Colors[this.dataset.color];
        }
        else if (this.dataset.colorSet) {
            this.colorSet = false;

            if (this.dataset.colorSet !== "false") {
                this.state.ColorSet = parseInt(this.dataset.colorSet);
            }
        }

        if (this.dataset.fade) {
            this.fade = false;

            if (this.dataset.fade !== "false") {
                this.state.Fade = parseInt(this.dataset.fade);
            }
        }

        if (this.dataset.deviceType) {
            this.state.Units = this.dataset.deviceType.split(',');
        }
    }

    onMessage(message) {
        let newModifier = 1 + (message.s * 2);
        let newSpeed = 1 + (message.i * 2);

        this.animationProbablyActive = !this.singleShot && this.webSocketHandler.previousSender == this;

        let shouldSend = this.animationProbablyActive;

        if (this.animation) {
            if (message.bS) {
                this.state.nextAnimation(this.channel);
            }
        }

        if (this.colorSet) {
            if (message.bM) {
                if (this.animationProbablyActive) {
                    this.state.updateTick();
                }
                else {
                    this.state.nextColorSet();
                }
            }
        }

        if (this.fade) {
            if (message.bR) {
                this.state.nextFade();
            }
        }

        if (this.modifier) {
            this.state.Modifier = newModifier;
        }

        if (this.speed) {
            this.state.Speed = newSpeed;
        }

        if (shouldSend) {
            this.sendMessage(false);
        }

        this.drawState();

        localStorage.setItem(this.id, JSON.stringify(this.state));
    }

    onPreset(preset) {
        if (!(preset instanceof InvokerPreset)) {
            return;
        }

        if (!this.animation && this.state.getAnimation() !== preset.animation){
            return;
        }

        this.dataset.underPreset = true;

        if (this.animation) {
            this.state.setAnimation(preset.animation);
        }

        if (this.colorSet) {
            this.state.setColorSet(preset.colors);
        }

        if (this.fade) {
            this.state.setFade(preset.fade);
        }
        
        if (this.modifier) {
            this.state.Modifier = preset.modifier;
        }

        if (this.speed) {
            this.state.Speed = preset.speed;
        }

        this.drawState();
    }

    onReset() {
        this.initialize();

        this.drawState();
    }

    sendMessage(sendAnimationName) {
        let animation = this.state.getAnimation();

        let message = animation.generateMessage(this.state);

        if (!sendAnimationName) {
            delete message['animation'];
        }

        this.drawState();

        this.webSocketHandler.send(this, message);
    }

    onKeyDown() {
        if (!this.singleShot) {
            this.state.reset();
            this.state.updateTick();
        }
        else {
            this.state.updateTick();
        }

        this.sendMessage(true);
    }

    drawState() {
        const animation = Constants.Animations[this.state.Animation];
        const allowedAnimations = Constants.Animations.filter(x => x.selectable.includes(this.channel));
        const animationName = spaceCapitals(animation.name);
        const fade = spaceCapitals(Constants.Fades[this.state.Fade]);

        let html = `<div>
            <h2 class="type">${this.dataset.key}</h2>`;

        if (!this.dataset.animation) {
            html += `<h2 class="animation">${leftPad(allowedAnimations.indexOf(animation) + 1, 2)}/${allowedAnimations.length}</h2>`;
        }

        html += this.createSettingHtml(animationName, this.dataset.animation, 's', !this.singleShot && this.animationProbablyActive);

        if (this.dataset.speed !== "false") {
            html += this.createValueHtml(this.state.Speed, spaceCapitals(animation.speedDescription ?? "&nbsp;"), this.dataset.speed || animation.speedDescription == null);
        }

        if (this.dataset.modifier !== "false") {
            html += this.createValueHtml(this.state.Modifier, spaceCapitals(animation.modifierDescription ?? "&nbsp;"), this.dataset.modifier);
        }

        if (this.dataset.color) {
            html += this.createColorsHtml([this.state.Color], true, 'm');
        }
        else if (this.dataset.colorSet !== "false") {
            html += this.createColorSetHtml(this.state.ColorSet, this.dataset.colorSet, 'm');
        }

        if (this.dataset.fade !== "false") {
            html += this.createSettingHtml(fade, this.dataset.fade, 'r');
        }

        html += '</div>';

        this.innerHTML = html;
    }
}

customElements.define('animation-invoker', AnimationInvoker);
