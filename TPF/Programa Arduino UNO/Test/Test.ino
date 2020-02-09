#define YAW_IN A0 // Rango: 160 - 900
#define PITCH_IN A1 // Rango: 160 - 840

void setup() {
  
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);

  pinMode(YAW_IN, INPUT);
  pinMode(PITCH_IN, INPUT);

  Serial.begin(9600);
}

void loop() {
  //int val = analogRead(YAW_IN);
  //Serial.print("YAW = ");
  //Serial.println(val);
  
  //int val2 = analogRead(PITCH_IN);
  //Serial.print("PITCH = ");
  //Serial.println(val2);

}
