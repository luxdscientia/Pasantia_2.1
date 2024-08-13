#include "TrueRMS.h"

#define RMS_WINDOW 50  // 50 muestras
#define PERIODO 1000   // 1 ms Periodo muestra
const int INICIO = 12;

unsigned long nextLoop;
Rms readRms;
int count;
int samples[RMS_WINDOW];
bool cruzoPorCero = false;
int crucesPorCero = 0;
bool cruces[RMS_WINDOW];  // Vector para marcar los cruces por cero

void configurar_medicion_alterna(float rango_voltaje, unsigned char bits) {
  // readRms.begin(rango_voltaje, RMS_WINDOW, bits, BLR_ON, CNT_SCAN);
  // readRms.start();
  count = 0;
  nextLoop = micros() + PERIODO;
  cruzoPorCero = false;
  crucesPorCero = 0;
  memset(cruces, 0, sizeof(cruces));  // Inicializar el vector de cruces por cero
}

void configurar_medicion_alterna_V1(float rango_voltaje, unsigned char bits) {
  readRms.begin(rango_voltaje, RMS_WINDOW, bits, BLR_ON, CNT_SCAN);

  readRms.start();

  count = 0;
  nextLoop = micros() + PERIODO;
}

bool detectar_cruce_por_cero() {
  static int valorAnterior = 0;
  int valorActual = analogRead(A1);
  // delayMicroseconds(200);
  bool ocurrio_cruce = (valorAnterior < 512 && valorActual >= 512) || (valorAnterior > 512 && valorActual <= 512);
  valorAnterior = valorActual;
  return ocurrio_cruce;
}

bool loop_medicion_alterna() {
  if (crucesPorCero < 4) {
    if (detectar_cruce_por_cero()) {
      crucesPorCero++;
    }
    return true;
  }

  int medicion = analogRead(A1);
  // delayMicroseconds(300);
  // readRms.update(medicion);
  samples[count] = medicion;
  cruces[count] = detectar_cruce_por_cero();  // Marcar si hay cruce por cero

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

bool loop_medicion_alterna_V1(int (*obtener_valor)()) {
  int medicion = obtener_valor();
  readRms.update(medicion);

  while (nextLoop > micros())
    ;
  nextLoop += micros() + PERIODO;
  count++;
  return count >= 1000 ? false : true;
}

float obtener_valor_rms() {

  readRms.publish();
  return readRms.rmsVal;
}

int get_digital_V1() {
  return analogRead(A1);
}

void setup() {
  Serial.begin(9600);
  pinMode(INICIO, INPUT);
  configurar_medicion_alterna(5.0, 10);  // Configurar con rango de voltaje de 5V y 10 bits de resolución
}

void loop() {
  if (digitalRead(INICIO) == HIGH) {
    if (!loop_medicion_alterna()) {
      enviando_valores();
      // float V1;
      // configurar_medicion_alterna_V1(700, 10);
      // while (loop_medicion_alterna_V1(&get_digital_V1))
      //   ;
      // V1 = obtener_valor_rms();
      // Serial.println("V2: " + String(V1));
      // delay(5000);


      configurar_medicion_alterna(5.0, 10);  // Configurar nuevamente
    }
  }
}
