#define LED_PIN 10
#define luzRes A1 
#include <Streaming.h>

struct paquete {
  char longitud[4];
  char tipo;
  char payload[555];
  bool leer() {
    Serial1.readBytes(longitud,4);
    l = hex2int(longitud,4);
    Serial1.readBytes(&tipo,1);
    Serial1.readBytes(payload,l-5);
  }

  void enviar() {
    if (tipo == 'l' || tipo == 'L')
      this->enviar(7);
  }

  void enviar(int longitud) {
    Serial1.write("\255",1);
    Serial1.write(this->longitud,4);
    Serial1.write(&tipo,1);
    Serial1.write(payload,longitud-5);
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

void int2hex(char * a, unsigned int n) {
  char x1 = n%16;
  char x2 = (n>>4)%16;
  a[1] = x1+'0';
  a[0] = x2+'0';
  
  if (x1 >= 10)
    a[1] = (x1-10)+'A';
  if (x2 >= 10)
    a[0] = (x2-10)+'A';
}

struct paquete luz;

void setup() {
  strcpy(luz.longitud,"000");
  luz.longitud[3] = '7';
  luz.tipo = 'l';
  
  // set the data rate for the SoftwareSerial port
  Serial1.begin(4800);
  Serial.begin(9600);
  //Serial1.println("");
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
  } else {
    int res = analogRead(luzRes);
    res = (unsigned char)(res/4);
    int2hex(luz.payload, res);
    luz.enviar();
    delay(50);
  }
}
