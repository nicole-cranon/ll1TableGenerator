# nicole cranon <nicole.cranon@ucdenver.edu>
# csci 4640, fall 2015
# assignment 6 - predict generator
# makefile

CC=g++ -std=c++11
CFLAGS=-c -Wall -g
INC=-I include/

predict: main.o predictGenerator.o grammerAnalyzer.o 
	$(CC) main.o predictGenerator.o grammerAnalyzer.o -o predict

main.o: src/main.cpp
	$(CC) $(INC) $(CFLAGS) src/main.cpp -o main.o

predictGenerator.o: src/predictGenerator.cpp
	$(CC) $(INC) $(CFLAGS) src/predictGenerator.cpp -o predictGenerator.o

grammerAnalyzer.o: src/grammerAnalyzer.cpp
	$(CC) $(INC) $(CFLAGS) src/grammerAnalyzer.cpp -o grammerAnalyzer.o

clean:
	rm *.o -f; rm predict -f
