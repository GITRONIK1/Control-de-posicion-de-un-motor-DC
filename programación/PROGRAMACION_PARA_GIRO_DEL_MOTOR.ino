#define PWM 3                                           //declaramos pines
#define AIN2 4                                          //declaramos pines
#define AIN1 5                                          //declaramos pines

int vel = 255;                                         //de aqui manipulamos la velocidad del giro

void setup() {
pinMode(AIN2,OUTPUT);                                   //declaramos salida
pinMode(AIN1,OUTPUT);                                   //declaramos salida
Serial.begin(9600);                                     //declaramos lectura monitor serie
}
 
void loop() {
    
    if(vel >=0){                                        //El motor girará a la derecha
    digitalWrite(AIN1, LOW);                            //activar para un lado
    digitalWrite(AIN2, HIGH);                           //desactivar para el otro
    analogWrite(PWM, vel);                              //le asignamos la velocidad
    }
    
    if(vel <=0){                                        //El motor girará a la izquierda
    digitalWrite(AIN1, HIGH);                           //activar para un lado
    digitalWrite(AIN2, LOW);                            //desactivar para el otro
    vel = -vel;                                         //le ponemos para que el giro sea inverso (negativos)
    analogWrite(PWM, vel);                              //asignamos velocidad 
    vel = -vel;                                         //le ponemos para que salga del giro inverso (positivos)
    }    
  }

