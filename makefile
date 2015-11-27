# nicole cranon <nicole.cranon@ucdenver.edu>
# csci 4640, fall 2015
# assignment 7 - ll1 table generator
# makefile

CC=g++ -std=c++11
CFLAGS=-c -Wall -g
INC=-I include/

ll1generate: main.o predictGenerator.o grammerAnalyzer.o generator.o helper.o
	$(CC) main.o predictGenerator.o grammerAnalyzer.o generator.o helper.o -o ll1generate

main.o: src/main.cpp
	$(CC) $(INC) $(CFLAGS) src/main.cpp -o main.o

generator.o: src/generator.cpp
	$(CC) $(INC) $(CFLAGS) src/generator.cpp -o generator.o

predictGenerator.o: src/predictGenerator.cpp
	$(CC) $(INC) $(CFLAGS) src/predictGenerator.cpp -o predictGenerator.o

grammerAnalyzer.o: src/grammerAnalyzer.cpp
	$(CC) $(INC) $(CFLAGS) src/grammerAnalyzer.cpp -o grammerAnalyzer.o

helper.o: src/helper.cpp
	$(CC) $(INC) $(CFLAGS) src/helper.cpp -o helper.o

clean:
	rm *.o -f; rm ll1generate -f
