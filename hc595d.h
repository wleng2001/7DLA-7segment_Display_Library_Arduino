#define LEFT 0
#define RIGHT 1
#define _reg_len 16 //length of register for letter

#ifndef hc595d_h
#define hc595d_h
#include "Arduino.h"

class hc595d{
  public:
    hc595d(byte data_pin, byte clock_pin, byte latch_pin){
      pinMode(data_pin, OUTPUT);
      _dt_pin=data_pin;
      pinMode(clock_pin, OUTPUT);
      _clk_pin=clock_pin;
      pinMode(latch_pin, OUTPUT);
      _l_pin=latch_pin;
    }
    
    void begin(byte display_amount=4){
      clear();
      _dis_amount=display_amount-1;
    }
    void display();

    void print(String text);

    void write(byte letter);

    void clear();

    void setCursor(byte place);

    void scroll(bool side, int speed); 
	
    void stopScroll();
	
	  bool ifScroll();

    char showRegister(byte char_n);
    
  private:
    volatile unsigned long _last_scroll=0;
    volatile bool _if_scroll=0;
    volatile bool _side; 
    volatile int _speed;
    volatile byte _start_place=0;
    volatile byte _reg[_reg_len];
    byte _l_w_seg=0; //last written segment
    byte _dis_amount;
    byte _dt_pin;
    byte _clk_pin;
    byte _l_pin;
    static uint8_t SEGMENT_SELECT[];//wybór wyświetlacza od 1. do 8. + wszystkie na raz 
    static uint8_t SEGMENT_MAP[]; 
    static byte _letter[];//all letter are here, but letter M and W are replace by 0x1 and 0x2
    static byte _double_letter[];// 0-1 = M, 2-3 = W
    static byte _number[]; //0-9
    static byte _special_char1[];
    static byte _special_char2[];
    static byte _special_char3[];

    byte n_of_letter(char letter);
    
    byte n_of_number(char letter);

    byte letter_look(char letter);
};

#endif
