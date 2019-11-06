#ifndef STRUCTURI_H_INCLUDED
#include "structuri.h"
#endif

#ifndef AMESTEC_H_INCLUDED
#include "amestec.h"
#endif

#ifndef LISTE_H_INCLUDED
#include "LISTE.h"	
#endif

#include <stdlib.h>
#include <stdio.h>
#include "coada_stiva.h"
#include <string.h>

p_echipa pop_echipa(p_stack stiva)
{
	if(stiva == NULL) return NULL;
	if(stiva->top != NULL)
	{
		p_echipa_stack de_sters = stiva->top;
		stiva->top = stiva->top->next;
		p_echipa echipa_de_returnat = de_sters->echipa;
		free(de_sters);
		return echipa_de_returnat;
	}
	return NULL;
}
p_echipa_stack element_nou_stiva(p_echipa adresa_echipa)
{
	p_echipa_stack nod = NULL;
	nod = (p_echipa_stack)malloc(sizeof(echipa_stack));
	if(nod == NULL)
	{
		fprintf(stderr, "Eroare la alocarea de memorie\n" );
		exit(1);
	}
	nod->echipa = adresa_echipa;
	nod->next = NULL;
	return nod;
}
void push_echipa(p_echipa adresa_echipa, p_stack stiva)
{
	p_echipa_stack nod = element_nou_stiva(adresa_echipa);
	nod->next = stiva->top;
	stiva->top = nod;
}
p_stack stiva_din_lista(p_echipa adresa_inceput)
{
	p_echipa copie_adresa_inceput = adresa_inceput;
	p_stack stiva = NULL;
	stiva = set_Stiva(); 
	while(copie_adresa_inceput != NULL)
	{
		push_echipa(copie_adresa_inceput, stiva);
		copie_adresa_inceput = copie_adresa_inceput->next;
	}
	stiva = rastoarna_stiva(stiva);
	return stiva;
}
p_stack rastoarna_stiva(p_stack stiva)
{
	p_stack stiva_rasturnata = NULL;
	stiva_rasturnata = set_Stiva();
	p_echipa nod = NULL;
	nod = pop_echipa(stiva);
	while(nod != NULL)
	{
		//printf("%s\n", "cool");
		push_echipa(nod, stiva_rasturnata);
		nod = pop_echipa(stiva);
	}
	free(stiva);
	return stiva_rasturnata;
}
p_meci meci_nou(p_echipa echipa1, p_echipa echipa2)
{
	p_meci nod = (p_meci)malloc(sizeof(meci));
	if(nod == NULL)
	{
		fprintf(stderr, "Eroare la alocarea de memorie\n");
		exit(1);
	}
	nod->echipa_1 = echipa1;
	nod->echipa_2 = echipa2;
	nod->next = NULL;

	return nod;
}
p_coada set_Coada()
{
	p_coada nod = (p_coada)malloc(sizeof(coada));
	if(nod == NULL)
	{
		fprintf(stderr, "Eroare la alocare\n");
		exit(1);
	}
	nod->adresa_inceput = nod->adresa_final = NULL;
	return nod;
}

void in_Coada(p_coada coada, p_meci de_adaugat_in_coada)
{
	if(coada->adresa_inceput == NULL)
	{
		coada->adresa_inceput = coada->adresa_final = de_adaugat_in_coada;
	}
	else
	{
		coada->adresa_final->next = de_adaugat_in_coada;
		coada->adresa_final = de_adaugat_in_coada;
	}
}

p_stack set_Stiva()
{
	p_stack stiva = NULL;
	stiva = (p_stack)malloc(sizeof(stack));
	if(stiva == NULL)
	{
		fprintf(stderr, "Eroare la alocarea de memorie\n" );
		exit(1);
	}
	stiva->top = NULL;
	return stiva;
}

p_doua_echipe de_Queue(p_coada coada)
{
	if(coada->adresa_inceput == NULL)
		return NULL;
	if(coada->adresa_inceput != NULL)
	{
		p_doua_echipe nod = NULL;
		nod = (p_doua_echipe)malloc(sizeof(doua_echipe));
		if(nod == NULL)
		{
			fprintf(stderr, "Eroare la alocarea de memorie\n");
			exit(1);
		}
		nod->echipa1 = coada->adresa_inceput->echipa_1;
		nod->echipa2 = coada->adresa_inceput->echipa_2;

		p_meci sterge_meci = NULL;
		sterge_meci = coada->adresa_inceput;
		coada->adresa_inceput = coada->adresa_inceput->next;
		free(sterge_meci);
		return nod;
	}


}

p_coada coada_noua(p_stack stiva)
{
	p_coada coada = set_Coada();
	p_echipa echipa1 = NULL, echipa2 = NULL;
	p_meci meci;
	echipa1 = pop_echipa(stiva);
	echipa2 = pop_echipa(stiva);
	while(echipa2 != NULL)
	{
		meci = meci_nou(echipa1, echipa2);
		in_Coada(coada, meci);
		echipa1 = pop_echipa(stiva);
		echipa2 = pop_echipa(stiva);
	}
	free(stiva);
	return coada;
}

void adauga_echipa_data_prin_adresa(p_echipa adresa_echipa, p_echipa *adresa_inceput_stiva)
{

	adresa_echipa->next = NULL;
	if(*adresa_inceput_stiva == NULL)
	{
		*adresa_inceput_stiva = adresa_echipa;
	}
	else
	{
		adresa_echipa->next = *adresa_inceput_stiva;
		*adresa_inceput_stiva = adresa_echipa;
	}
}

void afisare_rezultate(FILE *f, p_stack stiva)
{
	p_echipa_stack top = stiva->top;
	while(top != NULL)
	{
		fprintf(f, "%-25s ---% .2lf\n", top->echipa->nume, scor_echipa(top->echipa->adresa_inceput) );
		top = top->next;
	}
}
void afisare_meciuri(FILE *f, p_coada coada)
{
	p_meci adresa_inceput = coada->adresa_inceput;
	while(adresa_inceput != NULL)
	{
		fprintf(f, "%-25s -- %25s\n", adresa_inceput->echipa_1->nume, adresa_inceput->echipa_2->nume);
		adresa_inceput = adresa_inceput->next;
	}	
}
// mod == 1 sterge tot, mod == 0 sterge doar partea de p_echipa_stack
void goleste_stiva(p_stack stiva, int mode)
{
	if(mode == 1)
	{
		p_echipa adresa_echipa= pop_echipa(stiva);
		while(adresa_echipa != NULL)
		{
			sterge_echipa(&adresa_echipa);
			adresa_echipa = pop_echipa(stiva);
		}
	}
	else
	{
		p_echipa_stack adresa_echipa = NULL;

		while(stiva->top != NULL)
		{
			adresa_echipa =  stiva->top;	
			stiva->top = stiva->top->next;
			free(adresa_echipa);
		}
	}
	free(stiva);
}


p_echipa primele_8_echipe(p_stack stiva)
{
	p_echipa date_pentru_arbore = NULL;
	
	p_echipa_stack adresa_echipa = stiva->top;

	while( adresa_echipa != NULL )
	{
		adauga_echipa_data_prin_adresa(adresa_echipa->echipa, &date_pentru_arbore);
		adresa_echipa = adresa_echipa->next;
	}

	return date_pentru_arbore;
}


void campionat(FILE *f, p_stack stiva, int *num, p_echipa *date_pentru_arbore)
{
	if(*num == 1) return;
	p_stack castigatori = NULL;
	p_stack invinsi = NULL;
	castigatori = set_Stiva();
	invinsi = set_Stiva();
	p_coada coada = coada_noua(stiva);
	p_doua_echipe echipe = NULL;
	afisare_meciuri(f, coada);
	echipe = de_Queue(coada);
	while(echipe != NULL)
	{
		if(scor_echipa(echipe->echipa1->adresa_inceput) >= scor_echipa(echipe->echipa2->adresa_inceput))
		{
			adauga_1_la_scor(echipe->echipa1);
			push_echipa(echipe->echipa1, castigatori);
			push_echipa(echipe->echipa2, invinsi);
		}
		else
		{
			
			adauga_1_la_scor(echipe->echipa2);
			push_echipa(echipe->echipa2, castigatori);
			push_echipa(echipe->echipa1, invinsi);
		
		}
		free(echipe);
		echipe = de_Queue(coada);
	}
	free(coada);
	afisare_rezultate(f, castigatori);
	(*num) = (*num)/2;
	if(*num >= 8)
		goleste_stiva(invinsi, 1);
	else
		goleste_stiva(invinsi, 0);

	if(*num == 1)
		goleste_stiva(castigatori, 0);

	if(*num == 8)
	{
		*date_pentru_arbore = primele_8_echipe(castigatori);
		
	}
	campionat(f, castigatori, num, date_pentru_arbore);

}
