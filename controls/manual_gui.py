# Manual ALD GUI
# Hacker Fab 2025
# Joel Gonzalez
import tkinter as tk
import tkinter.scrolledtext as st

import serial #Serial imported for Serial communication
import threading
import time

# Create the master object
root = tk.Tk()

# Configure serial port (adjust COM port and baud rate)
try:
    ser = serial.Serial('COM3', 9600, timeout=1) 
    time.sleep(2) # Allow time for serial connection to establish
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    ser = None

def arduino_handler():
    while True:
        # txt = "blah\n"
        txt = ser.readline()
        prefix = txt.decode('utf-8').strip(":")

        if (prefix[0] == "V"):
            valve_log_box.insert(tk.END, txt)
            valve_log_box.see(tk.END)
        elif (prefix[0] == "T"):
            temp_log_box.insert(tk.END, txt)
            temp_log_box.see(tk.END)
        else:
            generic_log_box.insert(tk.END, txt)
            generic_log_box.see(tk.END)
        

def send_valve_to_arduino():
    if ser:
        valve_txt = "v" + str(valve_select.get()) + ";" + str(num_pulse.get()) + ";" + str(pulse_time.get()) + ";" + str(purge_time.get())

        ser.write(valve_txt.encode('utf-8'))
        print(f"Sent: {valve_txt}")
    else:
        print("Serial port not connected.")

def send_temp_to_arduino():
    if ser:
        tc_txt = "t" + str(tc2_entry.get()) + ";" + str(tc3_entry.get()) + ";" + str(tc4_entry.get()) + ";" + str(tc5_entry.get())

        ser.write(tc_txt.encode('utf-8'))
        print(f"Sent: {tc_txt}")
    else:
        print("Serial port not connected.")


# valve information
tk.Label(root, text="ALD Valve Selection:").grid(row=0, column=0, sticky='w')
valve_select = tk.Entry(root, width=50)
valve_select.grid(row=0, column=1, sticky='w')

tk.Label(root, text="ALD Valve Num. Pulses:").grid(row=1, column=0, sticky='w')
num_pulse = tk.Entry(root, width=50)
num_pulse.grid(row=1, column=1, sticky='w')

tk.Label(root, text="ALD Valve Pulse Time (ms):").grid(row=2, column=0, sticky='w')
pulse_time = tk.Entry(root, width=50)
pulse_time.grid(row=2, column=1, sticky='w')

tk.Label(root, text="Delivery Line Purge Time:").grid(row=3, column=0, sticky='w')
purge_time = tk.Entry(root, width=50)
purge_time.grid(row=3, column=1, sticky='w')

tk.Button(root, text="Send valve info to Arduino", command=send_valve_to_arduino).grid(row=4, column=1, sticky='w')


# thermocouple information
tk.Label(root, text="Thermocouple 2 (Delivery Line):" ).grid(row=5, column=0, sticky='w')
tc2_entry = tk.Entry(root, width=50)
tc2_entry.grid(row=5, column=1, sticky='w')

tk.Label(root, text="Thermocouple 3 (Precursor 1):" ).grid(row=6, column=0, sticky='w')
tc3_entry = tk.Entry(root, width=50)
tc3_entry.grid(row=6, column=1, sticky='w')

tk.Label(root, text="Thermocouple 4 (Precursor 2):" ).grid(row=7, column=0, sticky='w')
tc4_entry = tk.Entry(root, width=50)
tc4_entry.grid(row=7, column=1, sticky='w')

tk.Label(root, text="Thermocouple 5 (Substrate Heater):").grid(row=8, column=0, sticky='w')
tc5_entry = tk.Entry(root, width=50)
tc5_entry.grid(row=8, column=1, sticky='w')

tk.Button(root, text="Send temp. info to Arduino", command=send_temp_to_arduino).grid(row=9, column=1, sticky='w')


# output boxes from Arduino
generic_log_box = st.ScrolledText(root, width=50, height=10, wrap=tk.WORD)
generic_log_box.grid(row=12, column=0, sticky='w')

valve_log_box = st.ScrolledText(root, width=50, height=10, wrap=tk.WORD)
valve_log_box.grid(row=12, column=1, sticky='w')

temp_log_box = st.ScrolledText(root, width=50, height=10, wrap=tk.WORD)
temp_log_box.grid(row=12, column=2, sticky='w')



# begin
threading.Thread(target=arduino_handler, daemon=True).start()
root.mainloop()
