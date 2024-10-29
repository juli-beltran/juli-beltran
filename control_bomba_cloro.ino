void controlCicloClorado() {  // la peticion viene de ciclo de agua o control bomba
  static unsigned int tiempo = 0;

  if ((volumenAClorar != 0) && (errorClorado == LOW)) {  //volumenAClorar es la variable que da entrada a la funcion
                                                         //si no hay error efectua el ciclo clorado
                                                         //si hay error solo acumula volumen no clorado
                                                         //la entrada es por detencion de la bomba si elvolumen es mayor al minimo
                                                         //o por llegar al maximo ciclo de agua


    if (estadoBombaCloro == LOW) {

      pesoCicloClorado = (volumenAClorar /100000.0)* DOSIS_CLORO;//  en gr .  el volumen a clorar es en impulsos caudalimetro
      tiempoClorado = pesoCicloClorado / FACTOR_BOMBA_CLORO;

      //pesoInicial = leepeso;
      tiempo = 0;
      digitalWrite(RELE_CLORO, HIGH);
      estadoBombaCloro = HIGH;
      return;
    }
    if (tiempo < tiempoClorado) {
      tiempo++;
      return;
    }

    digitalWrite(RELE_CLORO, LOW);
    estadoBombaCloro = LOW;
    tiempo = 0;

    //pesofinal = leepeso;
    controlPeso();
    if (errorClorado == HIGH) {  //si el error se genera en el ciclo actual
      volumenNoClorado += volumenAClorar;
      EEPROM.write(0, volumenNoClorado);
    }
    volumenAClorar = 0;
    return;
  }


  if ((volumenAClorar != 0) && (errorClorado == HIGH)) {  //si el error es abterior a esta peticion de ciclo
    volumenNoClorado += volumenAClorar;
    EEPROM.write(0, volumenNoClorado);
    volumenAClorar = 0;
  }
}

void controlPeso() {
  unsigned int diferenciaPesoMedidoCloro;
  diferenciaPesoMedidoCloro = pesoInicialCloro - pesoFinalCloro;
  if (pesoFinalCloro < MINIMO_PESO_CLORO) {
    errorNivelCloro = HIGH;
  }
  if ((diferenciaPesoMedidoCloro > 1.1 * pesoCicloClorado) || (diferenciaPesoMedidoCloro < 1.1 * pesoCicloClorado)) {
    errorClorado = HIGH;
  }
}
