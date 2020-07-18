Engine: engine.cpp
	g++ engine.cpp -o Engine -lSDL2 -lSDL2main

run: Engine
	./Engine

.PHONY: run
