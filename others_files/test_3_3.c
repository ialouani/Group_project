#include<stdio.h>
#include<stdlib.h>
#include "../src/code_queue3.h"
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
//#define JAUNE 65535
//#define BLEU 255
#define JAUNE 16711680 //code bleu dans le code classique(2).( BGR )


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
    ww.t[a] = 0;
    /*  int aleat = rand()%(10);
    if (aleat == 9)
      ww.t[a]= JAUNE;
    */ 
  }

  //sol en bas 
  for(int k=0;k<WIDTH;k++){
    ww.t[(HEIGHT-1)*WIDTH + k] = BLANC;
  }/*
  //premier obstacle
  for(int k=0;k<WIDTH/2 + 15;k++){
    ww.t[(HEIGHT/3)*WIDTH + k] = BLANC;
  }

  //deuxieme obstacle
  for(int k=WIDTH/2 +10; k<WIDTH; k++){
    ww.t[(2*HEIGHT/3)*WIDTH + k] = BLANC;
  }
   */


  //REGLE POUR LE SABLE


  //le grain touche le sol 
  for(int b = 0; b < 8;b++){ 
    regles.rs[0].voisins[b]=-1;
  }
  regles.rs[0].voisins[6] = BLANC;
  regles.rs[0].own_color=JAUNE;
  regles.rs[0].new_color[0]=JAUNE;
  regles.rs[0].dx[0]=0;
  regles.rs[0].dy[0]=0;


  
  //le grain tombe tout droit
  for(int b = 0; b < 8;b++){ 
    regles.rs[1].voisins[b]=-1;
  }
  regles.rs[1].voisins[6] = 0;
  regles.rs[1].own_color=JAUNE;
  regles.rs[1].new_color[0]=JAUNE;
  regles.rs[1].dx[0]=1;
  regles.rs[1].dy[0]=0;


  //le grain tombe soit a droite soit a gauche

   for(int b = 0; b < 8;b++){ 
    regles.rs[2].voisins[b]=-1;
  }
  regles.rs[2].voisins[6] = JAUNE;
  regles.rs[2].voisins[5] = 0;
  regles.rs[2].voisins[7] = 0;
  
  regles.rs[2].own_color=JAUNE;
  regles.rs[2].new_color[0]=JAUNE;
  regles.rs[2].dx[0]=1;
  regles.rs[2].dy[0]=1;
  regles.rs[2].dy[1]=-1;
  

  //le grain tombe a gauche
  for(int b = 0; b < 8;b++){ 
    regles.rs[3].voisins[b]=-1;
  }
  regles.rs[3].voisins[6] = JAUNE;
  regles.rs[3].voisins[7] = JAUNE;
  regles.rs[3].voisins[5] = 0;
  
  regles.rs[3].own_color=JAUNE;
  regles.rs[3].new_color[0]=JAUNE;
  regles.rs[3].dx[0]=1;
  regles.rs[3].dy[0]=-1;

  
  //le grain tombe a droite
  for(int b = 0; b < 8;b++){ 
    regles.rs[4].voisins[b]=-1;
  }
  regles.rs[4].voisins[6] = JAUNE;
  regles.rs[4].voisins[5] = JAUNE;
  regles.rs[4].voisins[7] = 0;
  
  regles.rs[4].own_color=JAUNE;
  regles.rs[4].new_color[0]=JAUNE;
  regles.rs[4].dx[0]=1;
  regles.rs[4].dy[0]=1;

  
  //le grain va soit a droite soit a gauche

   for(int b = 0; b < 8;b++){ 
    regles.rs[5].voisins[b]=-1;
  }
  regles.rs[5].voisins[6] = JAUNE;
  regles.rs[5].voisins[5] = JAUNE;
  regles.rs[5].voisins[7] = JAUNE;
  regles.rs[5].voisins[3] = 0;
  regles.rs[5].voisins[4] = 0;
  
  
  regles.rs[5].own_color=JAUNE;
  regles.rs[5].new_color[0]=JAUNE;
  regles.rs[5].dx[0]=0;
  regles.rs[5].dy[0]=1;
  regles.rs[5].dy[1]=-1;


  //le grain va a gauche
  for(int b = 0; b < 8;b++){ 
    regles.rs[6].voisins[b]=-1;
  }
  regles.rs[6].voisins[6] = JAUNE;
  regles.rs[6].voisins[5] = JAUNE;
  regles.rs[6].voisins[7] = JAUNE;
  regles.rs[6].voisins[3] = 0;
  regles.rs[6].voisins[4] = JAUNE;
  
  
  regles.rs[6].own_color=JAUNE;
  regles.rs[6].new_color[0]=JAUNE;
  regles.rs[6].dx[0]=0;
  regles.rs[6].dy[0]=-1;

  //le grain va a droite
  for(int b = 0; b < 8;b++){ 
    regles.rs[7].voisins[b]=-1;
  }
  regles.rs[7].voisins[6] = JAUNE;
  regles.rs[7].voisins[5] = JAUNE;
  regles.rs[7].voisins[7] = JAUNE;
  regles.rs[7].voisins[3] = JAUNE;
  regles.rs[7].voisins[4] = 0;
  
  
  regles.rs[7].own_color=JAUNE;
  regles.rs[7].new_color[0]=JAUNE;
  regles.rs[7].dx[0]=0;
  regles.rs[7].dy[0]=1;
 
  for(int b=0;b<8;b++){
    regles.rs[8].voisins[b]=JAUNE;}
  regles.rs[8].own_color=0;
  regles.rs[8].new_color[0]=JAUNE;
  regles.rs[8].dx[0]=0;
  regles.rs[8].dy[0]=0;

  for(int b=0;b<8;b++){
    if(b==0 || b==1 || b==2) regles.rs[8].voisins[b]=-1;
    if(b==5 || b==6 || b==7) regles.rs[8].voisins[b]=JAUNE;}
  
    
  
  regles.rs[8].own_color=0;
  regles.rs[8].new_color[0]=JAUNE;
  regles.rs[8].dx[0]=0;
  regles.rs[8].dy[0]=0;

   for(int b=0;b<8;b++){
    regles.rs[9].voisins[b]=JAUNE;}
  
    
  
  regles.rs[9].own_color=0;
  regles.rs[9].new_color[0]=JAUNE;
  regles.rs[9].dx[0]=0;
  regles.rs[9].dy[0]=0;

  for(int b=0;b<8;b++){
    regles.rs[9].voisins[b]=JAUNE;}
  
    
  
  regles.rs[9].own_color=0;
  regles.rs[9].new_color[0]=JAUNE;
  regles.rs[9].dx[0]=0;
  regles.rs[9].dy[0]=0;
  for(int b=0;b<8;b++){
     if(b<3) regles.rs[10].voisins[b]=JAUNE;}
  
    
  
  regles.rs[10].own_color=0;
  regles.rs[10].new_color[0]=JAUNE;
  regles.rs[10].dx[0]=0;
  regles.rs[10].dy[0]=0;


  
  file_init();file_init2();
  int iterations;int c;char optstring[]="m";
  while((c=getopt(argc,argv,optstring))!=EOF){
    switch(c){
    case 'm':
      iterations=atoi(argv[optind]);
      break;}}
  printf("%d %d\n",WIDTH,HEIGHT);
  print_created_random_world(&ww);
  for(int cc=0;cc<iterations;cc++){
algo_iteration_4(&ww,&regles,1);
 ww.t[WIDTH/2]=JAUNE;}
  return 0;}

