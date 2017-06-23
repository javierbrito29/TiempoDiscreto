
/******

Controlador PID Digital 
Autores: Sophia Alvares Delgado
         Daniela Feoli Grant
         Javier Pacheco Brito
******/

/*******************************************************/
//Se realizan los include de las librerias 
/*******************************************************/
#include "Arduino.h"
#include <TaskScheduler.h> //Se carga la librería del Scheduler


/******************************************************/
//Declaracion de los pines Analgicos del Arduino 
/******************************************************/

const int iValorDeseadoPin = A0;      // *** SP *** Se de fine el pin del Valor Deseado 
const int iVarManiManualPin = A1;     // *** X  *** Se define el pin para el valor manual de la salida del controlador 
const int iVarControladaPin = A3;     // *** PV *** Se define el pin para la variable retroalimentada (Variable Controlada de la Planta)

/******************************************************/
//Declaracion de los pines Digitales del Arduino 
/******************************************************/

const int iModoPin = 2;              // *** M ***  Pin que determina en que modo se trabaja M=1 Manual M=0 Automatico
const int oVarManiPin = 3;           // *** CO *** Pin que tendra la salida del controlador modulacion PWM 
const int oLEDPin = 4;               // *** LED ** Pin de la salida del LED indicador del MODO


/******************************************************/
//Declaracion de las constantes y variables del programa 
/******************************************************/

/*****************/
// Constantes del PID Digital Kp,Ti,Td y Ts
/****************/
                   //Arrireg     //KayaServo    
float Kp =13.8191;//13.8191*;//10.6461;         //13.8191;       //10.6461; 
float Ti =1.9683; //1.9683*;//6.2255;         //1.5683;        //6.2255;
float Td =0.1;    //0.15;//0.1735;         //0;             //0.1735;
float Ts = 0.01;
float Tt =0;         //Ts*Ti/2;       //Ts/(sqrt(Td*Ti));
float beta = 1;
float alpha = 0.1;

/*****************/
// Declaracion de los valores constantes del controlador
/****************/

float Ki = (Kp*Ts)/(Ti);
float Kd = (Td)/((alpha*Td)+Ts);


/*****************/
// Parametros del Sistema
/****************/

float ValorDeseado=0;
float ValorDeseadoAnterior = 0;
float VariableControlada=0;
float VariableManipuladaManual=0;
float Modo=0;
float SalidaPID=0;
float Proporcional=0;
float VariableControladaAnterior=0;
float Derivativo = 0 ;
float DerivativoAnterior = 0;
float Integral = 0;
float IntegralAnterior = 0;
float SalidaControlPWM = 0;
float errosh= 0;
float VC;
float VD;
float SalActuador = 0;
float SalPWMDIG =0;


/******************/
// Objeto Scheduler definido de la libreria
/******************/
Scheduler RealTimeCore; 


/*****************/
//Se definen las funciones a utilizar
/****************/


void  LeerValores();
void  CalcularPID();
void  EscrituraSalidas();
void  ActualizarValor();
void  ControladorPID();

/******************************************************/
//Declaracion de la funcion ControladorPID
/******************************************************/
//Esta duncion se encarda de llamar al resto de funciones
void ControladorPID(){

  LeerValores();
  CalcularPID();
  EscrituraSalidas();
  ActualizarValor();  
}

/******************************************************/
//Declaracion de la tarea LazoCerrado 
/******************************************************/


Task LazoCerrado(10, TASK_FOREVER, &ControladorPID, &RealTimeCore); //Tarea que se repite cada 100 milisegundos indefinidamente




/******************************************************/
//   SETUP del Programa solo se ejecuta una vez
/******************************************************/


void setup() {
  
  /*******Declaracin de los Modos de los Pines Analogicos********/
  pinMode(iValorDeseadoPin,INPUT);  // Se como entrada el SP 
  pinMode(iVarManiManualPin, INPUT);// Se declara como entrada Valor manual del Controlador
  pinMode(iVarControladaPin,INPUT); // Se declara como entrada la salida de la planta PV
  /*******Declaracin de los Modos de los Pines Digitales********/
  pinMode(iModoPin, INPUT);	    // Se declara como entrada la seleccin de modo M
  pinMode(oVarManiPin, OUTPUT);	    // Se declara como salida el PWM de la salida del controlador
  pinMode(oLEDPin, OUTPUT);	    // Se declara como salida el Pin del LED 
  /*******Inicializacion de la comunicacion Serial***/
  Serial.begin(9600);               // se inicia la comunicación serial a 9600 bauds
  /*******Inicializacion de el objeto Scheduler***/
  RealTimeCore.init();              // Inicializa el scheduler
  RealTimeCore.addTask(LazoCerrado);// Se agrega LazoCerrado al scheduler
  LazoCerrado.enable();             // Se habilita la tarea de LazoCerrado
}


/******************************************************/
//        Declaracion del LOOP del Programa
/******************************************************/


void loop() {
  RealTimeCore.execute(); 
}



/******************************************************/
//Funcion encargada de leer los valores de los pines de entrada
/******************************************************/
void LeerValores() {
  //Lectura del Valor deseado
  ValorDeseado= analogRead(iValorDeseadoPin);
  //Serial.println(ValorDeseado);
  //Lectura de la Variable Controlada
  VariableControlada = analogRead(iVarControladaPin);
  //Serial.println(VariableControlada);
  //Lectura del controlador Manual
  VariableManipuladaManual = analogRead(iVarManiManualPin);
  //Serial.println(ValorDeseado);
  //Serial.print(",");
  //Lectura del Modo de operacio
  Modo = digitalRead(iModoPin);
  VC = VariableControlada * (5.0/1023.0);
  VD = ValorDeseado * (5.0/1023.0);
  Serial.println(VD); Serial.print("\t");
  Serial.print(VC); Serial.print("\t");
  //Serial.println(ValorDeseado); Serial.print("\t");
  //Serial.print(VariableControlada); Serial.print("\t");
}

/******************************************************/
//Funcion encargada de calcular la salida del PID
/******************************************************/
void CalcularPID() {
  //Implementacion de los calculos de un PID Digital 
  if(Modo){
    SalidaPID = VariableManipuladaManual;
    Integral = 0;
    errosh=0;
  }
  else {
    errosh= errosh+abs(VD - VC)*Ts;
    Serial.print(errosh); Serial.print("\t");
    Proporcional = Kp*((beta*ValorDeseado)-VariableControlada);
    Integral = IntegralAnterior + (Ki*(ValorDeseadoAnterior-VariableControladaAnterior)); 
    Derivativo = (alpha*Kd*DerivativoAnterior) - (Kp*Kd*(VariableControlada-VariableControladaAnterior));
    SalidaPID = Proporcional + Integral + Derivativo;    
    //Serial.println(Proporcional); Serial.print("\t");
    //Serial.print(Integral); Serial.print("\t");
    //Serial.print(Derivativo); Serial.print("\t");
    
    
  }
  
  //Implementacion de la logica Widup
  if(SalidaPID > 1023){
    SalidaPID = 1023;
    Integral = IntegralAnterior;
  }
  else if (SalidaPID < 0){
    SalidaPID = 0;
    Integral = IntegralAnterior;
  }
}

/******************************************************/
//Funcion encargada de escribir en los Pines de Salidas 
/******************************************************/

void EscrituraSalidas() {
  //Las salidas de los pines PWM de arduinos de de 8 bits por 
  // lo tanto se debe dividir entre 4 para eliminar 2 bits

  //Serial.print(SalidaPID); Serial.print("\t");
  SalidaControlPWM = (SalidaPID*255.0/1023.0);
  analogWrite(oVarManiPin,SalidaControlPWM);
  //SalPWMDIG = SalidaControlPWM*(5.0/255.0);
  //Serial.print(SalPWMDIG); Serial.print("\t");
  
  //Se revisa si es necesario encender o apagar el LED
  // Modo = 1 Led apagado ...... Modo = 0 Led Encendido 
  if(Modo) {
  digitalWrite(oLEDPin, LOW);
  } 
  else {
  digitalWrite(oLEDPin, HIGH);
  }
}

/******************************************************/
//Funcion encargada de actualizar Variables  
/******************************************************/

void ActualizarValor() {
  ValorDeseadoAnterior = ValorDeseado;
  VariableControladaAnterior = VariableControlada;
  IntegralAnterior = Integral;
  DerivativoAnterior = Derivativo; 
}





