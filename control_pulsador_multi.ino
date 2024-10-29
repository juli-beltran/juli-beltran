void controlPulsadorMulti(){
  static uint8_t controlBoton=0;
  static bool finReset=LOW;

  if((!digitalRead(BOTON_MULTI))&& (!finReset)){
    ledsApagados=HIGH;
    if (controlBoton==5){
      error1=LOW;
      error2=LOW;
      tiempoFuncionamientoBombaAgua = 0;
      confirmacionReset(LED_BOMBA_ROJO);
    }    
    if (controlBoton==10){
    errorClorado=0;
    volumenNoClorado=0;
    EEPROM.update (0,volumenNoClorado);
    confirmacionReset(LED_CLORO_ROJO);
    //controlBoton=0;
    finReset=HIGH;
    }
    if (controlBoton<10){
    controlBoton++;
    }
    
    
  }
  else {
    controlBoton=0;
    if(digitalRead(BOTON_MULTI))  finReset=LOW;
    ledsApagados=LOW;
  }
}