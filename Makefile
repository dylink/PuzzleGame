
Puzzle: main.o plateau.o jeu.o fonctions.o
	gcc -Wall -o Puzzle main.o plateau.o jeu.o fonctions.o

main.o: main.c plateau.c plateau.h jeu.c fonctions.c
	gcc -Wall -o main.o -c main.c

plateau.o: plateau.c plateau.h
	gcc -Wall -o plateau.o -c plateau.c

jeu.o: jeu.c plateau.h
	gcc -Wall -o jeu.o -c jeu.c

fonctions.o: fonctions.c plateau.h
	gcc -Wall -o fonctions.o -c fonctions.c

clean:
	rm -v -f *.o *~core
mrproper: clean
	rm -v -f Puzzle
