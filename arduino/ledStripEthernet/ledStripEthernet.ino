
#include <avr/pgmspace.h>
#include <SPI.h>
#include <Ethernet.h>

#define DATA_1 (PORTC |=  0X01)    // DATA 1    // for UNO
#define DATA_0 (PORTC &=  0XFE)    // DATA 0    // for UNO
#define STRIP_PINOUT (DDRC=0xFF)    // for UNO



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
uint32_t OFF = 0x000000;

uint32_t pattern_all_purple[10] = {DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE};
uint32_t pattern_all_white[10] = {WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE};
uint32_t pattern_purple_blue[10] = {DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DEEPPURPLE,DARKBLUE,DARKBLUE,DARKBLUE,DARKBLUE,DARKBLUE};
uint32_t pattern_small_green[10] = {0x000077,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF};
uint32_t pattern_small_red[10] = {0x770000,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF};
uint32_t pattern_small_white[10] = {0x777777,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF,OFF};




/**
 * Ethernet setup stuff
 */
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168, 137, 17);
IPAddress myDns(192,168,1, 1);

// telnet defaults to port 23
EthernetServer server(23);
boolean alreadyConnected = false; // whether or not the client was connected previously

float rBalance = .6;
unsigned long lastMaintain;

void setup() {     
              
  STRIP_PINOUT;        // set output pin - DEBUG: should auto detect which mother board for use
  reset_strip();
  writeAllStrip(pattern_small_white, 10);
  // Open serial communications and wait for port to open:
   Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // start the Ethernet connection:
  Serial.println("Trying to get an IP address using DHCP");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // initialize the Ethernet device not using DHCP:
    Ethernet.begin(mac, ip, myDns);
    writeAllStrip(pattern_small_red, 10);
  }else{
    writeAllStrip(pattern_small_green, 10);
  }
  // print your local IP address:
  Serial.print("My IP address: ");
  ip = Ethernet.localIP();
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(ip[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();
  // start listening for clients
  server.begin();

  lastMaintain = millis(); 

}
void loop()
{
  //wait for new client
  EthernetClient client = server.available();
  if (millis() - lastMaintain > 60000){
    Ethernet.maintain();
    Serial.println("Maintaining DHCP");
    lastMaintain = millis();
  }

  // when the client sends the first byte, say hello:
  if (client) {
    if (!alreadyConnected) {
      // clear out the input buffer:
      client.flush();
      Serial.println("We have a new client");
      alreadyConnected = true;
    }
    
    if (client.available() >= 3) {
      
      uint32_t rbyte = client.read() * rBalance;
      uint32_t bbyte = client.read();
      uint32_t gbyte = client.read();

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

