all: src/main.cpp build/mandel.o build/timer.o
	clang++ src/main.cpp build/mandel.o build/timer.o -o bin/mandel -O2 -lpng -std=c++0x

build/mandel.o: src/mandel.cpp src/mandel.h
	clang++ src/mandel.cpp -c -o build/mandel.o -O2 -std=c++0x

build/timer.o: src/timer.cpp src/timer.h
	clang++ src/timer.cpp -c -o build/timer.o -O2 -std=c++0x

clean:
	rm build/* bin/*
