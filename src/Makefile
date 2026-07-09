.PHONY: all clean

include ../config.mk

SUBDIRS := $(wildcard */)
SUBDIR_OBJS := $(addsuffix out.o,$(SUBDIRS))

OUT := out.o

all: $(OUT)

$(OUT): $(SUBDIR_OBJS)
	ld -r -o $@ $(SUBDIR_OBJS)

$(SUBDIR_OBJS):
	$(MAKE) -C $(dir $@)

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -f $(OUT)