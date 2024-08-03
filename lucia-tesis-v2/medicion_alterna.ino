#include "TrueRMS.h"

#define RMS_WINDOW 50  // rms para 50 muestras, 3 periodos en 60Hz
#define PERIODO 1000   // 1 ms Periodo muestra

unsigned long nextLoop;
Rms readRms;
int count;

void configurar_medicion_alterna(float rango_voltaje, unsigned char bits) {
  readRms.begin(rango_voltaje, RMS_WINDOW, bits, BLR_ON, CNT_SCAN);

  readRms.start();

  count = 0;
  nextLoop = micros() + PERIODO;
}

bool loop_medicion_alterna(int (*obtener_valor)()) {
  int medicion = obtener_valor();
  readRms.update(medicion);

  while (nextLoop > micros())
    ;
  nextLoop += PERIODO;
  count ++;
  return count >= 1000 ? false : true;
}

float obtener_valor_rms() {
  readRms.publish();
  return readRms.rmsVal;
}