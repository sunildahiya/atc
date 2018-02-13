import serial
from serial.tools import list_ports
from rasp_arduino import findPort
from format_change import bytes_to_int
import numpy as np


def get_com():

	a = list_ports.comports()
	b = np.zeros(len(a)).tolist()
	#print (a[0].device)

	for i in range(0,len(a)):
		if(a[i].device.split('/')[2][3:6] == 'ACM' or a[i].device.split('/')[2][3:6] == 'USB'):
			b[i] = findPort(a[i].device)
			b[i] = b[i] + "-" + a[i].device
		else:
			b[i] =   "No-device"
		
	return b

#b = get_com()
#for i in range(0, len(b)):
#	print(b[i])

port = serial.Serial("/dev/ttyACM2", baudrate=115200, timeout=3.0)

rcv = port.read(1)
for i in range(0, 5):
    port.write(bytes([216]))
    rcv = port.read(1)
    print(bytes_to_int(rcv))
    #port.write("\r\nYou sent:" + repr(rcv))
