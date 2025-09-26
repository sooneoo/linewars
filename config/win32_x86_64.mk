CC=gcc
PKG_CONFIG=pkg-config


PKGS=raylib

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Isrc/include
CFLAGS += $$($(PKG_CONFIG) --cflags $(PKGS))


LIBS += $$($(PKG_CONFIG) --libs $(PKGS))
LIBS += -lalloc
LIBS += -lm

OBJS += $(CACHE)/main.o

$(CACHE)/main.o: src/linewars/main.c
	$(CC) $(CFLAGS) -c src/linewars/main.c -o $@


$(RELEASE)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(RELEASE)/$(TARGET)



