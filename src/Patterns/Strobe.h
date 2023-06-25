#include "FastLED.h"

#include "Pattern.h"

class Strobe : public Pattern {
public:
    struct Opts {
        CRGBSet leds;
        Palette* palette;
        int bpm;
    };
    
    Strobe(Opts opts):
        Pattern(),
        leds(opts.leds),
        bpm(opts.bpm)
    {
        this->setPalette(opts.palette),
        this->periodMs = 60000 / this->bpm;
        this->nextToggle = millis();
    }

    void run() {
        if (millis() >= this->nextToggle) {
            this->on = !this->on;
            this->nextToggle = millis() + this->periodMs;
        }
        
        if (this->on) {
            this->leds = this->color(0);
        } else {
            this->leds = CRGB::Black;
        }

        FastLED.show();
    }

protected:
    CRGBSet leds;
    int bpm;

private:
    int periodMs;
    bool on = true;
    unsigned long nextToggle;
};