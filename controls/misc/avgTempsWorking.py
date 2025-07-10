import sm_tc
import time
import sys
from datetime import datetime

numReadings = 10
tempReadings = []
t = sm_tc.SMtc(0)

while True:
    tempVal = t.get_temp(2)
    tempReadings.append(tempVal)
    if len(tempReadings) > numReadings:
        tempReadings.pop(0)
    avgVal = sum(tempReadings) / len(tempReadings)
    print(avgVal)
    time.sleep(1.0)