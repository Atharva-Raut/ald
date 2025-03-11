import sm_tc
import time
import sys
from datetime import datetime

numReadings = 10
tempReadings1 = []
tempReadings2 = []
t = sm_tc.SMtc(0)

if "getTempChannel1":
    tempVal1 = t.get_temp(1)
    tempReadings1.append(tempVal1)
    if len(tempReadings1) or len> numReadings: 
        tempReadings1.pop(0)
    avgVal1 = sum(tempReadings1) / len(tempReadings1)
    print(avgVal1)
    time.sleep(1.0)

if "getTempChannel2":
    tempVal2 = t.get_temp(2)
    tempReadings2.append(tempVal2)
    if len(tempReadings2) or len> numReadings: 
        tempReadings2.pop(0)
    avgVal2 = sum(tempReadings2) / len(tempReadings2)
    print(avgVal2)
    time.sleep(1.0)

def main():
    if __name__ = '__main__':