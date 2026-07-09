CC := gcc

GTK_CFLAGS := $(shell pkg-config --cflags gtk4)
GTK_LIBS   := $(shell pkg-config --libs gtk4)

TDLIB_CFLAGS := -I/usr/local/include
TDLIB_LIBS   := -L/usr/local/lib -ltdjson

WARNINGS := \
    -Wall \
    -Wextra \
    -Wpedantic

CFLAGS += \
    $(WARNINGS) \
    $(GTK_CFLAGS) \
    $(TDLIB_CFLAGS)

LDLIBS += \
    $(GTK_LIBS) \
    $(TDLIB_LIBS)