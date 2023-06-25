#include "FastLED.h"

#include "Pattern.h"

class Rainbow : public Pattern {
public:
    struct Opts {
        int bpm;
        uint8_t hueDelta;
    };

    Rainbow(CRGBSet leds, Palette* palette, Direction direction, Opts opts) :
        Pattern(leds, palette, direction),
        bpm(opts.bpm)
    {
        uint8_t hueStart = 0;
        uint8_t hueEnd = this->leds.size() * opts.hueDelta;

        if (this->direction == Direction::Forward) {
            this->hueStart = hueStart;
            this->hueDelta = opts.hueDelta;
        } else {
            this->hueStart = hueEnd;
            this->hueDelta = -1 * opts.hueDelta;
        }
    }

    void run() override {
        uint8_t offset = beat8(this->bpm);
        this->leds.fill_rainbow(this->hueStart + offset, this->hueDelta);
        FastLED.show();
    }

private:
int bpm;
    uint8_t hueStart;
    uint8_t hueDelta;
};
