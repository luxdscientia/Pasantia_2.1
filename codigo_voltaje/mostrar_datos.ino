void mostrardatos() {
  if (estaCambiandoEstado) {
    Serial.println("Revisando datos Presione sig.");
    mostrarPantalla("Revisando datos", "Presione sig.");
    estaCambiandoEstado = false;
  }
  if (digitalRead(SIG) == HIGH) {
  // if (buttonSIG.seHaPresionado()) {
    float VF;
    float CF;
    float RF;
    EEPROM.get(voltageAddress, VF);
    EEPROM.get(currentAddress, CF);
    EEPROM.get(resistanceAddress, RF);
    Serial.print("Voltage: ");
    Serial.println(VF);

    Serial.print("Current: ");
    Serial.println(CF);

    Serial.print("Resistance: ");
    Serial.println(RF);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("A:");
    lcd.print(CF, 3);
    lcd.setCursor(8, 0);
    lcd.print("mA");
    lcd.setCursor(0, 1);
    lcd.print("Vrms:");
    lcd.print(VF, 0);
    lcd.setCursor(9, 1);
    lcd.print("Z:");
    lcd.print(RF);
    lcd.setCursor(15, 1);
    lcd.print("K");

    delay(6000);
    Serial.println("Repetir P. Sig ir a menu: A1-A2");
    mostrarPantalla("Repetir P. Sig", "ir a menu: A1-A2");
  }

  if (digitalRead(A_1) == HIGH || digitalRead(A_2) == HIGH) {
  // if (buttonA1.seHaPresionado() || buttonA2.seHaPresionado()) {
    estado = EstadoPrograma::MenuPrincipal;
    estaCambiandoEstado = true;
  }

  //mostrar los VRMS, Z e I mientras se espera activación siguiente, apagar reles
}