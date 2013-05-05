CC=gcc
CFLAGS=-Wall -O2
thinkpad_hdd_led: thinkpad_hdd_led.o

clean:
	rm -f thinkpad_hdd_led thinkpad_hdd_led.o
install:
	cp thinkpad_hdd_led /usr/sbin
uninstall:
	rm /usr/sbin/thinkpad_hdd_led

