void MenuPrincial() {
  if (estaCambiandoEstado) {
    mostrarPantalla("Areas de contacto", "1. A1, 2. A2");
    estaCambiandoEstado = false;
  }

  if (buttonA1.seHaPresionado()) {
    mostrarPantalla("Config. A= 8200 mm^2", "");
    delay(1000);
    estado = EstadoPrograma::modoA1;
  } else if (buttonA2.seHaPresionado()) {
    mostrarPantalla("Config. A= 100 mm^2", "");
    delay(1000);

    estado = EstadoPrograma::modoA2;
  }
}