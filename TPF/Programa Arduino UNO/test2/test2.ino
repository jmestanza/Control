//// TPF - 22.85 Sistemas de Control 

// ADC
#define MANUAL_PITCH A0
#define MANUAL_YAW A1
#define SIGNAL_YAW A2
#define SIGNAL_PITCH A3
#define YAW_IN A4 // Rango: 200 - 900
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

// Control PID
/* PERIODO SAMPLEO */
#define Ts_ms 10.0  //en milisegundos
#define Ts (Ts_ms/1e3) //en segundos

/* CONSTANTES PID */
#define _KpP 2.0
#define _KiP 2.4
#define _KdP 0.5

#define _KpY 2.0
#define _KiY 2.0
#define _KdY 0.4

float KpP = _KpP;
float KiP = _KiP * Ts;
float KdP = _KdP / Ts;

float KpY = _KpY;
float KiY = _KiY * Ts;
float KdY = _KdY / Ts;

/* LIMITES LECTURA SENSOR */
#define SENSOR_READ_P_MIN 200
#define SENSOR_READ_P_MAX 700

#define SENSOR_READ_Y_MIN 200
#define SENSOR_READ_Y_MAX 900

/* LIMITES VELOCIDAD GIRO HELICE */
//Duty de PWM para lograr las velocidades
#define MOTOR_SPEED_MIN -255
#define MOTOR_SPEED_MAX 255

/* PARA CONTROL DE DELAY */
unsigned long lastReadyTime;

/* ENTRADA DE LA PLANTA */
unsigned int prevPIDoutput_P = 0;
unsigned int prevPIDoutput_Y = 0;


/* LECTURA DEL SENSOR */
int sensorReadP = 500;
int sensorReadY = 500;

/* SET POINT - POSICION DESEADA */
int setPointP = 500;
int setPointY = 500;

int plantInputP = 0;
int plantInputY = 0;

/* ESTADO DE MOTOR */
bool motor_on = true;

/*
   iAmReady:
   Devuelve true:
   1) La primera vez que se llama.
   2) Si sucedieron mas de Ts milisegundos desde la ultima vez que devolvio true.
*/
bool iAmReady();

void PID_cycle(int setPointP, int sensorReadP, int *plantP, 
               int setPointY, int sensorReadY, int *plantY);


void setup() {
  
  initADC();
  initPuenteH();
}

void loop() {
  
  //in1 = analogRead(PITCH_IN);
  //aux = analogRead(MANUAL_PITCH);
  //sp1 = ((aux*500)/1023) + 200;
  
  //configMotor(MPITCH, out1);


  //ESPERAR QUE HAYAN SUCEDIDO TS MILISEGUNDOS
  while(!iAmReady()){}

  //OBTENER SALIDA DE LA PLANTA
  sensorReadP = analogRead(PITCH_IN);
  sensorReadY = analogRead(YAW_IN);
  
  double aux;
  double spP,spY;
  aux = analogRead(MANUAL_PITCH);
  spP = ((aux*500)/1023) + 200;
  aux = analogRead(MANUAL_YAW);
  spY = ((aux*700)/1023) + 200;
  //CALCULAR LA ENTRADA A LA PLANTA Y MANDAR POR PWM 
  PID_cycle(spP, sensorReadP, &plantInputP, spY, sensorReadY, &plantInputY);
  
  configMotor(MPITCH, -plantInputP);
  configMotor(MYAW, -plantInputY);

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
  else if(param < -190) { 
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

void PID_cycle(int setPointP, int sensorReadP, int *plantP, 
               int setPointY, int sensorReadY, int *plantY)
{
  static float prevSensorReadP = 0;
  static float prevSensorReadY = 0;
  static float prevErrorP = 0;
  static float prevErrorY = 0;
  static float integralTerm = MOTOR_SPEED_MIN;
  float proportionalTerm;
  float derivativeTerm;
  
  //Si la lectura del sensor esta fuera de rango, usar la anterior
  //if ( sensorRead < SENSOR_READ_MIN || sensorRead > SENSOR_READ_MAX ) { sensorRead = prevSensorRead; }


  // PITCH //
  float error = setPointP - sensorReadP;

  /******************************/
  /* Calculo de los 3 terminos: */
  /******************************/
  //(P)
  proportionalTerm = KpP * error;
  //(D)
#ifdef DERIVATIVE_MEASUREMENT
  derivativeTerm = KdP * (-sensorReadP - (-prevSensorReadP)); //no considera setPoint para evitar "Derivative Kick"
#else
  derivativeTerm = KdP * (error - prevErrorP);
#endif
  //(I)
  integralTerm += KiP * error;
  /******************************/
  
  prevErrorP = error;
  int outputP = proportionalTerm + integralTerm + derivativeTerm;
  if(outputP < MOTOR_SPEED_MIN) outputP = MOTOR_SPEED_MIN;
  if(outputP > MOTOR_SPEED_MAX) outputP = MOTOR_SPEED_MAX;


  //backup de valores para la proxima iteracion
  prevSensorReadP = sensorReadP;
  *plantP = outputP;

  // YAW //

  error = setPointY - sensorReadY;

  /******************************/
  /* Calculo de los 3 terminos: */
  /******************************/
  //(P)
  proportionalTerm = KpY * error;
  //(D)
#ifdef DERIVATIVE_MEASUREMENT
  derivativeTerm = KdY * (-sensorReadY - (-prevSensorReadY)); //no considera setPoint para evitar "Derivative Kick"
#else
  derivativeTerm = KdY * (error - prevErrorY);
#endif
  //(I)
  integralTerm += KiY * error;
  /******************************/
  
  prevErrorY = error;
  int outputY = proportionalTerm + integralTerm + derivativeTerm;
  if(outputY < MOTOR_SPEED_MIN) outputY = MOTOR_SPEED_MIN;
  if(outputY > MOTOR_SPEED_MAX) outputY = MOTOR_SPEED_MAX;


  //backup de valores para la proxima iteracion
  prevSensorReadY = sensorReadY;
  *plantY = outputY;
}

bool iAmReady()
{
  static bool firstTime = true;
  if (firstTime) //Primera vez que se llama
  {
    lastReadyTime = millis();
    firstTime = false;
    return true;  
  }
  unsigned long currentTime = millis();
  if(currentTime >= lastReadyTime + Ts_ms) //Sucedieron mas de Ts milisegundos desde la ultima vez que devolvio true
  {
    lastReadyTime = currentTime;
    return true;  
  }
  return false;
}
