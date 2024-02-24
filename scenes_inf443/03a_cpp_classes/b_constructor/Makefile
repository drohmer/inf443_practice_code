all: cpp_constructor

cpp_constructor: main.o
	g++ main.o -o cpp_constructor --std=c++14

main.o: src/main.cpp
	g++ -c src/main.cpp -o main.o --std=c++14

.PHONY: clean
clean:
	rm -f main.o cpp_constructor
