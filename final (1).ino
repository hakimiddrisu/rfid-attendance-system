#include <SPI.h>
#include <MFRC522.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include "FS.h"
#include "SD_MMC.h"

// ================= RFID =================
#define SS_PIN 5
#define RST_PIN 22

MFRC522 mfrc522(SS_PIN, RST_PIN);

// ================= RTC (DS1302) =================
// DS1302 CLK/SCLK
// DS1302 DAT/IO
// DS1302 RST/CE
ThreeWire myWire(26, 27, 25);  // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

// ================= LEDs =================
#define GREEN_LED 12
#define RED_LED   33 //13
#define BLUE_LED  13 //33

// ================= LED FUNCTIONS =================

void greenFlash()
{
  digitalWrite(GREEN_LED, HIGH);
  delay(300);
  digitalWrite(GREEN_LED, LOW);
}

void redFlash()
{
  digitalWrite(RED_LED, HIGH);
  delay(300);
  digitalWrite(RED_LED, LOW);
}

// ================= FUNCTIONS =================

// Get today's filename
String getTodayFileName()
{
  RtcDateTime now = Rtc.GetDateTime();

  char filename[20];

  snprintf(filename,
           sizeof(filename),
           "/%02u-%02u-%04u.csv",
           now.Day(),
           now.Month(),
           now.Year());

  return String(filename);
}

// Check duplicate UID
bool isDuplicate(String uid, String filename)
{
  File file = SD_MMC.open(filename, FILE_READ);

  if (!file)
    return false;

  while (file.available())
  {
    String line = file.readStringUntil('\n');

    if (line.startsWith(uid + ","))
    {
      file.close();
      return true;
    }
  }

  file.close();
  return false;
}

// Log attendance
void logAttendance(String uid)
{
  String filename = getTodayFileName();

  if (isDuplicate(uid, filename))
  {
    Serial.println("Duplicate Entry - Ignored");

    redFlash();

    return;
  }

  RtcDateTime now = Rtc.GetDateTime();

  char timeStamp[20];

  snprintf(timeStamp,
           sizeof(timeStamp),
           "%02u:%02u:%02u",
           now.Hour(),
           now.Minute(),
           now.Second());

  File file = SD_MMC.open(filename, FILE_APPEND);

  if (file)
  {
    file.print(uid);
    file.print(",");
    file.println(timeStamp);

    file.close();

    Serial.println("Attendance Logged");

    greenFlash();
  }
  else
  {
    Serial.println("File Open Failed");

    // Optional:
    // Flash red twice to indicate error

    redFlash();
    delay(200);
    redFlash();
  }
}

// Convert RFID UID to string
String getUID()
{
  String uid = "";

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    if (mfrc522.uid.uidByte[i] < 0x10)
      uid += "0";

    uid += String(mfrc522.uid.uidByte[i], HEX);
  }

  uid.toUpperCase();

  return uid;
}

// ================= SETUP =================

void setup()
{
  Serial.begin(115200);

  // LEDs
// LEDs
pinMode(GREEN_LED, OUTPUT);
pinMode(RED_LED, OUTPUT);
pinMode(BLUE_LED, OUTPUT);

digitalWrite(GREEN_LED, LOW);
digitalWrite(RED_LED, LOW);
digitalWrite(BLUE_LED, LOW);

  // RFID
  SPI.begin();
  mfrc522.PCD_Init();

  // RTC
  Rtc.Begin();

  if (!Rtc.IsDateTimeValid())
  {
    Rtc.SetDateTime(
      RtcDateTime(__DATE__, __TIME__)
    );
  }

  // SD CARD
  if (!SD_MMC.begin("/sdcard", true))
  {
    Serial.println("SD Card Mount Failed");

    // Signal startup failure
    while (true)
{
    digitalWrite(BLUE_LED, LOW);

    redFlash();

    delay(500);
}
  }

Serial.println("System Ready - Scan RFID Card");

// Turn on READY indicator
digitalWrite(BLUE_LED, HIGH);

// Startup confirmation
greenFlash();
}

// ================= LOOP =================

void loop()
{
  // Wait for RFID card
  if (!mfrc522.PICC_IsNewCardPresent())
    return;

  if (!mfrc522.PICC_ReadCardSerial())
    return;

  String uid = getUID();

  Serial.print("UID: ");
  Serial.println(uid);

  logAttendance(uid);

  mfrc522.PICC_HaltA();

  delay(1000);
}