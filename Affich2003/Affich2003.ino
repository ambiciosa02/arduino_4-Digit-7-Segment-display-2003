int data = 3;
int latch = 4;
int clock = 5;
int digitPins[] = {8, 9, 10, 11}; // Anode commune

// Chiffres de 0 à 9 pour anode commune (LOW active un segment)
byte digits[] = {
  0b0111111, // 0
  0b0000110, // 1
  0b1011011, // 2
  0b1001111, // 3
  0b1110100, // 4
  0b1101101, // 5
  0b1111101, // 6
  0b0000111, // 7
  0b1111111, // 8
  0b1101111  // 9
};

// Nombre à afficher (ex: 2025)
int nombre[] = {2, 0, 0, 3}; // De gauche à droite

void setup() {
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH); // OFF au départ
  }
}

void loop() {
  for (int i = 3; i >= 0; i--) {  // Commencer par la dernière position
    eteindreTous(); // Éteint tous les afficheurs

    digitalWrite(latch, LOW);
    shiftOut(data, clock, MSBFIRST, digits[nombre[3 - i]]); // Envoie du chiffre à l'envers
    digitalWrite(latch, HIGH);

    digitalWrite(digitPins[i], LOW); // Allume uniquement l'afficheur i
    delay(3); // Très court, pour effet de persistance visuelle
  }
}

void eteindreTous() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitPins[i], HIGH); // Anode commune -> HIGH = éteint
  }
}
