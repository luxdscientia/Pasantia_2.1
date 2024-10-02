#pragma once


void tomar_muestras(int (*obtener_valor)()) {

  int sample = obtener_valor();  // Manda a leer el pin Analogico correspondiente
  pruebas[numero_prueba][prueba_interna] = sample;
  prueba_interna++;
  delayMicroseconds(1600);
}