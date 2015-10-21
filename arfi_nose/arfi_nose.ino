// FadSpeed.ino - Arduino sketch to show a fading example of a DC motor using the Ardumoto Shield
// Copyright 2012 Jeroen Doggen (jeroendoggen@gmail.com)
//

#include <Ardumoto.h>

Ardumoto Moto;

#define SPEAKER1   10   // Piezo Speaker pin (positive, other pin to ground)
#define SPEAKER2   9   // Piezo Speaker pin (positive, other pin to ground)
#define SPEAKER3   8   // Piezo Speaker pin (positive, other pin to ground)

void setup()
{
  
  pinMode(SPEAKER1, OUTPUT);
  pinMode(SPEAKER2, OUTPUT);
  pinMode(SPEAKER3, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  Moto.begin();
}

void playTone(uint16_t tone1, uint16_t duration) {
  if(tone1 < 50 || tone1 > 15000) return;  // these do not play on a piezo
  int tic1 = 0;
  int tic2 = 0;
  for (long i = 0; i < duration * 1000L; i += tone1 * 2) {
     digitalWrite(SPEAKER1, HIGH);
     if(tic1==5){
      tic1=0;
      digitalWrite(SPEAKER2,HIGH);
     }
     if(tic2==7){
      tic2=0;
      digitalWrite(SPEAKER3,HIGH);
     }
     delayMicroseconds(tone1);
     digitalWrite(SPEAKER1, LOW);
     digitalWrite(SPEAKER2,LOW);
     digitalWrite(SPEAKER3,LOW);
     delayMicroseconds(tone1);
     tic1++;
     tic2++;
  }     
}


void ruff() {   // dog ruff
  uint16_t i;
  for(i=500; i<600; i+=2)     // "rrr"  (vary down)
     playTone(i,3);
  playTone(500,70);         // "ff"  (long, hard to do)
}
void arf() {   // dog ruff
  uint16_t i;
  for(i=500; i<400; i+=2)     // "rrr"  (vary down)
     playTone(i,3);
  playTone(300,170);         // "ff"  (long, hard to do)
}
void loop()
{
  delay (20);
  char c = Serial.read();
  if (c=='l'){
    digitalWrite(12,HIGH);
    delay(1000);
    digitalWrite(12,LOW);
    delay(1000);
  }
  if (c=='n'){
    digitalWrite(11,HIGH);
    delay(1000);
    digitalWrite(11,LOW);
    delay(1000);
    digitalWrite(11,HIGH);
    delay(1000);
    digitalWrite(11,LOW);
    delay(1000);
    
  }
  if (c=='b'){ 
    ruff();
  }
  if (c=='u'){ 
    arf();
  }
}
