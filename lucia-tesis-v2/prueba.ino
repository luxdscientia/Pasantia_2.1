 void hacerPrueba() {
    // Mientras 1 ciclo
    // Leer datos
    //v1
    configurar_medicion_alterna(250, 10);
    while (loop_medicion_alterna(&get_digital_V1))
      ;
    v1 = obtener_valor_rms();
    // v2
    configurar_medicion_alterna(250, 10);
    while (loop_medicion_alterna(&get_digital_V2))
      ;
    v2 = obtener_valor_rms();
  }

  void enviarDatos() {
    // Mostrar los datos serial
  }