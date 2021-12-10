#include<stdio.h>
#include<stdlib.h>
#ifndef __a
#define __a
#include "rule.h" //et donc world.h aussi.
#endif
#include<time.h>
#define MAX_RULES 30
#define MAX_COLOR 4294967295 //le plus grand entier sur 32 bits
#define BLANC 16777215
#define JAUNE 16776960



struct coord{
  int abs;
  int ord;};

struct file{
  struct coord xy;
  struct rule* regle;
  struct file* suite;
};

void file_init();
void afficher_premier_elt(struct file* f);
void ajouter_elt(struct file* f, struct coord co, struct rule* r);
void supprimer_premier_elt(struct file* f);
void afficher_file(struct file* f);


