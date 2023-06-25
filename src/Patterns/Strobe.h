#include "FastLED.h"

#include "Pattern.h"

class Strobe : public Pattern {
public:
    struct Opts {
        int bpm;
    };
    
    Strobe(CRGBSet leds, Palette* palette, Opts opts): Pattern(leds, palette), bpm(opts.bpm) {
        this->periodMs = 60000 / this->bpm;
        this->nextToggle = millis();
    }

    void run() {
        if (millis() >= this->nextToggle) {
            this->on = !this->on;
            this->nextToggle = millis() + this->periodMs;
        }
        
        if (this->on) {
            this->leds = *palette[0];
        } else {
            this->leds = CRGB::Black;
        }

        FastLED.show();
    }

protected:
    int bpm;

private:
    int periodMs;
    bool on = true;
    unsigned long nextToggle;
};