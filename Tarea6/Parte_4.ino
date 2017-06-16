int ledPinAr = 13; 		// LED que se encuentra en el pin 13
int ledPinBlue = 3; 		// LED que se encuentra en el pin 3
int ledPinGreen = 5; 		// LED que se encuentra en el pin 6
int ledPinRed = 6; 		// LED que se encuentra en el pin 7
void setup(){ 
   pinMode(ledPinAr, OUTPUT);	// El p1n 13 será una salida digital 
   pinMode(ledPinBlue, OUTPUT);	// El p1n 3 será una salida digital 
   pinMode(ledPinGreen, OUTPUT);	// El p1n 5 será una salida digital 
   pinMode(ledPinRed, OUTPUT);	// El p1n 6 será una salida digital 
} 
void loop(){ 
   digitalWrite(ledPinAr, HIGH);	// Enciende el LED
   digitalWrite(ledPinBlue, HIGH);	// Enciende el LED
   digitalWrite(ledPinGreen, HIGH);	// Enciende el LED
   digitalWrite(ledPinRed, HIGH);	// Enciende el LED
   delay(1000); 				// Pausa de 1 segundo 
   digitalWrite(ledPinAr, LOW);	// Apaga el LED 
   digitalWrite(ledPinBlue, LOW);	// Apaga el LED 
   digitalWrite(ledPinGreen, LOW);	// Apaga el LED 
   digitalWrite(ledPinRed, LOW);	// Apaga el LED 
   delay(1000);				// Pausa de 1 segundo 
} 

//La parte uno solo era cambiar el tiempo del delay con esto se consigue que el LED dure mas tiempo encendido o apagado, posteriormente lo unico que se hizo fue cambiar 
//el puerto de salida con esto ya se logra que encienda uno de los leds. 
