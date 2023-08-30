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

#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

int ende = false;
int remainingYears;
int remainingMonths;
volatile int remainingDays;

const char str[] PROGMEM = "und den Rest von Diesem";
int16_t    textX         = 32,
           textMin       = (int16_t)sizeof(str) * -12;

const char str1[] PROGMEM = "Moeller 0 : 1 Commodity";

void setup() {
  Serial.begin(9600);
  matrix.begin();
  rtc.begin();
  matrix.setTextWrap(false);
  matrix.setTextColor(matrix.Color333(255, 255, 255));
}


void loop() {
  //Jahr / Monat / Tag / Stunde / Minute / Sekunde
  DateTime futureDate(2023, 8, 10, 0, 0, 0);
  DateTime now = rtc.now();
  remainingYears = futureDate.year() - now.year();
  remainingMonths = futureDate.month() - now.month();
  remainingDays = futureDate.day() - now.day();
  int remainingHours = futureDate.hour() - now.hour();
  int remainingMinutes = futureDate.minute() - now.minute();
  int remainingSeconds = futureDate.second() - now.second();
  checkdate();

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

  if (remainingYears <= 0) {
    remainingYears = 0;
  }

  matrix.setCursor(1, 1);
  matrix.println("NUR");
  matrix.print("NOCH");
  delay(1500);
  matrix.fillScreen(0);
  matrix.setCursor(1, 1);
  matrix.println(remainingYears);
  if (remainingYears == 1 )
  {
    matrix.print("Jahr");
  }
  else {
    matrix.print("Jahre");
  }

  delay(1500);
  matrix.fillScreen(0);
  matrix.setCursor(1, 1);
  matrix.println(remainingMonths);
  matrix.print("Monate");
  delay(1500);
  matrix.fillScreen(0);
  int scroll = true;
  while (scroll == true) {
    matrix.fillScreen(0);
    matrix.setCursor(textX, 4);
    matrix.print(F2(str));
    delay(15);
    if ((--textX) < textMin) textX = matrix.width();
    if (textX == -220) {
      break;
    }
  }

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

void checkdate() {
  if (remainingYears <= 0 && remainingMonths <= 0) {
    ende = true;
  }

  while (ende == true) {
    matrix.setTextSize(2);
    matrix.fillScreen(0);
    matrix.setCursor(textX, 1);
    matrix.print(F2(str1));
    delay(15);
    if ((--textX) < textMin) textX = matrix.width();
  }
}
