#include <HashMap.h>

//define the max size of the hashtable
const byte HASH_SIZE = 9;
//storage
HashType<char, int> hashRawArray[HASH_SIZE];
//handles the storage [search,retrieve,insert]
HashMap<char, int> hashMap = HashMap<char, int>( hashRawArray , HASH_SIZE );
// duration of one dot, ms
const int dotLength = 150;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  hashMap[0]('c', 3131);
  hashMap[1]('d', 311);
  hashMap[2]('e', 1);
  hashMap[3]('h', 1111);
  hashMap[4]('l', 1311);
  hashMap[5]('o', 333);
  hashMap[6]('n', 31);
  hashMap[7]('t', 3);
  hashMap[8]('u', 113);  
}

void loop() {
  MorseMessage("do not touch");
  delay(dotLength * 20);
}
