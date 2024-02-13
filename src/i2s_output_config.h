#pragma once

#include <Arduino.h>

#include "driver/i2s.h"

class Simple_I2S_Output {
   private:
    uint8_t _pin_ws;
    uint8_t _pin_bclk;
    uint8_t _pin_data_in;
    uint32_t _sample_rate;
    i2s_bits_per_sample_t _bits_per_sample;
    i2s_port_t _i2s_num = I2S_NUM_0;
    bool _is_init = false;
    bool _is_installed = false;

   public:
    Simple_I2S_Output() {
    }  // allow having uninitialized variable at top of main file

    Simple_I2S_Output(
        uint8_t pin_ws, uint8_t pin_bclk, uint8_t pin_data_in,
        uint32_t sample_rate = 44100,
        i2s_bits_per_sample_t bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT)
        : _is_init(true),
          _pin_ws(pin_ws),
          _pin_bclk(pin_bclk),
          _pin_data_in(pin_data_in),
          _sample_rate(sample_rate),
          _bits_per_sample(bits_per_sample) {}

    uint32_t get_sample_rate() { return _sample_rate; }
    void set_sample_rate(uint32_t sample_rate) {
        this->_sample_rate = sample_rate;
    }

    i2s_bits_per_sample_t get_bits_per_sample() { return _bits_per_sample; }
    void set_bits_per_sample(i2s_bits_per_sample_t bits_per_sample) {
        this->_bits_per_sample = bits_per_sample;
    }

    i2s_port_t get_i2s_num() { return _i2s_num; }
    void set_i2s_num(i2s_port_t i2s_num) { this->_i2s_num = i2s_num; }

    bool is_installed() { return _is_installed; }
    void install();

    // Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
    void i2s_metadata_callback(void *cbData, const char *type, bool isUnicode,
                               const char *string);
};
