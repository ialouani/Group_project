#include<stdio.h>
#include<stdlib.h>
#include "rule.h" 
#ifndef __trois
#define __trois
#include "code_queue.h"
#endif
#define BLANC 16777215
#define JAUNE 16776960
#include<time.h>
#define BLEU 255
#define ENTIER_MAX 4294967295
#define LEN_MAX 100

//a compiler (tests inclus) avec: gcc -std=c99 code_queue.c rule.c .




void create_random_world(struct world* monde, unsigned int seed);
void print_created_random_world(struct world* monde);
void world_init();

struct file f;

void queue_init(){//initialise la file qui est declaree avant.(en publique)
  //  struct rule_index couple_rxy[HEIGHT*WIDTH+1];
  struct rule_index rule_index1;
  rule_index1.xy[0]=-1;
  rule_index1.xy[1]=-1;
  struct rule rules2;
  int i=0;
  while(i<8){
    rules2.couleurs_voisins_utiles[i]=-1;i++;}
  int j=0;
  while(j<2){
    rules2.nouvelle_couleur[j]=-1;j++;}
  rules2.own_color=-1;
  rules2.next=NULL;
  rule_index1.rules=rules2;
  int k=0;
  while(k<HEIGHT*WIDTH){
    f.couple_rxy[k]=rule_index1;k++;}
  return;}

void display_rxy(struct rule_index rxy){
  printf("%d\t(%d;%d)\n",rxy.rules.nouvelle_couleur[0],rxy.xy[0],rxy.xy[1]);
}

void display_file(struct file f){
  int h=0;
  while(h<HEIGHT*WIDTH){
    display_rxy(f.couple_rxy[h]);h++;}
  return;}

int file_vide(struct file f){
  int l=0;
  /*struct rule_index rxy;
    rxy.xy[0]=-1;rxy.xy[1]=-1;
    int k=0;
    while(k<8){
      rxy.rules.couleurs_voisins_utiles[k]=-1;k++;}
    int p=0;
    while(p<2){
      rxy.rules.nouvelle_couleur[p]=-1;p++;}
    rxy.rules.own_color=-1;
    rxy.rules.next=NULL;*/
  //ça sert à rien ci-dessus(on vient de s'apercevoir de cela)
  //car on veut juste tester si existe index/f.couple_rxy[index].xy[0/1]===-1.
    while(l<HEIGHT*WIDTH){
      if(f.couple_rxy[l].xy[0]!=-1 && f.couple_rxy[l].xy[1]!=-1) return 0;
      l++;}
    return 1;} 

void ajout_file(struct file* f, struct rule_index couple){
  //ajouter à la fin de la file f le couple en $2.
  if(file_vide(*f)){
    f->couple_rxy[HEIGHT*WIDTH-1]=couple;
    return;}
  int len=0;int indice=-1;
  while(len<HEIGHT*WIDTH && indice<0){
    if(f->couple_rxy[len].xy[0]!=-1 && f->couple_rxy[len].xy[1]!=-1){
      indice=len;}
    len++;}
  //sortie: indice>=0  donc à cet indice demarrent les vraies valeurs.
  int debut=indice-1;
  for(int i=debut;i<HEIGHT*WIDTH-1;i++){
    f->couple_rxy[i]=f->couple_rxy[i+1];}
  f->couple_rxy[HEIGHT*WIDTH-1]=couple;
}



void delete_file(struct file* f){
struct rule_index rxy;
    rxy.xy[0]=-1;rxy.xy[1]=-1;
    int k=0;
    while(k<8){
      rxy.rules.couleurs_voisins_utiles[k]=-1;k++;}
    int p=0;
    while(p<2){
      rxy.rules.nouvelle_couleur[p]=-1;p++;}
    rxy.rules.own_color=-1;
    rxy.rules.next=NULL;
  int j=0;
  while(j<HEIGHT*WIDTH){
    if(f->couple_rxy[j].xy[0]!=-1 && f->couple_rxy[j].xy[1]!=-1){
      f->couple_rxy[j].xy[0]=-1;
      f->couple_rxy[j].xy[1]=-1;
      f->couple_rxy[j].rules=rxy.rules;
      return;}
    j++;}}

void afficher_head_queue(struct file *f){
  int k=0;
  while(f->couple_rxy[k].xy[0]==-1 && f->couple_rxy[k].xy[1]==-1){
    k++;}
  display_rxy(f->couple_rxy[k]);}


