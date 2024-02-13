#include <Arduino.h>

#include "examples/play_from_spiffs.h"
#include "i2s_output_config.h"

// Pins
#define PIN_WORD_SELECT 13  // "LRC"
#define PIN_BCLK 14
#define PIN_DATA_IN 27

// Example file from https://freesound.org/people/vquesada/sounds/489515/
#define MP3_BELL "/mccathran-hall-bell.mp3"

Simple_I2S_Output i2s_output;

// To run spiffs test, make sure to upload the spiffs image to your Esp32 first!
void setup() {
    Serial.begin(115200);

    i2s_output = Simple_I2S_Output(PIN_WORD_SELECT, PIN_BCLK, PIN_DATA_IN);
    i2s_output.set_sample_rate(44100);
    i2s_output.set_bits_per_sample(I2S_BITS_PER_SAMPLE_16BIT);
    i2s_output.install();

    setup_ex_audio_from_spiffs(&i2s_output, MP3_BELL);
}

void loop() { loop_ex_audio_from_spiffs(); }
