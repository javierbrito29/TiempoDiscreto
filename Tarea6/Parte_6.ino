int ledPinRed = 6; 		// LED que se encuentra en el pin 6
int button=2;
void setup(){ 
   pinMode(ledPinRed, OUTPUT);	// El p1n 6 será una salida digital 
   pinMode(button,INPUT);       //Se declara el boton de entrada  
} 
void loop(){ 
   if (digitalRead(button)== HIGH){
   digitalWrite(ledPinRed, HIGH);	// Enciende el LED
   }
   else {
   digitalWrite(ledPinRed, LOW);	// Apaga el LED
   }
} 

//Se apaga y se prende un color de LED cada segundo 
