// Γιατί βάζουμε systemCheck = true; μέσα στη loop(); Αν σε έναν κύκλο είχαμε warning: και μετά σε επόμενο κύκλο οι τιμές διορθώνονταν, πρέπει το σύστημα να μπορεί να ξαναγίνει true.

#include <Wire.h>                  // βιβλιοθήκη για I2C επικοινωνία
#include <Adafruit_BME280.h>       // βιλιοθήκη για τον αισθητήρα

Adafruit_BME280 bme;              // Δημιουργία object αισθητήρα

int packet = 1;
float temperature; //real
float humidity;    //real
float presure;    //real

float batteryVoltage = 7.4;
float signalStrength = 12.0;

const float highTemperature = 40;
const float lowBatteryVoltage = 7.2;
const float lowSignalStrength = 50.0;




void setup() {
  Serial.begin(9600);

  delay(1000);

  while (!Serial) {
    // περιμένει να ανοίξει η σειριακή σύνδεση
  }


  // Αρχικοποίηση αισθητήρα
  if (!bme.begin(0x77)) {       // Αν δεν βρεθεί ο αισθητήρας στη διεύθυνση 0x76, εμφανίζει μήνυμα και σταματά.
    Serial.println("BME280 sensor not found");
    while (true) {
    }
  }

  Serial.println("BME280 initialized successfully");
  Serial.println("----------------------------");

}

void loop() {


  float temperature = bme.readTemperature(); // Λαμβάνει την πραγματική θερμοκρασία
  float humidity = bme.readHumidity(); // Λαμβάνει πραγματική υγρασία
  float presure = bme.readPressure()/100 ; // Λαμβάνει πραγματική πίεση from Pascal to hPa
  bool systemCheck;
  
  if(temperature > highTemperature || batteryVoltage < lowBatteryVoltage || signalStrength < lowSignalStrength){
    systemCheck = false;
  }else{
    systemCheck = true;
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
  Serial.print(presure, 1);
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
  delay(5000);

}

