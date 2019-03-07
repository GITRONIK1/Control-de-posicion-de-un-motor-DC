# define encoder0PinA 2
# define encoder0PinB 3

volatile long encoder0Pos=0; //cambiara  a int al final

void setup() {
// pinMode (encoder0PinA, INPUT);
// pinMode (encoder0PinB, INPUT);
 attachInterrupt(0,doEncoderA, CHANGE);
 attachInterrupt(1,doEncoderB, CHANGE);
 Serial.begin (9600);
 
}

void loop() {
 Serial.println (encoder0Pos, DEC);
 //delay(2000);
 
}

 void doEncoderA(){
    if (digitalRead(encoder0PinA)== LOW){
          if (digitalRead(encoder0PinB)== LOW){
                 encoder0Pos +=1;
          }       
          else {
                 encoder0Pos -=1; 
          }    
     }
     else {
          if (digitalRead(encoder0PinB)== HIGH){
                 encoder0Pos +=1;  
          }
          else {
                  encoder0Pos -=1; 
          }
     }
 }
 

  void doEncoderB(){
    if (digitalRead(encoder0PinA)== LOW){
          if (digitalRead(encoder0PinB)== LOW){
                 encoder0Pos -=1;
          }       
          else {
                 encoder0Pos +=1; 
          }    
     }
     else {
          if (digitalRead(encoder0PinB)== HIGH){
                 encoder0Pos -=1;  
          }
          else {
                  encoder0Pos +=1; 
          }
     }
 }



  
