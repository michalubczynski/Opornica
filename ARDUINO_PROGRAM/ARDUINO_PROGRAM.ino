#define cellPin A1
float counts=0;
float miliVolts=0;
const float mvToCount=4.8828125;   //  (5V/1024)=0.0048828125
const int StepX =2;
const int DirX=5;
int stepsPerRevolution=2048;
int motSpeed=10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
pinMode(StepX,OUTPUT);
pinMode(DirX,OUTPUT);
} 

void loop() {

  if(Serial.available()){
    char skret=Serial.read();
    obrot(skret);
    }
 
 }
void obrot(char m_skret){
  if(m_skret == 'p'){
      digitalWrite(DirX,HIGH); // Enables the motor to move in a particular direction
      for(int x = 0; x < 200; x++) {
      digitalWrite(StepX,HIGH); 
      delayMicroseconds(500); 
      digitalWrite(StepX,LOW); 
      delayMicroseconds(500); 
      }
    }
    else if(m_skret == 'l'){
              digitalWrite(DirX,LOW); //Changes the rotations direction
        for(int x = 0; x < 200; x++) {
        digitalWrite(StepX,HIGH);
        delayMicroseconds(500);
        digitalWrite(StepX,LOW);
        delayMicroseconds(500);
        }
      }
  }
 
