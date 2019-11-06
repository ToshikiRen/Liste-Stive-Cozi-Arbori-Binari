#ifndef ARBORI_H_INCLUDED
#define ARBORI_H_INCLUDED

#ifndef STRUCTURI_H_INCLUDED
#include "structuri.h"
#endif

#include <stdio.h>

p_arbore initializare_nod(p_echipa adresa_echipa);
void inorder_invers(p_arbore radacina, FILE *f);
p_arbore pozitia_de_inserat(p_arbore radacina, double valoare);
void leaga_de_arbore(p_arbore nod_parinte, p_arbore nod_fiu);
void sterge_arbore_si_date_aferente(p_arbore radacina);
p_arbore initializare_arbore(p_echipa adresa_inceput);
int inaltime(p_avl node);
int max(int x, int y);
p_avl rotatieDreapta(p_avl nod_de_rotit);
p_avl rotatieStanga(p_avl nod_de_rotit);
p_avl rotatieStangaDreapta(p_avl nod_de_rotit);
p_avl rotatieDreaptaStanga(p_avl nod_de_rotit);
p_avl adaugare_nod_in_avl(p_avl nod, p_echipa adresa_echipa);
int dist_to_root(p_avl nod, p_avl nod_de_cautat, int nivel);
void printLvL(p_avl root, p_avl nod, int nivel);
void eliberare_memorie_avl(p_avl root);
p_avl creare_avl(p_echipa date_pentru_avl);


#endif