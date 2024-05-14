#include <LiquidCrystal.h>
#include <EEPROM.h>


enum EstadoPrograma {
  MenuPrincipal,
  modoA1,
  modoA2,
  MostrarDatos,
  ResetPins,
};

const int RED_RELES[8] = { 2, 3, 4, 5, 6, 8, 9, 10 };
const int rs = 17, en = 42, d4 = 34, d5 = 36, d6 = 38, d7 = 40;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int A_1 = 26;
const int A_2 = 24;
const int SIG = 22;
const int PIN_OFF = 5;
const int yk = 18;
bool YKD;
const int voltageAddress = 0;  //COnfig para guardar datos en la eeprom
const int currentAddress = sizeof(float);
const int resistanceAddress = 2 * sizeof(float);
EstadoPrograma estado = EstadoPrograma::MenuPrincipal;
bool estaCambiandoEstado = true;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(A_1, INPUT);
  pinMode(A_2, INPUT);
  pinMode(SIG, INPUT);
  pinMode(A2, INPUT);
  digitalWrite(A_1, LOW);
  digitalWrite(A_2, LOW);
  digitalWrite(SIG, LOW);

  //SALIDA RED A1
  for (int i = 2; i < 2 + 5; i += 1) {
    pinMode(i, OUTPUT);
  }
  //SALIDA RED A2
  for (int i = 8; i < 8 + 3; i += 1) {
    pinMode(i, OUTPUT);
  }

  attachInterrupt(digitalPinToInterrupt(18), yakoactivo, CHANGE);
}
void off_reles() {
  // SALIDA RED A1
  for (int i = 2; i < 2 + 5; i += 1) {
    digitalWrite(i, LOW);
  }
  //SALIDA RED A2
  for (int i = 8; i < 8 + 3; i += 1) {
    digitalWrite(i, LOW);
  }
}
void yakoactivo() {
  if (digitalRead(yk) == HIGH) {
    mostrarPantalla("YAKOB DETECTADO", "Cambiando red Z");
     Serial.println("YAKOB CONECTADO");
    YKD = true;
    Serial.println(YKD);
    delay(1000);
    off_reles();
    estaCambiandoEstado = true;
    estado = EstadoPrograma::MenuPrincipal;
    Serial.println("YENDO MODO A1 YK");
  } else {
    mostrarPantalla("YAKOB DESCONECTADO", "Cambiando red Z");
    Serial.println("YAKOB DESCONECTADO");
    YKD = false;
    delay(1000);
    off_reles();
    estaCambiandoEstado = true;
    estado = EstadoPrograma::MenuPrincipal;
    
  }
}

void mostrarPantalla(String linea1, String linea2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linea1);
  lcd.setCursor(0, 1);
  lcd.print(linea2);
}

int get_digital_VIN() {
  return analogRead(A2);
}

int get_digital_IZ() {
  return analogRead(A0);
}

void loop() {
  switch (estado) {
    case MenuPrincipal:
      MenuPrincial();
      break;

    case modoA1:
      ModoA1();
      break;

    case modoA2:
      ModoA2();
      break;

    case MostrarDatos:
      mostrardatos();
      break;
  }
}
