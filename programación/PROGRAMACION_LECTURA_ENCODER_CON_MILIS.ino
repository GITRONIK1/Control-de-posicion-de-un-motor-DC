#define PWM 6                                          //declaramos pines
#define AIN2 4                                         //declaramos pines
#define AIN1 5                                         //declaramos pines
#define encoder0PinA 2                                 //declaramos pines                       
#define encoder0PinB 3                                 //declaramos pines

volatile long encoder0Pos=0;                           //cambiara  a int al final encoder
long milisprevio1=0;                                   //como estaba antes milis                                    
long intervalo1=100;                                   //DURACION intervalo milis

void setup() {
pinMode(AIN2,OUTPUT);                                   //declaramos salida puente h motor sentido 
pinMode(AIN1,OUTPUT);                                   //declaramos salida puente h motor sentido
pinMode (encoder0PinA, INPUT);                          //declaramos encoder
pinMode (encoder0PinB, INPUT);                         //declaramos encoder        
attachInterrupt(0,doEncoderA, CHANGE);                 //subrutinas para la lectura del encoder    
attachInterrupt(1,doEncoderB, CHANGE);                 //subrutinas para la lectura del encoder

Serial.begin(9600);                                     //declaramos lectura monitor serie
}
 
void loop() {
  
  long milisactual1=millis();                          //asignamos nombre al millis
   if(milisactual1-milisprevio1>=intervalo1){           //decimos si ha pasado el tiempo de milis
    Serial.println (encoder0Pos, DEC);                 //en el momitor serie que nos enseñe el valor de pulsos de encoder
    milisprevio1=milisactual1;                         // actualizamos y Recordamos el tiempo de milis  //le ponemos para que salga del giro inverso (positivos)
    }    
  }

 void doEncoderA(){                                     //subrutina el cual dice que dependiendo de configuracion del encoder aumenta o disminuye los pulsos mediante motor sentido
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
 
  void doEncoderB(){                                  //subrutina el cual dice que dependiendo de configuracion del encoder aumenta o disminuye los pulsos mediante motor sentido
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
