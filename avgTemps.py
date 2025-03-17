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

def avgTemps():
    if "ch1":
        counter1 = 0
        while True:
            tempReadings1.append(tempVal1)
            if len(tempReadings1) > numReadings: 
                tempReadings1.pop(0)
            counter1 += 1
            if counter1 // 5 == 0: 
                avgVal1 = sum(tempReadings1) / len(tempReadings1)
                return(avgVal1)
            time.sleep(1.0)

    if "ch2":
        counter2 = 0
        while True:
            tempReadings2.append(tempVal2)
            if len(tempReadings2) > numReadings: 
                tempReadings2.pop(0)
            counter2 += 1
            if counter2 // 5 == 0:
                avgVal2 = sum(tempReadings2) / len(tempReadings2)
                return(avgVal2)
            time.sleep(1.0)

    if "ch3":
        counter3 = 0
        while True:
            tempReadings3.append(tempVal3)
            if len(tempReadings3) > numReadings: 
                tempReadings3.pop(0)
            counter3 += 1
            if counter3 // 5 == 0: 
                avgVal3 = sum(tempReadings3) / len(tempReadings3)
                return(avgVal3)
            time.sleep(1.0)
    
    if "ch4":
        counter4 = 0
        while True:
            tempReadings4.append(tempVal4)
            if len(tempReadings4) > numReadings: 
                tempReadings4.pop(0)
            counter4 += 1
            if counter4 // 5 == 0:
                avgVal4 = sum(tempReadings4) / len(tempReadings4)
                return(avgVal4)
            time.sleep(1.0)
