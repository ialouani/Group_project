#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//ce fichier sans main sera compile avec une entree de regles,world,etc...
#include "code_queue2.h"
#define BLANC 16777215
#define JAUNE 16776960
#define MAX_COLOR 4294967295
//a compiler avec code_queue2.c

struct rule{
  int couleurs_voisinage[9];//couleurs des 8 cases voisines
  int own_color;
  int new_color;//pas tableau(deterministe)
};
struct rules{
  struct rule r[MAX_RULES];
};
//pq? car code_queue2.h inclut rule2.h qui definit le type incomplet struct rule
//donc pour pouvoir acceder aux elements dans une de ces fonctions suivantes, il faudrait imperativement l'implementer.

struct file f;
struct world w2;
struct rules all;
void world_init2(struct world* www){
  srand(time(NULL));
  for(int i=0; i<HEIGHT; i++){
    for(int j=0; j<WIDTH; j++){
      www->t[i*WIDTH+j] = rand()%(MAX_COLOR+1);
    }
  }
}
void display_world2(struct world* w){
  printf("#\n");
  for(int i=0; i<HEIGHT; i++){
    for(int j=0; j<WIDTH; j++){
      printf("%d ",w->t[i*WIDTH+j]);
      
      if((j+1)%WIDTH == 0){
	printf("\n");
      }
    }
  }
}

void world_apply(struct file* f,struct world* w){
  f = f->suite;
  while(f!=NULL){
    //appliquer le changement.
    int i = (f->xy).abs;
    int j = (f->xy).ord;
    w->t[i*WIDTH+j] = (f->regle)->new_color;
    f = f->suite;
  }
  return;
}



void apply_game(struct rules* rs,struct world* ww,unsigned int tours){
  int len_regles=0;
  while(rs->r[len_regles].new_color != -1 && rs->r[len_regles].own_color != -1){
    len_regles++;
  }
  int k=0;
  while(k<tours){
    file_init();
    for(int i=0; i<HEIGHT; i++){
      for(int j=0; j<WIDTH; j++){
	for(int h=0; h<len_regles; h++){
	  //il existe une seule regle au plus pour (i,j) sinon ca voudrait
	  //dire vu rule_match que 'est indeterministe(pas jeu de la vie)
	  //et donc impossible.
	  if(rule_match(ww,&(rs->r[h]),i,j)){
	    struct coord co = {i,j};
	    ajouter_elt(&f,co,&(rs->r[h]));
	  }
	}
      }
    }
    //on dispose de la file des changements ou chaque (x,y) apparait au plus
    //1 fois car c'est indeterministe.
    world_apply(&f,ww);
    display_world2(ww);
    k++;
  }
}


int main(int argc, char* argv[]){
  //printf("%d %d\n",HEIGHT,WIDTH);
  world_init2(&w2);
  // display_world2(&w2);(pour suite applications sdl).
  for(int n=0; n<=HEIGHT*WIDTH; n++){
    w2.t[n] = (rand()%2)*BLANC;
  }
  //monde de 1 et de 0.
   
  struct rule rule0={{BLANC,-1,-1,-1,-1,-1,-1,BLANC}, 0, JAUNE};
  rules_init();
  all.r[0] = rule0;
  w2.t[1] = BLANC;
  w2.t[3] = BLANC;
  w2.t[4] = 0;
  w2.t[8] = BLANC;
  // display_world2(&w2);(de meme)
  //  printf("----------------------\n");(dememe).//
  printf("%d %d\n", HEIGHT, WIDTH);
  display_world2(&w2);//il prend le jaune comme le bleu_ciel;;
  apply_game(&all, &w2, 10);
  //game() sortant le FAIT qu'une case dominee (extrem_one/two(|===&&))
  //et noire devient JAUNE.
  //par l'absurde(deja fait;../achiev2/*) on demontre qu'il y aura
  //1 seule transformation meme si le 2ieme argument augmente.
  return 0;
}
