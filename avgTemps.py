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
        for len(tempReadings1) in range(11):
            tempReadings1.append(tempVal1)
            if len(tempReadings1) or len> numReadings: 
                tempReadings1.pop(0)
            avgVal1 = sum(tempReadings1) / len(tempReadings1)
            return(avgVal1)
            time.sleep(1.0)

    if "ch2":
        for len(tempReadings2) in range(11):
            tempReadings2.append(tempVal2)
            if len(tempReadings2) or len> numReadings: 
                tempReadings2.pop(0)
            avgVal2 = sum(tempReadings2) / len(tempReadings2)
            return(avgVal2)
            time.sleep(1.0)

     if "ch3":
        for len(tempReadings3) in range(11):
            tempReadings3.append(tempVal3)
            if len(tempReadings3) or len> numReadings: 
                tempReadings3.pop(0)
            avgVal3 = sum(tempReadings3) / len(tempReadings3)
            return(avgVal3)
            time.sleep(1.0)
    
    if "ch4":
        for len(tempReadings4) in range(11):
            tempReadings4.append(tempVal4)
            if len(tempReadings4) or len> numReadings: 
                tempReadings4.pop(0)
            avgVal4 = sum(tempReadings4) / len(tempReadings4)
            return(avgVal4)
            time.sleep(1.0)
