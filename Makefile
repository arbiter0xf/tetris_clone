SRC := main.cpp Block.cpp Game.cpp Shape.cpp
OBJ := $(SRC:.c=.o)

all:
	g++-10 -c $(SRC) ; g++ $(OBJ) -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
