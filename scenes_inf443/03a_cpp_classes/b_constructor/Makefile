all: cpp_constructor

cpp_constructor: main.o
	g++ main.o -o cpp_constructor

main.o: src/main.cpp
	g++ -c src/main.cpp -o main.o

.PHONY: clean
clean:
	rm -f main.o cpp_constructor
