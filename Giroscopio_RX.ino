#include <SPI.h>
#include <RF24.h>
RF24 radio(10,8); // CE, CSN
const byte address[6] = "00001";
float GyX, GyY, GyZ;
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
  //Serial.println("Receptor iniciado");


void loop()
{
  if (radio.available())     
  {  
    float datos[3];
    radio.read(datos, sizeof(datos));
    GyX = datos[0];
    GyY = datos[1];
    GyZ = datos[2];
  Serial.print(GyX);
  Serial.print(",");
  Serial.print(GyY);
  Serial.print(",");
  Serial.println(GyZ);
  }
  delay(50);
}
