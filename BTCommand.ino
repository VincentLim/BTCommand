#include <BTSerial.h>

#define BT_DEBUG

#define BT_CMD 42
#define BT_PWR 43

#define TEL_ADDR "6cf3,73,df4a65"
//20c9,d0,83173c

BTSerial BT(&Serial1, BT_CMD, BT_PWR);

bool cmd = false;
unsigned long lastPush = 0;

void setup() {
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
	Serial.begin(9600);
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

	BT.version();
	Serial.println("--------------------------");
	delay(1000);

	BT.state();
	Serial.println("--------------------------");
	delay(1000);

	BT.address();
	Serial.println("--------------------------");
	delay(1000);

	BT.name();
	Serial.println("--------------------------");
	delay(1000);

	BT.command("AT+PROUT", 10);
	Serial.println("--------------------------");
	delay(1000);

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
