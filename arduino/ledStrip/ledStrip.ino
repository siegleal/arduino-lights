
#include <avr/pgmspace.h>

#define DATA_1 (PORTC |=  0X01)    // DATA 1    // for UNO
#define DATA_0 (PORTC &=  0XFE)    // DATA 0    // for UNO
#define STRIP_PINOUT (DDRC=0xFF)    // for UNO



PROGMEM const unsigned long pattern_test_red[10][10]={
  {0xff0000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
  {0x000000,0xff0000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
  {0x000000,0x000000,0xff0000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
  {0x000000,0x000000,0x000000,0xff0000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
  {0x000000,0x000000,0x000000,0x000000,0xff0000,0x000000,0x000000,0x000000,0x000000,0x000000},
  {0x000000,0x000000,0x000000,0x000000,0x000000,0xff0000,0x000000,0x000000,0x000000,0x000000},
  {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xff0000,0x000000,0x000000,0x000000},
  {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xff0000,0x000000,0x000000},
  {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xff0000,0x000000},
  {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xff0000},
};

uint32_t pattern_all_red[10] = {0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000,0xff0000};
uint32_t pattern_all_blue[10] = {0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00,0x00ff00};
uint32_t pattern_all_green[10] = {0x0000ff,0x0000ff,0x0000ff,0x0000ff,0x0000ff,0x0000ff,0x0000ff,0x0000ff,0x0000ff,0x0000ff};


uint32_t RED = 0xff0000;
uint32_t BLUE = 0x00ff00;
uint32_t GREEN = 0x0000ff;
uint32_t YELLOW = 0xff00ff;
uint32_t CYAN = 0x00ffff;
uint32_t PINK = 0xffff00;
uint32_t WHITE = 0xffffff;
uint32_t DEEPPURPLE = 0x4cdd00;
uint32_t DARKBLUE = 0x005c00;

uint32_t pattern_all_purple[10] = {DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE};
uint32_t pattern_purple_blue[10] = {DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DARKBLUE,DARKBLUE,DARKBLUE,DARKBLUE,DARKBLUE};


void setup() {               
  STRIP_PINOUT;        // set output pin - DEBUG: should auto detect which mother board for use
  reset_strip();
  Serial.begin(9600);
  Serial.write("!");
}
void loop()
{
//    writeAllStrip(pattern_all_red, 10);
//    delay(1000);
//    writeAllStrip(pattern_all_green, 10);
//    delay(1000);
//    writeAllStrip(pattern_all_blue, 10);
//    delay(1000);
//    uint32_t rainbow[7] = {RED, GREEN, BLUE, PINK, YELLOW, CYAN, WHITE};
//    writeAllStrip(rainbow, 7);
//    delay(1000);

//    writeAllStrip(pattern_all_purple, 10);
//    delay(5000);

  if (Serial.available() == 3 ) {
      uint32_t rbyte = Serial.read();
      uint32_t bbyte = Serial.read();
      uint32_t gbyte = Serial.read();

      rbyte = rbyte << 16;
      gbyte = gbyte << 8;
      uint32_t coorslight = rbyte | gbyte | bbyte;
      uint32_t* keg = (uint32_t*)malloc(sizeof(uint32_t) * 10);
      for(int i = 0; i < 10; i++){
        keg[i] = coorslight;
      }
      writeAllStrip(keg, 10);
  }
    
}

void writeAllStrip(uint32_t* data, int len){
  noInterrupts();
  int i = 0;
  int top = 10;
  if (len < top){top = len;}
  for (i=0; i < top; i++)
  {
    send_strip(data[i]);
  }
  interrupts();
}
void send_1M_pattern(const unsigned long data[][10], int pattern_no, int frame_rate)
{
  int i=0;
  int j=0;
  uint32_t temp_data;
  for (i=0;i<pattern_no;i++)
  {
    noInterrupts();
    for (j=0;j<10;j++)
    {
      temp_data=pgm_read_dword_near(&data[i][j]);
      send_strip(temp_data);
    }
    interrupts();
    delay(frame_rate);
  }
}
void send_strip(uint32_t data)
{
  int i;
  unsigned long j=0x800000;
  for (i=0;i<24;i++)
  {
    if (data & j)
    {
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");   
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      DATA_0;
    }
    else
    {
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");   
      DATA_0;
    }
    j>>=1;
  }
}
void  reset_strip()
{
  DATA_0;
  delayMicroseconds(20);
}

