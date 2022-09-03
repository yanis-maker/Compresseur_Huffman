
CC=gcc
EXEC1=huf
EXEC2=dehuf
SOURCE=$(wildcar *.c)
OBJ=$(SOURCE:.c=.o)

all: mrproper huf dehuf clean

$(EXEC1): Compresseur-main.o Compresseur.o
	$(CC) $^ -o $@

Compresseur-main.o: Compresseur-main.c
	$(CC) $< -c 

Compresseur.o: Compresseur.c
	$(CC) $< -c

$(EXEC2): Decompresseur.c
	$(CC) $< -o $(EXEC2) 

clean:
	rm -rf *.o

mrproper: 
	rm -f unzip && rm -f $(EXEC1) && rm -f $(EXEC2) 

#SOURCE: Tous les fichier avec une extension .c
#OBJ: Tout les fichiers avec l'extension 
