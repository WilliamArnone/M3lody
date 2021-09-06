#include <Arduino.h>

class M3lody
{
  public:
    M3lody(uint8_t clockPin, uint8_t dataPin, uint8_t channel);
    ~M3lody();
    bool init();
    bool update();
  private:
    uint8_t octave;
    bool manageKey(uint16_t key);
    bool isKeyPressed(uint8_t state);
    bool canPlay(uint8_t note);
    void playNote(uint8_t note);
    void stopNote(uint8_t note);
    uint8_t _channel;
    uint8_t lastKey;
    void custom(uint8_t value);
};
