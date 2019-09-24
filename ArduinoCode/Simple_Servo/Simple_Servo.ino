#include <Servo.h>

Servo myservo; 
int degre = 180;
void setup() {
  Serial.begin(115200);
  Serial.println();
}

void loop() {
  int pos;
  myservo.attach(2);
  for (pos = 0; pos <= degre; pos += 1) {
    // in steps of 1 degree
    myservo.write(pos);              
    delay(15);                       
  }
  
  /*
  for (pos = degre; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
  */
  Serial.print(myservo.read());
  myservo.detach();
  delay(5000);
}
