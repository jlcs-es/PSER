#define LED_PIN 10

struct paquete {
  char longitud[4];
  char tipo;
  char payload[555];
  void leer() {
    Serial1.readBytes(longitud,4);
    l = hex2int(longitud,4);
    Serial1.readBytes(&tipo,1);
    Serial1.readBytes(payload,l-5);
  }
  long length() {
    return l;
  }
private:
  long l;
};

unsigned long hex2int(char *a, unsigned int len)
{
   unsigned int i;
   unsigned long val = 0;

   for(i=0;i<len;i++)
      if(a[i] <= 57)
       val += (a[i]-48)*(1<<(4*(len-1-i)));
      else
       val += (a[i]-55)*(1<<(4*(len-1-i)));
   return val;
}

void setup() {
  // set the data rate for the SoftwareSerial port
  Serial1.begin(4800);
  Serial1.println("");
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN,255);
}

void loop() { // run over and over
  struct paquete p;  
  if (Serial1.available()) {
    p.leer();
    if (p.tipo == 'L') {
     long intensidad = hex2int(p.payload,2);
     analogWrite(LED_PIN, intensidad);
    }
  }
}
