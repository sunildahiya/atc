import serial

from time import sleep
from serial.tools import list_ports #.list_ports.comports
#from tools import list_ports

def findPort(port):
	
	#a = list_ports.comports()
	#print (a[0].device)

	try:
	
		ser = serial.Serial(port,9600)
		
		#ser.setDTR(False)
		#sleep(1)
		#ser.flushInput()
		#ser.setDTR(True)
		done = ""
		conf = 'ok'
		while True:
			read_serial=ser.readline()
		
			#print(str(read_serial.decode('ascii')))
			if(str(read_serial.decode('ascii'))[0:4] == 'TSS:'):
				done = str(read_serial.decode('ascii'))[4:8]
				ser.write(conf.encode('ascii'))
				break
		
		if(done == "Gest"):
			result = "Gesture"
			#print("here")
		elif(done == "Heal"):
			result = "Health"              #'/dev/ttyACM0'
		elif(done == "LocC"):
			result = "LocC"
		elif(done == "LocX"):
			result = "LocX"  
		else:
			result = 'unrecognized module'
		
		ser.close()
	
	except Exception as e:
		print(str(e))
		result = 'port not open'
	
	return result


