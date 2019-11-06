#ifndef COADA_STIVA_H
#define COADA_STIVA_H


#include <stdlib.h>
#include <stdio.h>

#ifndef STRUCTURI_H_INCLUDED
#include "structuri.h"
#endif



p_echipa pop_echipa(p_stack stiva);
p_echipa_stack element_nou_stiva(p_echipa adresa_echipa);
void push_echipa(p_echipa adresa_echipa, p_stack stiva);
p_stack stiva_din_lista(p_echipa adresa_inceput);
p_stack rastoarna_stiva(p_stack stiva);
p_meci meci_nou(p_echipa echipa1, p_echipa echipa2);
p_coada set_Coada();
void in_Coada(p_coada coada, p_meci de_adaugat_in_coada);
p_stack set_Stiva();
p_doua_echipe de_Queue(p_coada coada);
p_coada coada_noua(p_stack stiva);
void adauga_echipa_data_prin_adresa(p_echipa adresa_echipa, p_echipa *adresa_inceput_stiva);
void afisare_rezultate(FILE *f, p_stack stiva);
void afisare_meciuri(FILE *f, p_coada coada);
void goleste_stiva(p_stack stiva, int mode);
p_echipa primele_8_echipe(p_stack stiva);
void campionat(FILE *f, p_stack stiva, int *num, p_echipa *date_pentru_arbore);

#endif