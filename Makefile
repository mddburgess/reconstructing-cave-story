compile:
	clang++ -o gen/cavestory src/**.cc -std=c++14 -lSDL2 -lboost_system

run:
	gen/cavestory

all: compile run
