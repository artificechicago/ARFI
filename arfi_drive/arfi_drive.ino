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
      digitalWrite(SPEAKER2,HIGH);
     }
     if(tic2==7){
      digitalWrite(SPEAKER3,HIGH);
     }
     delayMicroseconds(tone1);
     digitalWrite(SPEAKER1, LOW);
     if(tic1==10){
      tic1=0;
      digitalWrite(SPEAKER2,LOW);
     }
     if(tic2==14){
      tic2=0;
      digitalWrite(SPEAKER3,LOW);
     }
     delayMicroseconds(tone1);
     tic1++;
     tic2++;
  }     
}


void ruff() {   // dog ruff
  uint16_t i;
  for(i=3000; i<3100; i+=2)     // "rrr"  (vary down)
     playTone(i,3);
  playTone(5000,70);         // "ff"  (long, hard to do)
}

void loop()
{
  int left_right = analogRead(A0);
  int go_go = analogRead(A1);
  double lr_val = (left_right-514.0)/514.0*100.0;
  double gg_val = 100.0*double(abs(go_go-514.0)>300);
  
  Moto.setSpeed('A',lr_val);
  Moto.setSpeed('B',gg_val);
  delay (20);
  char c = Serial.read();
//  if (c=='0') digitalWrite(10,LOW);
//  if (c=='1') digitalWrite(10,HIGH);
  if (c=='b'){ ruff();
  delay(400);
  ruff();
  delay(400);
  ruff();
  }
}
