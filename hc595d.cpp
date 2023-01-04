#include "hc595d.h"

uint8_t hc595d::SEGMENT_SELECT[] = {0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80,0xFF};
uint8_t hc595d::SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90}; 
byte hc595d::_letter[]={ 
  B10001000,/*A*/ 
  0x83,/*B*/ 
  0xA7,/*C*/ 
  0xA1,/*D*/ 
  0x86,/*E*/ 
  0x8e,/*F*/ 
  0xC2,/*G*/ 
  0x89,/*H*/ 
  0xCF,/*I*/ 
  0xF1,/*J*/ 
  0x8A,/*K*/ 
  0xC7,/*L*/ 
  0x1,/*M*/
  B10101011,/*N*/ 
  0xA3,/*O*/ 
  0x8C,/*P*/ 
  0x99,/*Q*/ 
  0xAF,/*R*/ 
  B10011010,/*S*/ 
  B11001110,/*T*/ 
  B11000001,/*U*/ 
  B11100011,/*V*/ 
  0x2,/*W*/ 
  B10011011,/*X*/ 
  B10010001,/*Y*/ 
  B10101100/*Z*/
}; //A-Z  M = 0x1, W = 0x2
byte hc595d::_double_letter[]={0xCC,0xD8, B11000011, B11100001}; // 0-1 = M, 2-3 = W
byte hc595d::_number[10]={
  B11000000, //0 
  B11111001, //1
  B10100100, //2
  B10110000, //3
  B10011001, //4
  B10010010, //5
  B10000010, //6
  B11111000, //7
  B10000000, //8
  B10010000 //9
}; //0-9

byte hc595d::_special_char1[]={
  B11111111, // " "
  B01111011, //!
  B11011101, //"
  B11111111, //#
  B11111111, //$
  B11111111, //%
  B11111111, //&
  B11111101, //'
  B11000110, //(
  B11110000, //)
  B10011100, //*
  B11111111, //+
  B01111111, //,
  B10111111, //-
  B01111111, //.
  B10101101, //"/"
};

byte hc595d::_special_char2[]={
  B10111110, //:
  B10111110, //;
  B11111111, //<
  B10110111, //=
  B11111111, //>
  B01011000, //?
  B11111111, //@
};

byte hc595d::_special_char3[]={
  B11000110, //[
  B11011011, //"\"
  B11110000, //]
  B11011100, //^
  B11110111, //_
  B11011111, //`
};

void hc595d::display(){
  if(_if_scroll==1){
    unsigned long time=millis();
    if(_last_scroll+_speed<=time){
      _last_scroll=time;
      if(_side==RIGHT and _start_place<_reg_len){
        _start_place++;
      }else{
        if(_start_place>0 and _side==LEFT){
          _start_place-=1;
        }else{
          _if_scroll=0;
        }
      }
    }
  } 
  byte choose_seg=0; 
  for(byte i=_start_place; i<=_start_place+_dis_amount; i++){
    byte letter;
    if(i>=_reg_len){
      letter=B11111111;
    }else{
      letter=_reg[i];
    }
    digitalWrite(_l_pin,LOW); 
    shiftOut(_dt_pin, _clk_pin, MSBFIRST, letter);
    shiftOut(_dt_pin, _clk_pin, MSBFIRST, SEGMENT_SELECT[choose_seg]);
    digitalWrite(_l_pin,HIGH); 
    choose_seg++;
  }
}

void hc595d::print(String text){
  char letter;
  byte l_look;
  for(byte i=0; i<text.length(); i++){
    if(_l_w_seg>=_reg_len){
      break;
    }
    letter=char(text[i]);
    l_look=letter_look(letter);
    if(l_look==B01111111 and (_l_w_seg+i)>0 and _reg[_l_w_seg-1]>128){
      _reg[_l_w_seg-1]=bitClear(_reg[_l_w_seg-1], 7);
      continue;
    }
    if(l_look<4){
      byte place=(l_look-1)*2;
      _reg[_l_w_seg]=_double_letter[place];
      _l_w_seg++;
      _reg[_l_w_seg]=_double_letter[place+1];
      _l_w_seg++;
      continue;
    }
    _reg[_l_w_seg]=l_look;
    _l_w_seg++;
  }
}

void hc595d::write(byte letter){
  if(_reg_len>=_l_w_seg){
    _reg[_l_w_seg]=letter;
    _l_w_seg++;
  }
}

void hc595d::clear(){
  for(byte i=0; i<=_reg_len; i++){
    _reg[i]=B11111111;
  }
  _l_w_seg=0;
}

void hc595d::setCursor(byte place){
  _start_place=place;
}

void hc595d::scroll(bool side, int speed){
  _if_scroll=1;
  _side=side;
  _speed=speed;
}

void hc595d::stopScroll(){
  _if_scroll=0;  
}

bool hc595d::ifScroll(){
	return _if_scroll;
}

byte hc595d::showRegister(byte char_n){
  if(char_n<_reg_len){
    return _reg[char_n];
  }else{
    return 0x86;
  }
}

//read data

byte hc595d::n_of_letter(char letter){
  if(letter>=65 and letter<=90){
    return letter-65;
  }else{
    if(letter>=97 and letter<=122){
      return letter-97;
    }else{
      return B11111111;
    }
  }
}

byte hc595d::n_of_number(char letter){
  if(letter>=48 and letter<=57){
    return letter-48;
  }else{
    return B11111111;
  }
}

byte hc595d::letter_look(char letter){
  byte l_n=letter; //number of letter in ascii table
  if(letter>=32 and letter<=47){
    return _special_char1[l_n-32];
  }
  if(letter>=58 and letter<=64){
    return _special_char2[l_n-58];
  }
  if(letter>=91 and letter<=96){
    return _special_char3[l_n-91];
  }
  l_n=n_of_letter(letter);
  if(l_n!=B11111111){
    return _letter[l_n];
  }
  l_n=n_of_number(letter);
  if(l_n!=B11111111){
    return _number[l_n];
  }else{
    return 0x86; //return E
  }
}
