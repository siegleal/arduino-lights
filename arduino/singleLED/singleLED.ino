
int RED = 9;
int GREEN = 10;
int BLUE = 11;
float gFactor = .6;
float bFactor = .6;
int incoming = 0;
int total = 0;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(9600);
  Serial.write("!");
}

void loop() {
  
  if (Serial.available() == 3 ) {
      int inbyte = Serial.read();
      analogWrite(RED, inbyte);
      inbyte = Serial.read();
      analogWrite(GREEN, inbyte * gFactor);
      inbyte = Serial.read();
      analogWrite(BLUE, inbyte * bFactor);
  }
 
}
