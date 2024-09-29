class Animation {
    name = "";
    selectable = [0, 1, 2, 3, 4, 5, 6, 7];
    modifierDescription = "Modifier";
    speedDescription = "Speed";

    generateMessage(state) { }
}

class SinglePulseAnimation extends Animation {
    constructor(isAll) {
        super();
        this.isAll = isAll;
        this.name = isAll ? "allSinglePulse" : "oneSinglePulse";
        this.modifierDescription = "fadeSpeed";
        this.speedDescription = null;
    }

    generateMessage(state) {
        let colorSet = state.getColorSet();

        let message = {
            animation: "singlePulse",
            led: this.isAll ? Leds.All : Leds.getLeds(),
            color1: getElement(colorSet, state.Tick).toArray(),
            color2: getElement(colorSet, state.Tick + 1).toArray(),
            fade: state.getFade(),
            speed: state.Modifier
        };

        return message;
    }
}

class SinglePartialPulseAnimation extends Animation {
    constructor(isAll) {
        super();
        this.isAll = isAll;
        this.name = isAll ? "allSinglePartialPulse" : "oneSinglePartialPulse";
        this.modifierDescription = "percentage";
        this.speedDescription = null;
    }

    generateMessage(state) {
        let colorSet = state.getColorSet();

        let message = {
            animation: 'singlePartialPulse',
            led: this.isAll ? Leds.All : Leds.getLeds(),
            color1: getElement(colorSet, state.Tick).toArray(),
            color2: getElement(colorSet, state.Tick + 1).toArray(),
            fade: state.getFade(),
            speed: 30,
            percentage: state.Modifier
        };

        return message;
    }
}

class DoublePulseAnimation extends Animation {
    constructor(isAll) {
        super();
        this.isAll = isAll;
        this.name = isAll ? "allDoublePulse" : "oneDoublePulse";
        this.modifierDescription = "percentage";
        this.speedDescription = "fadeSpeed";
    }

    generateMessage(state) {
        let colorSet = state.getColorSet();

        // use the same colors every tick if there are only 2
        let tick = colorSet.length == 2 ? 0 : state.Tick;

        let message = {
            animation: 'doublePulse',
            led: this.isAll ? Leds.All : Leds.getLeds(),
            color1: getElement(colorSet, tick).toArray(),
            color2: getElement(colorSet, tick + 1).toArray(),
            fade: state.getFade(),
            speed: Math.min(255, state.Speed * 3),
            percentage: state.Modifier
        };

        return message;
    }
}

class SingleChaseAnimation extends Animation {
    constructor(isAll, angle) {
        super();
        this.isAll = isAll;
        this.angle = angle;
        this.name = `${isAll ? "all" : "one"}SingleChase${getAngle(angle)}`;
        this.modifierDescription = "chaseSpeed";
        this.speedDescription = null;

        this.selectable = angle == 64 || angle == 128 ? [0, 2, 4, 6] : [1, 3, 5, 7];
    }

    generateMessage(state) {
        let colorSet = state.getColorSet();

        let message = {
            animation: 'singleChase',
            led: this.isAll ? Leds.All : Leds.getLeds(),
            angle: this.angle,
            color1: getElement(colorSet, state.Tick).toArray(),
            color2: getElement(colorSet, state.Tick + 1).toArray(),
            fade: state.getFade(),
            speed: state.Modifier
        };

        return message;
    }
}

class DoubleChaseAnimation extends Animation {
    constructor(isAll, angle) {
        super();
        this.isAll = isAll;
        this.angle = angle;
        this.name = `${isAll ? "all" : "one"}DoubleChase${getAngle(angle)}`;
        this.modifierDescription = "chaseSpeed";
        this.speedDescription = null;

        this.selectable = angle == 128 ? [0, 2, 4, 6] : [1, 3, 5, 7];
    }

    generateMessage(state) {
        let colorSet = state.getColorSet();

        let tick = colorSet.length == 2 ? 0 : state.Tick;

        let message = {
            animation: 'doubleChase',
            led: this.isAll ? Leds.All : Leds.getLeds(),
            angle: this.angle,
            color1: getElement(colorSet, tick).toArray(),
            color2: getElement(colorSet, tick + 1).toArray(),
            fade: state.getFade(),
            speed: state.Modifier
        };

        return message;
    }
}

class StroboAnimation extends Animation {
    constructor() {
        super();
        this.name = "strobo";
        this.selectable = [];
        this.modifierDescription = "speed";
        this.speedDescription = null;
    }

    generateMessage(state) {
        let colorSet = state.getColorSet();

        let message = {
            animation: 'strobo',
            color1: getElement(colorSet, state.Tick).toArray(),
            color2: getElement(colorSet, state.Tick + 1).toArray(),
            speed: state.Modifier
        };

        return message;
    }
}

class FireAnimation extends Animation {
    constructor() {
        super();
        this.name = "fire";
        this.selectable = [];
        this.modifierDescription = "heat";
        this.speedDescription = null;
    }

    generateMessage(state) {
        let message = {
            animation: 'fire',
            speed: state.Modifier
        };

        return message;
    }
}

class NoiseAnimation extends Animation {
    constructor() {
        super();
        this.name = "noise";
        this.selectable = [];
        this.modifierDescription = "intensity";
        this.speedDescription = null;
    }

    generateMessage(state) {
        let message = {
            animation: 'noise',
            speed: state.Modifier
        };

        return message;
    }
}

class StopAnimation extends Animation {
    constructor() {
        super();
        this.name = "stop";
        this.selectable = [];
        this.modifierDescription = null;
        this.speedDescription = null;
    }

    generateMessage(state) {
        let message = {
            animation: this.name
        };

        return message;
    }
}

class Constants {
    static Animations = [
        new SinglePulseAnimation(true),
        new SinglePartialPulseAnimation(true),
        new DoublePulseAnimation(true),
        new SinglePulseAnimation(false),
        new SinglePartialPulseAnimation(false),
        new DoublePulseAnimation(false),
        new SingleChaseAnimation(true, 0),
        new SingleChaseAnimation(true, 128),
        new SingleChaseAnimation(true, 64),
        new SingleChaseAnimation(true, 192),
        new DoubleChaseAnimation(true, 0),
        new DoubleChaseAnimation(true, 128),
        new SingleChaseAnimation(false, 0),
        new SingleChaseAnimation(false, 128),
        new SingleChaseAnimation(false, 64),
        new SingleChaseAnimation(false, 192),
        new DoubleChaseAnimation(false, 0),
        new DoubleChaseAnimation(false, 128),
        new StroboAnimation(),
        new FireAnimation(),
        new NoiseAnimation(),
        new StopAnimation()
    ];
    static ColorSets = [
        [Colors.Red, Colors.White],
        [Colors.Red, Colors.Blue],
        [Colors.Turquoise, Colors.Pink],
        [Colors.Pink],
        [Colors.Green, Colors.Orange],
        [Colors.Green, Colors.White],
        [Colors.Red, Colors.Orange],
        [Colors.Red, Colors.Orange, Colors.Yellow, Colors.Lime, Colors.Green, Colors.SeaGreen, Colors.Turquoise, Colors.Blue, Colors.Purple, Colors.Pink],
        [Colors.Red, Colors.Yellow, Colors.Pink, Colors.SeaGreen, Colors.Purple, Colors.Turquoise, Colors.Green, Colors.Orange, Colors.Blue, Colors.Lime],
        [Colors.Rainbow],
        [Colors.White]
    ];
    static Fades = ['none', 'fadeAll', 'oneByOne', 'sparkle'];
}

class AnimationState {
    // animations
    Modifier = 0;
    Speed = 0;
    Animation = 0;
    Color = null;
    ColorSet = 0;
    Fade = 0;

    // timings
    RepeatTime = 0;
    Tick = -1;

    getAnimation() { return Constants.Animations[this.Animation]; }
    nextAnimation(channel) {
        this.Animation++;
        if (this.Animation >= Constants.Animations.length) {
            this.Animation = 0;
        }
        if (!this.getAnimation().selectable.includes(channel)) {
            this.nextAnimation(channel);
        }
    }
    getColorSet() { return this.Color ? [this.Color] : Constants.ColorSets[this.ColorSet]; }
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
