
#ifndef STRUCTURI_H_INCLUDED
#include "structuri.h"
#endif

#ifndef AMESTEC_H_INCLUDEDaf
#include "amestec.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

p_jucator nod_nou(char *nume, char *prenume, int exp)
{
	p_jucator nod = (p_jucator)malloc(sizeof(jucator));
	nod->nume = malloc((strlen(nume) + 1) * sizeof(char));
	if(nod->nume == NULL)
	{
		fprintf(stderr, "Eroare la alocarea de memorie\n");
		exit(1);
	}
	strcpy(nod->nume, nume);
	nod->prenume = malloc((strlen(prenume) + 1) * sizeof(char));
	if(nod->prenume == NULL)
	{
		fprintf(stderr, "Eroare la alocarea de memorie\n");
		exit(1);
	}	
	strcpy(nod->prenume, prenume);
	nod->exp = exp;
	nod->next = NULL;
	return nod;
}
p_echipa echipa_noua(char *nume, int nr_membri, p_jucator adresa_inceput)
{
	p_echipa nod = (p_echipa)malloc(sizeof(echipa));
	if(nod == NULL)
	{
		fprintf(stderr, "Eroare la alocarea de memorie\n" );
		exit(1);
	}
	nod->nume = malloc((strlen(nume) + 1) * sizeof(char));
	if(nod->nume == NULL)
	{
		fprintf(stderr, "Eroare la alocarea de memorie\n");
		exit(1);
	}
	strcpy(nod->nume, nume);
	nod->nr_membri = nr_membri;
	nod->adresa_inceput = adresa_inceput;
	nod->next = NULL;
	return nod;
}

void adauga_echipa_la_inceput(char *nume, int nr_membri, p_jucator adresa_inceput, p_echipa *adresa_inceput_echipa)
{
	if(*adresa_inceput_echipa == NULL)
	{
		*adresa_inceput_echipa = echipa_noua(nume, nr_membri, adresa_inceput);
	}
	else
	{
		p_echipa nod;
		nod = echipa_noua(nume, nr_membri, adresa_inceput);
		nod->next = *adresa_inceput_echipa;
		*adresa_inceput_echipa = nod;

	}

}

void adauga_jucator_la_inceput(char *nume, char *prenume, int exp, p_jucator *adresa_inceput)
{
	if( *adresa_inceput == NULL )
	{
		*adresa_inceput = nod_nou(nume, prenume, exp);
	}
	else
	{
		p_jucator membru = nod_nou(nume, prenume, exp);
		membru->next = *adresa_inceput;
		*adresa_inceput = membru;
	}
}
void adauga_1_la_scor(p_echipa adresa_echipa)
{
	p_jucator copie_adresa_inceput = adresa_echipa->adresa_inceput;
	//adresa_echipa->puncte++;
	while(copie_adresa_inceput != NULL)
	{
		copie_adresa_inceput->exp ++;
		copie_adresa_inceput = copie_adresa_inceput->next;
	}
}
double scor_echipa(p_jucator adresa_inceput)
{
	if(adresa_inceput == NULL) return 10000;
	double total = 0;
	int nr = 0;
	while(adresa_inceput != NULL)
	{
		nr++;
		total += adresa_inceput->exp;
		adresa_inceput = adresa_inceput->next;
	}
	return total/nr;
}

p_echipa creare_lista_cu_inserare_la_inceput(char *filename, int *nr_echipe)
{
	FILE *f = deschide_fisier(filename, "rt");
	p_jucator adresa_inceput = NULL;
	p_echipa adresa_inceput_echipa = NULL;
	char buffer_nume[100], buffer_prenume[100];
	char buffer_nume_echipa[100];
	int exp;
	int i, j;
	int nr_membri;
	//double puncte = 0;
	fscanf(f, "%d", nr_echipe);
	for(i = 0; i < *nr_echipe; i++)
	{
		
		fscanf(f, "%d", &nr_membri);
		fgets(buffer_nume_echipa, 99, f);
		elimina_enter(buffer_nume_echipa);
		for(j = 0; j < nr_membri; j++)
		{
			fscanf(f, "%s", buffer_nume);
			fscanf(f, "%s", buffer_prenume);
			fscanf(f, "%d", &exp);
			//puncte += exp;
			adauga_jucator_la_inceput(buffer_nume, buffer_prenume, exp, &adresa_inceput);
		}
		adauga_echipa_la_inceput(buffer_nume_echipa, nr_membri, adresa_inceput, &adresa_inceput_echipa);
		//adresa_inceput_echipa->puncte = puncte/nr_membri;
		//printf("%f\n", adresa_inceput_echipa->puncte);
		adresa_inceput = NULL;
	}
	fclose(f);
	return adresa_inceput_echipa;
}

void sterge_membri_echipei(p_jucator *adresa_inceput)
{
	p_jucator copie_adresa_inceput = *adresa_inceput;
	p_jucator de_sters;
	while(copie_adresa_inceput != NULL)
	{
		de_sters = copie_adresa_inceput;
		free(de_sters->nume);
		free(de_sters->prenume);
		copie_adresa_inceput = copie_adresa_inceput->next;
		free(de_sters);
	}
	*adresa_inceput = NULL;
}
void sterge_echipa(p_echipa *adresa_elementului_pe_care_il_eliminam)
{
	if(*adresa_elementului_pe_care_il_eliminam == NULL) return;
	sterge_membri_echipei(&(*adresa_elementului_pe_care_il_eliminam)->adresa_inceput);
	free((*adresa_elementului_pe_care_il_eliminam)->nume);			
	free(*adresa_elementului_pe_care_il_eliminam);
	*adresa_elementului_pe_care_il_eliminam = NULL;
}
void afisare_normala(FILE *f, p_echipa adresa_inceput)
{
	if(adresa_inceput != NULL)
	{
		fprintf(f, "%s\n", adresa_inceput->nume);
		afisare_normala(f, adresa_inceput->next);
	}	
}
double minim_puncte(p_echipa adresa_inceput, int *nr)
{
	double min_puncte;
	p_echipa copie_adresa_inceput = adresa_inceput;
	min_puncte = scor_echipa(copie_adresa_inceput->adresa_inceput);
	while(copie_adresa_inceput != NULL)
	{
		if(scor_echipa(copie_adresa_inceput->adresa_inceput) < min_puncte)
		{
			min_puncte = scor_echipa(copie_adresa_inceput->adresa_inceput);
			*nr = 1;
		}
		else if(fabs(scor_echipa(copie_adresa_inceput->adresa_inceput) - min_puncte) < 0.0001) 
			(*nr)++;
		copie_adresa_inceput = copie_adresa_inceput->next;
	}
	return min_puncte;
}

void eliberare_memorie(p_echipa *adresa_inceput)
{
	p_echipa de_sters;
	while( *adresa_inceput != NULL )
	{
		de_sters = *adresa_inceput;
		*adresa_inceput = (*adresa_inceput)->next;
		sterge_echipa(&de_sters);
	}
	*adresa_inceput = NULL;
}

void elimina_echipe_pana_raman_2_la_k(p_echipa *adresa_inceput, int *nr_echipe)
{
	int nr_m = 0;
	int trebuie_sa_eliminam = *nr_echipe - putere_a_lui_2(*nr_echipe);
	(*nr_echipe) -= trebuie_sa_eliminam;
	double min_puncte;
	p_echipa copie_adresa_inceput = NULL;
	p_echipa adresa_elementului_pe_care_il_eliminam = NULL;
	p_echipa inainte_de_ce_sterg = NULL;

	while(trebuie_sa_eliminam > 0)
	{		
		min_puncte = minim_puncte(*adresa_inceput, &nr_m);
		if(copie_adresa_inceput == NULL) 
			copie_adresa_inceput = *adresa_inceput;
		while(fabs(scor_echipa((*adresa_inceput)->adresa_inceput) - min_puncte ) < 0.00001)
		{
			adresa_elementului_pe_care_il_eliminam = *adresa_inceput;
			(*adresa_inceput) = (*adresa_inceput)->next;
			sterge_echipa(&adresa_elementului_pe_care_il_eliminam);
			copie_adresa_inceput = *adresa_inceput;
			nr_m--;
			trebuie_sa_eliminam--;
			if(trebuie_sa_eliminam == 0 || nr_m == 0) break;
		}
				
		while(trebuie_sa_eliminam > 0 && nr_m > 0)
		{
			if(fabs( scor_echipa(copie_adresa_inceput->adresa_inceput) - min_puncte) < 0.00001)
			{
				adresa_elementului_pe_care_il_eliminam = copie_adresa_inceput;
				copie_adresa_inceput = copie_adresa_inceput->next;
				if(adresa_elementului_pe_care_il_eliminam->next == NULL)
					inainte_de_ce_sterg->next = NULL;
				else 
					inainte_de_ce_sterg->next = inainte_de_ce_sterg->next->next;
				sterge_echipa(&adresa_elementului_pe_care_il_eliminam);
				trebuie_sa_eliminam--;
				nr_m--;
			}
			else
			{
				inainte_de_ce_sterg = copie_adresa_inceput;
				copie_adresa_inceput = copie_adresa_inceput->next;
			}

			if(copie_adresa_inceput == NULL)
				copie_adresa_inceput = *adresa_inceput;

		}
	}
}
