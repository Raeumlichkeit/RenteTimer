
#include <TimeLib.h>
#include <I2C_RTC.h>
#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>


#define CLK 8
#define LAT A3
#define OE 9
#define A A0
#define B A1
#define C A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);


const unsigned long RENTE = 68806320;
unsigned long jetzt;
static DS1307 RTC;

int tage;
int monate;
int jahre;
int resttage;
int hue = 0;

/*char* str = RTC.getWeek();
int textX = matrix.width(),
    textMin = strlen(str) * -12;*/


void setup() {
  Serial.begin(9600);
  matrix.begin();
  RTC.begin();
  matrix.setTextWrap(false);  // Allow text to run off right edge
  matrix.setTextSize(2);
  if (RTC.isRunning())
    Serial.println("Yes");
  else
    Serial.println("No. Time may be Inaccurate");
}

void loop() {
  // Berechnung der verbleibenden Zeit
  jetzt = now();
  unsigned long remaining_seconds = RENTE - jetzt;
  tage = remaining_seconds / 86400;
  jahre = tage / 365;
  monate = (tage % 365) / 30;
  resttage = tage % 30;
  matrix.fillScreen(0);
matrix.setCursor(0 , 0);
matrix.print(RTC.getWeek());
Serial.print(RTC.getWeek());
delay(15);
 /* matrix.setTextColor(matrix.ColorHSV(hue, 255, 255, true));
  matrix.setCursor(textX, 1);
  matrix.print(RTC.getMonth());
  delay(15);

  // Move text left (w/wrap), increase hue
  if ((--textX) < textMin) textX = matrix.width();
  hue += 1;
  if (hue >= 1536) hue -= 1536;*/

  // Update display
  matrix.swapBuffers(true);
}
