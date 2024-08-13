
#define RMS_WINDOW 50  // 50 muestras
#define PERIODO 1000   // 1 ms Periodo muestra
const int INICIO = 12;

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

bool detectar_cruce_por_cero() {
  static int valorAnterior = 0;
  int valorActual = analogRead(A1);
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


void setup() {
  Serial.begin(9600);
  pinMode(INICIO, INPUT);
  configurar_medicion_alterna(5.0, 10);  // Configurar con rango de voltaje de 5V y 10 bits de resolución
}

void loop() {
  if (digitalRead(INICIO) == HIGH) {
    if (!loop_medicion_alterna()) {
      enviando_valores();

      configurar_medicion_alterna(5.0, 10);  // Configurar nuevamente
    }
  }
}
