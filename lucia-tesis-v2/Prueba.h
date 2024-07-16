#include "Arduino.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>
#pragma once

class Prueba {
public:
  void setConfiguracion(int configuracion[2]) {
    this->configuracion[0] = configuracion[0];
    this->configuracion[1] = configuracion[1];
  }

  void realizar() {
    configurar();
    hacerPrueba();
    enviarDatos();
  }

private:
  float v1;
  float v2;
  int configuracion[2];

  void configurar() {
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

  void enviarDatos() {
    // Mostrar los datos serial
  }
};