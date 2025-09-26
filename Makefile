PLATFORM ?= linux_x86_64


CACHE=.cache
RELEASE=$(CACHE)/release
TARGET=linewars


all: build


-include config/$(PLATFORM).mk


build: env $(RELEASE)/$(TARGET)


exec: build
	$(RELEASE)/$(TARGET)


.PHONY: env clear


env:
	mkdir -pv $(CACHE)
	mkdir -pv $(RELEASE)


clear: 
	rm -rvf $(CACHE)


