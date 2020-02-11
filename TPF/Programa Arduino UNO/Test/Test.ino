//// TPF - 22.85 Sistemas de Control 

#include<PID_v1.h>

#define KP 1.6 // Valor de oscilatorio 0.8 con KD y KI en 0
#define KI 0.8
#define KD 0.5

double aux = 0;
double sp = 500;
double in = 0;
double out = 0; 

PID myPID(&in , &out , &sp ,KP,KI ,KD, REVERSE);
// ADC
#define MANUAL_PITCH A0
#define MANUAL_YAW A1
#define SIGNAL_YAW A2
#define SIGNAL_PITCH A3
#define YAW_IN A4 // Rango: 320 - 1000
#define PITCH_IN A5 // Rango: 200 - 700

// Puente H - Maximo Duty en 200
#define ENA 11
#define IN1 10
#define IN2 9
#define IN3 1 
#define IN4 2
#define ENB 3

#define MYAW 0
#define MPITCH 1

void setup() {
  
  initADC();
  initPuenteH();
  myPID.SetMode(AUTOMATIC); 
  myPID.SetOutputLimits(-255 ,255);
  myPID.SetSampleTime(10);

  //Serial.begin(9600);
}

void loop() {
  
  in = analogRead(PITCH_IN);
  aux = analogRead(MANUAL_PITCH);
  sp = ((aux*500)/1023) + 200;
  //Serial.println(analogRead(YAW_IN));
  myPID.Compute();
  configMotor(MPITCH, out);
  
}

void initADC() {
  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
  pinMode (A2, INPUT);
  pinMode (A3, INPUT);
  pinMode (A4, INPUT);  
}

void initPuenteH() {
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void setForward(int motor) {
  if(motor == MYAW) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else if(motor == MPITCH) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
}

void setBackward(int motor) {
  if(motor == MYAW) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  else if(motor == MPITCH) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}

void setMotorSpeed(int motor, int value) { // 0 - 255
  if(motor == MYAW) {
    analogWrite(ENA, value);
  }
  else if(motor == MPITCH) {
    analogWrite(ENB, value);
  }
}

void configMotor(int motor, int param) {
  if(param > 190) {
    param = 190;
  }
  else if(param < 190) { 
    param = -190;
  }

  if(param > 0) {
    setBackward(motor);
    setMotorSpeed(motor, param);
  }
  else if(param < 0) {
    setForward(motor);
    setMotorSpeed(motor, -param);
  }
}
