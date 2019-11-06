

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void elimina_enter(char *sir)
{
	int i;
	i = strlen(sir) - 1;
	if(sir[i] == '\n') 
		sir[i] = '\0';
}
int putere_a_lui_2(int numar)
{
	int i, k, ultimul_bit_de_1;
	
	if(numar == 1) return 0;
	for(i = 0; i < 8 * sizeof(int); i++)
	{
		k = numar >> i;
		if(k&1) 
		{
			ultimul_bit_de_1 = (k << i) ;
		}
	}
	return ultimul_bit_de_1;

}
FILE* deschide_fisier(char *filename, char *mod)
{
	FILE *f_ptr = fopen(filename, mod);
	if(f_ptr == NULL)
	{
		fprintf(stderr, "Fisierul %s nu a fost deschis ! \n", filename);
		exit(1);
	}
	return f_ptr;
}
