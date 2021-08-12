PREFIX?=/usr/local
DESTDIR?=

install:
	install -m644 -D 50-qmk.rules $(DESTDIR)$(PREFIX)/udev/rules.d/50-qmk.rules

.PHONY: install
