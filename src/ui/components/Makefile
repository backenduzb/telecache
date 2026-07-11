include ../../../config.mk

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

OUT := out.o

all: $(OUT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT): $(OBJS)
	ld -r -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(OUT)

.PHONY: all clean