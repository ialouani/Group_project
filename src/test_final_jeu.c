#include<stdio.h>
#include<stdlib.h>
#ifndef __F
#define __F
#include "code_queue.h"
#endif
//indirectement on inclut le fichier world.h.
//a compiler avec rule.c et code_queue.c (pour avoir le resultat)
#define BLANC 16777215
#define JAUNE 16776960
#include<time.h>
#define BLEU 255
#define ENTIER_MAX 4294967295
#define LEN_MAX 100

void create_random_world(struct world* monde, unsigned int seed);
void print_created_random_world(struct world* monde);
void world_init();

struct world ww;
struct rule rules1;
struct file f;

void jeu(){
for(int i=0;i<HEIGHT;i++){
for(int j=0;j<WIDTH;j++){
if(rule_match(&ww,&rules1,i,j)){
struct rule_index couple;
couple.rules=rules1;
couple.xy[0]=i;
couple.xy[1]=j;
ajout_file(&f,couple);}}}
int index=0;
while(f.couple_rxy[index].xy[0]==-1 && f.couple_rxy[index].xy[1]==-1){
index++;
}
//à partir de indice, on commence le défilement.
int limite=WIDTH*HEIGHT;
while(index<limite){
int ii=f.couple_rxy[index].xy[0];
int jj=f.couple_rxy[index].xy[1];
int a=ii*WIDTH+jj;
ww.t[a]=f.couple_rxy[index].rules.nouvelle_couleur[0];
index++;
 }}

int main(int argc, char* argv[]){
  world_init();
print_created_random_world(&ww);
  rules_init();
  queue_init();
printf("------------------\n");
display_file(f);
printf("------------------\n");
  ww.t[5]=0;
ww.t[1]=BLANC;
ww.t[4]=BLANC;
ww.t[10]=BLANC;
ww.t[14]=0;
ww.t[13]=BLANC;
ww.t[3]=BLANC;
print_created_random_world(&ww);
printf("--------------\n");
jeu();
print_created_random_world(&ww);
  return 0;
}
