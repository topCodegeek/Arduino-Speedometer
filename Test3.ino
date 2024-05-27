#include <TM1637Display.h>
#define CLK 3
#define DIO 4
TM1637Display display = TM1637Display(CLK, DIO);
int vcc=5, gnd=6, irgnd=8;
int ir=7, irsig, t=0;
float speed;

const uint8_t lo[] = {
  SEG_G,                                           // -
  SEG_F | SEG_E | SEG_D,                           // L
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_G                                            // -
  };          

void setup() {
  // put your setup code here, to run once:
pinMode(vcc, OUTPUT);
pinMode(gnd, OUTPUT);
pinMode(irgnd, OUTPUT);
pinMode(ir, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

display.setBrightness(7, true); //Compulsary
digitalWrite(vcc, HIGH);
digitalWrite(gnd, LOW);
digitalWrite(irgnd, LOW);

irsig = digitalRead(ir);
if(irsig==1){
  t=0;
  while(irsig==1 && t<=3000)
  {
    t++;
    delay(1);
    irsig = digitalRead(ir);
  }
  speed = (110.00/t)*36;
}
if(speed<1.5){
  display.setSegments(lo);
}
else{
  display.showNumberDec(round(speed), false, 4, 0);
}
//delay(100);
}
