#include <Adafruit_SPIDevice.h>
#include <Arduino.h>

class AdaSPI_ADS1118 {
    public:
    AdaSPI_ADS1118(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t cs, uint32_t freq);
    void begin();
    word adsRead(uint8_t port);
    const uint8_t AIN0 = 0x40;
    const uint8_t AIN1 = 0x50;
    const uint8_t AIN2 = 0x60;
    const uint8_t AIN3 = 0x70;

    private:
    uint8_t _config_register[2];
    uint8_t _clk, _miso, _mosi, _cs;
    uint32_t _freq;
    Adafruit_SPIDevice *spi = NULL;
};