#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED


#ifndef STRUCTURI_H_INCLUDED
#include "structuri.h"
#endif

#include <stdio.h>

p_jucator nod_nou(char *nume, char *prenume, int exp);
p_echipa echipa_noua(char *nume, int nr_membri, p_jucator adresa_inceput);
void adauga_echipa_la_inceput(char *nume, int nr_membri, p_jucator adresa_inceput, p_echipa *adresa_inceput_echipa);
void adauga_jucator_la_inceput(char *nume, char *prenume, int exp, p_jucator *adresa_inceput);
double scor_echipa(p_jucator adresa_inceput);
void adauga_1_la_scor(p_echipa adresa_echipa);
p_echipa creare_lista_cu_inserare_la_inceput(char *filename, int *nr_echipe);
void sterge_membri_echipei(p_jucator *adresa_inceput);
void sterge_echipa(p_echipa *adresa_elementului_pe_care_il_eliminam);
void afisare_normala(FILE *f, p_echipa adresa_inceput);
double minim_puncte(p_echipa adresa_inceput, int *nr);
void eliberare_memorie(p_echipa *adresa_inceput);
void elimina_echipe_pana_raman_2_la_k(p_echipa *adresa_inceput, int *nr_echipe);
#endif