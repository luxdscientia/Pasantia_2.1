void setConfiguracionPrueba(int configuracion[2]) {
  digitalWrite(RELES_SRV[0], configuracion[0]);
  digitalWrite(RELES_SRV[1], configuracion[1]);
}

void encender_reles(int reles[2], int valores[2]) {
  for (int i = 0; i < 2; i++) {
    digitalWrite(reles[i], valores[i]);
  }
}


void configurarPrueba(int red[2], int i) {
  // Prender Reles
  encender_reles(RELES_SW, CONF_PROCESOS[i]);
}

void hacer_prueba(int (*get_v)()) {
  prueba_interna = 0;
  float v;
  int i;
  
  auto tiempo_inicio_prueba = micros();
  digitalWrite(31, HIGH);
  for (i = 0; i < 90; i++) {
    tomar_muestras(get_v);
  }
  digitalWrite(31, LOW);

  Log("Test:" + nombre_pruebas[numero_prueba]);
  lcd.clear();
  lcd.println("Secuencia " + nombre_pruebas[numero_prueba] + "  ");

  numero_prueba++;
}

void realizarPrueba(int configuracion[2]) {
  setConfiguracionPrueba(configuracion);
  // auto tiempo_inicio_prueba = micros();
  for (int i = 0; i < 3; i++) {

    Log("Inicio configuracion " + nombre_pruebas[numero_prueba]);
    configurarPrueba(RELES_SW, i);
    hacer_prueba(&get_digital_V1);
    hacer_prueba(&get_digital_V2);
    delay(1000);
  }
  // auto tiempo_finalizo_prueba = micros();
  // auto tiempo_f_S= (tiempo_finalizo_prueba-tiempo_inicio_prueba)* 1e-6;
  // Log("La prueba duro " + String(tiempo_finalizo_prueba - tiempo_inicio_prueba));

  // lcd.clear();
  // lcd.println("La prueba duro: ");
  // lcd.setCursor(0, 1);
  // lcd.println(String (tiempo_f_S) + " segundos");
  // delay(2000);
}