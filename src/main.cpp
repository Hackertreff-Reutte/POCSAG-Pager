#include <Arduino.h>
#include <BCH.h>


BCH bch;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  long x = 8;
  Serial.println(bch.getBinaryLength(x));
}

void loop() {
  // put your main code here, to run repeatedly:
}