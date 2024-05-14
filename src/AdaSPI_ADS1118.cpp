#include "AdaSPI_ADS1118.h"
    
AdaSPI_ADS1118::AdaSPI_ADS1118(uint8_t clk, uint8_t miso, uint8_t mosi, uint8_t cs, uint32_t freq = 2000000) {
    _clk = clk;
    _miso = miso;
    _mosi = mosi;
    _cs = cs;
    _freq = freq;
}
void AdaSPI_ADS1118::begin() {
    spi = new Adafruit_SPIDevice(_cs, _clk, _miso, _mosi, _freq, SPI_BITORDER_MSBFIRST);
    spi->begin();

    // Config register below
    //MSB : 
    _config_register[0] = _BV(2); // 010 = FSR is ±2.048 V (default)

    _config_register[1] = 
    _BV (1) ||    //update the Config register
    _BV (3) ||    //enable pullup
    _BV (7);    //100 = 128 SPS (default )

    Serial.println("Config register:");
    Serial.println( _config_register[0], BIN);
    Serial.println( _config_register[1], BIN);
}

word AdaSPI_ADS1118::adsRead(uint8_t port) {
    uint8_t data[2];
    data[0] |= port;
    memcpy(&data, &_config_register, 2);
    spi->write_and_read(data, 16);
    return word(data[0], data[1]);
}

/* Datarate (7:5 of config register )

000 = 8 SPS
001 = 16 SPS
010 = 32 SPS
011 = 64 SPS
100 = 128 SPS (default)
101 = 250 SPS
110 = 475 SPS
111 = 860 SPS

Programmable gain amplifier configuration (11:9 of config register)
These bits configure the programmable gain amplifier.
000 = FSR is ±6.144 V(1)
001 = FSR is ±4.096 V(1)
010 = FSR is ±2.048 V (default)
011 = FSR is ±1.024 V
100 = FSR is ±0.512 V
101 = FSR is ±0.256 V
110 = FSR is ±0.256 V
111 = FSR is ±0.256 V
*/