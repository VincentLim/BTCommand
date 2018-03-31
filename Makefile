# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

BOARD_TAG    	=  mega2560

USER_LIB_PATH	= ../../libraries
ARDUINO_LIBS	= BTSerial
MONITOR_PORT  = /dev/ttyUSB0
# uncomment next line for debug on serial monitor
#CPPFLAGS		= -DDEBUG
#CPPFLAGS		= -DBT_USE_SOFTWARE_SERIAL

include /usr/share/arduino/Arduino.mk
