#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "datos.h"
#include "Prueba.h"
#include "TrueRMS.h"

const int rs = 5, en = 6, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int INICIO = 12;
const int RELES_Rv[2] = {2,3};
const int RELES_SW[2]={4,5};

Prueba prueba;
void setup() {
  // Configurar pines de entrada y salida
  Serial.begin(9600);
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
void loop() {
  for (auto& configuracion : PRUEBAS) {
    prueba.setConfiguracion(configuracion);
  }

  prueba.realizar();
  delay(1000);
  
}
