/*
 * Este programa sirve de plantilla para utilizar la librería
 * TaskScheduler en el curso IE0731: Sistemas en Tiempo discreto
 * 
 * Se recomienda revisar la documentación que está
 * en el sitio virtual del curso, junto con la librería.
 * El sitio donde el autor de la librería aloja el código es el siguiente:
 * https://github.com/arkhipenko/TaskScheduler
 */
#include "Arduino.h"
#include <TaskScheduler.h> //Se carga la librería del Scheduler
Scheduler RealTimeCore; //Esto crea un objeto del tipo Scheduler (definido por la librería). En este caso, el objeto se llama RealTimeCore, pero se puede poner cualquier nombre

//Defino los puertos 
int ledPin1 = 3; 		// LED que se encuentra en el pin 3
int ledPin2 = 5; 		// LED que se encuentra en el pin 5
int ledPin3 = 6; 		// LED que se encuentra en el pin 6
int ledPin4 = 9; 		// LED que se encuentra en el pin 9

// Se deben definir los prototipos de las funciones de cada una de las tareas, en este caso se definen tres funciones. En inglés es lo que se llaman Callbacks. Se puede poner el nombre que quiera.
void tareaBlink2Fun();
void tareaBlink3Fun();
void tareaBlink5Fun();

// Acá se crean las tareas. Las tareas son objetos del tipo Task definidos por la librería:
Task tareaBlink2(2000, TASK_FOREVER, &tareaBlink2Fun, &RealTimeCore); //Tarea que se repite cada 1000 milisegundos indefinidamente
Task tareaBlink3(3000, TASK_FOREVER, &tareaBlink3Fun, &RealTimeCore); //Tarea que se repite cada 3000 milisegundos indefinidamente
Task tareaBlink5(5000, TASK_FOREVER, &tareaBlink5Fun, &RealTimeCore); //Tarea que se repite sólo tres veces cada 5000 milisegundos

// Ahora se deben definir explícitamente las funciones
void tareaBlink2Fun(){
  Serial.print("Enciende LED cada 2 segundos "); //Escribe un string en el puerto serial
  digitalWrite(ledPin1,HIGH);
  delay(50);
  digitalWrite(ledPin1,LOW);
  Serial.println(millis());
}

void tareaBlink3Fun(){
  Serial.print("Enciende LED cada 3 segundos "); //Escribe un string en el puerto serial
  digitalWrite(ledPin2,HIGH);
  delay(50);
  digitalWrite(ledPin2,LOW);
  Serial.println(millis());
}

void tareaBlink5Fun(){
  Serial.print("Enciende LED cada 5 segundos "); //Escribe un string en el puerto serial
  digitalWrite(ledPin3,HIGH);
  delay(50);
  digitalWrite(ledPin3,LOW);
  Serial.println(millis());
}

void setup() {
  
  pinMode(ledPin1, OUTPUT);	// El p1n 3 será una salida digital 
  pinMode(ledPin2, OUTPUT);	// El p1n 5 será una salida digital 
  pinMode(ledPin3, OUTPUT);	// El p1n 6 será una salida digital
  pinMode(ledPin4, OUTPUT);	// El p1n 9 será una salida digital
  attachInterrupt( 0, InteLED, RISING);
  // El código que se ponga acá se ejecuta una única vez al inicio:
  Serial.begin(9600); //se inicia la comunicación serial a 9600 bauds
  RealTimeCore.init(); //Inicializa el scheduler
  Serial.println("Se inicializo el Scheduler");
  RealTimeCore.addTask(tareaBlink2); //Se agrega la tarea 01 al scheduler
  RealTimeCore.addTask(tareaBlink3); //Se agrega la tarea 02 al scheduler
  RealTimeCore.addTask(tareaBlink5); //Se agrega la tarea 03 al scheduler
  Serial.println("Se agregaron las tareas al Scheduler");
  tareaBlink2.enable(); // Se pone el flag de enable para la tarea 01. Por default, las tareas están desabilitadas
  tareaBlink3.enable(); // Se pone el flag de enable para la tarea 02. Por default, las tareas están desabilitadas
  tareaBlink5.enable(); // Se pone el flag de enable para la tarea 03. Por default, las tareas están desabilitadas
}

void loop() {
  // Acá va el código que se repite indefinidamente:
  RealTimeCore.execute(); // Cuando se usa un scheduler, esta instrucción es la única que debería estar en el loop
}

void InteLED()

{
  Serial.println("Enciende LED Interrupcion"); //Escribe un string en el puerto serial
  digitalWrite(ledPin4,HIGH);
  delay(1000);
  digitalWrite(ledPin4,LOW);
  //Serial.println(millis()); 
  return;  
}
