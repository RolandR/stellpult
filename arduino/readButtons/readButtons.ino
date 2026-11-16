

#define clk 2
#define shld 4
#define ser 6

const int readDelay = 1;

int values[8];

void setup() {
  
  Serial.begin(9600);
  
  pinMode(clk, OUTPUT);
  pinMode(shld, OUTPUT);
  pinMode(ser, INPUT);

  digitalWrite(clk, LOW);
  digitalWrite(shld, HIGH);

}

void loop() {
  digitalWrite(shld, LOW);
  digitalWrite(shld, HIGH);
  
  for(int i = 0; i < 8; i++){
    values[i] = digitalRead(ser);
    //delay(readDelay);
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);
  }


  for(int i = 0; i < 8; i++){
    if(values[i] == 0){
      Serial.print("O");
    } else {
      Serial.print("X");
    }
  }
  Serial.println();

  delay(100);

}
