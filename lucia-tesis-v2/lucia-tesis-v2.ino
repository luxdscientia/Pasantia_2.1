#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "datos.h"
#include "TrueRMS.h"

#define LOG

const int rs = 6, en = 7, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int INICIO = 12;
const int RELES_SRV[2] = { 2, 3 };
const int RELES_SW[2] = { 4, 5 };

const char nombre_pruebas[4] = { 'A', 'B', 'C', 'D' };

int numero_prueba = 0;
float pruebas[4][8];

void setup() {
  // Configurar pines de entrada y salida
  Serial.begin(9600);
#ifdef LOG
  Serial1.begin(9600);
#endif
  lcd.begin(16, 2);
  pinMode(INICIO, INPUT);
  //RELES
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

int get_digital_V1() {
  return analogRead(A0);
}

int get_digital_V2() {
  return analogRead(A1);
}
void mostrarPantalla(String linea1, String linea2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linea1);

  lcd.setCursor(0, 1);
  lcd.print(linea2);
}

void loop() {
  mostrarPantalla("encendido", "....");
  if (digitalRead(INICIO) == HIGH) {
    numero_prueba = 0;
    for (auto& configuracion : CONF_PRUEBAS_RV) {
      realizarPrueba(configuracion);
      numero_prueba++;
      delay(1000);
    }

    enviar_datos_por_data_streamer();
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
  for (int i = 0; i < 4; i++) {
    Serial.print(nombre_pruebas[i]);
    Serial.print(", ");
    for (int j = 0; j < 6; j++) {
      Serial.print(pruebas[i][j]);
      Serial.print(", ");
    }
    Serial.println();
  }
}