#include<stdio.h>
#include<stdlib.h>
#ifndef __a
#define __a
#include "rule.h"
#endif
#define BLANC 16777215
#define JAUNE 16776960
#include<time.h>
#define BLEU 255
#define ENTIER_MAX 4294967295
#define LEN_MAX 100

struct rule{
  int couleurs_voisins_utiles[9];
  int nouvelle_couleur[LEN_MAX+2];
  int own_color;
  struct rule* next;
};

struct rule rules1;


struct rule_index{
  struct rule rules;
  int xy[3]; //structure representant le couple (r,(x,y)).
};

struct file{
  struct rule_index couple_rxy[HEIGHT*WIDTH+1];
};
//la file sera une structure qui se resume en un tableau de structures 
//ou chaque structure est une valeur typée de struct rule_index


void queue_init();
void display_rxy(struct rule_index rxy);
void display_file(struct file f);
int file_vide(struct file f);
void ajout_file(struct file* f, struct rule_index couple);
void delete_file(struct file* f);
void afficher_head_queue(struct file* f);
