int ledPinBlue = 3; 		// LED que se encuentra en el pin 3
int ledPinGreen = 5; 		// LED que se encuentra en el pin 6
int ledPinRed = 6; 		// LED que se encuentra en el pin 7
int button = 2;
int selectColor = 0;
//Se declaran los pines de las entradas analogicas
void setup(){ 
  pinMode(ledPinBlue, OUTPUT);	// El p1n 3 será una salida digital 
  pinMode(ledPinGreen, OUTPUT);	// El p1n 5 será una salida digital 
  pinMode(ledPinRed, OUTPUT);	// El p1n 6 será una salida digital
  pinMode(button, INPUT);	// El p1n 6 será una salida digital
  
} 
void loop(){ 
  
  if (digitalRead(button)== HIGH){
    
    
    Cambiarcolor();
   } 
   else {
    digitalWrite(ledPinBlue, LOW);	// Apaga el LED
    digitalWrite(ledPinRed,LOW);
    digitalWrite(ledPinGreen,LOW);
   } 
   
} 

//Tabla de verdad de los colores 
//Green   Blue   Red
//  0      0      1
//  0      1      0
//  0      1      1
//  1      0      0 
//  1      0      1
//  1      1      0
//  1      1      1
//  0      0      0 

void Cambiarcolor(){
 
 digitalWrite(ledPinBlue,LOW);
 digitalWrite(ledPinRed,HIGH);
 digitalWrite(ledPinGreen,LOW);
 delay(1000); 
 digitalWrite(ledPinBlue,HIGH);
 digitalWrite(ledPinRed,LOW);
 digitalWrite(ledPinGreen,LOW);
 delay(1000);
 digitalWrite(ledPinBlue,HIGH);
 digitalWrite(ledPinRed,HIGH);
 digitalWrite(ledPinGreen,LOW);
 delay(1000); 
 digitalWrite(ledPinBlue,LOW);
 digitalWrite(ledPinRed,LOW);
 digitalWrite(ledPinGreen,HIGH);
 delay(1000);
 digitalWrite(ledPinBlue,LOW);
 digitalWrite(ledPinRed,HIGH);
 digitalWrite(ledPinGreen,HIGH);
 delay(1000);
 digitalWrite(ledPinBlue,HIGH);
 digitalWrite(ledPinRed,LOW);
 digitalWrite(ledPinGreen,HIGH);
 delay(1000);
 digitalWrite(ledPinBlue,HIGH);
 digitalWrite(ledPinRed,HIGH);
 digitalWrite(ledPinGreen,HIGH);
 delay(1000);
 digitalWrite(ledPinBlue,LOW);
 digitalWrite(ledPinRed,LOW);
 digitalWrite(ledPinGreen,LOW);
 delay(1000); 
 }

