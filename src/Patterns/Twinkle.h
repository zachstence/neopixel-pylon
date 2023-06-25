#include "FastLED.h"

#include "Pattern.h"

class Twinkle : public Pattern {
public:
    struct TwinkleSpec {
        uint8_t offset;
        int bpm;
    };

    Twinkle(CRGBSet leds, Palette* palette): Pattern(leds, palette) {
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
            this->leds[i] = CHSV(this->color()->h, this->color()->s, v);
        }

        FastLED.show();
    }

private:
    int bpmMin = 20;
    int bpmMax = 40;

    TwinkleSpec *specs;

    uint8_t beat(uint8_t i) {
        auto spec = this->specs[i];
        return beatsin8(spec.bpm, 0, this->color()->v, 0, spec.offset);
    }

    TwinkleSpec randomTwinkleSpec() {
        auto offset = random8();
        auto bpm = random(this->bpmMin, this->bpmMax + 1);

        return TwinkleSpec { offset, bpm };
    }
};
