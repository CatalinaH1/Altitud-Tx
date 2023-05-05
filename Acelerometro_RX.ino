#include <SPI.h>
#include <RF24.h>

RF24 radio(10,8); // CE, CSN
const byte address[6] = "00001";
float AcX, AcY, AcZ;

void setup() 
{
ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
  Serial.begin(9600, SERIAL_8N1);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setChannel(101);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();
  /*Serial.println("Receptor iniciado");*/
}


void loop()
{
  if (radio.available())     
  {  
    float datos[3];
    radio.read(datos, sizeof(datos));
    AcX = datos[0];
    AcY = datos[1];
    AcZ = datos[2];
  Serial.print(AcX);
  Serial.print(",");
  Serial.print(AcY);
  Serial.print(",");
  Serial.println(AcZ);
  }
  delay(100);
}
