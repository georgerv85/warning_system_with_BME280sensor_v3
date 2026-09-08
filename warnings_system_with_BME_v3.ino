// Γιατί βάζουμε systemCheck = true; μέσα στη loop(); Αν σε έναν κύκλο είχαμε warning: και μετά σε επόμενο κύκλο οι τιμές διορθώνονταν, πρέπει το σύστημα να μπορεί να ξαναγίνει true.

#include <Wire.h>                  // βιβλιοθήκη για I2C επικοινωνία
#include <Adafruit_BME280.h>       // βιλιοθήκη για τον αισθητήρα
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;          // Δημιουργία object matrix
Adafruit_BME280 bme;              // Δημιουργία object αισθητήρα

int packet = 1;
float temperature; //real
float humidity;    //real
float pressure;    //real

float batteryVoltage = 7.4;
float signalStrength = 82.0;

const float highTemperature = 10;
const float lowBatteryVoltage = 7.2;
const float lowSignalStrength = 50.0;

uint8_t okFrame[8][12] = {
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,1,0,0},
  {0,0,0,0,0,0,0,0,1,0,0,0},
  {0,0,1,0,0,0,0,1,0,0,0,0},
  {0,0,0,1,0,0,1,0,0,0,0,0},
  {0,0,0,0,1,1,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0}
};

uint8_t tempFrame[8][12] = {
  {0,0,1,1,1,1,1,1,1,1,0,0},
  {0,0,0,0,0,1,1,0,0,0,0,0},
  {0,0,0,0,0,1,1,0,0,0,0,0},
  {0,0,0,0,0,1,1,0,0,0,0,0},
  {0,0,0,0,0,1,1,0,0,0,0,0},
  {0,0,0,0,0,1,1,0,0,0,0,0},
  {0,0,0,0,0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0}
};

uint8_t batteryFrame[8][12] = {
  {0,0,1,1,1,1,1,0,0,0,0,0},
  {0,0,1,0,0,0,0,1,0,0,0,0},
  {0,0,1,0,0,0,0,1,0,0,0,0},
  {0,0,1,1,1,1,1,0,0,0,0,0},
  {0,0,1,0,0,0,0,1,0,0,0,0},
  {0,0,1,0,0,0,0,1,0,0,0,0},
  {0,0,1,1,1,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0}
};

uint8_t signalFrame[8][12] = {
  {0,0,0,1,1,1,1,1,1,0,0,0},
  {0,0,1,0,0,0,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0,0,0,0,0},
  {0,0,0,1,1,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,0,0,0},
  {0,0,0,0,0,0,0,0,1,0,0,0},
  {0,0,1,1,1,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0}
};




void setup() {
  Serial.begin(9600);

  delay(1000);

  while (!Serial) {
    // περιμένει να ανοίξει η σειριακή σύνδεση
  }

  matrix.begin();

  // Αρχικοποίηση αισθητήρα bme280 και έλεγχος
  if (!bme.begin(0x77)) {       // Αν δεν βρεθεί ο αισθητήρας στη διεύθυνση 0x76, εμφανίζει μήνυμα και σταματά.
    Serial.println("BME280 sensor not found");
    while (true) {
    }
  }

  Serial.println("BME280 initialized successfully");
  Serial.println("----------------------------");

}

void loop() {


  temperature = bme.readTemperature(); // Λαμβάνει την πραγματική θερμοκρασία
  humidity = bme.readHumidity(); // Λαμβάνει πραγματική υγρασία
  pressure = bme.readPressure()/100 ; // Λαμβάνει πραγματική πίεση from Pascal to hPa

  bool systemCheck = true;
  
  if(temperature > highTemperature || batteryVoltage < lowBatteryVoltage || signalStrength < lowSignalStrength){
    systemCheck = false;
  }

  if (systemCheck){
    matrix.renderBitmap(okFrame, 8, 12);
  }else if (temperature > highTemperature){
    matrix.renderBitmap(tempFrame, 8, 12);
    delay(250);
    matrix.clear();
    delay(250);
  }else if (batteryVoltage < lowBatteryVoltage){
    matrix.renderBitmap(batteryFrame, 8, 12);
    delay(250);
    matrix.clear();
    delay(250);
  }else if (signalStrength < lowSignalStrength){
    matrix.renderBitmap(signalFrame, 8, 12);
    delay(250);
    matrix.clear();
    delay(250);
  }

  Serial.print("Packet: ");
  Serial.println(packet);

  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.println("C");

  Serial.print("Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  Serial.print("Pressure: ");
  Serial.print(pressure, 1);
  Serial.println(" hPa");

  Serial.print("Battery Voltage: ");
  Serial.println(batteryVoltage, 1);

  Serial.print("Signal Strength: ");
  Serial.println(signalStrength, 1);

  if (systemCheck) {
    Serial.println("System Check: OK");
  }else{

    Serial.println("System Check: WARNING");
    Serial.println("WARNINGS :");

    if (temperature > highTemperature) {
      Serial.println("HIGH TEMPERATURE");
    }

    if (batteryVoltage < lowBatteryVoltage) {
      Serial.println("LOW BATTERY VOLTAGE");
    }

    if (signalStrength < lowSignalStrength) {
      Serial.println("LOW SIGNAL STRENGTH");
    }

  }

  Serial.println("----------------------------");

  packet++;
  delay(2000);

}
