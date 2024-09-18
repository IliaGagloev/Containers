
run: test
	./test
run2: test2
	./test2
test: spisok.o vector.o Stack.o
	g++ spisok.o vector.o Stack.o -o test -L./ -lStackTest
test2:spisok.o vector.o Stack.o main.o
	g++ main.o spisok.o vector.o Stack.o -o test2

main.o: main.cpp
	g++ main.cpp -c

spisok: spisok.cpp
	g++ spisok.cpp -c

vector.o: vector.cpp
	g++ vector.cpp -c

Stack.o: Stack.cpp
	g++ Stack.cpp -c

clean:
	rm Stack.o main.o spisok.o vector.o test2 test
