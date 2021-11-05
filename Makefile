PREFIX?=/usr/local
DESTDIR?=

CC ?= gcc
CFLAGS  = -g -Wall -Wextra
ifneq ($(NOLIBC),)
CFLAGS += -static -nostdlib -include nolibc.h -fno-asynchronous-unwind-tables -fno-ident -fno-stack-protector -Os -g0
else
	CFLAGS += -Wpedantic -std=c11
endif

all: qmk_id

install: qmk_id
	install -m644 -D 50-qmk.rules $(DESTDIR)$(PREFIX)/lib/udev/rules.d/50-qmk.rules
	install -m755 -D qmk_id $(DESTDIR)$(PREFIX)/lib/udev/qmk_id

qmk_id: | test

test: qmk_id_test
	./qmk_id_test

clean:
	$(RM) qmk_id qmk_id_test

format:
	clang-format -i qmk_id.c
	clang-format -i qmk_id_test.c

.PHONY: install test clean format
