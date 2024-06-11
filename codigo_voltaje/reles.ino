void encender_reles(int reles[8], int valores[12]) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(reles[i], valores[i]);
  }
}

void guardar_info_rele(const float & valor_resistencia) {
    EEPROM.put(resistanceAddress, valor_resistencia);
    Serial.print("Resistencia eqv guardada.");
    Serial.println(valor_resistencia);
}

void prender_rele(float v, int red[8], int VALORES_RED[5][12], float VALOR_R[5]) {
  Serial.println("PRENDIENDO RELES");
  if (v >= 0 && v <= 50) {
    encender_reles(red, VALORES_RED[0]);
    guardar_info_rele(VALOR_R[0]);
  } else if (v > 50 && v <= 100) {
    digitalWrite(3, HIGH);
    encender_reles(red, VALORES_RED[1]);
    guardar_info_rele(VALOR_R[1]);
   } else if (v > 100 && v <= 150) {
    digitalWrite(4, HIGH);
    encender_reles(red, VALORES_RED[2]);
    guardar_info_rele(VALOR_R[2]);
} else if (v > 150 && v <= 190) {
    encender_reles(red, VALORES_RED[3]);
    guardar_info_rele(VALOR_R[3]);
   } else if (v > 190) {
    encender_reles(red, VALORES_RED[4]);
    guardar_info_rele(VALOR_R[4]);
  }
}