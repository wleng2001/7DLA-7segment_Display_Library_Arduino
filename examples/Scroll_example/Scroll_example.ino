#include <TimerOne.h> //library for interna interrupts
#include <hc595d.h> //add our library

#define refresh 1000 //how offten refresh display

const int latchPin = 4;
const int clockPin = 7; 
const int dataPin = 8;

//function for timer
volatile int milis=0; 
volatile int sec=0; 


hc595d hc(dataPin, clockPin, latchPin); //create object oc hc595d class

void interrupt_func(){ //function, which works when inturrupts is enable
  hc.display(); //display data 
  milis+=refresh/1000;
  if(milis==1000){
    milis=0;
    sec+=1;
  }
}

void timer(){
}

void setup(){
  hc.begin(); //start of hc595d library, default display have 4 part so you don't have to add number here
  Timer1.initialize(refresh); //initialize internal interrupts in every 10 seconds
  Timer1.attachInterrupt(interrupt_func); //add function to internal interrupts
  interrupts(); //activate interrupts
  hc.print("HI"); //add "HI" to library register so to display
  while(milis<=998){ //delay 1 second

  }
  hc.clear(); //clear libary register so display
}

void loop(){
  hc.clear();
  hc.print("Some example!!"); //add "Some text for all reg" to library register so to display
  while(milis<=998){
    
  }
  hc.setCursor(1); //start print on display from 2. place so you can see on the display: "ome "
  while(milis<=998){
    
  }
  hc.scroll(RIGHT, 250); //scroll to the right
  while(hc.ifScroll()){ //if_scroll directive return True if display scroll

  }
  while(milis<=998){
    
  }
  hc.scroll(LEFT, 250); //scroll to the right
  while(hc.ifScroll()){

  }
  while(milis<=998){
    
  }
  hc.stopScroll(); //stop scroll
  hc.setCursor(0); //set cursor on the start
}
