build: 
	gcc -g tema.c amestec.c coada_stiva.c LISTE.c arbori.c -o lanParty
clean:
	rm -f *.o
	rm -f lanParty
