int ledPinBlue = 3; 		// LED que se encuentra en el pin 3
int ledPinGreen = 5; 		// LED que se encuentra en el pin 6
int ledPinRed = 6; 		// LED que se encuentra en el pin 7
int button=2;
void setup(){ 
   pinMode(ledPinBlue, OUTPUT);	// El p1n 3 será una salida digital 
   pinMode(ledPinGreen, OUTPUT);	// El p1n 5 será una salida digital 
   pinMode(ledPinRed, OUTPUT);	// El p1n 6 será una salida digital l 
   pinMode(button,INPUT);       //Se declara el boton de entrada  
} 
void loop(){ 
   if (digitalRead(button)== HIGH){
     digitalWrite(ledPinBlue, LOW);	// Apaga el LED
     digitalWrite(ledPinRed, HIGH);	// Enciende el LED
     delay(1000); 
     digitalWrite(ledPinRed, LOW);	// Apaga el LED
     digitalWrite(ledPinGreen, HIGH);	// Enciende el LED
     delay(1000);
     digitalWrite(ledPinGreen, LOW);	// Apaga el LED
     digitalWrite(ledPinBlue, HIGH);	// Enciende el LED
     delay(1000); 		        // Pausa de 1 segundo 
   } //if
   else {
     digitalWrite(ledPinBlue, LOW);	// Apaga el LED
   } //else
} 


//Se apaga y se prende un color de LED cada segundo despues de apretar el boton
