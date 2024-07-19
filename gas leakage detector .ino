#include <SoftwareSerial.h>

SoftwareSerial SIM900(8, 7); // SoftSerial( RX , TX );
// 8 pin connect to TX of GSM SIM 900 Module
// 7 pin connect to RX of GSM SIM 900 Module

const char PHONE_NUMBER[] = "+252612338944"; // Define your phone number here

int GAS_SENSOR = A0;  // This is our input pin
int red_led = 3;
int green_led = 4;
int BUZZ = 5;
int fire = 6;

void setup() {
  Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
  SIM900.begin(9600); // Setting the baud rate of GSM Module
  Serial.println("SIM900 Ready");
  delay(100);
  Serial.println("Type s to send message");

  pinMode(GAS_SENSOR, INPUT);
  pinMode(fire, INPUT);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  digitalWrite(green_led, HIGH);
  pinMode(BUZZ, OUTPUT);
}

void loop() {
  int Value = analogRead(GAS_SENSOR);
  Serial.print("Analog read: ");
  Serial.println(Value);

  int fireVal = digitalRead(fire);
  Serial.println(fireVal);

  if (Value >= 900 || fireVal == LOW) {
    digitalWrite(red_led, HIGH);
    digitalWrite(green_led, LOW);
    digitalWrite(BUZZ, HIGH);
    SendMessage();
    makeCall(PHONE_NUMBER); // Call the predefined number
    delay(1000);
  } else {
    digitalWrite(red_led, LOW);
    digitalWrite(green_led, HIGH);
    digitalWrite(BUZZ, LOW);
  }
  delay(200);
}

void SendMessage() {
  Serial.println("Sending Message");
  SIM900.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println("Set SMS Number");
  SIM900.println("AT+CMGS=\"252612338944" + String(PHONE_NUMBER) + "\"\r"); // Write Mobile number to send message
  delay(1000);
  Serial.println("Set SMS Content");
  SIM900.println("BAKHAAR :NO,1230, DAB AYAA KA KACAY!\n Address: Howlwadaag, Bakaaro Market\n"); // Message content
  delay(100);
  Serial.println("Finish");
  SIM900.println((char)26); // ASCII code of CTRL+Z
  delay(1000);
  Serial.println("Message has been sent ->SMS Selesai dikirim");
}

void makeCall(const char* number) {
  Serial.println("Making Call");
  SIM900.println("ATD" + String(number) + ";");
  delay(10000); // Wait for the call to connect
  Serial.println("Call attempt finished");
}
