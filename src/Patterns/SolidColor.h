#include "FastLED.h"

#include "Pattern.h"

class SolidColor : public Pattern {
public:
    SolidColor(CRGBSet leds, Palette* palette) : Pattern(leds, palette) {}

    void run() override {
        EVERY_N_MILLIS(500) {
            Serial.print("SolidColor.run() ");
            Serial.print(this->color()->h);
            Serial.print(" ");
            Serial.print(this->color()->s);
            Serial.print(" ");
            Serial.print(this->color()->v);
            Serial.println();
        }
        this->leds.fill_solid(*this->color());
        FastLED.show();
        EVERY_N_MILLIS(500) {
            Serial.println("SolidColor.run() done");
        }
    }
};
