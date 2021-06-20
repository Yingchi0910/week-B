#define C3 131
#define D3 147
#define E3 165
#define F3 175
#define G3 196
#define A3 220
#define B3 247
#define C4 262

int thisNote=-1,noteDuration=0;
long previousTime=0,  
     presentTime=0,
     pauseBetweenNotes=0;


int latchPin=8;
int clockPin=12;
int dataPin=11;

int buttonState = 0;
int presentState=0;
int note[] = {C3,D3,E3,F3,G3,A3,B3,C4};


    
byte colDataMatrix[8]={
  B11111110,
  B11111101,
  B11111011,
  B11110111,
  B11101111,
  B11011111,
  B10111111,
  B01111111};
byte a[8]={
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000};
  

void checkToPlay()
{
  presentTime = millis();
  if(presentTime - previousTime >= pauseBetweenNotes)
  {
    thisNote += 1;
    if(thisNote >= 48)
    {
      thisNote = -1;
      pauseBetweenNotes = 100;
      previousTime = millis();
    }
    else
    {
      noteDuration = 500 / noteDurations[thisNote];
      tone(9,melody[thisNote],noteDuration);
      pauseBetweenNotes = noteDuration * 1.2;
      previousTime = millis();
    }
  }
}
int but[] = {2,3,4,5,6,7,10,13};
int i;
int butstate = 1;
int note[] = {C3,D3,E3,F3,G3,A3,B3,C4};
void setup()
{
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  for(i=0;i<8;i++){
      pinMode(but[i],INPUT_PULLUP);


};

void loop()
{  
  for(int i = 0;i<8;i++)
  {
    butState = digitalRead(but[i]);
    if (butState == LOW)
        {
      	  count++;
      	  if(count>=8)count = 0;
      	  
          tone(9,note[i],150);
        }
  }
  delay(50);
  
}
  
void loop()
{
   presentState = digitalRead(2);
   for(int i = 0; i < 8 ; i++)
  {    
     digitalWrite(latchPin,LOW);
     shiftOut(dataPin,clockPin,MSBFIRST,colDataMatrix[i]);
     if(presentState == 0)
     {
       pattern ++;
       if(pattern > 2)pattern = 0;
     }
     if(pattern == 0)
     {
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,colDataMatrix[i]);
      shiftOut(dataPin,clockPin,MSBFIRST,a[i]);
      digitalWrite(latchPin,HIGH);
      checkToPlay();
      delay(1);
     }
     else if(pattern == 1)
     {
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,colDataMatrix[i]);
      shiftOut(dataPin,clockPin,MSBFIRST,b[i]);
      digitalWrite(latchPin,HIGH);
      checkToPlay();
      delay(1);
     }
  }
}