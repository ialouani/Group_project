#include<stdio.h>
#include<stdlib.h>
#ifndef __b
#define __b
#include "../src/rule.h"
#endif
#include<time.h>
#define MAX_RULES 30
#define MAX_COLOR 4294967295
#define BLANC 16777215
#define JAUNE 16776960

//on initialise que les structures non definies dans les headers.
//inclure header=>utiliser directement sans re-implementer les structures ceux
//dans le header.


struct rule{
  int couleurs_voisinage[9];
  int own_color;
  int new_color;
};
struct rules{
  struct rule r[MAX_RULES];};


struct world w;//juste car struct world se trouve dans les headers.
struct rules all;


void display_world(struct world w);
struct world world_init();


int main(int argc, char* argv[]){
world_init();
display_world(w);
 display_world(w);
 printf("----------\n");
 rules_init();
 //printf("%d -- %d------\n\n",all.r[0].own_color,all.r[1].new_color);
 printf("%d-----------\n\n",(int)rules_count());
 //test sur rule_get.
 //struct rule* r10=all.r[9];//10-ieme regle.
 all.r[9].own_color=0;
 all.r[9].new_color=BLANC;
 struct rule* r10=rule_get(9);
 printf("%d -- %d\n",r10->own_color,r10->new_color);
 //dernierement, les regles de match (oui/non.)::
 //HEIGHT=3 et WIDTH=3 absolument.(POUR CE TEST)
 w.t[1]=BLANC;
 w.t[3]=BLANC;
 w.t[4]=0;
 w.t[8]=BLANC;//la regle de depart..
 display_world(w);
 struct rule rule0;
 rule0.own_color=0;rule0.new_color=JAUNE;
 rule0.couleurs_voisinage[0]=-1;
 rule0.couleurs_voisinage[1]=BLANC;
 rule0.couleurs_voisinage[2]=-1;
 rule0.couleurs_voisinage[3]=BLANC;
 rule0.couleurs_voisinage[4]=-1;
 rule0.couleurs_voisinage[5]=-1;
 rule0.couleurs_voisinage[6]=-1;
 rule0.couleurs_voisinage[7]=BLANC;
 printf("%d\n",rule_match(&w,&rule0,1,1));
return 0;}

