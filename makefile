Engine: engine.cpp data-structures.cpp
	g++ engine.cpp data-structures.cpp -o Engine -lSDL2 -lSDL2main

run: Engine
	./Engine

.PHONY: run
