/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Pitch & Roll & Yaw Gyroscope Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MPU6050.h>
#include<Servo.h>
MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;
Servo myservo1,myservo2;
float th_des=0,e_old,kp=0.3,kd=25,ki=0,en,e_dot,E,u,th_new,th_old;


void setup() 
{
  
    myservo1.attach(9);
    myservo2.attach(10);
    myservo1.write(30);
    myservo2.write(30);
    delay(3000);

    Serial.begin(115200);

    e_old=0;
  
    
  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // Calibrate gyroscope. The calibration must be at rest.
    // If you don't want calibrate, comment this line.
    mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);
}

void loop()
{
  timer = millis();

  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

  // Output raw
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);  
  Serial.print(" Yaw = ");
  Serial.println(yaw);
  myservo1.write(40);
  myservo2.write(40); 

  th_old=roll;
//if(timer>3000)
//{
 // for(float t=0;t<80;t=t+0.2)
 // {
      en=th_des-th_old;
      e_dot=en-e_old;
      E=e_old+en;
      u=kp*en+kd*e_dot+ki*E;
      th_new=th_old+u*0.2*0.2;
      e_old=en;
      th_old=th_new;
      myservo1.write(45+u/2);
      myservo2.write(45-u/2); 
     // Serial.print(u);
   //  if(u==0)
    // {
    // break;
    // }
  // }
 // }
}

  // Wait to full timeStep period
 // delay((timeStep*1000) - (millis() - timer));
