int ledPinBlue = 3; 		// LED que se encuentra en el pin 3
int ledPinGreen = 5; 		// LED que se encuentra en el pin 5
int ledPinRed = 6; 		// LED que se encuentra en el pin 6
void setup(){ 
   pinMode(ledPinBlue, OUTPUT);	// El p1n 3 será una salida digital 
   pinMode(ledPinGreen, OUTPUT);	// El p1n 5 será una salida digital 
   pinMode(ledPinRed, OUTPUT);	// El p1n 6 será una salida digital  
} 
void loop(){ 
   digitalWrite(ledPinBlue, LOW);	// Enciende el LED
   digitalWrite(ledPinRed, HIGH);	// Enciende el LED
   delay(1000); 
   digitalWrite(ledPinRed, LOW);	// Apaga el 
   digitalWrite(ledPinGreen, HIGH);	// Enciende el LED
   delay(1000);
   digitalWrite(ledPinGreen, LOW);	// Enciende el LED
   digitalWrite(ledPinBlue, HIGH);	// Enciende el LED
   delay(1000); 				// Pausa de 1 segundo 
} 

//Se apaga y se prende un color de LED cada segundo 
