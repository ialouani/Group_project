#include<stdio.h>
#include<stdlib.h>
#include "code_queue3.h"
#define LEN_MAX 100
#include <time.h>
#include<unistd.h>
#include<getopt.h>
#define ENTIER_MAX 4294967295
#define MAX_RULES 50
#define ROUGE 255
#define BLANC 16777215
#define BLEU_CLAIR 16776990
#define BLEU_FONCE 16711680
#define JAUNE 65535

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

struct xyr{
  struct coord xy;
  struct rule* regle;
};

struct xyr xyr0={{-1,-1},NULL};
/*
struct coord0;
struct coord0.abs = -1;
struct coord0.ord = -1; */


struct file f;
struct rules regles;

//a compiler avec code_queue3.c et rule3.c
//fonctions des regles et fonctions sur la file disponible.

struct world ww;


void create_random_world(struct world* monde, unsigned int seed);
void print_created_random_world(struct world* monde);
void world_init();


void game(int nombre_de_fois){
  printf("%d %d\n",HEIGHT,WIDTH);
  print_created_random_world(&ww);
  int number_rules=rules_count();
  for(int k;k<nombre_de_fois;k++){
  for(int i=0;i<HEIGHT;i++){
    for(int j=0;j<WIDTH;j++){
      for(int k=0;k<number_rules;k++){
	struct rule* rule_k=rule_get(k);
	if(rule_match(&ww,rule_k,i,j)){
	  struct coord ab={i,j};
	  ajouter_elt(&f,ab,rule_k);
	 
	}}}}
  //afficher_file(&f);
  //appliquer les changements deterministes(cas simples).
  struct file* ptr=&f;//l'adresse de la file.
  struct xyr chgts[WIDTH*HEIGHT];

  for (int k=0; k < (WIDTH*HEIGHT); k++){
    chgts[k] = xyr0;
  }
  
  while(ptr->next!=NULL){
    int i = ptr->next->xy.abs;
    int j = ptr->next->xy.ord;
   
    
    int idi=i + ptr->next->regle->dx[0];
    int jdj=j + ptr->next->regle->dy[0];//i pour triangle.
    
    if(idi>=HEIGHT){
      idi= idi - HEIGHT;}
    if(jdj>=WIDTH){
      jdj= jdj - WIDTH;}
    if(idi<0){
      idi=HEIGHT + idi;}
    if(jdj<0){
      jdj=WIDTH + jdj;}
    
    int a = idi * WIDTH + jdj;
    struct xyr xyrule;
    
    xyrule.xy = ptr->next->xy;
    xyrule.regle = ptr->next->regle;
    chgts[a] = xyrule;
    ptr= ptr->next;

  }
  
  for(int k = 0; k < (WIDTH*HEIGHT); k++){

    if (chgts[k].regle != NULL){

      int aa = chgts[k].xy.abs;
      int bb = chgts[k].xy.ord;
      int nb_color = rule_num_changes(chgts[k].regle);
      int color = chgts[k].regle->new_color[rand()%(nb_color)];
      ww.t[aa*WIDTH+bb]=0;
      ww.t[k]= color;
    }

   
   
  }
  file_init();
  print_created_random_world(&ww);
  }
}

    

// rand()%(ENTIER_MAX+1);





int main(int argc, char* argv[]){
  rules_init();
  /*int centrale=(HEIGHT-1)/2;//il faut que les dimensions soient impairs.*/
  world_init();//ww disponible aleatoirement.

  //fond noir
  for(int a=0;a<HEIGHT*WIDTH;a++){
    ww.t[a] = 0;
    if ((rand()%(3)) == 2)
      ww.t[a]= JAUNE;
    
  }

  //sol en bas 
  for(int k=0;k<WIDTH;k++){
    ww.t[(HEIGHT-1)*WIDTH + k] = BLANC;
  }
  //premier obstacle
  for(int k=0;k<WIDTH/2 + 15;k++){
    ww.t[(HEIGHT/3)*WIDTH + k] = BLANC;
  }

  //deuxieme obstacle
  for(int k=WIDTH/2 +10; k<WIDTH; k++){
    ww.t[(2*HEIGHT/3)*WIDTH + k] = BLANC;
  }
 


  //REGLE POUR LE SABLE

  //le grain tombe tout droit
  for(int b = 0; b < 8;b++){ 
    regles.rs[0].voisins[b]=-1;
  }
  regles.rs[0].voisins[6] = 0;
  regles.rs[0].own_color=JAUNE;
  regles.rs[0].new_color[0]=JAUNE;
  regles.rs[0].dx[0]=1;
  regles.rs[0].dy[0]=0;


  //le grain tombe soit a droite soit a gauche

   for(int b = 0; b < 8;b++){ 
    regles.rs[1].voisins[b]=-1;
  }
  regles.rs[1].voisins[6] = JAUNE;
  regles.rs[1].voisins[5] = 0;
  regles.rs[1].voisins[7] = 0;
  
  regles.rs[1].own_color=JAUNE;
  regles.rs[1].new_color[0]=JAUNE;
  regles.rs[1].dx[0]=1;
  regles.rs[1].dy[0]=1;
  regles.rs[1].dy[1]=-1;
  

  //le grain tombe a gauche
  for(int b = 0; b < 8;b++){ 
    regles.rs[2].voisins[b]=-1;
  }
  regles.rs[2].voisins[6] = JAUNE;
  regles.rs[2].voisins[7] = JAUNE;
  regles.rs[2].voisins[5] = 0;
  
  regles.rs[2].own_color=JAUNE;
  regles.rs[2].new_color[0]=JAUNE;
  regles.rs[2].dx[0]=1;
  regles.rs[2].dy[0]=-1;

  //le grain tombe a droite
  for(int b = 0; b < 8;b++){ 
    regles.rs[3].voisins[b]=-1;
  }
  regles.rs[3].voisins[6] = JAUNE;
  regles.rs[3].voisins[5] = JAUNE;
  regles.rs[3].voisins[7] = 0;
  
  regles.rs[3].own_color=JAUNE;
  regles.rs[3].new_color[0]=JAUNE;
  regles.rs[3].dx[0]=1;
  regles.rs[3].dy[0]=1;






  
  file_init();
  int iterations;int c;char optstring[]="m";
  while((c=getopt(argc,argv,optstring))!=EOF){
    switch(c){
    case 'm':
      iterations=atoi(argv[optind]);
      break;}}
  game(iterations);
  return 0;}

