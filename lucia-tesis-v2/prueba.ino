
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

int prueba_interna;
void hacerPrueba() {
  float v1;
  float v2;
  // Mientras 2 ciclos de red
  // Proceso A
  //v1
  configurar_medicion_alterna(707, 10);  //referencia de corriente
  while (loop_medicion_alterna(&get_digital_V1))
    ;
  v1 = obtener_valor_rms();
  pruebas[numero_prueba][prueba_interna] = v1;
  // prueba_interna++;
  // v2
  configurar_medicion_alterna(566, 10);  //referencia de voltaje
  while (loop_medicion_alterna(&get_digital_V2))
    ;
  v2 = obtener_valor_rms();
  pruebas[numero_prueba][prueba_interna] = v2;
  prueba_interna++;
  lcd.clear();
  Log("Test: " + String(prueba_interna) + ", V1:" + String(v1) + ", V2: " + String(v2));
  lcd.print("Test:" + String(prueba_interna));
  lcd.setCursor(7, 0);
  lcd.print("V1:" + String(v1));
  lcd.setCursor(7, 1);
  lcd.print("V2:" + String(v2));
  delay(200);
}

void realizarPrueba(int configuracion[2]) {
  prueba_interna = 0;
  Log("Inicio configuracion " + String(nombre_pruebas[numero_prueba]));
  delay(100);
  lcd.clear();
  lcd.println("Configuracion" + String(nombre_pruebas[numero_prueba]));
  setConfiguracionPrueba(configuracion);
  auto tiempo_inicio_prueba = micros();
  for (int i = 0; i < 3; i++) {
    configurarPrueba(RELES_SW, i);
    hacerPrueba();
  }
  auto tiempo_finalizo_prueba = micros();
  Log("La prueba duro " + String(tiempo_finalizo_prueba - tiempo_inicio_prueba));
}