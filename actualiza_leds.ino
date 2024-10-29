////////////////////////////////////////////////////ACTUALIZA TODOS LOS LEDS///////////////////////////////////////////////////////////////////////////

void actualizaLeds(bool off){//actualiza todos los leds
  if (off==HIGH ){
    apagaLeds();
    return;
  }
  actualizaLedBomba();
  actualizaLedCloro();
  actualizaLedNivel();
}
///////////////////////////////////////////////////ACTUALIZA LED CLORO////////////////////////////////////////////////////////////////////////////////////////77

void actualizaLedCloro(){//actualiza el led de cloro

  if (errorClorado == HIGH) {
    digitalWrite(LED_CLORO_VERDE, LOW);
    digitalWrite (LED_CLORO_ROJO, HIGH);
  return;
 }
 if (estadoBombaCloro ==HIGH) {
    digitalWrite(LED_CLORO_VERDE, tic1);
    digitalWrite (LED_CLORO_ROJO, LOW);
    return;
 }
  if (errorNivelCloro == HIGH) {
    digitalWrite(LED_CLORO_VERDE, HIGH);
    digitalWrite (LED_CLORO_ROJO, HIGH);
  return;
 }
 
  digitalWrite(LED_CLORO_VERDE, HIGH );
  digitalWrite (LED_CLORO_ROJO, LOW);
 }

//   static byte anteriorTic = LOW;
//   static byte ticsApagado = 5;
//   static byte copiaCiclosNoClorados = 0;
//  if (ciclosNoClorados!=0){ ///si hay ciclos sin clorar entra en la rutina de muestra
   
    
//     if (ticsApagado!=0){ // 5s led apagado
//       digitalWrite(LED_CLORO_VERDE, LOW); //apaga el led
//       if(tic1 == LOW) digitalWrite(LED_CLORO_ROJO, LOW);
//       if (tic1 != anteriorTic){//5 sg led apagado
//         anteriorTic = tic1;
//         ticsApagado--;
//        return;
//         }
//        }
//     if (copiaCiclosNoClorados == 0) {//resetea pulsaciones de ciclo a mostrar
//       copiaCiclosNoClorados = ciclosNoClorados;
//       ticsApagado =5;
//       return;
//     }
//     if (copiaCiclosNoClorados!= 0){ //empieza rutina de pulsaciones
//       if (tic1 != anteriorTic){
//       digitalWrite(LED_CLORO_VERDE, LOW);
//       digitalWrite(LED_CLORO_ROJO, tic1);
//       anteriorTic = tic1;
//       if (tic1==HIGH) copiaCiclosNoClorados --;//descuenta pulsaciones
//        }
//       }
//  }

///////////////////////////////////////////////////////////ACTUALIZA LED BOMBA//////////////////////////////////////////////////////////////////////////////
void actualizaLedBomba(){//actualiza el led de bomba
  
  if (error1 == true) {
    digitalWrite(LED_BOMBA_VERDE, LOW);
    digitalWrite (LED_BOMBA_ROJO, tic0);
  return;
 }
  if (error2 == true) {
    digitalWrite(LED_BOMBA_VERDE, LOW);
    digitalWrite (LED_BOMBA_ROJO, tic1);
  return;
 }
 if (estadoBombaAgua ==HIGH) {
    digitalWrite(LED_BOMBA_VERDE, HIGH);
    digitalWrite (LED_BOMBA_ROJO, LOW);
 }
 else{
  digitalWrite(LED_BOMBA_VERDE, LOW);
  digitalWrite (LED_BOMBA_ROJO, LOW);
 }
}
////////////////////////////////////////////////////////ACTUALIZA LED NIVEL AGUA///////////////////////////////////////////////////////////////////////7
void actualizaLedNivel(){ //actualiza el led de nivel
  //led nivel agua//////////////////////////////////////////////////////////////////////////////////////////////////7
  if (nivelAgua >= ALTO) {
    digitalWrite(LED_AGUA_ROJO, LOW); // apaga led rojo
    if (bloqueAguaCopia != 0) //si hay flujo
      digitalWrite (LED_AGUA_VERDE,tic1); // led verde parpadea
    else digitalWrite (LED_AGUA_VERDE, HIGH); //led verde fijo
    return;
  }

  if (nivelAgua == MEDIO) {
    if (bloqueAguaCopia != 0){
      digitalWrite (LED_AGUA_VERDE,tic1);
      digitalWrite (LED_AGUA_ROJO, tic1);
    }
    else {
      digitalWrite (LED_AGUA_VERDE, HIGH);
      digitalWrite (LED_AGUA_ROJO, HIGH);
    }
    return;
  }
  if (nivelAgua == BAJO) {
    digitalWrite(LED_AGUA_VERDE, LOW);
    if (bloqueAguaCopia != 0) 
      digitalWrite (LED_AGUA_ROJO,tic1);
    else 
      digitalWrite (LED_AGUA_ROJO, HIGH);
    return;
  }
  
  

  
}

///////////////////////////////////////////////////CONFIRMACION LED DE RESET//////////////////////////////////////////////////////////////////////////////////////

void confirmacionReset( unsigned char led){//ciclo parpadeo rapido confirmacion de reset
  apagaLeds();
  for (unsigned char i = 1; i<4; i++) {
  digitalWrite(led, HIGH);
  delay (50);
  digitalWrite(led,LOW);
  delay (50);
  }
}
////////////////////////////////////////////////////////////////APAGADO DE LEDS///////////////////////////////////////////////////////////////////////
void apagaLeds (){ //apaga todos los leds
  for ( int i = LED_BOMBA_VERDE; i <= LED_AGUA_ROJO; i++){
    digitalWrite(i, LOW);}
}


///////////////////////////////////////////////TEST LEDS//////////////////////////////////////////////////////////////////////////////////////////////////////
void testLeds () {
    digitalWrite(LED_AGUA_ROJO, HIGH);
    digitalWrite(LED_CLORO_ROJO, HIGH);
    digitalWrite(LED_BOMBA_ROJO, HIGH);
    delay(1000);
    digitalWrite(LED_AGUA_VERDE, HIGH);
    digitalWrite(LED_CLORO_VERDE, HIGH);
    digitalWrite(LED_BOMBA_VERDE, HIGH);
    delay(1000);
    digitalWrite(LED_AGUA_ROJO, LOW);//los tres leds en verde
    digitalWrite(LED_CLORO_ROJO, LOW);
    digitalWrite(LED_BOMBA_ROJO, LOW);
    delay(1000);
    digitalWrite(LED_AGUA_VERDE, LOW);//los tres leds apagados
    digitalWrite(LED_CLORO_VERDE, LOW);
    digitalWrite(LED_BOMBA_VERDE, LOW); 
    return;

  }