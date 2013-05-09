CC=gcc
CFLAGS=-Wall -O2
ifdef PREFIX
BINDIR = $(PREFIX)/sbin
else
BINDIR = /usr/sbin
endif

thinkpad_hdd_led: thinkpad_hdd_led.o

clean:
	rm -f thinkpad_hdd_led thinkpad_hdd_led.o
install:
	cp thinkpad_hdd_led $(BINDIR)/
uninstall:
	rm $(BINDIR)/thinkpad_hdd_led

