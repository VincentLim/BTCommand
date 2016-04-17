#include "BTSerial.h"


#define BT_DEBUG

#define BT_CMD 42
#define BT_PWR 43


#define TEL_ADDR "6cf3,73,df4a65"
//20c9,d0,83173c

BTSerial BT(&Serial1, BT_CMD, BT_PWR);

bool cmd=false;
unsigned long lastPush=0;

void setup()
{

	pinMode(13, OUTPUT);
	digitalWrite(13,HIGH);
	Serial.begin(9600);
	delay(3000);
	digitalWrite(13,LOW);

	BT.powerOn(cmd, 9600);
	delay(3000);
	digitalWrite(13,cmd?HIGH:LOW);

	BT.command("AT",200);
	delay(200);
	BT.command("AT+VERSION?",200);
	delay(200);
	BT.command("AT+ROLE?",200);
	delay(200);
	Serial.println("Trying to connect to 6cf3,73,df4a65");
//	char* response = BT.command("AT");
//	Serial.print("response : ");
//	Serial.println(response);
	BT.command("AT+LINK=6cf3,73,df4a65",5000);

}

void loop()
{
	while(BT.available()){
		Serial.write(BT.read());
	}

	while(Serial.available()){
		int rb = Serial.read();
		if(rb=='#'){
			BT._cmd(true);
		}
		else if(rb=='@'){
			BT._cmd(false);
		} else {
			BT.write(rb);
		}
	}


}
