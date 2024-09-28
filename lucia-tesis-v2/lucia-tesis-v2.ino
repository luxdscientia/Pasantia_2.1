#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "datos.h"

#define LOG
#define NUMERO_PRUEBAS 18
#define SAMPLE_SIZE 90


const int rs = 6, en = 7, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int INICIO = 12;
const int SW0 = 31;
const int SW1 = 33;
const int SW2 = 39;
const int SW3 = 35;
const int SW4 = 37;
const int RELES_SRV[2] = { SW3, SW4 };
const int RELES_SW[2] = { SW1, SW2 };

const String nombre_pruebas[NUMERO_PRUEBAS] = {
  "A1:V1", "A1:V2", "B1:V1", "B1:V2", "C1:V1", "C1:V2",
  "A2:V1", "A2:V2", "B2:V1", "B2:V2", "C2:V1", "C2:V2",
  "A3:V1", "A3:V2", "B3:V1", "B3:V2", "C3:V1", "C3:V2",
  // "A4:V1", "A4:V2", "B4:V1", "B4:V2", "C4:V1", "C4:V2"
};

int numero_prueba = 0;
int prueba_interna = 0;
int pruebas[NUMERO_PRUEBAS][SAMPLE_SIZE];



void setup() {
  // Configurar pines de entrada y salida
  analogReference(EXTERNAL);
  Serial.begin(9600);
#ifdef LOG
  Serial1.begin(9600);
#endif
  lcd.begin(16, 2);
  pinMode(INICIO, INPUT);
  //RELES
  for (int i = 31; i < 51; i = i + 2) {
    pinMode(i, OUTPUT);
  }

  for (int i = 0; i < 2; i++) {
    digitalWrite(RELES_SRV[i], HIGH);
    digitalWrite(RELES_SW[i], HIGH);
  }
  digitalWrite(31, LOW);
}

int get_digital_V1() {
  int n;
  n = numero_prueba;
  if (n == 0 || n == 3 || n == 6 || n == 9 || n == 12 || n == 15) {
    // delay(1);
    return analogRead(A7);  //sin resistencia humana
  } else {
    // delay(1);
    return analogRead(A5);  //con resistencia humana
  }
}

int get_digital_V2() {

  return analogRead(A3);  //voltaje de alimentacion
}
void mostrarPantalla(String linea1, String linea2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linea1);

  lcd.setCursor(0, 1);
  lcd.print(linea2);
}

long ultima_vez_actualizo_pantalla = 0;
int tiempo_actualizacion_pantalla = 100;

void loop() {
  if ((millis() - ultima_vez_actualizo_pantalla) > 16) {
    mostrarPantalla("encendido", "....");

    ultima_vez_actualizo_pantalla = millis();
  }
  if (digitalRead(INICIO) == HIGH) {
    numero_prueba = 0;
    mostrarPantalla("INICIO ", "PRUEBAS");
    delay(200);
    auto tiempo_inicio_prueba = micros();
    for (auto& configuracion : CONF_PRUEBAS_RV) {
      realizarPrueba(configuracion);
      for (int i = 0; i < 2; i++) {
        digitalWrite(RELES_SRV[i], HIGH);
        digitalWrite(RELES_SW[i], HIGH);
      }
    }
    auto tiempo_finalizo_prueba = micros();
    auto tiempo_f_S = (tiempo_finalizo_prueba - tiempo_inicio_prueba) * 1e-6;
    Log("La prueba duro " + String(tiempo_finalizo_prueba - tiempo_inicio_prueba));
    lcd.clear();
    lcd.println("La prueba duro: ");
    lcd.setCursor(0, 1);
    lcd.println(String(tiempo_f_S) + " S");
    delay(2000);
    while (digitalRead(INICIO) == LOW) {
      if ((millis() - ultima_vez_actualizo_pantalla) > 16) {
        mostrarPantalla("Presione para", "Cargar data");

        ultima_vez_actualizo_pantalla = millis();
      }
    }
    enviar_datos_por_data_streamer();
    // delay(200);
    mostrarPantalla("Datos", "Enviados");
  }
}
void Log(String mensaje) {
#ifdef LOG
  Serial1.println(mensaje);
#endif
}

/*
 * Esta funcion hace uso del puerto serial para enviar datos al DataStreamer
 * El DataStreamer es un plugin de Excel para manejar informacion que 
 * proviene desde un arduino
 * https://www.microsoft.com/en-us/download/details.aspx?id=56976
 */
void enviar_datos_por_data_streamer() {
  for (int i = 0; i < NUMERO_PRUEBAS; i++) {
    Serial.print(nombre_pruebas[i]);
    Serial.print(", ");
    for (int j = 0; j < SAMPLE_SIZE; j++) {
      Serial.print(pruebas[i][j]);
      Serial.print(",");
    }
    Serial.println();
  }
}