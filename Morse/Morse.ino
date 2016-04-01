int codes[26];

//storage
// duration of one dot, ms
const int dotLength = 150;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  codes[2]= 3131; //c
  codes[3] = 311; //d
  codes[4] = 1; //e
  codes[7] = 1111; //h
  codes[11] = 1311; // l
  codes[13] = 31; // n
  codes[14] = 333; // o
  codes[19] = 3; // t
  codes[20] = 113; // u
}

void loop() {
  MorseMessage("do not touch");
  delay(dotLength * 20);
}
