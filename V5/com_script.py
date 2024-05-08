# Auth: Jatan Pandya

import serial
import serial.tools.list_ports
import time

BAUD_RATE = 115200
FILE_NAME = "all_merged.txt"
REPLAY_TIME = 0.007

def find_serial_port():
    """
    Finds the serial port of the connected ESP device.
    
    Returns:
        str or None: The serial port name if found, otherwise None.
    """
    ports = serial.tools.list_ports.comports()
    for port in ports:
        if "USB" in port.description:
            return port.device
    return None

def open_serial_port():
    """
    Opens the serial port for communication with the ESP device.
    
    Returns:
        Serial or None: The opened serial port if successful, otherwise None.
    """
    com_port = find_serial_port()
    if com_port:
        try:
            ser = serial.Serial(com_port, BAUD_RATE)
            return ser
        except serial.SerialException as e:
            print(f"Failed to open serial port {com_port}: {e}")
            return None
    else:
        print("ESP device not found.")
        return None

def read_file(ser):
    """
    Reads data from the specified file and sends it over the serial port.
    
    Args:
        ser (Serial): The opened serial port.
    """
    try:
        with open(FILE_NAME, 'r') as file:
            for line in file:
                line = line.strip() 
                send_data(line, ser)
                time.sleep(REPLAY_TIME)
                
    except FileNotFoundError as e:
        print(f"Failed to open file {FILE_NAME}: {e}")

def send_data(data, ser):
    """
    Sends data over the serial port.
    
    Args:
        data (str): The data to be sent.
        ser (Serial): The opened serial port.
    """
    try:
        if ser:
            ser.write(data.encode())  
            ser.write(b'\n') 
        else:
            print("Serial port is not open. Cannot send data.")
    except serial.SerialException as e:
        print(f"Failed to send data over serial port: {e}")

def main():
    """
    Main function to run the script.
    """
    user_input = input("Do you want to run the file? (y/n): ").strip().lower()
    if user_input == 'y':
        time.sleep(1)
        ser = open_serial_port()
        print("Running...")
        if not ser:
            return
        read_file(ser)
        ser.close()
        print("Completed!")
    elif user_input == 'n':
        print("script stopped")
    else:
        print("Invalid input. Please enter 'y' or 'n'.")

if __name__ == "__main__":
    main()
