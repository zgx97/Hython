
.PHONY: clean

TARGET='./bin/hython'
DEFS = -DDEUG

all: 
	cd ./thirdpart && make
	g++ -g -Wall -std=c++11 $(DEFS) *.cpp ./src/*.cc ./thirdpart/*.c ./thirdpart/libs/libantlr3c.a -o $(TARGET) -I./include -I ./thirdpart/include -I ./thirdpart/
	$(TARGET) ./bin/program1.hl
	$(TARGET) ./bin/program2.hl

clean:
	rm -rf $(TARGET)
