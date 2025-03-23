import sm_tc
import time
import sys
from datetime import datetime

numReadings = 10
tempReadings1 = []
tempVal1 = t.get_temp(1)
tempReadings2 = []
tempVal2 = t.get_temp(2)
tempReadings3 = []
tempVal3 = t.get_temp(3)
tempReadings4 = []
tempVal4 = t.get_temp(4)
t = sm_tc.SMtc(0)

def avgTemps(arg = None):
    avgVals = [avgVal1, avgVal2, avgVal3, avgVal4]
    while True:
        count = 0
        tempReadings1.append(tempVal1)
        if len(tempReadings1) > numReadings: 
            tempReadings1.pop(0)
        avgVal1 = sum(tempReadings1) / len(tempReadings1)

        tempReadings2.append(tempVal2)
        if len(tempReadings2) > numReadings: 
            tempReadings2.pop(0)
        avgVal2 = sum(tempReadings2) / len(tempReadings2)

        tempReadings3.append(tempVal3)
        if len(tempReadings3) > numReadings: 
            tempReadings3.pop(0)
        avgVal3 = sum(tempReadings3) / len(tempReadings3)

        tempReadings4.append(tempVal4)
        if len(tempReadings4) > numReadings: 
            tempReadings4.pop(0)
        avgVal4 = sum(tempReadings4) / len(tempReadings4)

        time.sleep(1.0)
        count += 1
        if count // 5 == 0: 
            return avgVals
