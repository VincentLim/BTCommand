#define BT_DEBUG
#include "BTCommand.h"
#include <BTSerial.h>


BTSerial BT(&Serial1, BT_CMD, BT_PWR);

bool cmd = false;
unsigned long lastPush = 0;

int freeRam ()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void setup() {
	pinMode(13, OUTPUT);

	char pin[6];
	pin[0] = 0x3A;
	pin[1] = 0x39;
	pin[2] = 0x33;
	pin[3] = 0xBC;
	pin[4] = 0x1D;
	pin[5] = 0x00;

	digitalWrite(13, HIGH);
	Serial.begin(9600);
	Serial.println("***** STARTING ******");
	Serial.print("Free ram : ");
	Serial.println(freeRam());
	delay(3000);
	digitalWrite(13, LOW);

	//resetFactory();

	//findBauds();

	BT.powerOn(false, 9600);
	delay(200);

	BT.version();

	delay(500);
	BT.state();
	BT.checkModule();

	BT.setPasswd(pin,6);
	delay(200);
	BT.pair("1D,BC,33393A", "20");
	delay(200);
	BT.link("1D,BC,33393A");
	delay(200);



//	BT.reset();
//	BT.command("AT+INQM?");

}

void resetFactory(){
	BT.powerOff();
	delay(200);
	BT.powerOn(false, 9600);
	BT.orgl();
	BT.powerOff();
	delay(500);
	BT.powerOn(false, 9600);
}

void findBauds() {
	const unsigned long rates[] = {4800,9600,19200,38400,57600,115200};
	BT._cmd(true);
	for(int i = 0; i < 6; i++){
		BT.powerOn(false, rates[i]);
		delay(1000);
		BT.flush();
		BT.command("AT+STATE?", 2000);
		delay(2000);
		BT.powerOff();
		delay(2000);
	}

}

void loop() {
	if (BT.available()) {
		Serial.write(BT.read());
	}

	if (Serial.available()) {
		int rb = Serial.read();
		if (rb == '#') {
			BT._cmd(true);
		} else if (rb == '@') {
			BT._cmd(false);
		} else {
			Serial.write(rb);
			BT.write(rb);
		}
	}

}
