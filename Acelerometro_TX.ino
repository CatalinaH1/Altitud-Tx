#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <RF24.h>


RF24 radio(10, 8); // CE, CSN
const byte address[6] = "00001";
Adafruit_BMP280 bmp;
const int MPU_addr=0x68;  // Direccion del sensor MPU6050 en el bus I2C
int16_t AcX,AcY,AcZ;
void setup()
{
  ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
  Serial.begin(9600);  // Inicializar la comunicación serial a 9600 baudios
  Serial.println("Iniciando...");
  Wire.begin();        // Inicializar el bus I2C
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);     // PWR_MGMT_1 register
  Wire.write(0);        // Setear en 0 para activar el sensor
  Wire.endTransmission(true);


  radio.begin();
  radio.openWritingPipe(address);
  radio.setChannel(101);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);


  if (!bmp.begin()){
    Serial.println("BMP280 no encontrado !");
    while (1);
  }
}
void loop()
{
  Wire.beginTransmission(MPU_addr); // Iniciar la comunicación con el MPU6050
  Wire.write(0x3B);                 // Dirección del registro donde comienza la lectura
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true); // Leer 14 bytes de datos


  AcX=Wire.read()<<8|Wire.read();   // Leer los valores del acelerómetro
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
float datos[3] = {AcX, AcY, AcZ};
 radio.write(datos, sizeof(datos));
 Serial.print(AcX);
   Serial.print(",");
   Serial.print(AcY);
   Serial.print(",");
   Serial.println(AcZ);
delay(100); 
}
