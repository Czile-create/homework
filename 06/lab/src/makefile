all: main.o process.o readfile.o start.o main

process.o :
	g++ -c process.cpp -o process.o

readfile.o :
	g++ -c readfile.cpp -o readfile.o

start.o :
	g++ -c start.cpp -o start.o

main.o :
	g++ -c main.cpp -o main.o

main : process.o readfile.o start.o main.o
	g++ -std=c++14 process.o readfile.o start.o main.o -o main

clean:
	rm -rf process.o readfile.o start.o main.o