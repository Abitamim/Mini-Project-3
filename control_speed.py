import serial

arduinoComPort="/dev/cu.usbmodem101" # fill out later
baudRate = 9600
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)
inputs = {1:0.5,2:1,3:2,4:5}

while(True):
	cmd_id = int(Input('Choose speed\n1 - Slow mode\n2 - Normal\n3 - Fast\n4 - Wild mode'))
	if cmd_id not in valid.keys():
		print('Invalid input')
	else:
		serialPort.write(f'M:{inputs[cmd_id]')