#define RMS_WINDOW 50  // 50 muestras
#define PERIODO 1000   // 1 ms Periodo muestra


unsigned long nextLoop;

int count;
int samples[RMS_WINDOW];
bool cruzoPorCero = false;
int crucesPorCero = 0;
bool cruces[RMS_WINDOW];  // Vector para marcar los cruces por cero

void configurar_medicion_alterna(float rango_voltaje, unsigned char bits) {
  count = 0;
  nextLoop = micros() + PERIODO;
  cruzoPorCero = false;
  crucesPorCero = 0;
  memset(cruces, 0, sizeof(cruces));  // Inicializar el vector de cruces por cero
}

bool detectar_cruce_por_cero(int (*obtener_valor)()) {
  static int valorAnterior = 0;
  int valorActual = obtener_valor();
  bool ocurrio_cruce = (valorAnterior < 512 && valorActual >= 512) || (valorAnterior > 512 && valorActual <= 512);
  valorAnterior = valorActual;
  return ocurrio_cruce;
}

bool loop_medicion_alterna(int (*obtener_valor)()) {
  if (crucesPorCero < 4) {
    if (detectar_cruce_por_cero(obtener_valor)) {
      crucesPorCero++;
    }
    return true;
  }

  int medicion = obtener_valor();

  samples[count] = medicion;
  pruebas[numero_prueba][prueba_interna] = medicion;
  prueba_interna++;
  cruces[count] = detectar_cruce_por_cero(obtener_valor);  // Marcar si hay cruce por cero

  while (nextLoop > micros())
    ;
  nextLoop = micros() + PERIODO;
  count++;
  return count >= RMS_WINDOW ? false : true;
}

void enviando_valores() {
  for (int i = 0; i < RMS_WINDOW; i++) {
    Serial.print(samples[i]);
    if (cruces[i]) {
      // Serial.print(" <- Cruce por cero");
    }
    Serial.println();
  }
}
