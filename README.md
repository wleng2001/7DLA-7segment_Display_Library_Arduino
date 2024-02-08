# 7DLA-7segment_Display_Library_Arduino
## Description
 It's simple library for arduino, which allow to controll 7 segment display, which driver is 74hc595d shift register. You can print on it numbers, letters and special chars.
## Initialize library
 Library offers some methods, but first you must create object by:
 #### `hc595d hc(byte dataPin, byte clockPin, byte latchPin);`
 
 Next you must add it in setup() function:
 
 #### `  hc.begin(byte display_amount);`
 
 *display_amount* inform how many part have display (if you don't write information it give here 4)
 
 You can use methods of library!
 
 Length of register is set up for 16 chars. If you want change it you must change number in the line in *hc595d.h* file:
 
 #### `#define _reg_len 16`
 
 ## Methods of library
  It's list of methods:
 ```
 void display();
 void clear();
 void write(byte letter);
 void print(String text);
 void setCursor(byte place);
 void scroll(bool side, int speed); 
 void stopScroll();
 bool ifScroll(); 
 char showRegister(byte char_n);
 ```

 `display();`

Print information on the screen one time.

`clear();`

Clear information printed on display.

`write(byte letter);`

Add one char to display buffer.

'print(String text);'

Add *text* to buffer.

`setCursor(byte place);`

Print display at the *place*.

`scroll(bool side, int speed);`

if you get *0* or *LEFT* display scrolls at left if you get *1* or *RIGHT* it scrolls at right. Speed is in char/ms.

`stopScroll()`

The method stops scrolling.

`ifScroll();`

Return information about, that display is scrolling.

`showRegister(byte char_n)`

Return char, which is contained at the *char_n*


## Hardware
 You can see example of hardware <a href="https://www.tinkercad.com/things/94vdo8qcPSc">here</a> or use *multifunction shield*. You can see photo of hardware in TinkerCad bellow.
 ![It's photo of hardware](https://github.com/wleng2001/7DCw7-7segment_Display_Controled_with_74hc595d_by_arduino/blob/main/hardware.png)
 
 ## Software 
  You can use the library in <a href="https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE">Arduino IDE</a>. You must add it to your program. <a href="https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries">Here</a> is how you can do it.
