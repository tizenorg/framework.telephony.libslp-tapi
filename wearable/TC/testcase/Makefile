include ../config

CC ?= gcc

C_FILES = $(shell ls utc*.c)

PKGS = $(PKG_NAME)
PKGS += glib-2.0

LDFLAGS = `pkg-config --libs $(PKGS)`
LDFLAGS += $(TET_ROOT)/lib/tet3/tcm_s.o
LDFLAGS += -L$(TET_ROOT)/lib/tet3 -ltcm_s
LDFLAGS += -L$(TET_ROOT)/lib/tet3 -lapi_s

CFLAGS = -I. `pkg-config --cflags $(PKGS)`
CFLAGS += -I$(TET_ROOT)/inc/tet3
CFLAGS += -Wall

TCS := $(shell ls -1 utc*.c | cut -d. -f1)

all: $(TCS)

%: %.c
	$(CC) -o $@ $< util_common.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TCS)
