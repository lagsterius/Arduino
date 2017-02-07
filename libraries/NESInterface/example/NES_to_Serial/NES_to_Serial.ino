/**NES Data pin  ----> 2pin Arduino**/
/**NES Clock pin ----> 3pin Arduino**/
/**NES Latch pin ----> 4pin Arduino**/
#include <nesinterface.h>

#define latch 4
#define clock 3
#define data  2

NES NES;

void setup() {
	NES.Init(clock, latch, data);
	Serial.begin(9600);
}

void loop() {
	NES.Update();
	byte val = NES.Read();
	Serial.println(val, BIN);
	delay(600);
}