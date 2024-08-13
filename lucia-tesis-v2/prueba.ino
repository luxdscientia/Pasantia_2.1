
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
void hacerPrueba_V1() {
  float v1;
  // v2
  configurar_medicion_alterna(5.0, 10);
  while (loop_medicion_alterna(&get_digital_V1))
    ;
  enviando_valores();
  prueba_interna++;
  Serial.println("Test:" + String(prueba_interna) + " V1 ");

  // lcd.clear();
  // Log("Test: " + String(prueba_interna) + ", V1:" + String(v1) + ", V2: " + String(v2));  //corrergir
  // lcd.print("Test:" + String(prueba_interna) + " ");
  // lcd.setCursor(7, 0);
  // lcd.print("V1:" + String(v1));
  // lcd.setCursor(7, 1);
  // lcd.print("V2:" + String(v2));
  // delay(200);
}
void hacerPrueba_V2() {
  float v2;
  // v2
  configurar_medicion_alterna(5.0, 10);
  while (loop_medicion_alterna(&get_digital_V2))
    ;
  enviando_valores();
  prueba_interna++;
  Serial.println("Test:" + String(prueba_interna) + " V2 ");
}

void realizarPrueba(int configuracion[2]) {
  prueba_interna = 0;
  Log("Inicio configuracion " + String(nombre_pruebas[numero_prueba]));
  lcd.clear();
  lcd.println("Secuencia " + String(nombre_pruebas[numero_prueba]) + "     ");
  setConfiguracionPrueba(configuracion);
  auto tiempo_inicio_prueba = micros();
  for (int i = 0; i < 3; i++) {
    configurarPrueba(RELES_SW, i);
    hacerPrueba_V1();
    hacerPrueba_V2();
  }
  auto tiempo_finalizo_prueba = micros();
  Log("La prueba duro " + String(tiempo_finalizo_prueba - tiempo_inicio_prueba));
}