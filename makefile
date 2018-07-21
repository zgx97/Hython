.PHONY: clean

DEFS = -DDEUG
TARGET='./bin/hy_run'
LIBPATH='./thirdpart/libs/libantlr3c-3.4/.libs/libantlr3c.a'

all: 
	cd ./thirdpart && make
	g++ -g -std=c++11 -Wall *.cpp ./src/*.cc ./thirdpart/*.c $(LIBPATH) -o $(TARGET) -I./include -I ./thirdpart/include -I ./thirdpart/

clean:
	rm -rf $(TARGET)
