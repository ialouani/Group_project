#include<stdio.h>
#include<stdlib.h>
#ifndef __T
#define __T
#include "../src/code_queue3.h" 
#endif
#define LEN_MAX 100
#include <time.h>
#define ENTIER_MAX 4294967295
#define MAX_RULES 50
#define BLEU 255
#define BLANC 16777215
#define JAUNE 16776990

struct rule{
  int voisins[9];
  int own_color;
  int new_color[LEN_MAX];
  int dx[LEN_MAX];
  int dy[LEN_MAX];
};


struct rules{
  struct rule rs[MAX_RULES];};

struct coord{
  int abs;
  int ord;
};

struct file{
  struct coord xy;
  struct rule* regle;
  struct file* next;
};

struct file f;
struct rules regles;
struct world ww;
void create_random_world(struct world* monde, unsigned int seed);
void print_created_random_world(struct world* monde);
void world_init();

int main(int argc, char* argv[]){
  rules_init();
  printf("la nouvelle couleur de la 1ere regle est: %d\n----------\n",regles.rs[0].new_color[0]);
  world_init();
  printf("%d %d\n",HEIGHT,WIDTH);
  print_created_random_world(&ww);
  printf("-----------------\n\n");
  //testons le fonctions sur la file maintenant:
  file_init();
  printf("La file initiale:(f):\n");
  afficher_file(&f);
  struct coord coord1={2,2};
  struct rule* rule0=rule_get(0);
  ajouter_elt(&f,coord1,rule0);
  printf("\n\nLa file (f) apres l'ajout de (2,2);&(regles.rs[0])\n");
  afficher_file(&f);
  struct coord coord2={3,3};
  struct coord coord3={4,4};
  struct rule* rule1=rule_get(1);
  struct rule* rule2=rule_get(2);
  ajouter_elt(&f,coord2,rule1);
  ajouter_elt(&f,coord3,rule2);
  printf("----------ajout de 2 autres elements:----------\n\n\n");
  afficher_file(&f);
  printf("\n\n\n\n");
  //existent 5 fonctions: on a teste: file_init
  //afficher_file ; ajouter_elt ; restent::>
  //afficher_premier_elt et supprimer_premier_el.
  printf("first element:\n");
  afficher_premier_elt(&f);
  printf("\n test de la fonction supprimer:\n");
  supprimer_premier_elt(&f);
  afficher_file(&f);
  printf("\nOn supprime tous les element de la file manuellement maintenant:\n");
  supprimer_premier_elt(&f);
  supprimer_premier_elt(&f);
  printf("La nouvelle file sera:\n");
  afficher_file(&f);
  //On recommence.
  ajouter_elt(&f,coord2,rule1);
  ajouter_elt(&f,coord3,rule2);
  afficher_file(&f);
  printf("recommence:\n");
   supprimer_premier_elt(&f);
   afficher_file(&f);
   //toutes les 5 fonctions de la structure file ont ete testees.
  return 0;}
