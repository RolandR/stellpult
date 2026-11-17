
#include <SPI.h>

#define NOP __asm__ __volatile__ ("nop\n\t")

// SPI opcodes
#define WREN  6
#define WRDI  4
#define RDSR  5
#define WRSR  1
#define READ  3
#define WRITE 2


#define addrMode 9
#define copi 11
#define cipo 12
#define srclk 13

unsigned int bit = 0;

unsigned int values[256];
unsigned int buttons[256];

byte one = 109;

unsigned int pattern[30] = {
  0b1000000000000000,
  0b0100000000000000,
  0b0010000000000000,
  0b0001000000000000,
  0b0000100000000000,
  0b0000010000000000,
  0b0000001000000000,
  0b0000000100000000,
  0b0000000010000000,
  0b0000000001000000,
  0b0000000000100000,
  0b0000000000010000,
  0b0000000000001000,
  0b0000000000000100,
  0b0000000000000010,
  0b0000000000000001,
  0b0000000000000010,
  0b0000000000000100,
  0b0000000000001000,
  0b0000000000010000,
  0b0000000000100000,
  0b0000000001000000,
  0b0000000010000000,
  0b0000000100000000,
  0b0000001000000000,
  0b0000010000000000,
  0b0000100000000000,
  0b0001000000000000,
  0b0010000000000000,
  0b0100000000000000,
};

void setup() {
  
  Serial.begin(2000000);
  
  pinMode(addrMode, OUTPUT);
  pinMode(copi, OUTPUT);
  pinMode(cipo, INPUT);
  pinMode(srclk, OUTPUT);

  digitalWrite(addrMode, LOW);
  digitalWrite(copi, LOW);
  digitalWrite(srclk, LOW);

  for(int i = 0; i < 256; i++){
    values[i] = random(pow(2, 16));
  }

  for(int i = 0; i < 256; i++){
    buttons[i] = 0;
  }

  SPI.begin();

}

void loop() {

  //values[one] = random(pow(2, 16));
  //updateAll();

  /*set(0b1110000011100000);
  set(0b0111000001110000);
  set(0b0011100000111000);
  set(0b0001110000011100);
  set(0b0000111000001110);
  set(0b0000011100000111);
  set(0b1000001110000011);
  set(0b1100000111000001);*/

  /*set(0b1111111100000000);
  set(0b0111111110000000);
  set(0b0011111111000000);
  set(0b0001111111100000);
  set(0b0000111111110000);
  set(0b0000011111111000);
  set(0b0000001111111100);
  set(0b0000000111111110);
  set(0b0000000011111111);
  set(0b1000000001111111);
  set(0b1100000000111111);
  set(0b1110000000011111);
  set(0b1111000000001111);
  set(0b1111100000000111);
  set(0b1111110000000011);
  set(0b1111111000000001);*/
  
  for(int i = 0; i < 30; i++){
    /*for(int u = 0; u < 30; u++){
      set(pattern[i]);
    }*/

    set(pattern[i]);
  }

  //printButton(one);

}

void set(unsigned int value){
  values[one] = value;
  updateAll();
}

void checkButtons(unsigned int i, unsigned int value){
  if(buttons[i] == value){
    return;
  } else {
    buttons[i] = value;
    printButton(i);
  }
}

void updateAll(){
  for(unsigned int i = 0; i < 256; i++){
    buttons[i] = readWrite(i, values[i]);
    printButton(i);
  }

  /*int i = 74;
  buttons[i] = (byte)readWrite(i, values[i]);

  i = one;
  buttons[i] = (byte)readWrite(i, values[i]);

  i = 222;
  buttons[i] = (byte)readWrite(i, values[i]);

  i = 89;
  buttons[i] = (byte)readWrite(i, values[i]);*/

  
  
  delay(1000);
}

void printButton(byte index){

  unsigned int value = buttons[index];

  Serial.print(index);
  Serial.print(": ");
  
  for(int u = 0; u < 16; u++){
    
    if((value >> u) & 0x01 == 1){
      Serial.print("X");
    } else {
      Serial.print("O");
    }

    if(u == 7){
      Serial.print(" ");
    }
  }
  Serial.println();
}

void printButtoon(byte index){
  
  String outStr = String(String(index)+": "+String(buttons[index], BIN));
  
  Serial.println(outStr);
}

unsigned int readWrite(byte address, unsigned int data){

  SPI.beginTransaction(SPISettings(6000000, LSBFIRST, SPI_MODE0));

  //digitalWrite(addrMode, LOW);
  
  SPI.transfer(address);

  digitalWrite(addrMode, HIGH);

  delay(0);

  unsigned int result = SPI.transfer16(data);

  delay(0);

  digitalWrite(addrMode, LOW);

  SPI.endTransaction();

  return result;
}
