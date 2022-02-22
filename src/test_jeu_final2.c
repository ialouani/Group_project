#include <stdio.h>
#include <stdlib.h>
#include "code_queue3.h"
#define LEN_MAX 100
#include <time.h>
#define ENTIER_MAX 4294967295
#define MAX_RULES 50
#define BLEU 255
#define BLANC 16777215
#define JAUNE 16776990
#define ROUGE 16711680

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

struct file f;
struct rules regles;

//a compiler avec code_queue3.c et rule3.c
//fonctions des regles et fonctions sur la file disponible.

struct world ww;


void create_random_world(struct world* monde, unsigned int seed);
void print_created_random_world(struct world* monde);
void world_init();


void game(){
  printf("%d %d\n", HEIGHT, WIDTH);
  print_created_random_world(&ww);
  int number_rules = rules_count();
  for(int i=0; i<HEIGHT; i++){
    for(int j=0; j<WIDTH; j++){
      for(int k=0; k<number_rules; k++){
	struct rule* rule_k = rule_get(k);
	
	if(rule_match(&ww,rule_k,i,j)){
	  struct coord ab = {i,j};
	  ajouter_elt(&f,ab,rule_k);
	  // afficher_file(&f);
	}
      }
    }
  }
  //appliquer les changements deterministes(cas simples).
  struct file* ptr = &f;//l'adresse de la file.
  while(ptr->next != NULL){//tant que au moins un element significatif dans la file((*))
    //recuperer le premier couple.
    int aa = (ptr->next->xy).abs;//traiter l'element(*)
    int bb = (ptr->next->xy).ord;
    int color = ptr->next->regle->new_color[0];
    int dx_ab = ptr->next->regle->dx[0];
    int dy_ab = ptr->next->regle->dy[0];
    int new_x = aa+dx_ab;
    int new_y = bb+dy_ab;
    
    ww.t[aa*WIDTH+bb] = 0;
    ww.t[new_x*WIDTH+new_y] = color;
    ptr = ptr->next;
  }
  print_created_random_world(&ww);
}


int main(int argc, char* argv[]){
  rules_init();
  world_init();//ww disponible aleatoirement.
  ww.t[4] = JAUNE;//HEIGHT=3,WIDTH=3.
  
  for(int a=0; a<HEIGHT*WIDTH; a++){
    if(a != 4){
      ww.t[a] = BLANC;
    }
  }
  
  for(int b=0; b<8; b++){
    regles.rs[0].voisins[0]=BLANC; 
  }
  regles.rs[0].own_color = JAUNE;
  regles.rs[0].new_color[0] = ROUGE;
  regles.rs[0].dx[0] = 1;
  regles.rs[0].dy[0] = 0;
  //grille 3*3 le sable case centrale tomber implique new_color
  //suivant 3 et translation ++x y.
  file_init();
  game();
  return 0;
}

