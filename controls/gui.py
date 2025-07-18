import tkinter as tk
import serial #Serial imported for Serial communication
import threading

# Create the master object
root = tk.Tk()

# ArduinoSerial = serial.Serial('com5', 9600) #Create Serial port object called arduinoSerialData

# Configure serial port (adjust COM port and baud rate)
try:
    ser = serial.Serial('COM3', 9600, timeout=1) 
    time.sleep(2) # Allow time for serial connection to establish
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    ser = None

def arduino_handler():
    while True:
        # data = ArduinoSerial.readline().strip()
        data = "0;100;200;300;400;0;0;0" # example string
        split_data = data.split(";")
        tc2.set(split_data[1])
        tc3.set(split_data[2])
        tc4.set(split_data[3])
        tc5.set(split_data[4])

def send_to_arduino():
    if ser:
        text_to_send = entry_widget.get()
        ser.write(text_to_send.encode('utf-8'))
        print(f"Sent: {text_to_send}")
    else:
        print("Serial port not connected.")


# display thermocouple data
tk.Label(root, text="Thermocouple 2 (Delivery Line):" ).grid(row=0, column=0, sticky='w')
tc2 = tk.StringVar()
tk.Label(root, textvariable=tc2).grid(row=0, column=1, sticky='w')

tk.Label(root, text="Thermocouple 3 (Precursor 1):" ).grid(row=1, column=0, sticky='w')
tc3 = tk.StringVar()
tk.Label(root, textvariable=tc3).grid(row=1, column=1, sticky='w')

tk.Label(root, text="Thermocouple 4 (Precursor 2):" ).grid(row=2, column=0, sticky='w')
tc4 = tk.StringVar()
tk.Label(root, textvariable=tc4).grid(row=2, column=1, sticky='w')

tk.Label(root, text="Thermocouple 5 (Substrate Heater):").grid(row=3, column=0, sticky='w')
tc5 = tk.StringVar()
tk.Label(root, textvariable=tc5).grid(row=3, column=1, sticky='w')

# Create Entry widget
tk.Entry(root, width=50).grid(row=5, column=0, sticky='w')
# entry_widget.pack(pady=10)

# Create Send Button
tk.Button(root, text="Send job to Arduino", command=send_to_arduino).grid(row=6, column=0, sticky='w')
# send_button.pack(pady=5)

threading.Thread(target=arduino_handler, daemon=True).start()
root.mainloop()