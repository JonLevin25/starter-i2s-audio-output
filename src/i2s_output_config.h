#pragma once

#include <Arduino.h>

#include "driver/i2s.h"

class Simple_I2S_Output {
   private:
    uint8_t pin_ws;
    uint8_t pin_bclk;
    uint8_t pin_data_in;
    uint32_t sample_rate;
    i2s_bits_per_sample_t bits_per_sample;
    i2s_port_t i2s_num = I2S_NUM_0;
    bool is_init = false;

   public:
    Simple_I2S_Output() {
    }  // allow having uninitialized variable at top of main file

    Simple_I2S_Output(
        uint8_t pin_ws, uint8_t pin_bclk, uint8_t pin_data_in,
        uint32_t sample_rate = 44100,
        i2s_bits_per_sample_t bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT)
        : is_init(true),
          pin_ws(pin_ws),
          pin_bclk(pin_bclk),
          pin_data_in(pin_data_in),
          sample_rate(sample_rate),
          bits_per_sample(bits_per_sample) {}

    uint32_t get_sample_rate() { return sample_rate; }
    void set_sample_rate(uint32_t sample_rate) {
        this->sample_rate = sample_rate;
    }

    i2s_bits_per_sample_t get_bits_per_sample() { return bits_per_sample; }
    void set_bits_per_sample(i2s_bits_per_sample_t bits_per_sample) {
        this->bits_per_sample = bits_per_sample;
    }

    i2s_port_t get_i2s_num() { return i2s_num; }
    void set_i2s_num(i2s_port_t i2s_num) { this->i2s_num = i2s_num; }

    void install();

    // Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
    void i2s_metadata_callback(void *cbData, const char *type, bool isUnicode,
                               const char *string);
};
