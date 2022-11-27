#include <signal.h>
#include <Servo.h>
//signal(
#define RIGHT_HAND_SERVO_PORT 10
#define LEFT_HAND_SERVO_PORT 11
Servo servo_right; // #right hand servo port 10
Servo servo_left; // #left hand servo port 11
const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;

int dataNumber = 0;             // new for this version

void setup() {
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
    servo_right.attach(RIGHT_HAND_SERVO_PORT);
    servo_left.attach(LEFT_HAND_SERVO_PORT);
    for (int i = 2; i <= 8; i = i + 1) {
      pinMode(i, OUTPUT);
  }

}

void loop() {
   recvWithEndMarker();
   lightOrgan();

}
// 4 LEFT
// 6 RIGHT
// 8 DOWN
// 2 UP
void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    if (Serial.available() > 0) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void lightOrgan() {
  digitalWrite(dataNumber, LOW);             // new for this version
  dataNumber = (atoi(receivedChars));
  digitalWrite(dataNumber, HIGH);
  if (dataNumber == 6){
    rightMotorMovment();
  }
  if (dataNumber == 4){
   leftMotorMovment();
  }
}

void motorMovment(Servo servo, int min_degree, int max_degree){
  int pos = 0;
  for(pos=min_degree;pos<=max_degree ;pos++){
    servo.write(pos);
    delay(20);
  }
   delay(100); 
   for(pos=max_degree;pos>=min_degree;pos--){
      servo.write(pos);
      delay(20);
    }
   
   delay(100);
}

void moveToBaseLine(Servo servo){
  for(int i=0;i<=5;i++){
    servo.write(15);  
  }
  
}
void leftMotorMovment(){
  moveToBaseLine(servo_right);
  motorMovment(servo_left, 20,80);
}


void rightMotorMovment(){
  moveToBaseLine(servo_left);
  motorMovment(servo_right, 10, 40);
}
