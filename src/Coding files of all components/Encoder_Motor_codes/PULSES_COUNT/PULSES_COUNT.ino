#define ENCA 20 // YELLOW
#define ENCB 21 // WHITE

volatile int posi = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
}

void loop() {
  noInterrupts(); // Disable interrupts to read 'posi' safely
  int pos = posi;
  interrupts();   // Re-enable interrupts

  Serial.println(pos);
}

void readEncoder() {
  int b = digitalRead(ENCB);
  if (b > 0) {
    noInterrupts(); // Disable interrupts to modify 'posi' safely
    posi++;
    interrupts();   // Re-enable interrupts
  } else {
    noInterrupts(); // Disable interrupts to modify 'posi' safely
    posi--;
    interrupts();   // Re-enable interrupts
  }
}
