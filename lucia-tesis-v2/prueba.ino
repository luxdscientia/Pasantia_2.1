int configuracion[2];

void setConfiguracionPrueba(int configuracion[2]) {
  configuracion[0] = configuracion[0];
  configuracion[1] = configuracion[1];
}

float v1;
float v2;

void configurarPrueba() {
  // Prender Reles
}


void hacerPrueba() {
  // Mientras 1 ciclo
  // Leer datos
  //v1
  configurar_medicion_alterna(250, 10);
  while (loop_medicion_alterna(&get_digital_V1))
    ;
  v1 = obtener_valor_rms();
  // v2
  configurar_medicion_alterna(250, 10);
  while (loop_medicion_alterna(&get_digital_V2))
    ;
  v2 = obtener_valor_rms();
}

void enviarDatosPrueba() {
  // Mostrar los datos serial
}

void realizarPrueba(int configuracion[2]) {
  setConfiguracionPrueba(configuracion);
  configurarPrueba();
  hacerPrueba();
  enviarDatosPrueba();
}