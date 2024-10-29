#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711.h>
#include <EEPROM.h>
#include <stdint.h>
#include "declaraciones.h"

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 
HX711 balanza;
void setup() { //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.begin(9600);
  configurarGpio();
  balanza.begin(SENSOR_PESO_DOUT, SENSOR_PESO_SCK);
  lcd.init();// initialize the lcd 
  lcd.noBacklight ();


                   
  tic0=LOW;
  tic1=LOW;
  tic2=LOW;
  error1=LOW;
  error2=LOW;
  ledsApagados=LOW;
  estadoBombaAgua=LOW;
  bloqueAgua = 0;
  cicloAgua = 0;
  tiempoFuncionamientoBombaAgua = 0;
  tiempoClorado = 0;
  volumenAClorar = 0;
  volumenNoClorado = EEPROM.read (0);
  errorClorado = LOW;
  errorNivelCloro = LOW;
  testLeds();
  lcd.backlight();
  lcd.setCursor ( 3,1);
  lcd.print ("control llenado");
  lcd.setCursor ( 3,2);
  lcd.print ("V 1.0");
  pesoInicialCloro = leepeso();
  if(pesoInicialCloro < MINIMO_PESO_CLORO){
    errorNivelCloro = HIGH;
  }
  delay(2000);
  lcd.clear();
  
  attachInterrupt(digitalPinToInterrupt(SENSOR_FLUJO), incrementoBloqueAgua, RISING); //inicia interrupcion pin 2 caudalimetro
}

//LOOP//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  static boolean anteriorTic0;
  static boolean anteriorTic1;
  static boolean anteriorTic2;

  generacionTics(); // modifica tic0, tic1 y tic2
  
  
  


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(tic0 != anteriorTic0){
    anteriorTic0 = tic0;
    //PROCESOS QUE ACTUALIZAN CADA TIC0
    controlPulsadorMulti();
    actualizaLeds(ledsApagados);
    
  } 
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(tic1 != anteriorTic1){
    anteriorTic1 = tic1;
    //PROCESOS QUE ACTUALIZAN CADA TIC1
    controlNivel();// actualiza nivel Agua;
    controlBombaAgua(); //activa o desactiva rele bomba, modifica estadoBombaAgua, activa error 2
    controlCicloClorado ();
    
    }


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(tic2 != anteriorTic2){
    anteriorTic2 = tic2;
    //PROCESOS QUE ACTUALIZAN CADA TIC2
    controlCicloAgua();
     // cada 5 sg. resetea bloqueAgua, modifica bloqueAguaCopia usada como indicador de flujo, activa error 1, modifica ciclos clorado, modifica ciclo agua
    calculos();
    consola();
    actualiza_lcd();
    }


}

















