
#FLAGS=-g -pg 
#optimizaciones 
FLAGS=-O3
all: main.o filtros.o
	gcc $(FLAGS) main.o filtros.o -o main.exe

main.o: main.c
	gcc $(FLAGS) -c main.c -o main.o

filtros.o: filtros.c
	gcc $(FLAGS) -c filtros.c -o filtros.o

clean:
	rm *.o main.exe
