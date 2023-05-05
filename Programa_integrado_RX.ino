#include <SPI.h>
#include <RF24.h>

RF24 radio(10, 8); // CE, CSN
const byte address[6] = "00001";
float lectura[2];
char lectura_char[1];
float AcX, AcY, AcZ, GyX, GyY, GyZ, ALTITUD;


void setup() 
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setChannel(101);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();
  /*Serial.println("Receptor iniciado"); */
}

void loop()
{
  if (radio.available())     
  {  
    float datos[7];
    radio.read(datos, sizeof(datos));
    AcX = datos[0];
    AcY = datos[1];
    AcZ = datos[2];
    GyX = datos[3];
    GyY = datos[4];
    GyZ = datos[5];
    ALTITUD = datos[6];

    Serial.print(ALTITUD);
    Serial.print(",");
    Serial.print(AcX);
    Serial.print(",");
    Serial.print(AcY);
    Serial.print(",");
    Serial.print(AcZ);
    Serial.print(",");
    Serial.print(GyX);
    Serial.print(",");
    Serial.print(GyY);
    Serial.print(",");
    Serial.println(GyZ);

  }
  delay(100);
}
