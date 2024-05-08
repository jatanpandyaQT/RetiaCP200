/*
   Author: Jatan Pandya

   Script to transmit serial data to MCP4725 DAC using ESP32

   Tested on:
   - ESP32V2 Feather Huzzah
   - ESP32V1 Feather 
   - Current Build Config Files for: ESP32 V2 FEATHER 8M Flash, 2MB PSRAM

   API Calls and Webserver Code have been removed.
*/

#include <Adafruit_MCP4725.h>

#define FIRMWARE_VERSION "v1.0.0"
#define DAC_ADDRESS 0x62

// Function Prototypes
void setup();
void loop();
void handleSerialCommand(String command);
bool isValidNumber(String str);
void transmitData(String data);

Adafruit_MCP4725 dac;

/*
   setup: This function initializes serial communication, DAC, and prints a welcome message.
*/
void setup() {
  Serial.begin(115200);
  dac.begin(DAC_ADDRESS);

  Serial.println("\n***********************");
  Serial.println("Welcome to Retia CP200");
  Serial.print("Firmware: ");
  Serial.println(FIRMWARE_VERSION);
  Serial.println("***********************\n");
}

/*
   loop: This function continuously checks for serial input and calls handleSerialCommand if input is available.
*/
void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    Serial.println(command);
    handleSerialCommand(command);
  }
}

/*
   handleSerialCommand: This function handles serial commands.
   If the command is numeric, it calls transmitData function.
   If the command is "DeviceName", it prints the device name and firmware version.
   If the command is invalid, it prints an error message.
*/
void handleSerialCommand(String command) {
  if (command.equals("DeviceName")) {
    Serial.println("\n--CP200-" + String(FIRMWARE_VERSION) + "--\n");
  } else if (isValidNumber(command)) {
    transmitData(command);
  } else {
    Serial.println("[API] Invalid command");
  }
}

/*
   isValidNumber: This function checks if a given string is a valid numeric value.
*/
bool isValidNumber(String str) {
  for (size_t i = 0; i < str.length(); i++) {
    if (!isdigit(str[i]) && str[i] != '.') {
      return false;
    }
  }
  return true;
}

/*
   transmitData: This function converts the received data (in mmHg) to DAC value and sets the voltage.
   Explanation:
   - The input data is converted from string to float representing mmHg (millimeters of mercury).
   - The mmHg value is mapped to a voltage range from 0 to 3.0 volts, corresponding to 0 to 300 mmHg.
   - The voltage value is then mapped to the range of DAC values (0 - 4095).
   - Finally, the DAC value is constrained within the range of 0 to 4095 and set as the output voltage.
*/
void transmitData(String data) {
  float mmHg = data.toFloat();

  // Scale down the input to fit within the range of 0 to 300
  float scaledData = mmHg / 300.0;

  // New reference Voltage mapping: scale it down by 3.0/3.3
  float maxInput = 3.0;
  float mappedData = scaledData * maxInput;
  int dacValue = mappedData * 4095.0 / 3.3;

  dacValue = constrain(dacValue, 0, 4095);

  dac.setVoltage(dacValue, false);
  Serial.print("Set Voltage to: ");
  Serial.println(dacValue);
}
