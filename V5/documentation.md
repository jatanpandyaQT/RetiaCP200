
---

# Retia CP200 Documentation
### Author: Jatan Pandya
## Overview

These scripts are designed to facilitate the transmission of serial data to an MCP4725 DAC using an ESP32 microcontroller. 

## Scripts

### 1. `retia.ino`

This Arduino script runs on an ESP32 microcontroller and continuously listens for serial input. 
It handles commands received via serial communication and converts numeric data (representing blood pressure in mmHg) to corresponding DAC voltage values. 
The converted values are then transmitted to the MCP4725 DAC.

### 2. `com_script.py`

This Python script operates on a host computer and interacts with the ESP32 microcontroller over a serial connection. 
It reads data from a specified text file and sends it line by line to the ESP32 for DAC conversion and transmission. 

By default, the script runs for the file `all_merged.txt` which is the combined version of all the sample txt files supplied (`Stable Baseline.txt`, `sine_1.25Hz.txt`, `Demo Mode BP.txt` etc.)

The script will automatically detect the connected ESP32 device and transmit data from the specified file to the ESP32 for transmission.

The device communicates over `115200` baud rate.

#### Input File

- The ESP32 expects the input data in ASCII format, with each entry on a new line and with a two-decimal precision, e.g., "``74.48``" (mmHg).
- The valid range of data is from "``0.00 mmHg``" to "``300.00 mmHg``".

## Usage

### 1. `retia.ino`

#### Setup

- Connect the ESP32 microcontroller to PC.
- Upload the `retia.ino` script to the ESP32 using the Arduino IDE or any compatible development environment.
- Dependency : `<Adafruit_MCP4725.h>` library.

#### ACK

- Sending "``DeviceName``" command over serial retrieves device information (`--CP200-v1.0.0--`)

---