CC=gcc
CFLAGS1= -Wall -std=c99 -framework SDL2 -framework SDL2_image -framework SDL2_ttf
CFLAGS2= -Wall -std=c99 
EXEC1= Hex
EXEC2= Tests
OBJ1= main.o interface.o regles.o persistance.o plateau.o IA1.o
OBJ2=regles.o persistance.o plateau.o IA1.o test.o

game:	$(OBJ1)
	$(CC) $(CFLAGS1) $(OBJ1) -o $(EXEC1) 
 
tests: $(OBJ2)
	$(CC) $(CFLAGS2) $(OBJ2) -o $(EXEC2) 

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
test.o: test.c
		gcc -c test.c
IA1.o: IA/IA1.c 
		gcc -c IA/IA1.c

.PHONY: all clean maxclean
clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
