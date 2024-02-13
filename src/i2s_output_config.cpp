#include "i2s_output_config.h"

#include <Arduino.h>

#include "driver/i2s.h"

void Simple_I2S_Output::install() {
    if (!_is_init) {
        Serial.println(
            "Simple_I2S_Output was not not initialized before calling "
            "install()!");
        return;
    }

    _is_installed = true;

    auto mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
    i2s_config_t i2s_config = {
        .mode = mode,
        .sample_rate = _sample_rate,
        .bits_per_sample = _bits_per_sample,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags =
            ESP_INTR_FLAG_LEVEL1,  // Interrupt level 1, default 0
        .dma_buf_count = 8,        // .dma_desc_num = 8,
        .dma_buf_len = 64,         // .dma_frame_num = 64,
        .use_apll = false,
        .tx_desc_auto_clear = false,
    };

    static const i2s_pin_config_t pin_config = {
        .bck_io_num = _pin_bclk,
        .ws_io_num = _pin_ws,
        .data_out_num = _pin_data_in,
        .data_in_num = I2S_PIN_NO_CHANGE};

    i2s_driver_install(_i2s_num, &i2s_config, 0, NULL);
    i2s_set_pin(_i2s_num, &pin_config);
}
