void encender_reles(int reles[8], int valores[8]) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(reles[i], valores[i]);
  }
}

void prender_rele(float v, int red[8], int VALORES_RED[5][8], float VALOR_R[5]) {
  Serial.println("PRENDIENDO RELES");
  if (v >= 25 && v <= 50) {
    encender_reles(red, VALORES_RED[0]);
    float R = VALOR_R[0];
    EEPROM.put(resistanceAddress, R);
    Serial.print("Resistencia eqv.");
    Serial.println(R);
  }
  if (v >= 60 && v <= 90) {
    digitalWrite(3, HIGH);
    encender_reles(red, VALORES_RED[0]);
    float R = VALOR_R_A1[1];
    EEPROM.put(resistanceAddress, R);
    Serial.print("Resistencia eqv.");
    Serial.println(R);

  } else if (v >= 110 && v <= 140) {
    digitalWrite(4, HIGH);
    encender_reles(red, VALORES_RED[2]);
    float R = VALOR_R_A1[2];
    EEPROM.put(resistanceAddress, R);
    Serial.print("Resistencia eqv: ");
    Serial.println(R);

  } else if (v >= 160 && v <= 190) {
    encender_reles(red, VALORES_RED[3]);
    float R = VALOR_R_A1[3];
    EEPROM.put(resistanceAddress, R);
    Serial.print("Resistencia eqv. ");
    Serial.println(R);

  } else if (v >= 200) {
    encender_reles(red, VALORES_RED[4]);
    float R = VALOR_R_A1[4];
    Serial.print("Resistencia eqv. ");
    Serial.println(R);
  }
}