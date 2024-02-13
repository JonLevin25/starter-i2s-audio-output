#pragma once

#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>

#include "SPIFFS.h"
#else
#include <ESP8266WiFi.h>
#endif

#include "../i2s_output_config.h"

// test functions (setup/loop)
void setup_ex_audio_from_sd(Simple_I2S_Output *i2s_output,
                            const char *fileName);

void loop_ex_audio_from_sd();

// void start_audio(const char *fileName);
// void stop_audio();
