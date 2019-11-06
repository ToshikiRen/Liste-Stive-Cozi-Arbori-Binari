#ifndef STRUCTURI_H_INCLUDED
#define STRUCTURI_H_INCLUDED


typedef struct juc
{
	char *nume;
	char *prenume;
	int exp;
	struct juc *next;
}jucator, *p_jucator;

typedef struct ech
{
	char *nume;
	// nu are rost sa tin minte nr de jucatori...
	int nr_membri;
	//float puncte;
	p_jucator adresa_inceput;
	struct ech *next;
}echipa, *p_echipa;

typedef struct avl
{
	p_echipa echipa;
	struct avl *left, *right;
	int height;
}avl, *p_avl;

typedef struct st
{
	p_echipa echipa;
	struct st *next;
}echipa_stack, *p_echipa_stack;

typedef struct 
{
	echipa_stack *top;
}stack, *p_stack;
typedef struct arb
{
	p_echipa echipa;
	struct arb *left, *right;
}arbore, *p_arbore;

typedef struct mec
{
	echipa *echipa_1;
	echipa *echipa_2;
	struct mec *next;
}meci, *p_meci;

typedef struct dq
{
	p_echipa echipa1;
	p_echipa echipa2;
}doua_echipe, *p_doua_echipe;

typedef struct 
{
	p_meci adresa_inceput;
	p_meci adresa_final;
}coada, *p_coada;



#endif







