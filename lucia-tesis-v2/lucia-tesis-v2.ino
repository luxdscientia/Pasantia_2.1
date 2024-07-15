#include "datos.h"
#include "Prueba.h"

Prueba prueba;
void setup() {
  // Configurar pines de entrada y salida

}

void loop() {
  for (auto& configuracion : PRUEBAS) {
    prueba.setConfiguracion(configuracion);
  }

  prueba.realizar();
  delay(1000);
  
}
