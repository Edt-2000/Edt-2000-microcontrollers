#pragma once

namespace Drivers
{
class RgbLedDriver
{
private:
public:
    virtual inline void reset() = 0;
    virtual inline void output(int r, int g, int b) = 0;
};
} // namespace Drivers

// inline void Animators::RgbLedAnimator::output() {
// 	// moronic pinout:
// 	//
// 	// | AUX | LED 1 | LED 2 | LED 3  | LED 4    | LED 5   |
// 	// | 1   | 2 3 4 | 5 6 7 | 8 9 10 | 11 12 13 | 14 15 0 |
// 	// |     | G B R | G B R | G B R  | G  B  R  | G  B  R |
// 	//
// 	// (who designed the board? :P)

// 	// tclAddress is a struct with a 4 bit integer
// 	// so 15 + 1 = 0 automatically
// 	tlcAddress tlc;

// 	tlc.address = 1;

// 	for (int i = 0; i < nrOfLeds; i++) {
// 		uint8_t red = _leds[i].red;
// 		uint8_t blue = qsub8(_leds[i].blue, red / 8);
// 		uint8_t green = qsub8(qsub8(_leds[i].green, red / 6), blue / 8);

// 		_tlc->set(++tlc.address, 4095 - (int)((((double)green) / 255.0) * 4095));
// 		_tlc->set(++tlc.address, 4095 - (int)((((double)blue) / 255.0) * 4095));
// 		_tlc->set(++tlc.address, 4095 - (int)((((double)red) / 255.0) * 4095));
// 	}
// }