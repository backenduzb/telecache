.PHONY: all clean run

CC = gcc

export CC
export CFLAGS += $(shell pkg-config --cflags gtk4)

LDLIBS += $(shell pkg-config --libs gtk4) -ltdjson

ALL_SUBDIRS := $(wildcard */)
IGNORE_DIRS := include/ assets/ tdlib_files/ tdlib_db/ 
SUBDIRS := $(filter-out $(IGNORE_DIRS),$(ALL_SUBDIRS))

SUBDIR_OBJS := $(addsuffix out.o,$(SUBDIRS))

OUT = app

all: $(OUT)

$(OUT): $(SUBDIR_OBJS)
	$(CC) -o $@ $(SUBDIR_OBJS) $(LDLIBS)

$(SUBDIR_OBJS):
	$(MAKE) -C $(dir $@)

run: all
	./$(OUT)

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -f $(OUT)

.PHONY: all clean