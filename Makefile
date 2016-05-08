CC=gcc
CFLAGS= -Wall -std=c99 -framework SDL2 -framework SDL2_image -framework SDL2_ttf
EXEC= Hex
OBJ= main.o interface.o regles.o persistance.o plateau.o IA1.o

all:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC) 

main.o: main.c 
		gcc -c main.c
interface.o: Interface/interface.c 
		gcc -c Interface/interface.c
regles.o: Regles/regles.c 
		gcc -c Regles/regles.c
persistance.o: Persistance/persistance.c 
		gcc -c Persistance/persistance.c
plateau.o: Structure/plateau.c 
		gcc -c Structure/plateau.c
IA1.o: IA/IA1.c 
		gcc -c IA/IA1.c

.PHONY: all clean maxclean
clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
