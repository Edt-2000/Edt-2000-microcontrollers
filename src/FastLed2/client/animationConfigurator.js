class AnimationConfigurator extends AnimationElementBase {
    constructor() {
        super();
    }

    connectedCallback() {
        this.id = `configurator-${this.dataset.channel}`;

        this.hue = 0;
        this.outputHue = 0;
        this.output = 1;
        this.fastLedUnit = 3;

        this.channel = parseInt(this.dataset.channel);

        this.drawState(false);
    }

    onMessage(message) {
        if (message.bS) {
            Leds.nextConfig();
        }

        if (message.bR) {
            FastLedUnits.nextConfig();
        }


        let newHue = (message.s * 2);
        let hueChanged = newHue != this.outputHue;
        if (hueChanged) {
            this.output = 1;
        }
        this.hue = newHue;

        if (message.bM) {
            if (!hueChanged) {
                this.output = (this.output % 5) + 1;
            }

            this.outputHue = this.hue;
            let color = new HSV(this.hue, 255, this.output * 50);
            this.webSocketHandler.send(this, {
                animation: 'singlePulse',
                led: 255,
                fade: 0,
                color1: color.toArray(),
                color2: color.toArray(),
                speed: 0,
                units: FastLedUnits.getUnits()
            });
        }

        this.drawState();
    }

    drawState() {
        let html = `<div><h2 class="type">Config</h2>`;

        html += this.createSettingHtml(Leds.getConfig(), false, 's');

        let colorStyle = `background: hsl(${360.0 * (this.hue / 255.0)} 100% 50%);`;

        html += `<p class="color-setting" style="${colorStyle}" data-button="m">${this.output * 20}% color</p>`;

        let fastLedColorStyle = FastLedUnits._activeMode + 1 == FastLedUnits._modes.length ? '' : 'background: red';

        html += `<p class="text-setting" style="${fastLedColorStyle}" ${this.createButtonHtml('r')}>${FastLedUnits.getUnits().join(', ')}</p>`;

        html += '</div>';

        this.innerHTML = html;
    }
}

customElements.define('animation-configurator', AnimationConfigurator);