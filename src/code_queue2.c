#include <stdio.h>
#include <stdlib.h>
#ifndef __a
#define __a
#include "code_queue2.h" //et donc world.h aussi.
#endif
#include<time.h>
#define MAX_RULES 30
#define MAX_COLOR 4294967295 //le plus grand entier sur 32 bits
#define BLANC 16777215
#define JAUNE 16776960

struct rule{
  int couleurs_voisinages[9];
  int own_color;
  int new_color;
};

struct rules{
  struct rule r[MAX_RULES];
};

struct file f;

struct rule rule0={{-1,-1,-1,-1,-1,-1,-1,-1}, -1, -1};

void file_init(){
  //initialise la file chainee.
  //forcement doit remplir la file f car pas declaration pointeur &f...
  f.xy.abs = -1;
  f.xy.ord = -1;//le dernier de la file avant le NULL marquant la fin de la file
  //et ne servant a rien car pas reel.(c'est oblige car la file chainee vide
  //ne peut pas suivant ce qu'on a fait ici faire en sorte que la fonction
  //LUI RETOURNE NULL.)
  f.regle = &rule0;
  f.suite = NULL;}

void afficher_premier_elt(struct file* f){
   printf("(%d;%d) %d \n", f->xy.abs, f->xy.ord,(f->regle)->new_color);
}

void ajouter_elt(struct file* f, struct coord co, struct rule* r){
  struct file* pointeur = f;
  while(pointeur->suite != NULL){
    pointeur = pointeur->suite;
  }
  pointeur->suite=malloc(sizeof(struct file));
  
  (pointeur->suite)->suite = NULL;
  (pointeur->suite)->xy = co;
  (pointeur->suite)->regle = r;
}

void supprimer_premier_elt(struct file* f){
  f->xy = (f->suite)->xy;
  f->regle = (f->suite)->regle;
  f->suite = (f->suite)->suite;
}

void afficher_file(struct file* f){
  struct file* pointeur = f;
  while (pointeur != NULL){

    printf("(%d;%d)/ %d -- ", pointeur->xy.abs, pointeur->xy.ord, pointeur->regle->new_color);
    pointeur = pointeur->suite;
  }

  printf("\n");

}









  
