#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>
#ifndef __quatre
#define __quatre
#include "../src/code_queue3.h"
#include "../src/rule.h"
#endif
#define LEN_MAX 100
#include <time.h>
#define ENTIER_MAX 4294967295 
#define MAX_RULES 50 
#define BLEU 255
#define BLANC 16777215
//#define JAUNE 16776990
#define JAUNE 65535
#define ROUGE 16711680
#define VERT 32768

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


struct coord2{
  struct coord x_y;
  int color;};

struct file f;
struct file ff;
struct rules regles;
struct world ww;


void create_random_world(struct world* monde, unsigned int seed);
void print_created_random_world(struct world* monde);
void world_init();

void algo_iteration_4(struct world* w, struct rules* regles, unsigned int tours);


int main(int argc, char* argv[]){
  rules_init();
  /*int centrale=(HEIGHT-1)/2;//il faut que les dimensions soient impairs.*/
  world_init();//ww disponible aleatoirement.

  //fond noir
  for(int a=0;a<HEIGHT*WIDTH;a++){
    ww.t[a]=0;}

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
  

  
  /*
  for(int l=0; l< HEIGHT-10; l+=1){

    ww.t[l*WIDTH + WIDTH/2]=JAUNE;
    ww.t[l*WIDTH + WIDTH/2 + 5]=JAUNE;


  }
  */ 


 


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

  //le grain tombe a droite
  for(int b = 0; b < 8;b++){ 
    regles.rs[1].voisins[b]=-1;
  }
  regles.rs[1].voisins[6] = JAUNE;
  regles.rs[1].voisins[7] = 0;
  
  regles.rs[1].own_color=JAUNE;
  regles.rs[1].new_color[0]=JAUNE;
  regles.rs[1].dx[0]=1;
  regles.rs[1].dy[0]=1;

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








  
  file_init();file_init2();
  int iterations;int c;char optstring[]="m";
  while((c=getopt(argc,argv,optstring))!=EOF){
    switch(c){
    case 'm':
      iterations=atoi(argv[optind]);
      break;}}
  printf("%d %d\n",WIDTH,HEIGHT);
  print_created_random_world(&ww);
  for(int r=0;r<iterations;r++){
    algo_iteration_4(&ww,&regles,1);
    ww.t[WIDTH/2]=JAUNE;
  }
  return 0;}


