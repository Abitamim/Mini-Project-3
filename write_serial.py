import serial
import math
import pdb
import time


# Setting Arduino parameters
arduinoComPort="/dev/cu.usbmodem101" # fill out later
baudRate = 9600
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)
print(baudRate)

start = time.time()
with open('data.csv', 'w') as f:
    while(True):
        lineOfData = serialPort.readline().decode()
        if len(lineOfData)>0:
            print(lineOfData)
            left_speed, right_speed, left_sensor, right_sensor = [x for x in lineOfData.split(',')]
            print(left_speed, right_speed, left_sensor, right_sensor)
            f.write(f'{left_speed},{right_speed},{left_sensor},{right_sensor}')
        if time.time() >= 20 + start:
            f.close()
            break
            