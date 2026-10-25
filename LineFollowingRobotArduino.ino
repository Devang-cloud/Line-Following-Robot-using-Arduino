#define enA 10//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 8 //Motor1  L298 Pin in1 
#define in3 7 //Motor2  L298 Pin in1 
#define in4 6 //Motor2  L298 Pin in1 
#define enB 5 //Enable2 L298 Pin enB 
#define R_S A0 //ir sensor Right
#define L_S A1 //ir sensor Left

void setup(){ //  setup code here, to run once

pinMode(R_S, INPUT); // declare if sensor as input  
pinMode(L_S, INPUT); // declare ir sensor as input

pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 

analogWrite(enA, 150); //  Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, 150); // Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 
delay(1000);
}
void loop() {
  int right = digitalRead(R_S);
  int left  = digitalRead(L_S);

  if (right == 0 && left == 0)      forward();
  else if (right == 1 && left == 0) turnRight();
  else if (right == 0 && left == 1) turnLeft();
  else                              Stop();
}

void forward(){  //forward
digitalWrite(in1, HIGH); //Right Motor forward Pin 
digitalWrite(in2, LOW);  //Right Motor backward Pin 
digitalWrite(in3, LOW);  //Left Motor backward Pin 
digitalWrite(in4, HIGH); //Left Motor forward Pin 
}

void turnRight(){ //turnRight
digitalWrite(in1, LOW);  //Right Motor forward Pin 
digitalWrite(in2, HIGH); //Right Motor backward Pin  
digitalWrite(in3, LOW);  //Left Motor backward Pin 
digitalWrite(in4, HIGH); //Left Motor forward Pin 
}

void turnLeft(){ //turnLeft
digitalWrite(in1, HIGH); //Right Motor forward Pin 
digitalWrite(in2, LOW);  //Right Motor backward Pin 
digitalWrite(in3, HIGH); //Left Motor backward Pin 
digitalWrite(in4, LOW);  //Left Motor forward Pin 
}

void Stop(){ //stop
digitalWrite(in1, LOW); //Right Motor forward Pin 
digitalWrite(in2, LOW); //Right Motor backward Pin 
digitalWrite(in3, LOW); //Left Motor backward Pin 
digitalWrite(in4, LOW); //Left Motor forward Pin 
}
