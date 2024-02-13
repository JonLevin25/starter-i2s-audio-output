#include "play_from_sd.h"

#include <AudioFileSourceID3.h>
#include <AudioFileSourceSD.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2SNoDAC.h>

static AudioGeneratorMP3 *mp3;
static AudioOutputI2S *out;
static AudioFileSourceID3 *id3;
static AudioFileSourceSD *file;
static bool is_playing = false;
static String songName;

static Simple_I2S_Output *_i2s_output;

static void start_audio(const char *fileName);
static void stop_audio();
static void metadataCB(void *cbData, const char *type, bool isUnicode,
                       const char *string);

// test functions (setup/loop)
void setup_ex_audio_from_sd(Simple_I2S_Output *i2s_output,
                            const char *fileName) {
    if (!i2s_output || !i2s_output->is_installed()) {
        Serial.println(
            "Tried to setup audio, but the Simple_I2S_Output "
            "was either null or not installed!");
        return;
    }
    Serial.println("");
    delay(1000);

    audioLogger = &Serial;

    Serial.println("audio setup complete.");

// NOTE: SD.begin(...) should be called AFTER AudioOutputSPDIF()
//       to takover the the SPI pins if they share some with I2S
//       (i.e. D8 on Wemos D1 mini is both I2S BCK and SPI SS)
#if defined(ESP8266)
    SD.begin(SS, SPI_SPEED);
#else
    SD.begin();
#endif

    Serial.println("SD setup complete.");
    Serial.println("Trying to playing example file from Sd...");

    // Play on awake
    start_audio(fileName);
}

void loop_ex_audio_from_sd() {
    if (!mp3 || !mp3->isRunning()) return;
    bool _continue = mp3->loop();
    if (!_continue) {
        stop_audio();
    }
}

// audio functions
static void start_audio(const char *fileName) {
    printf("start_audio_sd: %s\n", fileName);

    if (is_playing) stop_audio();
    is_playing = true;
    songName = String(fileName);

    auto ms_before = millis();

    file = new AudioFileSourceSD(fileName);
    id3 = new AudioFileSourceID3(file);
    id3->RegisterMetadataCB(metadataCB, (void *)"ID3TAG");
    out = new AudioOutputI2S();  // should be same as AudioOutputI2SNoDAC()
    mp3 = new AudioGeneratorMP3();

    printf("File loaded (open: %i, size: %u)\n", file->isOpen(),
           file->getSize());

    auto ms_after = millis();  // 30ms max
    Serial.printf("Playing file!... setup took: %lu\n", ms_after - ms_before);

    mp3->begin(id3, out);
}

static void stop_audio() {
    mp3->stop();
    free(file);
    free(id3);
    free(out);
    free(mp3);

    is_playing = false;
    Serial.println("MP3 end cleanup finished");
}

// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.)
static void metadataCB(void *cbData, const char *type, bool isUnicode,
                       const char *string) {
    (void)cbData;
    Serial.printf("ID3 callback for: %s = '", type);

    if (isUnicode) {
        string += 2;
    }

    while (*string) {
        char a = *(string++);
        if (isUnicode) {
            string++;
        }
        Serial.printf("%c", a);
    }
    Serial.printf("'\n");
    Serial.flush();
}