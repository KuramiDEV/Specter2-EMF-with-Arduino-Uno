/////////////////////////////////////
/// Pinos de cada item do projeto ///
/////////////////////////////////////

const int Leds[] = {2, 3, 4, 5, 6}; // Leds do EMF (1 ao 5) em ordem
const int QuantiaDeLeds = 5; // Quantia de leds utilizadas no projeto
const int Potenciometro = A0;
const int Buzzer = 8;

/////////////////////////////////////
///  Códigos para funcionamento   ///
/////////////////////////////////////

int NiveldoEMF = 0; // Nível atual de EMF
bool SiteouPotenciometro = true; // mudar pelo site ou pelo potenciometro

void setup() {
  Serial.begin(9600); // Ligar na merda do flask
  for (int i = 0; i < QuantiaDeLeds; i++) {
    pinMode(Leds[i], OUTPUT);
  }
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');

    if (comando.startsWith("L")) {
      NiveldoEMF = comando.substring(1).toInt();
      SiteouPotenciometro = false;
    }

    if (comando.startsWith("P")) {
      SiteouPotenciometro = true;
    }
  }

  if (SiteouPotenciometro) {
    int potValue = analogRead(Potenciometro); // Fazer de 0 a 5
    NiveldoEMF = map(potValue, 0, 1023, 0, QuantiaDeLeds);
  }

  for (int i = 0; i < QuantiaDeLeds; i++) {
    digitalWrite(Leds[i], (i < NiveldoEMF) ? HIGH : LOW);
  }

  if (NiveldoEMF > 0) {
    int Delaydosom = map(NiveldoEMF, 1, QuantiaDeLeds, 500, 100);
    int frequenciadosom = map(NiveldoEMF, 1, QuantiaDeLeds, 500, 2000);

    tone(Buzzer, frequenciadosom);
    delay(50);
    noTone(Buzzer);
    delay(Delaydosom);
  } else {
    noTone(Buzzer);
    delay(200);
  }
}
