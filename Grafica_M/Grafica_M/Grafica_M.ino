// #include "TrueRMS.h"

// #define RMS_WINDOW 50  // 50 muestras, 3 periodos en 60Hz
// #define PERIODO 1   // 0.3 ms Periodo muestra
// const int INICIO = 12;

// unsigned long nextLoop;
// Rms readRms;
// int count;
// int samples[RMS_WINDOW];

// void configurar_medicion_alterna(float rango_voltaje, unsigned char bits) {
//   readRms.begin(rango_voltaje, RMS_WINDOW, bits, BLR_ON, CNT_SCAN);
//   readRms.start();
//   count = 0;
//   nextLoop = micros() + PERIODO;
// }

// bool loop_medicion_alterna() {
//   int medicion = analogRead(A1);
//   readRms.update(medicion);
//   samples[count] = medicion;

//   while (nextLoop > micros())
//     ;
//   nextLoop += PERIODO;
//   count++;
//   return count >= RMS_WINDOW ? false : true;
// }

// void obtener_valores() {
//   for (int i = 0; i < RMS_WINDOW; i++) {
//         // Serial.print(i);
//     // Serial.print(". ");
//     Serial.println(samples[i]);
//   }
// }

// void setup() {
//   Serial.begin(9600);
//   pinMode(INICIO, INPUT);
//   configurar_medicion_alterna(5.0, 10);  // Configurar con rango de voltaje de 5V y 10 bits de resolución
// }

// void loop() {
//   if (digitalRead(INICIO) == HIGH) {
//     if (!loop_medicion_alterna()) {
//       obtener_valores();
//       delay(1000);                           // Esperar 1 segundo antes de tomar nuevas muestras
//       configurar_medicion_alterna(5.0, 10);  // Configurar nuevamente
//     }
//   }
// }

#include "TrueRMS.h"

#define RMS_WINDOW 50  // 50 muestras
#define PERIODO 50000   // 1 ms Periodo muestra
const int INICIO = 12;

unsigned long nextLoop;
Rms readRms;
int count;
int samples[RMS_WINDOW];
bool cruzoPorCero = false;
int crucesPorCero = 0;
bool cruces[RMS_WINDOW];  // Vector para marcar los cruces por cero

void configurar_medicion_alterna(float rango_voltaje, unsigned char bits) {
  readRms.begin(rango_voltaje, RMS_WINDOW, bits, BLR_ON, CNT_SCAN);
  readRms.start();
  count = 0;
  nextLoop = micros() + PERIODO;
  cruzoPorCero = false;
  crucesPorCero = 0;
  memset(cruces, 0, sizeof(cruces));  // Inicializar el vector de cruces por cero
}

bool detectar_cruce_por_cero() {
  static int valorAnterior = 0;
  int valorActual = analogRead(A1);
  bool cruce = (valorAnterior < 512 && valorActual >= 512) || (valorAnterior > 512 && valorActual <= 512);
  valorAnterior = valorActual;
  return cruce;
}

bool loop_medicion_alterna() {
  if (crucesPorCero < 4) {
    if (detectar_cruce_por_cero()) {
      crucesPorCero++;
    }
    return true;
  }

  int medicion = analogRead(A1);
  readRms.update(medicion);
  samples[count] = medicion;
  cruces[count] = detectar_cruce_por_cero();  // Marcar si hay cruce por cero

  while (nextLoop > micros())
    ;
  nextLoop += PERIODO;
  count++;
  return count >= RMS_WINDOW ? false : true;
}

void obtener_valores() {
  for (int i = 0; i < RMS_WINDOW; i++) {
    Serial.print(samples[i]);
    if (cruces[i]) {
      Serial.print(" <- Cruce por cero");
    }
    Serial.println();
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(INICIO, INPUT);
  configurar_medicion_alterna(5.0, 10);  // Configurar con rango de voltaje de 5V y 10 bits de resolución
}

void loop() {
  if (digitalRead(INICIO) == HIGH) {
    if (!loop_medicion_alterna()) {
      obtener_valores();
      delay(1000);                           // Esperar 1 segundo antes de tomar nuevas muestras
      configurar_medicion_alterna(5.0, 10);  // Configurar nuevamente
    }
  }
}



