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
        if (this.dataset.continuous) {
            this.singleShot = false;
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
                this.state.Animation = Constants.Animations.findIndex(x => x.name === this.dataset.animation)
            }
        }

        // TODO: allow for configuring specific colors instead of a set (for 1->0)

        if (this.dataset.colorSet) {
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

        const key = this.dataset.key;

        window.addEventListener("keydown", (e) => {
            if (!e.repeat && e.code === key) {
                this.onKeyDown();
            }
        })

        this.drawState(false);
    }

    onMessage(message) {
        let newModifier = 1 + (message.s * 2);
        let newSpeed = 1 + (message.i * 2);

        let animationProbablyActive = !this.singleShot && this.webSocketHandler.previousSender == this;

        let shouldSend = animationProbablyActive;

        if (this.animation) {
            if (message.bS) {
                this.state.nextAnimation();
            }
        }

        if (this.colorSet) {
            if (message.bM) {
                if (animationProbablyActive) {
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
    }

    sendMessage(sendAnimationName) {
        let animation = this.state.getAnimation();

        let message = animation.generateMessage(this.state);

        if (!sendAnimationName) {
            delete message['animation'];
        }

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
        const animation = spaceCapitals(Constants.Animations[this.state.Animation].name);
        const fade = spaceCapitals(Constants.Fades[this.state.Fade]);

        // TODO: this should make clear some settings are disabled

        let html = `<div>
            
            <h2 class="type">${this.dataset.key}</h2>

            <p class="text-setting">${animation}</p>`;

        if (this.dataset.speed !== "false") {
            html += this.createSettingHtml(this.state.Speed, "Speed");
        }

        if (this.dataset.modifier !== "false") {
            html += this.createSettingHtml(this.state.Modifier, "Modifier");
        }

        if (this.dataset.dataSet !== "false") {
            html += this.createColorSetHtml(this.state.ColorSet);
        }

        if (this.dataset.fade !== "false") {
            html += `<p class="text-setting">${fade}</p>`;
        }

        html += '</div>';

        this.innerHTML = html;
    }
}

customElements.define('animation-invoker', AnimationInvoker);