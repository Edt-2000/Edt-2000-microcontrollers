class AnimationConfigurator extends AnimationElementBase {
    constructor() {
        super();
    }

    connectedCallback() {
        this.id = `configurator-${this.dataset.channel}`;

        

        this.channel = parseInt(this.dataset.channel);

        this.drawState(false);
    }

    onMessage(message) {
        if (message.bS) {
            Leds.nextConfig();
        }

        this.drawState();
    }

    drawState() {
        let html = `<div><h2 class="type">Config</h2>`;

        html += this.createSettingHtml(Leds.getConfig());

        html += '</div>';

        this.innerHTML = html;
    }
}

customElements.define('animation-configurator', AnimationConfigurator);