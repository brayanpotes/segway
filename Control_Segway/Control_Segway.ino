#include <Wire.h> 

#define MPU 0x68  //Direccion I2C de la IMU
#define LEFT 10   
#define RIGHT 11
int16_t GY; // la MPU arroja valores de 16 bits

void setup() {
  pinMode(LEFT,OUTPUT);
  pinMode(RIGHT,OUTPUT);
  Wire.begin();
  Wire.beginTransmission(MPU);  // Se inicia la comunicacion por I2C con el MPU
  Wire.write(0x6B);   
  Wire.write(0);  // Se activa la comunicacion enviando el comando 0
  Wire.endTransmission(true);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(3<<3);
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop() {
   /* Lectura de el giroscopio en el eje y */
   Wire.beginTransmission(MPU);
   Wire.write(0x45); // Pedir el registro 0x45 - correspnde a los datos giroscopio en y  
   Wire.endTransmission(false);
   Wire.requestFrom(MPU,2,true); //A partir del 0x45, se pide el dato del giroscopio en y
   GY=Wire.read()<<8|Wire.read();  
   Serial.print("GY: "); 
   Serial.print(GY);  
   Serial.print("\n");
   
   if(GY>0){
     analogWrite(LEFT,HIGH);
     analogWrite(RIGHT,LOW);
   }else{
     analogWrite(LEFT,LOW);
     analogWrite(RIGHT,HIGH);   
   }
   
   delay(333); //Tiempo entre muestra, 0.01  
}
