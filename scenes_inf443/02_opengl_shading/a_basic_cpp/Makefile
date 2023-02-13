all: 01_basic_cpp

01_basic_cpp: main.o
	g++ main.o -o 01_basic_cpp

main.o: src/main.cpp
	g++ -c src/main.cpp -o main.o

.PHONY: clean
clean:
	rm -f main.o 01_basic_cpp
