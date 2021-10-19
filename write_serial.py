import serial
import math
import pdb

# Setting Arduino parameters
arduinoComPort="/dev/cu.usbmodem101" # fill out later
baudRate = 9600
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)
print(baudRate)
pdb.set_trace()

with open('data.csv', 'w') as f:
    while(True):
        lineOfData = serialPort.readline().decode()
        print(lineOfData)
        if len(lineOfData)>0:
            print(lineOfData)
            pdb.set_trace()
            left_speed, right_speed, left_sensor, right_sensor = [x for x in lineOfData.split(',')]
            print(left_speed, right_speed, left_sensor, right_sensor)
            f.write(f'{left_speed},{right_speed},{left_sensor},{right_sensor}\n')
            