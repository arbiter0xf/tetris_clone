
all:
	g++-10 -c main.cpp ; g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
