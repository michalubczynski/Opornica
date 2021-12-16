#define cellPin A1
float counts=0;
float miliVolts=0;
const float mvToCount=4.8828125;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

} 

void loop() {
  // put your main code here, to run repeatedly:
 counts = analogRead(cellPin);
 //Serial.println(String(cellPin));
 //  (5V/1024)=0.0048828125
if(counts<274){
 miliVolts=counts*mvToCount*0.001;
 Serial.print(String(miliVolts));
// Serial.println(" Volts");
 delay(1000);
}
 

}
