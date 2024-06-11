void MenuPrincial() {
  if (estaCambiandoEstado) {
    Serial.println("Entrando a menu principal");
    mostrarPantalla("Areas de contacto", "1. A1, 2. A2");
    estaCambiandoEstado = false;
  }


  if (digitalRead(A_1) == HIGH) {
    Serial.println("Se presiono A1");
    mostrarPantalla("Config. A= 8200 mm^2", "");
    delay(1000);
    estado = EstadoPrograma::modoA1;
  } else if (digitalRead(A_2) == HIGH) {
    mostrarPantalla("Config. A= 100 mm^2", "");
    delay(1000);

    estado = EstadoPrograma::modoA2;
  }
}