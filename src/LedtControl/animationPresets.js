class AnimationPresets extends HTMLElement {
    currentPreset = 0;
    receivers = [];

    constructor() {
        super();
    }

    connectedCallback() {
        window.addEventListener("keydown", (e) => {
            if (!e.repeat && (e.code === 'ArrowLeft' || e.code === 'ArrowRight')) {
                e.preventDefault();
                this.onKeyDown(e.code === 'ArrowLeft' ? -1 : 1);
            }
        });

        this.drawState();
    }

    setPresetReceivers(receivers) {
        this.receivers = receivers;
    }

    onKeyDown(delta) {
        if (this.currentPreset + delta < 0) {
            this.currentPreset = 0;
        } else if (this.currentPreset + delta >= Presets.items.length) {
            this.currentPreset = Presets.items.length - 1;
        }
        else {
            this.currentPreset += delta;
        }

        let preset = Presets.items[this.currentPreset];

        if (preset != null) {
            this.applyPreset(preset);
        }
        else {
            this.applyReset();
        }

        this.drawState();
    }

    applyPreset(preset) {
        for (let receiver of this.receivers) {
            receiver.resetPresetState();
        }
        for (let channelPreset of preset.channels) {
            for (let receiver of this.receivers) {
                if (receiver.dataset.channel == channelPreset.channel) {
                    receiver.onPreset(channelPreset);
                }
            }
        }
    }

    applyReset() {
        for (let receiver of this.receivers) {
            receiver.resetPresetState();
            receiver.onReset();
        }
    }

    drawState() {
        const preset = Presets.items[this.currentPreset];

        const name = preset?.name ?? "None";

        let html = `<div>`;
        
        html +=`<h2 class="type">Preset ${name.toUpperCase()}</h2>`;

        html += `</div>`;

        this.innerHTML = html;
    }
}

customElements.define('animation-presets', AnimationPresets);
