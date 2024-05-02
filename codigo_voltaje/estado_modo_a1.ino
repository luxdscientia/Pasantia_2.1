#include "red_resistencias.h"

void ModoA1() {
  Serial.println("Entrando a estado A1");
  mostrarPantalla("Estas en modo A1", "Realizando mediciones");
  // float v = get_VRMS();
  configurar_medicion_alterna(240, 10);
  while(loop_medicion_alterna(&get_digital_VIN));
  float v = obtener_valor_rms();
  EEPROM.put(voltageAddress, v);
  lcd.clear();
  lcd.print("voltaje");
  lcd.setCursor(0, 1);
  lcd.print(v);
  delay(1000);

  prender_rele(v, RED_RELES, VALORES_RED_A1, VALOR_R_A1);
  float iz = get_IZ();
  delay(500);
  estado = EstadoPrograma::MostrarDatos;
  estaCambiandoEstado = true;
  Serial.println("Saliendo de estado A1");
}
