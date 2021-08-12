PREFIX?=/usr/local
DESTDIR?=

CC ?= gcc
CFLAGS  = -g -Wall -Wextra -Wpedantic -std=c11

all: qmk_id

install: qmk_id
	install -m644 -D 50-qmk.rules $(DESTDIR)$(PREFIX)/lib/udev/rules.d/50-qmk.rules
	install -m755 -D qmk_id $(DESTDIR)$(PREFIX)/lib/udev/qmk_id

qmk_id: | test

test: qmk_id_test
	./qmk_id_test

clean:
	$(RM) qmk_id qmk_id_test

.PHONY: install test clean
