#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>
#include <RTClib.h>

RTC_DS1307 rtc;

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
  rtc.begin();
  matrix.setTextColor(matrix.Color333(255, 255, 255));
}


void loop() {

  DateTime futureDate(2025, 07, 01, 0, 0, 0);
  DateTime now = rtc.now();
  int remainingYears = futureDate.year() - now.year();
  int remainingMonths = futureDate.month() - now.month();
  int remainingDays = futureDate.day() - now.day();
  int remainingHours = futureDate.hour() - now.hour();
  int remainingMinutes = futureDate.minute() - now.minute();
  int remainingSeconds = futureDate.second() - now.second();

  if (remainingSeconds < 0) {
    remainingMinutes--;
    remainingSeconds += 60;
  }
  if (remainingMinutes < 0) {
    remainingHours--;
    remainingMinutes += 60;
  }
  if (remainingHours < 0) {
    remainingDays--;
    remainingHours += 24;
  }
  if (remainingDays < 0) {
    remainingMonths--;
    remainingDays += daysInMonth(now.year(), now.month());
  }
  if (remainingMonths < 0) {
    remainingYears--;
    remainingMonths += 12;
  }

  matrix.setCursor(1, 1);
  matrix.print("NUR  NOCH");
  delay(1000);
  matrix.fillScreen(0);
  matrix.setCursor(1, 1);
  matrix.println(remainingYears);
  matrix.print("Jahre");
  delay(1000);
  matrix.fillScreen(0);
  matrix.setCursor(1, 1);
  matrix.println(remainingMonths);
  matrix.print("Monate");
  delay(1000);
  matrix.fillScreen(0);
  matrix.swapBuffers(true);
}


int daysInMonth(int year, int month) {
  int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int result = days[month - 1];

  if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
    result++; // Schaltjahr: Februar hat 29 Tage
  }

  return result;
}
