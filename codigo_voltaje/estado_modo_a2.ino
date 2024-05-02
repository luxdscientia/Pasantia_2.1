#include "red_resistencias.h"

void ModoA2() {
  Serial.println("Entrando a estado A2");
  mostrarPantalla("Estas en modo A2", "Realizando mediciones");
  float v = get_VRMS();
  EEPROM.put(voltageAddress, v);
  lcd.clear();
  lcd.print("voltaje");
  lcd.setCursor(0, 1);
  lcd.print(v);

  prender_rele(v, RED_RELES, VALORES_RED_A2, VALOR_R_A2);
  float iz = get_IZ();
  delay(500);
  estado = EstadoPrograma::MostrarDatos;
  estaCambiandoEstado = true;
}