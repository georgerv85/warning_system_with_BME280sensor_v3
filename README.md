# Arduino UNO R4 WiFi - BME280 Telemetry

Beginner environmental telemetry project using the **Arduino UNO R4 WiFi** and a **BME280 sensor**.

The project reads real environmental data from the BME280 sensor and combines it with simulated telemetry values to create a simple monitoring and warning system.

The built-in **12×8 LED Matrix** of the Arduino UNO R4 WiFi is also used as a visual system status indicator.

![Project Overview](assets/image1.png)

---

## Project Overview

The system currently monitors:

- Temperature
- Humidity
- Atmospheric pressure
- Battery voltage *(simulated)*
- Signal strength *(simulated)*

The Arduino evaluates the telemetry values against predefined thresholds and reports the overall system status through:

- the **Serial Monitor**
- the built-in **LED Matrix**

The system can report either:

```text
System Check: OK
```

or:

```text
System Check: WARNING
```

---

## Hardware

- Arduino UNO R4 WiFi
- BME280 sensor
- Jumper wires
- USB-C data cable

---

## BME280 Connection

| BME280 | Arduino UNO R4 WiFi |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | SDA |
| SCL | SCL |

The BME280 used in this project is detected at:

```text
I2C address: 0x77
```

---

## Libraries

The project uses:

```cpp
#include <Wire.h>
#include <Adafruit_BME280.h>
#include "Arduino_LED_Matrix.h"
```

Required libraries:

- Adafruit BME280 Library
- Adafruit Unified Sensor
- Arduino LED Matrix Library

---

## Real Sensor Data

The BME280 provides real measurements for:

- Temperature
- Humidity
- Atmospheric pressure

Example:

```text
Temperature: 24.8 C
Humidity: 47.3 %
Pressure: 1009.6 hPa
```

---

## Simulated Telemetry Data

The following values are currently simulated in software:

```cpp
float batteryVoltage = 7.4;
float signalStrength = 82.0;
```

These values will be replaced by real measurements or calculated values in future versions.

---

## Warning Thresholds

The current warning thresholds are:

```cpp
const float highTemperature = 40.0;
const float lowBatteryVoltage = 7.2;
const float lowSignalStrength = 50.0;
```

Warning conditions:

```text
Temperature > 40.0 °C
Battery Voltage < 7.2 V
Signal Strength < 50.0
```

Possible warning messages:

```text
HIGH TEMPERATURE
LOW BATTERY VOLTAGE
LOW SIGNAL STRENGTH
```

Multiple warnings can be active simultaneously in the Serial Monitor.

---

## LED Matrix Status

The built-in **12×8 LED Matrix** is used as a visual system status indicator.

Current display logic:

```text
System OK          → ✓
High Temperature   → T
Low Battery        → B
Low Signal         → S
```

The matrix displays one warning symbol at a time.

Current warning priority:

```text
1. High Temperature
2. Low Battery Voltage
3. Low Signal Strength
```

The Serial Monitor can still display all active warnings simultaneously.

---

## Example Serial Monitor Output

### Normal Condition

```text
Packet: 1
Temperature: 24.8 C
Humidity: 47.3 %
Pressure: 1009.6 hPa
Battery Voltage: 7.4
Signal Strength: 82.0
System Check: OK
----------------------------
```

### Warning Condition

```text
Packet: 2
Temperature: 41.5 C
Humidity: 47.3 %
Pressure: 1009.6 hPa
Battery Voltage: 7.4
Signal Strength: 12.0
System Check: WARNING
WARNINGS:
HIGH TEMPERATURE
LOW SIGNAL STRENGTH
----------------------------
```

---

## System Flow

```text
BME280 Sensor
     |
     v
Temperature / Humidity / Pressure
     |
     v
Arduino UNO R4 WiFi
     |
     v
Telemetry Packet
     |
     v
Threshold Checks
     |
     v
System Check
   /       \
  OK      WARNING
  |          |
  v          v
LED        LED Matrix
Matrix      T / B / S
  |
  v
Serial Monitor
```

---

## Concepts Practiced

This project is part of my Arduino learning process and currently includes:

- Arduino C/C++ basics
- Variables and constants
- `float`
- `bool`
- `if / else`
- Logical operators
- Serial communication
- I2C communication
- BME280 sensor integration
- Real sensor readings
- Telemetry packet structure
- Threshold-based monitoring
- Warning logic
- LED Matrix control
- Hardware/software interaction

---

## Current Project Status

- [x] Serial Monitor communication
- [x] Telemetry packet counter
- [x] BME280 initialization
- [x] Real temperature measurement
- [x] Real humidity measurement
- [x] Real pressure measurement
- [x] Simulated battery voltage
- [x] Simulated signal strength
- [x] Automatic system status
- [x] Multiple warning detection
- [x] LED Matrix system status
- [x] Different matrix symbols for different warnings

---

## Next Steps

- [ ] Blinking warning symbols on the LED Matrix
- [ ] Replace `delay()` with `millis()`
- [ ] Non-blocking telemetry execution
- [ ] Real WiFi signal strength
- [ ] Real battery voltage measurement
- [ ] WiFi telemetry transmission
- [ ] JSON telemetry packets
- [ ] Arduino-to-Python communication
- [ ] Live telemetry dashboard
- [ ] Data logging
- [ ] MQTT communication
- [ ] Additional sensors

---

## Learning Goal

The purpose of this repository is educational.

It documents my progress while learning:

- Arduino UNO R4 WiFi
- Embedded programming
- Sensor integration
- Telemetry systems
- Hardware/software interaction
- IoT concepts

The project will gradually evolve from a simple telemetry monitoring example into a more complete embedded telemetry platform.