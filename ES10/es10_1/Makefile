CC = g++
CFLAGS = -Wall -O3 --std=c++11

main.exe : main.o random.o individual.o
	$(CC) random.o individual.o main.o -o main.exe
main.o : main.cpp main.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
individual.o : individual.cpp individual.h
	$(CC) -c individual.cpp -o individual.o $(CFLAGS)
clean :
	rm *.o main.exe seed.out
