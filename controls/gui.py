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
        # data = "0;100;200;300;400;0;0;0;0\n" # example string
        data = ser.readline().strip()
        log_box.insert(tk.INSERT, "{data}\n")

        # split_data = data.split(";")
        # tc2.set(split_data[1])
        # tc3.set(split_data[2])
        # tc4.set(split_data[3])
        # tc5.set(split_data[4])

def send_to_arduino():
    if ser:
        purge_txt = purge_entry.get()

        v1_numpulse_txt = v1_numpulse_entry.get()
        v1_pulsetime_txt = v1_pulsetime_entry.get()
        v2_numpulse_txt = v2_numpulse_entry.get()
        v2_pulsetime_txt = v2_pulsetime_entry.get()
        v3_numpulse_txt = v3_numpulse_entry.get()
        v3_pulsetime_txt = v3_pulsetime_entry.get()
        valve_txt = str(v1_numpulse_txt) + ";" + str(v1_pulsetime_txt) + ";" + str(v2_numpulse_txt) + ";" + str(v2_pulsetime_txt) + ";" + str(v3_numpulse_txt) + ";" + str(v3_pulsetime_txt) + ";"

        tc2_txt = tc2_entry.get()
        tc3_txt = tc3_entry.get()
        tc4_txt = tc4_entry.get()
        tc5_txt = tc5_entry.get()
        tc_txt = str(tc2_txt) + ";" + str(tc3_txt) + ";" + str(tc4_txt) + ";" + str(tc5_txt) + ";"

        text_to_send = purge_txt + ";" + valve_txt + tc_txt

        ser.write(text_to_send.encode('utf-8'))
        print(f"Sent: {text_to_send}")
    else:
        print("Serial port not connected.")

def begin_job():
    if ser:
        ser.write("BEGIN".encode('utf-8'))
        print("BEGIN")
    else:
        print("Serial port not connected.")

tk.Label(root, text="Purge Time (ms):").grid(row=0, column=0, sticky='w')
purge_entry = tk.Entry(root, width=50)
purge_entry.grid(row=0, column=1, sticky='w')



tk.Label(root, text="ALD Valve 1 Num. Pulses:").grid(row=1, column=0, sticky='w')
v1_numpulse_entry = tk.Entry(root, width=50)
v1_numpulse_entry.grid(row=1, column=1, sticky='w')

tk.Label(root, text="ALD Valve 1 Pulse Time (ms):").grid(row=2, column=0, sticky='w')
v1_pulsetime_entry = tk.Entry(root, width=50)
v1_pulsetime_entry.grid(row=2, column=1, sticky='w')

tk.Label(root, text="ALD Valve 2 Num. Pulses:").grid(row=3, column=0, sticky='w')
v2_numpulse_entry = tk.Entry(root, width=50)
v2_numpulse_entry.grid(row=3, column=1, sticky='w')

tk.Label(root, text="ALD Valve 2 Pulse Time (ms):").grid(row=4, column=0, sticky='w')
v2_pulsetime_entry = tk.Entry(root, width=50)
v2_pulsetime_entry.grid(row=4, column=1, sticky='w')

tk.Label(root, text="ALD Valve 3 Num. Pulses:").grid(row=5, column=0, sticky='w')
v3_numpulse_entry = tk.Entry(root, width=50)
v3_numpulse_entry.grid(row=5, column=1, sticky='w')

tk.Label(root, text="ALD Valve 3 Pulse Time (ms):").grid(row=6, column=0, sticky='w')
v3_pulsetime_entry = tk.Entry(root, width=50)
v3_pulsetime_entry.grid(row=6, column=1, sticky='w')



tk.Label(root, text="Thermocouple 2 (Delivery Line):" ).grid(row=7, column=0, sticky='w')
tc2_entry = tk.Entry(root, width=50)
tc2_entry.grid(row=7, column=1, sticky='w')
tc2 = tk.StringVar()
tk.Label(root, textvariable=tc2).grid(row=7, column=2, sticky='w')

tk.Label(root, text="Thermocouple 3 (Precursor 1):" ).grid(row=8, column=0, sticky='w')
tc3_entry = tk.Entry(root, width=50)
tc3_entry.grid(row=8, column=1, sticky='w')
tc3 = tk.StringVar()
tk.Label(root, textvariable=tc3).grid(row=8, column=2, sticky='w')

tk.Label(root, text="Thermocouple 4 (Precursor 2):" ).grid(row=9, column=0, sticky='w')
tc4_entry = tk.Entry(root, width=50)
tc4_entry.grid(row=9, column=1, sticky='w')
tc4 = tk.StringVar()
tk.Label(root, textvariable=tc4).grid(row=9, column=2, sticky='w')

tk.Label(root, text="Thermocouple 5 (Substrate Heater):").grid(row=10, column=0, sticky='w')
tc5_entry = tk.Entry(root, width=50)
tc5_entry.grid(row=10, column=1, sticky='w')
tc5 = tk.StringVar()
tk.Label(root, textvariable=tc5).grid(row=10, column=2, sticky='w')



tk.Button(root, text="Send job to Arduino", command=send_to_arduino).grid(row=11, column=1, sticky='w')
tk.Button(root, text="Begin job!", command=begin_job).grid(row=11, column=2, sticky='w')



# log = tk.StringVar()
# tk.Label(root, textvariable=log).grid(row=12, column=0, sticky='w')
log_box = st.ScrolledText(root, width=50, height=10, wrap=tk.WORD)
log_box.grid(row=12, column=0, sticky='w')



threading.Thread(target=arduino_handler, daemon=True).start()
root.mainloop()
