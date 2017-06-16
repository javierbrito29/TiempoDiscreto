int ledPinBlue = 3; 		// LED que se encuentra en el pin 3
int ledPinGreen = 5; 		// LED que se encuentra en el pin 6
int ledPinRed = 6; 		// LED que se encuentra en el pin 7
//Se declaran los pines de las entradas analogicas
int potPIN0= A0;
int potPIN1= A1;
int potPIN2= A2;
//Se lee el valor del potenciometro
float valorPOTA0;
float valorPOTA1;
float valorPOTA2;
//Se calcula la razon de color de 0 -255
float razonColorPot0;
float razonColorPot1;
float razonColorPot2;
void setup(){ 
  Serial.begin(9600);
   } 
void loop(){ 
   
   valorPOTA0=analogRead(potPIN0);
   razonColorPot0=map(valorPOTA0, 0, 1023, 0, 255);
   Serial.print("Valor Pot1 ");
   Serial.println(razonColorPot0);
   valorPOTA1=analogRead(potPIN1);
   razonColorPot1=map(valorPOTA1, 0, 1023, 0, 255);
   Serial.print("Valor Pot2: ");
   Serial.println(razonColorPot1);
   valorPOTA2=analogRead(potPIN2);
   razonColorPot2=map(valorPOTA2, 0, 1023, 0, 255);
   Serial.print("Valor Pot3: ");
   Serial.println(razonColorPot2);
   analogWrite(ledPinBlue, razonColorPot0);	// Enciende el LED
   analogWrite(ledPinGreen, razonColorPot1);	// Enciende el LED
   analogWrite(ledPinRed, razonColorPot2);	// Enciende el LED
			
} 

//Este programa cambia la intensidad de los leds 
