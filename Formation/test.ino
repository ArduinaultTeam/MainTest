/* Le but du projet est le suivant :
 *  Je dois récupérer les infos de 3 boutons et 2 capteurs
 *  Puis faire bouger une LED en conséquence
 *  
 *  Le premier bouton sert à allumer ou éteindre le système
 *  Le second sert à afficher la valeur des 2 capteurs sur le 7 segments
 *  Le 3ème va allumer la led si la différence de valeur entre les 2 capteurs est grande
 */


// On commence à déclarer les données utiles au 7seg

#include <TM1637Display.h>

const int CLK = 2;
const int DIO = 3;

uint8_t tabSeg[] = { 0xff, 0xff, 0xff, 0xff };

int digit1 = 0;
int digit2 = 0;
int digit3 = 0;
int digit4 = 0;

TM1637Display display(CLK,DIO);





// On définit les pins d'I/O

#define BP_1 1
#define BP_2 4
#define BP_3 5

#define LUMI_1 A0
#define LUMI_2 A1

#define LED 6



// On déclare les variables qui vont nous être utile

int vb_bp_1=0;
int vb_bp_2=0;
int vb_bp_3=0;

int vi_lumi1=0;
int vi_lumi2=0;

int led_activate = 0;







void setup() {
  
  pinMode(1,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  
  pinMode(4,OUTPUT);
  
  Serial.begin(9600);

}

void loop() {

  // On fait une lecture basique de nos capteurs
  
  vb_bp1 = digitalRead(1);
  vb_bp1 = digitalRead(2);
  vb_bp1 = digitalRead(3);

  vi_lumi1=analogRead(LUMI_1);
  vi_lumi2=analogRead(LUMI_2);

  // On prépare la variable qui servira à activer la LED

  if(abs(vi_lumi1-vi_lumi2) > 10)
    led_activate = 1;
  else
  {
    led_activate = 0;
    digitalWrite(LED,LOW);
  }

  // On affiche des choses sur l'afficheur

  display.setBrightness(0x0f);
  display.setSegments(tabSeg);
  delay(2000);

  // On prépare les digits qui seront affichés
  
  digit1 = vi_lumi1/10;
  digit2 = vi_lumi1%10;
  digit3 = vi_lumi2/10;
  digit4 = vi_lumi2%10;

  // Fonctions de débogage :

  /*
  if (vb_bp1==HIGH)
    Serial.println("Le bouton 1 est appuye");
  else
    Serial.println("Le bouton 1 est relache");

  if (vb_bp2==HIGH)
    Serial.println("Le bouton 2 est appuye");
  else
    Serial.println("Le bouton 2 est relache");

  if (vb_bp3==HIGH)
    Serial.println("Le bouton 3 est appuye");
  else
    Serial.println("Le bouton 3 est relache");
  */

  /*
  Serial.println("La valeur du premier capteur est : "+vi_lumi1);
  Serial.println("La valeur du second capteur est : "+vi_lumi2);
  */

  // Le vrai code qui fait des chose si on appuie sur des boutons

  if(vb_bp1==HIGH)
  {    
    if(vb_bp2==HIGH) // On affiche la valeur des capteurs sur le 7 segment
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
