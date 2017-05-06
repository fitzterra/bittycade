# Arduino Make file. Refer to https://github.com/sudar/Arduino-Makefile

ARDUINO_DIR = /usr/local/share/arduino-1.8.2

ARCHITECTURE  = avr
BOARD_TAG    = nano
BOARD_SUB    = atmega328
ISP_PORT = /dev/ttyUSB0
MONITOR_PORT = /dev/ttyUSB0
MONITOR_CMD = miniterm.py
OBJDIR = _build-$(BOARD_TAG)
ifdef BOARD_SUB
	OBJDIR = _build-$(BOARD_TAG)-$(BOARD_SUB)
endif

#ARDMK_DIR=/usr/share/arduino
ARDMK_DIR=/home/tomc/ownCloud/Electronics/Arduino/Arduino-Makefile

#USER_LIB_PATH = libraries

# The -fno-threadsafe-statics flag is needed to avoid the :
#   undefined reference to `__cxa_guard_acquire`
# errors
CXXFLAGS = -Wno-deprecated-declarations -g3 -std=gnu++11 -fno-threadsafe-statics

MONITOR_BAUDRATE = 115200

ARDUINO_LIBS = \
		   LinkedList \
		   LedControl \
		   Streaming  \
		   Encoder

-include $(ARDMK_DIR)/Arduino.mk

CFLAGS_STD = -Wall -Wundef -Werror
CXXFLAGS_STD = -Wall -Werror
# !!! Important. You have to use make ispload to upload when using ISP programmer

