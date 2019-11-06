#ifndef LISTE_H_INCLUDED
#include "LISTE.h"
#endif

#ifndef STRUCTURI_H_INCLUDED
#include "structuri.h"
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

p_arbore initializare_nod(p_echipa adresa_echipa)
{
	p_arbore nod = (p_arbore)malloc(sizeof(arbore));
	if(nod == NULL)
	{
		fprintf(stderr, "Eroare la alocarea de memorie\n" );
		exit(1);
	}
	nod->echipa = adresa_echipa;
	nod->right = nod->left = NULL;
	return nod;
}

void inorder_invers(p_arbore radacina, FILE *f)
{
	if(radacina != NULL)
	{
		inorder_invers(radacina->right, f);
		fprintf(f, "%-20s -- %.2lf\n", radacina->echipa->nume, scor_echipa(radacina->echipa->adresa_inceput));
		inorder_invers(radacina->left, f);
	}
}

p_arbore pozitia_de_inserat(p_arbore radacina, double valoare)
{

	if( fabs(scor_echipa(radacina->echipa->adresa_inceput) - valoare) < 0.001 )
		return NULL;

	else if( scor_echipa(radacina->echipa->adresa_inceput) < valoare && radacina->right != NULL)
			return pozitia_de_inserat(radacina->right, valoare);
		else if(radacina->right == NULL && scor_echipa(radacina->echipa->adresa_inceput) < valoare) 
			return radacina;
		else if(radacina->left != NULL)
			return pozitia_de_inserat(radacina->left, valoare);
		else
			return radacina;
}
void leaga_de_arbore(p_arbore nod_parinte, p_arbore nod_fiu)
{
	if( scor_echipa(nod_parinte->echipa->adresa_inceput) < scor_echipa(nod_fiu->echipa->adresa_inceput))
	{
		nod_parinte->right = nod_fiu;
	}	
	else
	{
		nod_parinte->left = nod_fiu;
	}
}
void sterge_arbore_si_date_aferente(p_arbore radacina)
{
	if(radacina == NULL) return;
	p_arbore de_sters = radacina;
	if(radacina != NULL)
	{
		sterge_arbore_si_date_aferente(radacina->left);
		sterge_arbore_si_date_aferente(radacina->right);
		free(de_sters);
	}
}
p_arbore initializare_arbore(p_echipa adresa_inceput)
{
	p_arbore radacina = initializare_nod(adresa_inceput);
	p_arbore pozitie_inserare;
	p_arbore nod_de_inserat;
	adresa_inceput = adresa_inceput->next;
	while(adresa_inceput != NULL)
	{
		nod_de_inserat = initializare_nod(adresa_inceput);
		pozitie_inserare = pozitia_de_inserat(radacina, scor_echipa(adresa_inceput->adresa_inceput) );
		adresa_inceput = adresa_inceput->next;
		if(pozitie_inserare != NULL)
			leaga_de_arbore(pozitie_inserare , nod_de_inserat);
		else
			free(nod_de_inserat);		

	}
	return radacina;
}


p_avl initializare_nod_avl(p_echipa adresa_echipa)
{
	p_avl nod = (p_avl)malloc(sizeof(avl));
	if(nod == NULL)
	{
		fprintf(stderr, "Eroare la alocarea de memorie\n" );
		exit(1);
	}
	nod->echipa = adresa_echipa;
	nod->left = nod->right = NULL;
	nod->height = 0;
	return nod;
}

int inaltime(p_avl node)
{
	if(node == NULL) return -1;
	return node->height;
}



int max(int x, int y)
{
	if(x > y) 
		return x;
	return y;
}

p_avl rotatieDreapta(p_avl nod_de_rotit)
{
	p_avl in_stanga_nodului = nod_de_rotit->left;
	p_avl in_dreapta = in_stanga_nodului->right;

	in_stanga_nodului->right = nod_de_rotit;
	nod_de_rotit->left = in_dreapta;

	nod_de_rotit->height = max(inaltime(nod_de_rotit->left), inaltime(nod_de_rotit->right)) + 1;
	in_stanga_nodului->height = max(inaltime(in_stanga_nodului->left), inaltime(in_stanga_nodului->right)) + 1;

	return in_stanga_nodului;
}

p_avl rotatieStanga(p_avl nod_de_rotit)
{
	p_avl in_dreapta_nodului = nod_de_rotit->right;
	p_avl in_stanga = in_dreapta_nodului->left;

	in_dreapta_nodului->left = nod_de_rotit;
	nod_de_rotit->right = in_stanga;

	nod_de_rotit->height = max(inaltime(nod_de_rotit->left), inaltime(nod_de_rotit->right)) + 1;
	in_dreapta_nodului->height = max(inaltime(in_dreapta_nodului->left), inaltime(in_dreapta_nodului->right)) + 1;

	return in_dreapta_nodului;

}

p_avl rotatieStangaDreapta(p_avl nod_de_rotit)
{
	nod_de_rotit->left = rotatieStanga(nod_de_rotit->left);
	return rotatieDreapta(nod_de_rotit);
}
p_avl rotatieDreaptaStanga(p_avl nod_de_rotit)
{
	nod_de_rotit->right = rotatieDreapta(nod_de_rotit->right);
	return rotatieStanga(nod_de_rotit);
}

p_avl adaugare_nod_in_avl(p_avl nod, p_echipa adresa_echipa)
{
	if(nod == NULL)
	{
		nod = initializare_nod_avl(adresa_echipa);
		return nod;
	}
	else if( scor_echipa(adresa_echipa->adresa_inceput) < scor_echipa(nod->echipa->adresa_inceput) )
			nod->left =  adaugare_nod_in_avl(nod->left, adresa_echipa);
	else if(scor_echipa(adresa_echipa->adresa_inceput) > scor_echipa(nod->echipa->adresa_inceput))
			nod->right =  adaugare_nod_in_avl(nod->right, adresa_echipa);
	else return nod;

	nod->height = max(inaltime(nod->left), inaltime(nod->right)) + 1;

	int k = inaltime(nod->left) - inaltime(nod->right);

	if(k > 1 && scor_echipa(adresa_echipa->adresa_inceput) < scor_echipa(nod->left->echipa->adresa_inceput))
		return rotatieDreapta(nod);
	else if(k > 1 && scor_echipa(adresa_echipa->adresa_inceput) > scor_echipa(nod->left->echipa->adresa_inceput))
		return rotatieStangaDreapta(nod);
	else if(k < -1 && scor_echipa(adresa_echipa->adresa_inceput) < scor_echipa(nod->right->echipa->adresa_inceput))
		return rotatieDreaptaStanga(nod);
	else if(k < -1 && scor_echipa(adresa_echipa->adresa_inceput) > scor_echipa(nod->right->echipa->adresa_inceput))
		return rotatieStanga(nod);

	return nod;

}
int dist_to_root(p_avl nod, p_avl nod_de_cautat, int nivel)
{
	if(nod == nod_de_cautat) return nivel;
	if(nod!= NULL)
	{
		int k1;
		k1 = dist_to_root(nod->left, nod_de_cautat, nivel + 1) ;
		if(k1 != 0)
			return k1;
		k1 = dist_to_root(nod->right, nod_de_cautat, nivel + 1) ;
		return k1;
	}
	return 0;
}
void printLvL(p_avl root, p_avl nod, int nivel)
{
	if(root)
	{
		printLvL(root->left, nod, nivel);
		printLvL(root->right, nod, nivel);
		if(nivel == dist_to_root(nod, root, 0))
			printf("%s nivel %d \n", root->echipa->nume, dist_to_root(nod, root, 0));

	/*	if(root->height == nivel) 
			printf("%d ", root->data);
	*/}
}

void eliberare_memorie_avl(p_avl root)
{
	p_avl de_sters = root;
	if(root != NULL)
	{
		eliberare_memorie_avl(root->left);
		eliberare_memorie_avl(root->right);
		free(de_sters);
	}

}

p_avl creare_avl(p_echipa date_pentru_avl)
{
	p_avl root = NULL;
	p_echipa adresa_echipa = date_pentru_avl;
	while(adresa_echipa != NULL)
	{
		root = adaugare_nod_in_avl(root, adresa_echipa);
		adresa_echipa = adresa_echipa->next;
	}
	return root;
}