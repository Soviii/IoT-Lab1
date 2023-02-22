#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Adafruit_CAP1188.h>

#include <Wire.h>
#include <SPI.h>




// Part 1
TFT_eSPI tft = TFT_eSPI(135, 240);
//End of Part 1

// Part 2
// Adafruit_CAP1188 cap = Adafruit_CAP1188();
// End of Part 2

//Part 3
// pins for SPI
int cs_pin = GPIO_NUM_26;
int clk_pin = GPIO_NUM_25;
int miso_pin = GPIO_NUM_33;
int mosi_pin = GPIO_NUM_32;
int reset_pin = GPIO_NUM_13;
int sck_pin = GPIO_NUM_25;

// initialization for object when using SPI 
Adafruit_CAP1188 cap = Adafruit_CAP1188(clk_pin, miso_pin, mosi_pin, cs_pin, reset_pin);
// End of Part 3


// counts number of sensors being touched/activated, for both part 2 and part 3
int counter = 0;

void setup() {
  Serial.begin(9600);

  // Part 1 (ungraded)
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_DARKGREEN);
  // tft.fillScreen(TFT_PINK);
  tft.setTextSize(3);
  tft.setTextColor(TFT_WHITE);
  // tft.setTextColor(TFT_BLUE);
  tft.setCursor(0,0);
  tft.setTextDatum(MC_DATUM);
  tft.setTextSize(5);
  

  // Part 2 
  // initialize the sensor, if using i2c you can pass in the i2c address
  /*
  cap.begin();
  if (!cap.begin(0x28)) {
  if (!cap.begin(0x28)) {
    Serial.println("CAP1188 not found");
    while (1);
  }
  Serial.println("CAP1188 found!");
  */

  // Part 3
  // initialize sensor via SPI initialization for cap object
  sleep(1);
  if(!cap.begin()){
    Serial.println("CAP1188 not found");
    while(1){};
  }
  Serial.println("CAP1188 found!");



}

void loop() {

  // Part 1
  /*
  tft.fillScreen(TFT_PINK);
  tft.drawString(String(counter), tft.width()/2, tft.height()/2-16);
  sleep(1);
  counter++;
  */


  // Part 2 & Part 3
  uint8_t touched = cap.touched();

  if (touched == 0) {
    // No touch detected
    Serial.println("None");
  } else {
    Serial.println("Active!");
  }
  
  // if a sensor is being active, then increment counter
  for (uint8_t i=0; i<8; i++) {
    if (touched & (1 << i)) {
      counter += 1;
    }
  }

  // fill screen with green and write counter to screen
  tft.fillScreen(TFT_DARKGREEN);
  // tft.fillScreen(TFT_PINK);
  tft.drawString(String(counter), tft.width()/2, tft.height()/2-16);
  counter = 0;

  delay(150);
  
}
