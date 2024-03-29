import sys
import BaseHTTPServer
from SimpleHTTPServer import SimpleHTTPRequestHandler
import RPi.GPIO as GPIO
import time
import serial
GPIO.cleanup() ## Hago una limpieza de los GPIO
GPIO.setmode(GPIO.BCM)
#GPIO.setup(21, GPIO.OUT) ## GPIO 17 como salida

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
                self.puerto.write("\255"+bytes)

	def leer(self):
		print self.long + self.tipo + self.payload
		sync = self.puerto.read(1)
		while sync != "\255":
			sync = self.puerto.read(1)
		self.long = self.puerto.read(4)
		self.tipo = self.puerto.read(1)
		self.payload = self.puerto.read(int(self.long,16)-5)

        long = "0007"
        tipo = "L"
        payload = "0"



luz = 0
tmp = 0
class PUTHandler(SimpleHTTPRequestHandler):
    p = paquete(port)
    def do_PUT(self):
	if self.path == "/led":
        	length = int(self.headers['Content-Length'])
        	content = self.rfile.read(length)
        	self.send_response(200)
		x = int(content)%256
		self.p.tipo = "L"
		self.p.payload = hex(x)[2:]
		self.p.payload = (2-len(self.p.payload))*"0"+self.p.payload
		self.p.enviar()
	elif self.path == "/display":
        	length = int(self.headers['Content-Length'])
        	content = self.rfile.read(length)
		content = content[0:min(length,80)]
		if length < 80:
			content = content + " "*(80-len(content))
		print content
		content = content[0:20]+content[40:60]+content[20:40]+content[60:80]
		print len(content)
		self.send_response(200)
		self.p.long = "0055"
		self.p.tipo = "D"
		self.p.payload = content
		self.p.enviar()
		

    def do_GET(self):
	global luz
	global tmp
	if self.path in ["/luz", "/tmp"]:
        	while self.p.puerto.inWaiting() > 0:
                	self.p.leer()
                	if (self.p.tipo == "l"):
                    		luz = self.p.payload
			elif (self.p.tipo == "t"):
				tmp = self.p.payload
        	self.send_response(200)
        	self.send_header("Content-type", "text/plain")
        	self.end_headers()
        	self.wfile.write([luz,(1.-int(tmp,16)/256.)*200.-2.][self.path == "/tmp"])
		return
	return SimpleHTTPRequestHandler.do_GET(self)
		

HandlerClass = PUTHandler
ServerClass  = BaseHTTPServer.HTTPServer
Protocol     = "HTTP/1.0"

if sys.argv[1:]:
    port = int(sys.argv[1])
else:
    port = 8000
server_address = ('', port)

HandlerClass.protocol_version = Protocol
httpd = ServerClass(server_address, HandlerClass)

sa = httpd.socket.getsockname()
print "Serving HTTP on", sa[0], "port", sa[1], "..."
try:
	httpd.serve_forever()
except:
	GPIO.cleanup()
	print "limpiando"

