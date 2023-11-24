FLAGS = -pedantic-errors -std=c++11

game.o: game.cpp
	g++ $(FLAGS) -c $<

game: game.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f game.o game

.PHONY clean
