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


	digitalWrite(13, HIGH);
	Serial.begin(9600);
	Serial.println("***** STARTING ******");
	Serial.print("Free ram : ");
	Serial.println(freeRam());

	delay(3000);
	digitalWrite(13, LOW);

	BT.powerOn(cmd, 9600);
	delay(3000);
	digitalWrite(13, cmd ? HIGH : LOW);
	Serial.println("--------------------------");

	char buffResult[64];

	BT.checkModule();
	BTResult resCall = BT.getLastResult(buffResult, 64);
	Serial.println(buffResult);
	Serial.println("--------------------------");
	delay(1000);

	BT.command("AT+INQC",200);

	BT.version();
	Serial.println("--------------------------");
	delay(1000);

	BT.state();
	Serial.println("--------------------------");
	delay(1000);

	Serial.println(BT.address());
	Serial.println("--------------------------");
	delay(1000);

//	BT.setName("Anextraordinarylongnametotestifthebufferoverflowiswellhandled"); //72 char
//	Serial.println("--------------------------");
//	delay(1000);

	BT.setName("TOTOROOOOOO");
	Serial.println("--------------------------");
	delay(1000);

//	BT.setName("BLUETOOFFE");
//	Serial.println("--------------------------");
//	delay(1000);

	BT.name();
	Serial.println("--------------------------");
	delay(1000);

	Serial.println(BT.getRole());
	Serial.println("--------------------------");
	delay(1000);

	Serial.println(BT.setRole(MASTER));
	Serial.println("--------------------------");
	delay(2000);

	Serial.println(BT.getRole());
	Serial.println("--------------------------");
	delay(1000);

	Serial.println(BT.setInqAC("9e8b33"));
	Serial.println("--------------------------");
	delay(1000);

//	Serial.println(BT.setRole(SLAVE));
//	Serial.println("--------------------------");
//	delay(2000);
//
//	Serial.println(BT.getRole());
//	Serial.println("--------------------------");
//	delay(1000);
//
//	Serial.println(BT.init());
//	Serial.println("--------------------------");
//	delay(1000);
//
//	Serial.println(BT.getPasswd());
//	Serial.println("--------------------------");
//	delay(1000);

	Serial.println(BT.setPasswd("1234"));
	Serial.println("--------------------------");
	delay(1000);

	Serial.println(BT.getPasswd());
	Serial.println("--------------------------");
	delay(1000);

	Serial.println(BT.setCMode(ANY));
	Serial.println("--------------------------");
	delay(1000);

	Serial.println((char) BT.getCMode());
	Serial.println("--------------------------");
	delay(1000);

	Serial.println(BT.seekDevice(TEL_ADDR));
	Serial.println("--------------------------");
	delay(1000);

	Serial.println(BT.link(TEL_ADDR));
	Serial.println("--------------------------");
	delay(1000);

	Serial.println(BT.countPairList());
	Serial.println("--------------------------");
	delay(1000);
//
//	Serial.println(BT.deletePairList());
//	Serial.println("--------------------------");
//	delay(1000);
//
//	Serial.println(BT.countPairList());
//	Serial.println("--------------------------");
//	delay(1000);

//	BT.command("AT+WRONG", 10);
//	Serial.println("--------------------------");
//	delay(1000);
//
//	BT.command("AT+RESET");

	Serial.print("Free ram : ");
	Serial.println(freeRam());

}

void loop() {
	while (BT.available()) {
		Serial.write(BT.read());
	}

	while (Serial.available()) {
		int rb = Serial.read();
		if (rb == '#') {
			BT._cmd(true);
		} else if (rb == '@') {
			BT._cmd(false);
		} else {
			BT.write(rb);
		}
	}

}
