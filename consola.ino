////////////////////////////////////////////LCD/////////////////////////////////////////////////////////////////////////////
void actualiza_lcd(void) {

  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("f=");
  lcd.setCursor(3,0);
  lcd.print(caudal);
  lcd.setCursor(10,0);
  lcd.print("V=");
  lcd.setCursor(13,0);
  lcd.print(litrosCicloAgua);
  lcd.setCursor(0 ,1);
  lcd.print("T=");
  lcd.setCursor(3,1);
  lcd.print(tiempoFuncionamientoBombaAgua);
  
  lcd.setCursor(10,1);
  lcd.print("nC=");
  lcd.setCursor(13, 1);
  lcd.print(litrosNoClorados);
  lcd.setCursor(0,2);
  lcd.print("er1=");
  lcd.setCursor(4,2);
  lcd.print(error1);
  lcd.setCursor(10,2);
  lcd.print("er2=");
  lcd.setCursor(14,2);
  lcd.print(error2);
  lcd.setCursor(0 ,3);
  lcd.print("erC");
  lcd.setCursor(4,3);
  lcd.print(errorClorado);
  
  lcd.setCursor(10,3);
  lcd.print("nCl");
  lcd.setCursor(14,3);
  lcd.print(errorNivelCloro);
}



////////////////////////////////////////////////////SALIDA LCD/////////////////////////////////////////////////////////////////////




   void consola() {
  Serial.print("BLOQUE DE AGUA  ");
  Serial.println(bloqueAguaCopia);
  //Serial.print( "MINIMO_BLOQUE_AGUA    "); Serial.println ( MINIMO_BLOQUE_AGUA);
  Serial.print("error1    ");
  Serial.println(error1);
  Serial.print("error2    ");
  Serial.println(error2);
  Serial.print("TIEMPO FUNCIONAMIENTO BOMBA    ");
  Serial.println(tiempoFuncionamientoBombaAgua);
  Serial.print("CICLO_AGUA    ");
  Serial.println(cicloAgua);
  Serial.print("volumen no clorado    ");
  Serial.println(litrosNoClorados);
  Serial.print ("FIN_CICLO_AGUA    "); Serial.println ( FIN_CICLO_AGUA);
  Serial.print("NIVEL    ");
  Serial.println(nivelAgua);
  Serial.print("caudal      ");
  Serial.println(caudal);
  Serial.print("llenado          ");
  Serial.println(litrosCicloAgua);
  Serial.println("////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
  //Serial.println ("//");
}
/////////////////////////////////////////CALCULOS CAUDAL Y AGUA ACUMULADA EN FLOAT/////////////////////////////////////////////////////////////////////7777
void calculos() {
  caudal = bloqueAguaCopia * FACTOR_CAUDALIMETRO / 83.3333;
  litrosCicloAgua = cicloAgua * FACTOR_CAUDALIMETRO / 1000;
  litrosNoClorados= volumenNoClorado * FACTOR_CAUDALIMETRO /1000;
}
