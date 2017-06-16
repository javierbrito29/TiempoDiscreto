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
    
    
    Cambiarcolor(selectColor);
    selectColor++;
    delay(1000);
   } 
   else {
    digitalWrite(ledPinBlue, LOW);	// Apaga el LED
    digitalWrite(ledPinRed,LOW);
    digitalWrite(ledPinGreen,LOW);
    selectColor=0; ////Solo se le agrego esta linea para que no guarde el valor anterior
   } 
   
   
   
   if(selectColor == 8){
   
     selectColor=0;
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

void Cambiarcolor(int colorNumber){
 
 switch(colorNumber){
 
 case 0: 
 digitalWrite(ledPinBlue,LOW);
 digitalWrite(ledPinRed,HIGH);
 digitalWrite(ledPinGreen,LOW);
 break;
 
 case 1: 
 digitalWrite(ledPinBlue,HIGH);
 digitalWrite(ledPinRed,LOW);
 digitalWrite(ledPinGreen,LOW);
 break;
 
 case 2: 
 digitalWrite(ledPinBlue,HIGH);
 digitalWrite(ledPinRed,HIGH);
 digitalWrite(ledPinGreen,LOW);
 break;
 
 case 3: 
 digitalWrite(ledPinBlue,LOW);
 digitalWrite(ledPinRed,LOW);
 digitalWrite(ledPinGreen,HIGH);
 break;
 
 case 4: 
 digitalWrite(ledPinBlue,LOW);
 digitalWrite(ledPinRed,HIGH);
 digitalWrite(ledPinGreen,HIGH);
 break;
 
 case 5: 
 digitalWrite(ledPinBlue,HIGH);
 digitalWrite(ledPinRed,LOW);
 digitalWrite(ledPinGreen,HIGH);
 break;
 
 case 6: 
 digitalWrite(ledPinBlue,HIGH);
 digitalWrite(ledPinRed,HIGH);
 digitalWrite(ledPinGreen,HIGH);
 break;
 
 case 7: 
 digitalWrite(ledPinBlue,LOW);
 digitalWrite(ledPinRed,LOW);
 digitalWrite(ledPinGreen,LOW);
 break;
 
 return; 
 }
 
}
