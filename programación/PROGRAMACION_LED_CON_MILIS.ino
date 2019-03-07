int led1=2;                      //asignamos nombre al led
int estadoled1=LOW;              //nos dice como esta led al empezar
long milisprevio1=0;             //como estaba led
long intervalo1=1000;            //tiempo duracion led

void setup() {
  pinMode(led1,OUTPUT);          //decimos salida led
}

void loop() {
  long milisactual1=millis();                //asignamos nombre al millis
  if(milisactual1-milisprevio1>=intervalo1){     //decimos si ha pasado el tiempo de duracion del led 
    if(estadoled1==LOW){                       //si led estaba apagado 
      estadoled1=HIGH;                         //lo encendemos
    }
    else{                                       //si estaba encendido
      estadoled1=LOW;                            //lo apagamos
    }
    milisprevio1=milisactual1;                  // actualizamos y Recordamos el tiempo 
    digitalWrite(led1,estadoled1);                
  }
}
