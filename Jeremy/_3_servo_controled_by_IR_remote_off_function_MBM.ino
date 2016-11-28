#include<IRremote.h>
IRrecv receiver(11);
decode_results results;

#include<Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;

int CASE = 0;
int servopos1=20;
int servopos2=0;
int inity=0;
int etat=0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
receiver.enableIRIn();

servo1.attach(5);
servo2.attach(4);
servo3.attach(3);
pinMode(13,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
if(receiver.decode(&results)){
  int val= results.value;
  Serial.println(val,HEX);
inity=1;
  switch(val)
  {
    case 0xFF629D:
    CASE=1;
    break;

    case 0xFFA857:
    CASE=2;
    break;

    case 0xFF22DD:
    CASE=3;
    break;

    case 0xFFC23D:
    CASE=4;
    break;

    case 0xFF4AB5:
    CASE=5;
    if (etat==0)
    etat=1;
    if(etat==1)
    etat=0;
    break;



    case 0xFFFFFFFF:
    break;
  }
  if(etat==0)
  {
    digitalWrite(13,HIGH);
  switchCaseSimplify(CASE);
  servo1.write(servopos1);
  servo2.write(servopos2);
  servo3.write(servopos2);
  }
  else
  {
    digitalWrite(13,LOW);
     servo1.write(40);
    servo2.write(40);
    servo3.write(40);
  }
  receiver.resume();
delay(100);
}
if(inity==0)
  {
    servo1.write(20);
    servo2.write(0);
    servo3.write(0);
  }
}
