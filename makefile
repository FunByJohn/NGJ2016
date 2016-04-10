
all: build link
	./ngj

link:
	g++ *.o -o ngj -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

build:
	g++ -std=c++11 -c *.cpp

