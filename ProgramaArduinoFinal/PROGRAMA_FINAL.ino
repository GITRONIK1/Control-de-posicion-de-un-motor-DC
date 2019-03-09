
#define PWM 6                                          //declaramos pines
#define AIN2 4                                         //declaramos pines
#define AIN1 5                                         //declaramos pines
#define encoder0PinA 2                                 //declaramos pines                       
#define encoder0PinB 3                                 //declaramos pines

float pot1=A3;
float pot2=A4;
float pot3=A5;
float kp=0.0;
float ki=0.0;
float kd=0.0;
float setpoint=0.0;
float error = 0.0;
float errorInt = 0.0;
float errorDer = 0.0;
float lasterror = 0.0;

volatile long encoder0Pos=0;                           //cambiara  a int al final encoder (contador encoder)

long milisprevio1=0;                                   //como estaba antes milis encoder  contador                                 
long intervalo1=1;                                   //DURACION INTERVALO MILIS ENCODER CONTADOR       ////
long intervalo2=2000;                                  //DURACION INTERVALO MILIS DE ERROR ////
long milisprevio2=0;                                   //como estaba antes milis error                                   

float vel = 0.0;                                         //MANIPULAR SENTIDO DEL GIRO MOTOR ////

void setup() {

pinMode(AIN2,OUTPUT);                                  //declaramos salida puente h motor sentido 
pinMode(AIN1,OUTPUT);                                  //declaramos salida puente h motor sentido
pinMode (encoder0PinA, INPUT);                         //declaramos encoder
pinMode (encoder0PinB, INPUT);                         //declaramos encoder        
attachInterrupt(0,doEncoderA, CHANGE);                 //subrutinas para la lectura del encoder    
attachInterrupt(1,doEncoderB, CHANGE);                 //subrutinas para la lectura del encoder

Serial.begin(9600);                                    //declaramos lectura monitor serie
}
 
void loop() {

kp=analogRead(pot1);
kp= kp * 50 /1023;
ki=analogRead(pot2);
ki= ki * 0.05 /1023;
kd=analogRead(pot3);
kd= kd * 1000 /1023;

CONTROLPID ();
VISUALIZARDATOS ();
MOTORES ();
}


void CONTROLPID(){
  long milisactual1=millis();                          //asignamos nombre al millis
   if(milisactual1-milisprevio1>=intervalo1){          //decimos si ha pasado el tiempo de milis
                       // actualizamos y Recordamos el tiempo de milis                                    //le ponemos para que salga del giro inverso (positivos)
      error=setpoint+encoder0Pos;                           //calculamos el error
      errorInt += error;                                          // respuesta proporcional al error
      errorDer=(error-lasterror);                                          // respuesta proporcional al error
      vel= (kp * error) + (ki * errorInt) + (kd * errorDer);                                          // respuesta proporcional al error
      lasterror = error;
      if (vel >= 255.0) vel =255.0;                             //dice que cuando lega alos 255 de velocidad el conteo del encoder error no empieze de cero
      if (vel <= -255.0) vel =-255.0;                          //dice que cuando lega alos -255 de velocidad el conteo del encoder error no empieze de cero
                                                            //el 1 es la tolerancia del error
      milisprevio1=milisactual1;  
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

void VISUALIZARDATOS(){
    long milisactual2=millis();                          //asignamos nombre al millis
   if(milisactual2-milisprevio2>=intervalo2){          //decimos si ha pasado el tiempo de milis
    Serial.println("error");                           //en monitor serie nos enseña "error"
    Serial.println(error,DEC);                          //en monitor serie nos muestra el valor error en decimales
    Serial.println("vel");                         
    Serial.println(vel,DEC);

    Serial.println("kp");                         
    Serial.println(kp);

     Serial.println("ki");                         
    Serial.println(ki);

     Serial.println("kd");                         
    Serial.println(kd);

    
    Serial.println (encoder0Pos, DEC);                 //en el momitor serie que nos enseñe el valor de pulsos de encoder
    
    milisprevio2=milisactual2;                         // actualizamos y Recordamos el tiempo de milis                                  
    }
}

 void MOTORES(){        

  if(vel >=0){                                         //El motor girará a la derecha
    digitalWrite(AIN1, LOW);                           //activar para un lado
    digitalWrite(AIN2, HIGH);                          //desactivar para el otro
    analogWrite(PWM, vel);                             //le asignamos la velocidad
    }
    
  if(vel <=0){                                         //El motor girará a la izquierda
    digitalWrite(AIN1, HIGH);                          //activar para un lado
    digitalWrite(AIN2, LOW);                           //desactivar para el otro
    vel = -vel;                                        //le ponemos para que el giro sea inverso (negativos)
    analogWrite(PWM, vel);                             //asignamos velocidad 
    vel = -vel;                                        //le ponemos para que salga del giro inverso (positivos)
    }
 }
