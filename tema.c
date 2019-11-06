#include "structuri.h"
#include "amestec.h"
#include "LISTE.h"
#include "coada_stiva.h"
#include <stdio.h>
#include <stdlib.h>
#include "arbori.h"

int main(int argc, char *args[])
{

	int num;
	p_avl root = NULL;
	p_arbore radacina = NULL;
	p_echipa date_pentru_arbore = NULL;
	p_echipa adresa_inceput;
	adresa_inceput = creare_lista_cu_inserare_la_inceput(args[2], &num);

    FILE *f, *fp;
    fp = deschide_fisier(args[3], "wt");
    f = deschide_fisier(args[1], "rt");

    int cerinta;
	fscanf(f, "%d", &cerinta);
    fscanf(f, "%d", &cerinta);
    if(cerinta == 1)
    {
    	elimina_echipe_pana_raman_2_la_k(&adresa_inceput, &num);
    }
		afisare_normala(fp, adresa_inceput);


    fscanf(f, "%d", &cerinta);
	if(cerinta == 1)
	{
		p_stack stiva = stiva_din_lista(adresa_inceput);
		campionat(fp, stiva, &num, &date_pentru_arbore);
	}
	else
		eliberare_memorie(&adresa_inceput);

	   fscanf(f, "%d", &cerinta);
	if(cerinta == 1)
	{
		radacina = initializare_arbore(date_pentru_arbore);
		inorder_invers(radacina, fp);
	}
	fscanf(f, "%d", &cerinta);
	if(cerinta == 1)
	{
		root = creare_avl(date_pentru_arbore);
		//inorder_invers(radacina, stderr);
		printLvL(root, root , 2);
		//root = NULL;
	}
		fclose(fp);
		fclose(f);
		eliberare_memorie(&date_pentru_arbore);
		eliberare_memorie_avl(root);
		sterge_arbore_si_date_aferente(radacina);
	 return 0;
}
