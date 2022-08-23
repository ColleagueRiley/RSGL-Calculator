OUTPUT = RSGL-Calculator
GXX = g++
SOURCE = source/*.cpp source/*.o
LIBS = $(shell RSGL-static)

build:
	make source/parser.o
	mkdir -p build
	$(GXX) $(SOURCE) $(LIBS) -o build/$(OUTPUT)
	cp -r res ./build

source/parser.o:
	$(GXX) source/parser/parser.cpp -c -o source/parser.o

install:
	chmod +x $(OUTPUT)
	cp $(OUTPUT) /usr/bin
	mkdir -p /usr/share/$(OUTPUT)
	cp -r build/* /usr/share/$(OUTPUT)
