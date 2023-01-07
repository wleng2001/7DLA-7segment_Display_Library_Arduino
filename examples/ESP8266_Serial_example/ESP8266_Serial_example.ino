#include <Ticker.h>

#include <hc595d.h>
#define refresh 1000

const int latchPin = D4;//ST_CP
const int clockPin = D7;//SH_CP 
const int dataPin = D8; //DS 

hc595d hc(dataPin, clockPin, latchPin);
Ticker interrupt;

void interrupt_func(){
  hc.display();
}

String receive_data(){
  String data="";
  if(Serial.available() > 0) {
    data=Serial.readStringUntil('\n'); //read input to '\n' sign
  }
  return data;
}

void setup(){
  Serial.begin(9600);
  Serial.println("Work!");
  hc.begin(4);
  interrupt.attach(0.001, interrupt_func);
  hc.print("HI");
  String reg="";
  for(byte i=0; i<_reg_len; i++){
    Serial.print(hc.showRegister(i));
    Serial.print(";");
  }
  Serial.println("");
}

void loop(){
  String data=receive_data();
  if(data!=""){
    Serial.println(data);
    hc.clear();
    hc.print(data);
  }
}
