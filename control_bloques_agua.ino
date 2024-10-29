/////////////////////////////////////////////FUNCION INTERRUPCION SENSOR FLUJO//////////////////////////////////////////////////////////////////////////
void incrementoBloqueAgua() {  //Funcion interrupcion señal caudalimetro
  bloqueAgua++;
  return;
}

/////////////////////////////////////////////CONTROL NIVEL AGUA///////////////////////////////////////////////////////////////////////////////////////////
// la funcion lee el nivel de agua/////////////////////////////////////////////////////////////////////
// modifica  la variable global nivelAgua/////////////////////////////////////////////////////////////
void controlNivel() {
  if (digitalRead(SENSOR_NIVEL_MAX) == LOW) {
    nivelAgua = MAX;
    return;
  }
  if (digitalRead(SENSOR_NIVEL_ALTO) == LOW) {
    nivelAgua = ALTO;
    return;
  }
  if (digitalRead(SENSOR_NIVEL_MEDIO) == LOW) {
    nivelAgua = MEDIO;
    return;
  } else {
    nivelAgua = BAJO;
    return;
  }
}

/////////////////////////////////////////////CONTROL BLOQUES DE AGUA/////////////////////////////////////////////////////////////////////////////////////////
void controlCicloAgua() {
  bool estadoLlenado;
  bool estadoDeConteo = CONTANDO_BLOQUES_CON_CAUDAL;
  unsigned int tiempoLlenado = 0;
  unsigned int tiempoSinLlenado =0;
  detachInterrupt(digitalPinToInterrupt(SENSOR_FLUJO));  // detiene interrupccion
  bloqueAguaCopia = bloqueAgua;                          // salva bloque de agua  en bloque de agua copia para su uso y lo resetea
  bloqueAgua = 0;
  attachInterrupt(digitalPinToInterrupt(SENSOR_FLUJO), incrementoBloqueAgua, RISING);  //activa interrupcion

  cicloAgua += bloqueAguaCopia;  //incrementa ciclo de agua

  if (bloqueAguaCopia == 0) { // comprueba si hay caudal o no
    estadoLlenado = HAY_CAUDAL;
  }
  else {
    estadoLlenado == SIN_CAUDAL;
  }

  if ((bloqueAguaCopia < MINIMO_BLOQUE_AGUA) && (estadoBombaAgua == HIGH) && (tiempoFuncionamientoBombaAgua > 30)) {  // comprueba que exista caudal minimocon la bomba en funcionamiento
    error1 = true;
  }

  if (cicloAgua > FIN_CICLO_AGUA) {  //comprueba si se ha alcanzado el voñumen a clorar, carga volumen a clorar y resetea ciclo agua
    volumenAClorar = cicloAgua;
    cicloAgua = 0;
  }

// queda escribir codigo que tras TIEMPO_MINIMO_CAUDAL seguidos de caudal y TIEMPO_MINIMO_SIN_CAUDAL detenido sin caudal se inicie el proceso de clorado siempre que haya el volumenminimo








} // cierre funcion


 
   
    


  



    
  



//////////////////////////////////////////////CONTROL BOMBA AGUA////////////////////////////////////////////////////////////////////////////////////////////

void controlBombaAgua() {

  if (estadoBombaAgua == LOW) {                                      //si la bomba esta parada, comprueba condciones para ponerse en marcha
    if ((nivelAgua < ALTO) && (error1 == LOW) && (error2 == LOW)) {  //arranca la bomba si deposito inferior a alto y no hay errores 1 y 2
      estadoBombaAgua = HIGH;                                        //arranca bomba y pone a cero el contador de tiempo y sale de la funcion
      digitalWrite(RELE_AGUA, HIGH);
      tiempoFuncionamientoBombaAgua = 0;
    }
    return;
  } 
  else {                                                            //la bomba esta en funcionamiento, comprueba condiciones para detener en funcionamiemto
    if (tiempoFuncionamientoBombaAgua >= MAXIMO_TIEMPO_TICS_BOMBA) {  //comprueba tiempo de funconamiento, si esta rebasado actualiza error2
      error2 = HIGH;
    }

    if ((nivelAgua == MAX) || (error1 == HIGH) || (error2 == HIGH)) {  //si se dan las condiciones detiene la bomba
      estadoBombaAgua = LOW;
      digitalWrite(RELE_AGUA, LOW);
      //if (cicloAgua > MINIMO_VOLUMEN_A_CLORAR) {
       // volumenAClorar = cicloAgua;
       // cicloAgua = 0;
      //}
    } 
    else {  //la bomba continua su funcionamiento
      tiempoFuncionamientoBombaAgua++;
    }
    return;
  }
}
