all: cpp_classes

cpp_classes: main.o
	g++ main.o -o cpp_classes

main.o: src/main.cpp
	g++ -c src/main.cpp -o main.o

.PHONY: clean
clean:
	rm -f main.o cpp_classes
