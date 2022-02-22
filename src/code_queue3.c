#include<stdio.h>
#include<stdlib.h>
#include "code_queue3.h"
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
  struct rule rs[MAX_RULES];
};

struct coord{
  int abs;
  int ord;
};

struct file{
  struct coord xy;
  struct rule* regle;
  struct file* next;
};

//a compiler avec src/rule3.c sans main donc compilation sur tst/test_queue3.c
//avec src.code_queue3.c (celui-la).

struct file f;
struct file ff;

void file_init(){//remplir la file avec un premier element de n'importe quoi
  f.xy.abs = -1;
  f.xy.ord = -1;//changements sur un couple imaginaire.
  f.regle = NULL;
  f.next = NULL;
  return;
}//la file vide(<=>1;2(propositions))
//est celle qui a 1 element : (-1,-1) NULL
//i.e. appliquer rien en un couple imaginaire.


void file_init2(){//remplir la file avec un premier element de n'importe quoi
  ff.xy.abs = -1;
  ff.xy.ord = -1;//changements sur un couple imaginaire.
  ff.regle = NULL;
  ff.next = NULL;
  return;
}//la file vide(<=>1;2(propositions))
//est celle qui a 1 element : (-1,-1) NULL
//i.e. appliquer rien en un couple imaginaire.

void afficher_premier_elt(struct file* f){
  if(f->next == NULL){
    printf("(%d,%d) -- %p\n", f->xy.abs, f->xy.ord, f->regle);
  }
  else{//f->next a afficher
      printf("(%d,%d) -- %p\n", f->next->xy.abs, f->next->xy.ord, f->next->regle);
  }
}

void ajouter_elt(struct file* f, struct coord co, struct rule* r){
  struct file* pointeur = f;//f->next accessible car f!=NULL ici.
    while(pointeur->next!=NULL){
      pointeur=pointeur->next;
    }
    pointeur->next = malloc(sizeof(struct file));
    (pointeur->next)->xy = co;
    (pointeur->next)->regle = r;
    (pointeur->next)->next = NULL;
}



void supprimer_premier_elt(struct file* f){
  if(f->next == NULL){//la file est vide elle est egale a -1,-1 NULL.
    return;
  }
    //f->next!=NULL
  else if(f->next->next == NULL){//1 element significatif dans la file.
    f->next = NULL;
    return;
  }
  else{//au moins de bons elements dans la file.
    f->next = f->next->next;
    return;
  }
}



void afficher_file(struct file* f){
  struct file* pointeur = f;
  while(pointeur != NULL){
    printf("(%d,%d);%p -- ", pointeur->xy.abs, pointeur->xy.ord, pointeur->regle); 
    pointeur = pointeur->next;
  }
  printf("\n");
}





  



