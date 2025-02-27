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

    onSelectUpdate(s) {
        let newHue = (s * 2);

        this.hue = newHue;

        this.drawState();
    }

    onIntensityUpdate(i) {

    }

    onButtonPress(s, m, r) {
        if (s) {
            Leds.nextConfig();
        }

        if (m) {
            let hueChanged = this.hue != this.outputHue;
            if (hueChanged) {
                this.output = 1;
            }
            else {
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

        if (r) {
            FastLedUnits.nextConfig();
        }

        this.drawState();
    }

    onPreset(preset) {
        if (!preset instanceof ConfiguratorPreset) {
            return;
        }

        if (preset.color != null) {
            this.hue = preset.color.H;
        }
        if (preset.config != null) {
            Leds.setConfig(preset.config);
        }
        this.outputHue = -1;
        this.output = 1;

        this.drawState();
    }

    drawState() {
        let html = `<div><h2 class="type">Config</h2>`;

        html += this.createSettingHtml(Leds.getConfig(), false, 's');

        let colorStyle = `background: hsl(${360.0 * (this.hue / 255.0)} 100% 50%);`;

        html += `<p class="color-setting" style="${colorStyle}" data-button="m">${this.output * 20}% color</p>`;

        let fastLedColorStyle = FastLedUnits._activeMode == 0 ? '' : 'background: red';

        html += `<p class="text-setting" style="${fastLedColorStyle}" ${this.createButtonHtml('r')}>${FastLedUnits.getUnits().join(', ')}</p>`;

        html += '</div>';

        this.innerHTML = html;
    }
}

customElements.define('animation-configurator', AnimationConfigurator);
