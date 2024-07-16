
int configuracion[2];

void setConfiguracionPrueba(int configuracion[2]) {
  configuracion[0] = configuracion[0];
  configuracion[1] = configuracion[1];
}
void encender_reles(int reles[2], int valores[2]) {
  for (int i = 0; i < 2; i++) {
    digitalWrite(reles[i], valores[i]);
  }
}
float v1[30];
float v2[30];

void configurarPrueba(int red[2],int valores[3][2]) {
  // Prender Reles
  //Proceso A
  encender_reles(RELES_SW, procesos[0]); 

  //proceso B
  encender_reles(RELES_SW, procesos[1]);
  //Proceso C
  encender_reles(RELES_SW, procesos[3]);
}


void hacerPrueba() {
  // Mientras 1 ciclo
  // Proceso A
  //v1
  configurar_medicion_alterna(250, 10);
  while (loop_medicion_alterna(&get_digital_V1))
    ;
  v1[0] = obtener_valor_rms();
  // v2
  configurar_medicion_alterna(250, 10);
  while (loop_medicion_alterna(&get_digital_V2))
    ;
  v2[0] = obtener_valor_rms();
  // Proceso B
  //v1
  configurar_medicion_alterna(250, 10);
  while (loop_medicion_alterna(&get_digital_V1))
    ;
  v1[1] = obtener_valor_rms();
  // v2
  configurar_medicion_alterna(250, 10);
  while (loop_medicion_alterna(&get_digital_V2))
    ;
  v2[1] = obtener_valor_rms();
  // Proceso C
  //v1
  configurar_medicion_alterna(250, 10);
  while (loop_medicion_alterna(&get_digital_V1))
    ;
  v1[2] = obtener_valor_rms();
  // v2
  configurar_medicion_alterna(250, 10);
  while (loop_medicion_alterna(&get_digital_V2))
    ;
  v2[2] = obtener_valor_rms();
}

void enviarDatosPrueba() {
  // Mostrar los datos serial
}


void realizarPrueba(int configuracion[2]) {
  setConfiguracionPrueba(configuracion);
  configurarPrueba(RELES_SW,procesos);
  hacerPrueba();
  enviarDatosPrueba();
}