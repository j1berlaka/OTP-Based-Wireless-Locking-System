#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Pin Definitions
#define relay 4
#define red 16
#define green 15
#define irsensor A0
#define rxGSM 10
#define txGSM 11

// Setup GSM serial
SoftwareSerial sim800l(rxGSM, txGSM); // RX, TX

// Phone number to send OTP
String phoneNumber = "XXXXXXXXXX";

// OTP variables
int otp;
String otpstring = "";

// Keypad Setup
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { 13, 12, 11, 10 };
byte colPins[COLS] = { 9, 8, 7, 6 };
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// LCD Setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize IO
  pinMode(relay, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(irsensor, INPUT_PULLUP);
  digitalWrite(relay, LOW); // Door locked
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH); // Ready

  // Serial and GSM
  Serial.begin(9600);
  sim800l.begin(4800);

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");

  // GSM setup
  sim800l.println("AT");
  delay(500);
  sim800l.println("AT+CSQ");
  delay(500);
  sim800l.println("AT+CMGF=1");
  delay(500);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print(" OTP Based ");
  lcd.setCursor(0, 1);
  lcd.print(" Door Lock ");

  if (digitalRead(irsensor) == LOW) {
    // Generate OTP
    otp = random(2000, 9999);
    otpstring = String(otp);
    Serial.print("Generated OTP: ");
    Serial.println(otpstring);

    while (digitalRead(irsensor) == LOW); // wait for object to move

    // Notify user
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("OTP Sent to");
    lcd.setCursor(0, 1);
    lcd.print("Your Mobile");
    delay(1000);

    sendSMS(); // New correct SMS sending logic

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter OTP :");

    getotp(); // Handle user input and verification
  }
}

// Function to read OTP from keypad and verify
void getotp() {
  String enteredOTP = "";
  lcd.setCursor(0, 1);
  lcd.print("____");

  while (enteredOTP.length() < 4) {
    char key = customKeypad.getKey();
    if (key) {
      enteredOTP += key;
      lcd.setCursor(enteredOTP.length() - 1, 1);
      lcd.print(key);
    }
  }

  Serial.print("Entered OTP: ");
  Serial.println(enteredOTP);

  if (enteredOTP == otpstring) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted");
    lcd.setCursor(0, 1);
    lcd.print("Door Opening");
    digitalWrite(relay, HIGH);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    delay(5000);
    digitalWrite(relay, LOW);
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    lcd.setCursor(0, 1);
    lcd.print("Try Again!");
    delay(3000);
  }
}

// ✅ NEW GSM SMS Function (Correct one you provided)
void sendSMS() {
  Serial.println("Sending SMS");
  sim800l.println("AT+CMGF=1");
  delay(1000);
  sim800l.print("AT+CMGS=\"");
  sim800l.print(phoneNumber);
  sim800l.println("\"");
  delay(1000);
  sim800l.println("Your OTP is: " + otpstring);
  delay(100);
  sim800l.write(26); // Ctrl+Z to send
  delay(1000);

  while (sim800l.available()) {
    String response = sim800l.readString();
    Serial.println(response);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("OTP Sent!");
}
