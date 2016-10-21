#include <TM1637Display.h>

const int CLK = 2;
const int DIO = 3;

uint8_t tabSeg[] = { 0xff, 0xff, 0xff, 0xff };

int digit1 = 0;
int digit2 = 0;
int digit3 = 0;
int digit4 = 0;

TM1637Display display(CLK,DIO);

#define BP_1 4
#define BP_2 5
#define BP_3 6

#define LUMI_1 A0
#define LUMI_2 A1

#define LED 7

int vb_bp_1=0;
int vb_bp_2=0;
int vb_bp_3=0;

int vi_lumi1=0;
int vi_lumi2=0;

int led_activate = 0;

void setup() 
{
  pinMode(BP_1,INPUT);
  pinMode(BP_2,INPUT);
  pinMode(BP_3,INPUT);
  
  pinMode(LED4,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  
  vb_bp1 = digitalRead(BP_1);
  vb_bp1 = digitalRead(BP_2);
  vb_bp1 = digitalRead(BP_3);

  vi_lumi1=analogRead(LUMI_1);
  vi_lumi2=analogRead(LUMI_2);

  if(abs(vi_lumi1-vi_lumi2) > 10)
    led_activate = 1;
  else
  {
    led_activate = 0;
    digitalWrite(LED,LOW);
  }

  display.setBrightness(0x0f);
  display.setSegments(tabSeg);
  delay(2000);
  
  digit1 = vi_lumi1/10;
  digit2 = vi_lumi1%10;
  digit3 = vi_lumi2/10;
  digit4 = vi_lumi2%10;

  if(vb_bp1==HIGH)
  {    
    if(vb_bp2==HIGH)
      {
        tabSeg[0] = display.encodeDigit(digit1);
        tabSeg[1] = display.encodeDigit(digit2);
        tabSeg[2] = display.encodeDigit(digit3);
        tabSeg[3] = display.encodeDigit(digit4);
      }
    
    if(vb_bp3==HIGH && led_activate==1)
      digitalWrite(LED,HIGH);
  }
  else
    Serial.println("Le systeme est déconnecte");
}
