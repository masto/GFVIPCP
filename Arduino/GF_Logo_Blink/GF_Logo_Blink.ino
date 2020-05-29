// This: https://youtu.be/DAKhwMr7sG8
// For this: https://community.glowforge.com/t/pentagonal-hexecontahedron/58099

#define SEQUENCE_TIME (60L * 1000L)

// Some meaninful order of the lights, for patterns where it matters
int pins[] = { 3, 7, 9, 6, 10, 4, A1, A0, A2, 8, 2, 11, 12, 5 };
int num_pins = sizeof(pins) / sizeof(int);

// Define some simple animations

void GF_stringy() {
  for (int i = 0; i < num_pins; i++) {
    digitalWrite(pins[i], HIGH);
    delay(100);
  }

  for (int i = 0; i < num_pins; i++) {
    digitalWrite(pins[i], LOW);
    delay(100);
  }  
}

void GF_single() {
  static int last = 0;
  digitalWrite(pins[last], LOW);
  last = random(num_pins);
  digitalWrite(pins[last], HIGH);
  delay(250);
}

void GF_chase() {
  for (int i = 0; i < num_pins; i++) {
    digitalWrite(pins[i], i % 2 ? LOW : HIGH);
  }
  delay(250);
  for (int i = 0; i < num_pins; i++) {
    digitalWrite(pins[i], i % 2 ? HIGH : LOW);
  }
  delay(250);
}

void GF_blink() {
  for (int i = 0; i < num_pins; i++) {
    digitalWrite(pins[i], LOW);
  }
  delay(1000);
  for (int i = 0; i < num_pins; i++) {
    digitalWrite(pins[i], HIGH);
  }
  delay(1000);  
}

// To keep track of when to run the next pattern
unsigned long startTime;
void setup() {
  // set everything to output
  for (int i = 0; i < num_pins; i++) pinMode(pins[i], OUTPUT);

  startTime = millis();
}

int anim = 0;
void loop() {
  unsigned long m = millis();
  if (m - startTime > SEQUENCE_TIME) {
    if (++anim > 3) anim = 0;
    startTime = m;
    for (int i = 0; i < num_pins; i++) digitalWrite(i, LOW);
  }

  switch (anim) {
    case 0:
      GF_stringy();
      break;
    case 1:
      GF_single();
      break;
    case 2:
      GF_chase();
      break;
    case 3:
      GF_blink();
      break;
  }
}
