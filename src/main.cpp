#include <Arduino.h>
#include "Wire.h"
#include "SPI.h"
#include <Adafruit_SharpMem.h>
#include "AdaSPI_ADS1118.h"

#define SHARP_SCK  18
#define SHARP_MOSI 23
#define SHARP_SS   2

AdaSPI_ADS1118 ads(18, 19, 23, 5, 2000000);
Adafruit_SharpMem display(SHARP_SCK, SHARP_MOSI, SHARP_SS, 400, 240);

void setup() {
ads.begin();
}

void loop() {
  Serial.println(ads.adsRead(ads.AIN0));
  display.println("test");
  
  // put your main code here, to run repeatedly:
}
