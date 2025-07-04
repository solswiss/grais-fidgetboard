#include <vector>
#include <string>
#include <random>


// r,g,b oder ander
int b1 = D4;
int b2 = D5;
int b3 = D6;
int l1 = D0;
int l2 = D1;
int l3 = D2;

long b1zeit;
long b2zeit;
long b3zeit;

int b1p;
int b2p;
int b3p;

int mode; // 0 = def, 1 = farbe mem spiel
int dd = 500; // default delay

// mode vars
std::vector<int> farbe_ptn;
int score = 0;

void displayStats() {
  if (mode == 1) {
    digitalWrite(l1, LOW);
    digitalWrite(l2, LOW);
    digitalWrite(l3, LOW);

    if (score > 100) {
      digitalWrite(l1, HIGH); delay(dd); digitalWrite(l1, LOW);
      digitalWrite(l2, HIGH); delay(dd); digitalWrite(l2, LOW);
      digitalWrite(l3, HIGH); delay(dd); digitalWrite(l3, LOW);
    } else {
      int n1 = (score / 100) % 10;
      int n2 = (score / 10) % 10;
      int n3 = score % 10;

      for (int i = 0; i < n1; i++) {
        digitalWrite(l1, HIGH); delay(dd); digitalWrite(l1, LOW);
      }
      for (int i = 0; i < n2; i++) {
        digitalWrite(l2, HIGH); delay(dd); digitalWrite(l1, LOW);
      }
      for (int i = 0; i < n3; i++) {
        digitalWrite(l3, HIGH); delay(dd); digitalWrite(l1, LOW);
      }
    }
  }
}

void reset() {
  b1zeit = b2zeit = b3zeit;
  b1p = b2p = b3p;
}

void restart() {
  digitalWrite(l1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(l3, LOW);
  
  // mode selection
  while (b1zeit == 0 && b2zeit == 0 && b3zeit == 0) {
    if (digitalRead(b1) == HIGH) {
      b1zeit++;
    } else if (digitalRead(b2) == HIGH) {
      b2zeit++;
    } else if (digitalRead(b3) == HIGH) {
      b3zeit++;
    }
  }
  if (b1zeit == 1) {
    mode = 0;
    digitalWrite(l1, HIGH); // nod
    delay(dd);
    digitalWrite(l1, LOW);
  } else if (b2zeit == 1) {
    mode = 1;
    farbe_ptn.reserve(25);
    digitalWrite(l2, HIGH);
    delay(dd);
    digitalWrite(l2, LOW);
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);

  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);

  //long startZeit = millis(); 
  // assuming the user isn't insane, blink r for minutes, g for 10s of seconds & b for 01s of seconds (maybe try different way also? it'd be hard to count)

  // greet
  digitalWrite(l1, HIGH);
  delay(200);
  digitalWrite(l1, LOW);
  digitalWrite(l2, HIGH);
  delay(200);
  digitalWrite(l2, LOW);
  digitalWrite(l3, HIGH);
  delay(200);
  digitalWrite(l3, LOW);

  digitalWrite(l1, HIGH);
  digitalWrite(l2, HIGH);
  digitalWrite(l3, HIGH);
  delay(200);
  digitalWrite(l1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(l3, LOW);

  restart();
}

// the loop function runs over and over again forever
void loop() {
  // quit param (recursive)
  // reset
  reset();

  if (digitalRead(b1) == HIGH && digitalRead(b2) == HIGH) { // could become rhythm game, for now i/o are single led
    b1zeit = millis();
    b2zeit = millis();
    if (b1zeit >= 1000 && b2zeit >= 1000) {
      displayStats();
      restart();
    } else {
      reset();
    }
  }
  if (mode == 0) {
    if (digitalRead(b1) == HIGH) digitalWrite(l1, HIGH);
    else digitalWrite(l1, LOW);
    if (digitalRead(b2) == HIGH) digitalWrite(l2, HIGH);
    else digitalWrite(l2, LOW);
    if (digitalRead(b3) == HIGH) digitalWrite(l3, HIGH);
    else digitalWrite(l3, LOW);
  }
  else { // if mode == 1, but there's only one other mode so :)
    // add new led to pattern
    farbe_ptn.push_back(random(0,2));

    // show pattern
    for (int i = 0; i < farbe_ptn.size(); i++) {
      switch(farbe_ptn[i]) {
        case 1: digitalWrite(l1, HIGH); delay(dd); digitalWrite(l1, LOW); break;
        case 2: digitalWrite(l2, HIGH); delay(dd); digitalWrite(l2, LOW); break;
        case 3: digitalWrite(l3, HIGH); delay(dd); digitalWrite(l3, LOW); break;
      }
    }

    // check input against pattern
    int n_in = 0;
    int l_in = -1;
    while (n_in < farbe_ptn.size()) {
      while (l_in == -1) {
        if (digitalRead(b1) == HIGH) l_in = 0;
        else if (digitalRead(b2) == HIGH) l_in = 1;
        else if (digitalRead(b3) == HIGH) l_in = 2;
      }
      if (l_in == farbe_ptn[n_in]) score++;
      else displayStats();
    }
  }
}
