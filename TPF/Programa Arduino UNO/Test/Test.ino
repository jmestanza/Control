//// TPF - 22.85 SisteMYAWs de Control 

// ADC
#define MYAWNUAL_PITCH A0
#define MYAWNUAL_YAW A1
#define SIGNAL_YAW A2
#define SIGNAL_PITCH A3
#define YAW_IN A4 // Rango: 160 - 900
#define PITCH_IN A5 // Rango: 160 - 840

// Puente H - MYAWximo Duty en 200
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

  setForward(MYAW);
  setMotorSpeed(MYAW, 195);
  
  //Serial.begin(9600);
}

void loop() {
  //int val = analogRead(YAW_IN);
  //Serial.print("YAW = ");
  //Serial.println(val);
  
  //int val2 = analogRead(PITCH_IN);
  //Serial.print("PITCH = ");
  //Serial.println(val2);

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
