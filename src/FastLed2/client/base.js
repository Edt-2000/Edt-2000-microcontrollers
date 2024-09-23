class HSV {
    H = 0;
    S = 0;
    V = 0;

    constructor(h, s, v) {
        this.H = h;
        this.S = s ?? 255;
        this.V = v ?? 255;
    }

    toHsl() {
        let vFactor = this.S == 0 ? 100.0 : 50.0;
        return `hsl(${((360.0 * this.H) / 255.0)} ${((100.0 * this.S) / 255.0)}% ${((vFactor * this.V) / 255.0)}%)`
    }
    toArray() {
        return [this.H, this.S, this.V];
    }
}

class Colors {
    static Black = new HSV(0, 0, 0);
    static Red = new HSV(0);
    static Amber = new HSV(11);
    static Orange = new HSV(18);
    static Yellow = new HSV(58);
    static Lime = new HSV(85);
    static Green = new HSV(95);
    static SeaGreen = new HSV(105);
    static Turquoise = new HSV(129);
    static Blue = new HSV(158);
    static Purple = new HSV(183);
    static Pink = new HSV(238);
    static White = new HSV(0, 0, 255);
}

function getElement(array, index) {
    if (array.length === 0) {
        return null;
    }

    return array[index % array.length];
}

function spaceCapitals(text)  {
    return text.replace(/([A-Z])/g, ' $1').trim();
}

function arrayEquals(a, b) {
    if (a === b) return true;
    if (a == null || b == null) return false;
    if (a.length !== b.length) return false;

    for (let i = 0; i < a.length; ++i) {
        if (a[i] !== b[i]) return false;
    }
    return true;
}

var previousMessage = {};
