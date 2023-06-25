#include "FastLED.h"

#include "Pattern.h"
#include "../utils.h"

class Twinkle : public Pattern {
public:
    struct Opts {
        CRGBSet leds;
        Palette* palette;
    };

    struct TwinkleSpec {
        uint8_t offset;
        int bpm;
    };

    Twinkle(Opts opts): Pattern(), leds(opts.leds) {
        this->setPalette(opts.palette);
        this->specs = new TwinkleSpec[this->leds.len];
        for (auto i = 0; i < this->leds.len; i++) {
            this->specs[i] = this->randomTwinkleSpec();
        }
    }

    ~Twinkle() {
        delete this->specs;
    }

    void run() {
        for (auto i = 0; i < this->leds.len; i++) {
            uint8_t v = this->beat(i);
            this->leds[i] = CHSV(this->color(0).h, this->color(0).s, v);
        }

        FastLED.show();
    }

protected:
    CRGBSet leds;

private:
    int bpmMin = 20;
    int bpmMax = 40;

    TwinkleSpec *specs;

    uint8_t beat(uint8_t i) {
        auto spec = this->specs[i];
        return beatsin8(spec.bpm, 0, this->color(0).v, 0, spec.offset);
    }

    TwinkleSpec randomTwinkleSpec() {
        auto offset = random8();
        auto bpm = random(this->bpmMin, this->bpmMax + 1);

        return TwinkleSpec { offset, bpm };
    }
};
