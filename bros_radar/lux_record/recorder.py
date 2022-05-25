import serial

from signal import signal, SIGINT
from sys import exit

import time


def handler(signal_received, frame):
	# Handle any cleanup here
	print('finish!')

	with open('recLux.txt','w') as f:
		for i in rec:
			f.write(str(i) + ",")


	exit(0)

rec = []
j = 0
ser = serial.Serial('/dev/ttyACM3',115200)  # open serial port

if __name__ == '__main__':
	# Tell Python to run the handler() function when SIGINT is recieved
	signal(SIGINT, handler)

	print('Running. Press CTRL-C to exit.')
	while True:
		# Do nothing and hog CPU forever until SIGINT received.
	
		line = ser.readline()
		l = line.strip()
		print(l)
		rec.append(l)

		pass
