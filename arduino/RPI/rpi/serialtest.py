import serial
from time import sleep

port = serial.Serial("/dev/ttyAMA0", baudrate=4800, timeout=3.0)

class paquete:
	puerto = None
	def __init__(self, s):	
		self.puerto = s

	def enviar(self):
		bytes = self.long + self.tipo + self.payload
		length = int(self.long)
		if (length > len(bytes)):
			bytes += "0"*(length - len(bytes))
		self.puerto.write(bytes)
		print bytes
	long = "0007"
	tipo = "L"
	payload = "0"
	

p = paquete(port)
intensidad = 0
while True:
	sleep(0.5)
	intensidad = (intensidad+16)%256
	p.payload = hex(intensidad)[2:]
	p.enviar()
	
