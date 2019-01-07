
#include <Wire.h>
#include <MPU6050.h>
#include<Servo.h>
MPU6050 mpu;

unsigned long timer = 0;
float timeStep = 0.01;

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
  
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
    mpu.calibrateGyro();

  mpu.setThreshold(3);
}

void loop()
{
  timer = millis();

  Vector norm = mpu.readNormalizeGyro();

  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;
    
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);  
  Serial.print(" Yaw = ");
  Serial.println(yaw);
  myservo1.write(40);
  myservo2.write(40); 

  th_old=roll;
    
      en=th_des-th_old;
      e_dot=en-e_old;
      E=e_old+en;
      u=kp*en+kd*e_dot+ki*E;
      th_new=th_old+u*0.2*0.2;
      e_old=en;
      th_old=th_new;
      myservo1.write(45+u/2);
      myservo2.write(45-u/2); 
    
}
