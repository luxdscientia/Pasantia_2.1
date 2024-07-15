#include "Arduino.h"
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
    // Finaliza la prueba
    // Cambiar el Rele 3 y 4
  }

  void enviarDatos() {
    // Mostrar los datos serial
  }
};