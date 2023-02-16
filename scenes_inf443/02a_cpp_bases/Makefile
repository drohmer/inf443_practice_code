all: cpp_bases

cpp_bases: main.o
	g++ main.o -o cpp_bases

main.o: src/main.cpp
	g++ -c src/main.cpp -o main.o

.PHONY: clean
clean:
	rm -f main.o cpp_bases
