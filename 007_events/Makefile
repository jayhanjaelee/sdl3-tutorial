all: main run

main: main.cpp
	bear -- clang++ -o main main.cpp `pkg-config --cflags --libs sdl3`

run:
	./main

.PHONY: clean

clean:
	@rm -f main

