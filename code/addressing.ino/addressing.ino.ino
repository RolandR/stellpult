
#define srclk 2
#define srclr 3
#define rclk 4
#define ser 5
#define p6 6
#define p7 7

#define p8 8
#define p9 9
#define p10 10
#define p11 11
#define p12 12
#define p13 13

const int smallDelay = 0;

const unsigned int mine = 0b01110011;

unsigned int values[256];

unsigned int bit = 0;


void setup() {
  pinMode(srclk, OUTPUT);
  pinMode(ser, OUTPUT);
  pinMode(rclk, OUTPUT);
  pinMode(srclr, OUTPUT);
  pinMode(p6, OUTPUT);
  pinMode(p7, OUTPUT);

  pinMode(p8, OUTPUT);
  pinMode(p9, OUTPUT);
  pinMode(p10, OUTPUT);
  pinMode(p11, OUTPUT);
  pinMode(p12, OUTPUT);
  pinMode(p13, OUTPUT);

  digitalWrite(srclk, LOW);
  digitalWrite(ser, LOW);
  digitalWrite(rclk, LOW);
  digitalWrite(srclr, LOW);
  digitalWrite(p6, LOW);
  digitalWrite(p7, LOW);
  
  digitalWrite(p8, LOW);
  digitalWrite(p9, LOW);
  digitalWrite(p10, LOW);
  digitalWrite(p11, LOW);
  digitalWrite(p12, LOW);
  digitalWrite(p13, LOW);

  digitalWrite(srclr, HIGH);

  for(int i = 0; i < 256; i++){
    values[i] = random(pow(2, 16));
  }

}

void loop() {

  

  //values[a] = random(pow(2, 16)-1);
  //updateAll();

  //delay(200);

  /*display(0b1000000000000000);
  display(0b0100000000000000);
  display(0b0010000000000000);
  display(0b0001000000000000);
  display(0b0000100000000000);
  display(0b0000010000000000);
  display(0b0000001000000000);
  display(0b0000000100000000);
  display(0b0000000010000000);
  display(0b0000000001000000);
  display(0b0000000000100000);
  display(0b0000000000010000);
  display(0b0000000000001000);
  display(0b0000000000000100);
  display(0b0000000000000010);
  display(0b0000000000000001);
  display(0b0000000000000010);
  display(0b0000000000000100);
  display(0b0000000000001000);
  display(0b0000000000010000);
  display(0b0000000000100000);
  display(0b0000000001000000);
  display(0b0000000010000000);
  display(0b0000000100000000);
  display(0b0000001000000000);
  display(0b0000010000000000);
  display(0b0000100000000000);
  display(0b0001000000000000);
  display(0b0010000000000000);
  display(0b0100000000000000);*/

  display(0b1000000000000011);
  display(0b1100000000000001);
  display(0b1110000000000000);
  display(0b0111000000000000);
  display(0b0011100000000000);
  display(0b0001110000000000);
  display(0b0000111000000000);
  display(0b0000011100000000);
  display(0b0000001110000000);
  display(0b0000000111000000);
  display(0b0000000011100000);
  display(0b0000000001110000);
  display(0b0000000000111000);
  display(0b0000000000011100);
  display(0b0000000000001110);
  display(0b0000000000000111);
    
}

void display(unsigned int value){
  values[mine] = value;
  updateAll();
}

void updateAll(){
  for(int i = 0; i < 256; i++){
    setAddress(i);
    shiftOut(values[i]);
  }
}


void setAddress(byte addr){
  
  digitalWrite(p6,  addr & 0b00000001);
  digitalWrite(p7,  addr & 0b00000010);
  digitalWrite(p8,  addr & 0b00000100);
  digitalWrite(p9,  addr & 0b00001000);
  digitalWrite(p10, addr & 0b00010000);
  digitalWrite(p11, addr & 0b00100000);
  digitalWrite(p12, addr & 0b01000000);
  digitalWrite(p13, addr & 0b10000000);
  
}

void shiftOut(unsigned int data){
  for (byte j = 0; j < 16; j++){
    bit = (data >> j) & 0x01;
    digitalWrite(ser, bit); 
    digitalWrite(srclk, HIGH);
    digitalWrite(srclk, LOW);
  }

  digitalWrite(rclk, HIGH);
  digitalWrite(rclk, LOW);
}
