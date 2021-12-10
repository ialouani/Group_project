#include<stdio.h>
#include<stdlib.h>
#ifndef __a
#define __a
#include "../src/code_queue2.h" //et donc world.h aussi.
#endif
#include<time.h>
#define MAX_RULES 30
#define MAX_COLOR 4294967295 //le plus grand entier sur 32 bits
#define BLANC 16777215
#define JAUNE 16776960
#define BLEU 255

struct rule{
  int couleurs_voisinages[9];
  int own_color;
  int new_color;
};

struct file f;

int main(){
  file_init();
  afficher_file(&f);
  //essayons d'ajouter sur la file.
  struct rule rule1={{BLANC,-1,-1,-1,-1,-1,-1,BLANC},BLEU,JAUNE};
  struct rule rule2={{BLANC,BLANC,-1,-1,-1,-1,-1,-1},BLANC,BLEU};
  struct rule rule3={{-1,-1,BLANC,-1,-1,-1,-1,-1},0,BLANC};
  struct rule rule4={{-1,-1,-1,-1,-1,-1,BLANC,-1},JAUNE,0};
  struct coord co1={2,2};
   struct coord co2={2,3};
    struct coord co3={1,4};
    struct coord co4={4,0};
    printf("-----------------------\n");
    ajouter_elt(&f,co1,&rule1);
    ajouter_elt(&f,co2,&rule2);
    ajouter_elt(&f,co3,&rule3);
    afficher_file(&f);
     printf("-----------------------\n");
    supprimer_premier_elt(&f);
    afficher_file(&f);
     printf("-----------------------\n");
    ajouter_elt(&f,co3,&rule3);
    ajouter_elt(&f,co4,&rule4);
    afficher_file(&f);
     printf("-----------------------\n");
     afficher_premier_elt(&f);
     afficher_file(&f);
      printf("-----------------------\n");
      supprimer_premier_elt(&f);
      supprimer_premier_elt(&f);
      supprimer_premier_elt(&f);
      supprimer_premier_elt(&f);
      afficher_file(&f);
  return 0;
}
  



