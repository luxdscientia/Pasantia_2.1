void MenuPrincial() {
  if (estaCambiandoEstado) {
    mostrarPantalla("Areas de contacto", "1. A1, 2. A2");
    estaCambiandoEstado = false;
  }

  if (digitalRead(A_1) == HIGH) {
    mostrarPantalla("Config. A= 8200 mm^2", "");
    delay(2000);
    estado = EstadoPrograma::modoA1;
  } else if (digitalRead(A_2) == HIGH) {
    mostrarPantalla("Config. A= 100 mm^2", "");
    delay(2000);
    estado = EstadoPrograma::modoA2;
  }
}