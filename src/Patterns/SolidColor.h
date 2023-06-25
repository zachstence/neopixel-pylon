#include "Arduino.h"
#include "FastLED.h"

#include "Pattern.h"
#include "../utils.h"

class SolidColor : public Pattern {
public:
    struct Opts {
        CRGBSet leds;
        Palette* palette;  
    };

    SolidColor(Opts opts) : Pattern(), leds(opts.leds) {
        this->setPalette(opts.palette);
    }

    void run() override {
        this->leds = Pattern::color(0);
        FastLED.show();
    }
private:
    CRGBSet leds;
};
