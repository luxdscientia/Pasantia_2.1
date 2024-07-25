
void setConfiguracionPrueba(int configuracion[2]) {
  digitalWrite(RELES_SRV[0], configuracion[0]);
  digitalWrite(RELES_SRV[1], configuracion[1]);
}
void encender_reles(int reles[2], int valores[2]) {
  for (int i = 0; i < 2; i++) {
    digitalWrite(reles[i], valores[i]);
  }
}
float v1[9];
float v2[9];

void configurarPrueba(int red[2], int i) {
  // Prender Reles
  encender_reles(RELES_SW, CONF_PROCESOS[i]);
}


void hacerPrueba(int i) {
  // Mientras 2 ciclos de red
  // Proceso A
  //v1
  configurar_medicion_alterna(566, 10);  //referencia de corriente
  while (loop_medicion_alterna(&get_digital_V1))
    ;
  v1[i] = obtener_valor_rms();
  Serial.print("V1: ");
  Serial.println(v1[i]);
  // v2
  configurar_medicion_alterna(707, 10);  //referencia de voltaje
  while (loop_medicion_alterna(&get_digital_V2))
    ;
  v2[i] = obtener_valor_rms();
  Serial.print("V2: ");
  Serial.println(v2[i]);
}

void enviarDatosPrueba() {
  // Mostrar los datos serial
  for (int i = 0; i < 10; i++) {
    Serial.print("Proceso ");
    Serial.println(i);
    Serial.print("V1: ");
    Serial.println(v1[i]);
    Serial.print("V2: ");
    Serial.println(v2[i]);
  }
}


void realizarPrueba(int configuracion[2]) {
  Serial.println("inicio config");
  setConfiguracionPrueba(configuracion);

  for (int i = 0; i < 3; i++) {
    configurarPrueba(RELES_SW, i);
    hacerPrueba(i);
  }

  enviarDatosPrueba();
  delay(1000);
}