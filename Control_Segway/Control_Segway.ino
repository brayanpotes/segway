#include <Wire.h> 

#define MPU 0x68  //Direccion I2C de la IMU
#define LEFT 11   
#define RIGHT 10
#define ENABLE 9
int vel;
int16_t GY; // la MPU arroja valores de 16 bits

void setup() {
  pinMode(LEFT,OUTPUT);
  pinMode(RIGHT,OUTPUT);
  pinMode(ENABLE,OUTPUT);
   pinMode(A0,INPUT);
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
   //Serial.print("GY: "); 
   //Serial.print(GY);  
   //Serial.print("\n");
   
   
   if(GY>0){
     digitalWrite(LEFT,LOW);
     digitalWrite(RIGHT,HIGH);
     vel=map(GY,0,10000,255,90);
     analogWrite(ENABLE,vel);
   }else if(GY<=-0){
     digitalWrite(LEFT,HIGH);
     digitalWrite(RIGHT,LOW);
     vel=map(GY,-10000,0,70,255);
     analogWrite(ENABLE,vel);
   }
   
   delay(10); //Tiempo entre muestra, 0.01  
}
