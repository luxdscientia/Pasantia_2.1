#include "red_resistencias.h"

void ModoA1() {
  Serial.println("Entrando a estado A1");
  mostrarPantalla("Estas en modo A1", "Realizando mediciones");
  configurar_medicion_alterna(707, 10);
  while (loop_medicion_alterna(&get_digital_VIN));
  float v = obtener_valor_rms();
  EEPROM.put(voltageAddress, v);

  lcd.clear();
  lcd.print("Voltaje");
  lcd.setCursor(0, 1);
  lcd.print(v);
  if (YKD) {
    Serial.println("CAMBIANDO Z A ZYK");
    prender_rele(v, RED_RELES, VALORES_REDYK_A1, VALOR_ZYK_A1);
    configurar_medicion_alterna(250, 10);
    float iz = obtener_valor_rms();
    EEPROM.put(currentAddress, iz);
    estado = EstadoPrograma::MostrarDatos;
    estaCambiandoEstado = true;
    YKD=true;
  Serial.println("Saliendo de estado A1 YK");
  } else {
    prender_rele(v, RED_RELES, VALORES_RED_A1, VALOR_R_A1);
  configurar_medicion_alterna(566, 10);
  while (loop_medicion_alterna(&get_digital_IZ));
  float iz = obtener_valor_rms();
  EEPROM.put(currentAddress, iz);

  delay(500);
  estado = EstadoPrograma::MostrarDatos;
  estaCambiandoEstado = true;
  Serial.println("Saliendo de estado A1");
  }  
}
