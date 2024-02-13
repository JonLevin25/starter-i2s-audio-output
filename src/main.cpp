#include <Arduino.h>

#include "i2s_output_config.h"

// Pins
#define PIN_WORD_SELECT 13  // "LRC"
#define PIN_BCLK 14
#define PIN_DATA_IN 27

Simple_I2S_Output i2s_output;

void setup() {
    Serial.begin(115200);

    i2s_output = Simple_I2S_Output(PIN_WORD_SELECT, PIN_BCLK, PIN_DATA_IN);
    i2s_output.set_sample_rate(44100);
    i2s_output.set_bits_per_sample(I2S_BITS_PER_SAMPLE_16BIT);
    i2s_output.install();
}

void loop() {
    // put your main code here, to run repeatedly:
}
