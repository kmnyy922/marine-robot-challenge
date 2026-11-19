int g1 = 1, g2 = 2;

void setup(void) {
  Serial.begin(9600);
}

void loop() {
  int h1, h2, h3;
  float h4;
  h1 = add(g1, g2);
  h2 = subtract(g1, g2);
  h3 = multiply(g1, g2);
  h4 = divide(g1, g2);
  Serial.println(h1);
  Serial.println(h2);
  Serial.println(h3);
  Serial.println(h4);
  delay(5000);
}

int add(int x1, int x2) {
  int y;
  y = x1 + x2;
  return(y);
}

int subtract(int x1, int x2) {
  int y;
  y = x1 - x2;
  return(y);
}

int multiply(int x1, int x2) {
  int y;
  y = x1 * x2;
  return(y);
}

float divide(int x1, int x2) {
  float y;
  y = (float)x1 / x2;
  return(y);
}
