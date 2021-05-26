all: main.o process.o readfile.o start.o hzip

process.o : process.cpp process.h
	g++ -c process.cpp -o process.o

readfile.o : readfile.cpp readfile.h
	g++ -c readfile.cpp -o readfile.o

start.o : start.cpp start.h
	g++ -c start.cpp -o start.o

main.o : main.cpp
	g++ -c main.cpp -o main.o

hzip : process.o readfile.o start.o main.o
	g++ -std=c++14 process.o readfile.o start.o main.o -o hzip

clean:
	rm -rf process.o readfile.o start.o main.o