compile:
	clang++ -o gen/cavestory src/**.cc -std=c++14 -lSDL2

run:
	gen/cavestory

all: compile run
