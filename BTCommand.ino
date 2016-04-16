
#include "BTSerial.h"
#define DEBUG_

#include "debug.h"


#define BT_CMD 42
#define BT_PWR 43
#define BOUTON 8

#define BOUNCE_TIME 500

#define TEL_ADDR "20c9,d0,83173c"

BTSerial BT(&Serial1, BT_CMD, BT_PWR);

bool cmd=true;
unsigned long lastPush=0;

void setup()
{

	pinMode(BOUTON, INPUT);
	pinMode(13, OUTPUT);
	digitalWrite(13,HIGH);
	Serial.begin(9600);
	delay(3000);
	digitalWrite(13,LOW);

	BT.powerOn(cmd, 9600);
	delay(3000);
	digitalWrite(13,cmd?HIGH:LOW);
}

void loop()
{
	while(BT.available()){
		Serial.write(BT.read());
	}

	while(Serial.available()){
		BT.write(Serial.read());
	}
//
//	if(Serial.available()){
//		int readByte = Serial.read();
//		switch(readByte){
//		case '0':
//			BT.print("AT\r\n");
//			break;
//		case '1':
//			BT.print("AT+VERSION?\r\n");
//			break;
//		default:
//			// nothing
//			break;
//		}

	// bouton qui va changer le CMD pour voir.
	if(digitalRead(BOUTON)==HIGH){
		if((lastPush+BOUNCE_TIME) < millis()){
			cmd=!cmd;
			BT.end();
			BT._cmd(cmd);
			if(cmd){
				BT.begin(9600);
			} else {
				BT.begin(38400);
			}
			delay(BOUNCE_TIME/2);
			digitalWrite(13, cmd?HIGH:LOW);
			lastPush=millis();

		}
	}

}
