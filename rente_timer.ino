
#include <DS1307RTC.h>
#include <TimeLib.h>
#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>

int Jahre;
int Monate;
int Tage = "Rest von diesem";


#define CLK 8
#define LAT A3
#define OE 9
#define A A0
#define B A1
#define C A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);


  void setup() {
  Serial.begin(9600);
  matrix.begin();
  setSyncProvider(RTC.get);
  matrix.setTextColor(matrix.Color333(255, 255, 255));
}


void loop() {
  Berechnung();
  matrix.setCursor(1, 1);
  matrix.print("NUR  NOCH");
  delay(1000);
  matrix.fillScreen(0);
  matrix.setCursor(1, 1);
  matrix.println(Jahre);
  matrix.print("Jahre");
  delay(1000);
  matrix.fillScreen(0);
  matrix.setCursor(1, 1);
  matrix.println(month());
  matrix.print("Monate");
  delay(1000);
  matrix.fillScreen(0);
  matrix.swapBuffers(true);
}

void Berechnung(){
int jetztjahr = year();
int jetztmonat = month();







Serial.println(jetztmonat);
Serial.println(Monate);
}
