// DM13A 16-segment LED digit driver demo
// Author Susan Amber Bruce 27/4/2025.

#define DAI 4  // SIN
#define DCK 5 // SCLK
#define LAT 6 // Input terminal of data strobe (pin 4 on DM13A)
#define BLANK 7

unsigned int nuffer[8] = {0b000000001,
                           0b00000010,
                           0b00000100,
                           0b00001000,
                           0b00010000,
                           0b00100000,
                           0b01000000,
                           0b10000000,
}; // Example bit patterns for 16 segments

                  
unsigned int buffer[16] = {42345, 0, 2152, 0,
                  0, 15423, 0, 31666,
                  53261, 0, 12345, 0,
                  0, 42167, 0, 65535
}; // Example bit patterns for 16 segments

int smallDelay = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(DAI, OUTPUT);
  pinMode(DCK, OUTPUT);
  pinMode(LAT, OUTPUT);
  pinMode(BLANK, OUTPUT);

  digitalWrite(DAI, LOW);
  digitalWrite(DCK, LOW);
  digitalWrite(LAT, LOW);
  digitalWrite(BLANK, LOW);
}

void loop() 
{
  /*for (int i = 0; i < 8; i++) // Loop through all 16 segments
  {
    shiftOut(nuffer[i]); // Shift out the 16-bit value
    latch_output();      // Latch the data
    delay(100);
  }*/

  for (byte i = 0; i < 256; i++){
    shiftOut(i);
    latch_output();
    delay(100);
  }
  
}

void shiftOut(unsigned int data) // Function to shift out 16 bits
{
  for (unsigned int j = 0; j < 8; j++) // Loop through all 16 bits
  {
    unsigned int bit = (data >> j) & 0x01; // Extract the j-th bit
    digitalWrite(DAI, bit);       // Write the bit to DAI
    delay(smallDelay);
    digitalWrite(DCK, HIGH);      // Clock pulse
    delay(smallDelay);
    digitalWrite(DCK, LOW);
    delay(smallDelay);
  }
}

void latch_output() // Push latch pulse to LAT pin to latch the output data
{
  delay(smallDelay);
  digitalWrite(LAT, HIGH);
  delay(smallDelay);
  digitalWrite(LAT, LOW);
  delay(smallDelay);
}
