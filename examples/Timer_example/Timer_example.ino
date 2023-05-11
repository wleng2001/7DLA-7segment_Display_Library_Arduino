#include <TimerOne.h>
#include <hc595d.h>

#define refresh 1000

const int latchPin = 4;//ST_CP
const int clockPin = 7;//SH_CP 
const int dataPin = 8; //DS 
volatile int milis=0;
volatile int sec=0;
volatile int mins=0;


hc595d hc(dataPin, clockPin, latchPin);

void interrupt_func(){
  hc.display();
  milis+=refresh/1000;
  if(milis==1000){
    milis=0;
    sec+=1;
  }
}

void timer(){
}

void setup(){
  hc.begin(); //default display have 4 part
  Timer1.initialize(refresh);
  Timer1.attachInterrupt(interrupt_func); 
  interrupts();
  hc.print("HI");
  while(milis<=1000){
    
  }
}

void loop(){
  String text=""; //variable to save part of displayed data

  if(sec>=60){
    sec=0;
    mins+=1;
    if(mins==100){
      mins=0;
    }
  }
  
  if(mins<10){
    text+="0";
  }
  text+=String(mins);
  if(milis<=500){
    text+=".";
  }
  if(sec<10){
    text+="0";
  }
  text+=String(sec);
  hc.clear(); //clear register of the display
  hc.print(text);
}
