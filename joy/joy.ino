int xAxisPin = A1;
int yAxisPin = A0;

int first4Btns = 2;
int second4Btns = 3;
int drainBtns = 4;

int btn1 = 8;
int btn2 = 9;
int btn3 = 10;
int btn4 = 11;

#define PROTOCOL_VERSION 'b'

#define RAxis (100000)
#define axisMax (100000.0)

void setup() 
{ 
  digitalWrite(13, LOW);
  
  // ARROWS
  pinMode(xAxisPin, INPUT);
  pinMode(yAxisPin, INPUT);
  
  // BUTTONS
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
 
  pinMode(drainBtns, OUTPUT);
  digitalWrite(drainBtns, HIGH);
  
  // END
  
  pinMode(13, OUTPUT);
  
  Serial.begin(9600); // Подготовка Serial Monitor для вывода информации
  Serial.write(PROTOCOL_VERSION);
} 

int getPosition(int value) {
  return (RAxis / (1023. / value - 1)) / axisMax * 256 - 128;
}

// BUTTONS READ

void setBtnModeRead() {
  pinMode(first4Btns, OUTPUT);
  digitalWrite(first4Btns, LOW);
  pinMode(second4Btns, INPUT);
}

void setArrowsModeRead() {
  pinMode(first4Btns, INPUT);
  
  pinMode(second4Btns, OUTPUT);
  digitalWrite(second4Btns, LOW);
}

uint8_t getBtnMask() {
  uint8_t btnMask = 0;
  setBtnModeRead();
  btnMask = (digitalRead(btn1) << 7)
 + (digitalRead(btn2) << 6)
 + (digitalRead(btn3) << 5)
 + (digitalRead(btn4) << 4);
  
  setArrowsModeRead();
  btnMask += (digitalRead(btn1) << 3)
 + (digitalRead(btn2) << 2)
 + (digitalRead(btn3) << 1)
 + (digitalRead(btn4) << 0);
 
 
  
  return ~btnMask;
}

void sendInt(uint16_t val) {
uint16_t mask   = B11111111;          // 0000 0000 1111 1111
uint8_t first_half   = val >> 8;   // >>>> >>>> 0001 0110
uint8_t sencond_half = val & mask; // ____ ____ 0100 0111

Serial.write(first_half);
Serial.write(sencond_half);
}

#define _DEBUG 

void loop() 
{
#ifndef DEBUG
  digitalWrite(13, LOW);
  int incomingByte = -1;
  while (incomingByte == -1) {
    incomingByte = Serial.read();
  }
  digitalWrite(13, HIGH);
  
  if (incomingByte) {
    int xAxisV = analogRead(xAxisPin);
    int yAxisV = analogRead(yAxisPin);
    
    signed char xAxisPos = getPosition(xAxisV);
    signed char yAxisPos = - getPosition(yAxisV);
    
    sendInt(xAxisV);
    sendInt(yAxisV);    
    Serial.write(xAxisPos);
    Serial.write(yAxisPos);
    
    Serial.write((int) getBtnMask());
    
    Serial.flush();
  }
  
#else

Serial.println(getBtnMask());

#endif


}
