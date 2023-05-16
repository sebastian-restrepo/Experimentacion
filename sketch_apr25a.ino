/* 
 * Arduino 101: timer and interrupts
 * 2: Timer1 overflow interrupt example 
 * more infos: http://www.letmakerobots.com/node/28278
 * created by RobotFreak 
 */

// Librerias I2C para controlar el mpu6050
// la libreria MPU6050.h necesita I2Cdev.h, I2Cdev.h necesita Wire.h
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

// La dirección del MPU6050 puede ser 0x68 o 0x69, dependiendo 
// del estado de AD0. Si no se especifica, 0x68 estará implicito
MPU6050 sensor;

// Valores RAW (sin procesar) del acelerometro y giroscopio en los ejes x,y,z
int ax, ay, az;
int gx, gy, gz;


//#define ledPin 13

unsigned long t1, t2;

void setup()
{
  Serial.begin(115200);
  //pinMode(ledPin, OUTPUT);
  t1 = 0; t2 = 0;
  
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor
  
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 63535;            // preload timer 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS11);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}
// interrupt service routine that wraps a user defined function 
// supplied by attachInterrupt
ISR(TIMER1_OVF_vect)        
{
  TCNT1 = 63535;            // preload timer
  //digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
  t2 = micros();
  //Serial.print(t2 - t1);
  //Serial.println("us");
  t1 = t2;

  
}

void loop()
{
  // your program here...
  // Leer las aceleraciones y velocidades angulares
  sensor.getAcceleration(&ax, &ay, &az);
  //sensor.getRotation(&gx, &gy, &gz);

  //Mostrar las lecturas separadas por un [tab]
  //Serial.print("a(z)");
  //Serial.print("a[x y z] g[x y z]:\t");
  //Serial.print(ax); Serial.print("\t");
  //Serial.print(ay); Serial.print("\t");
  Serial.println(az); //Serial.print("\n");
  //Serial.print(gx); Serial.print("\t");
  //Serial.print(gy); Serial.print("\t");
  //Serial.println(gz);
  //delay(1);
}