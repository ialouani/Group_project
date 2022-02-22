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
//#define BLEU 255
#define BLEU 16711680
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

int nbr_sable(struct world* w){
  int b=0;
  for(int a=0;a<HEIGHT*WIDTH;a++){
    if(w->t[a]==JAUNE) b++;}
  return b;}


void algo_iteration_4(struct world* w, struct rules* regles, unsigned int tours);

void algo_iteration_2(struct world* w,unsigned int tours,struct rules* rls,unsigned int numero_determinisme);

int main(int argc, char* argv[]){
  rules_init();
  /*int centrale=(HEIGHT-1)/2;//il faut que les dimensions soient impairs.*/
  world_init();//ww disponible aleatoirement.
  srand(time(NULL));
  for(int r=0;r<HEIGHT*WIDTH;r++){
    ww.t[r]=0;}
  for(int i=0;i<HEIGHT;i++){
    ww.t[i*WIDTH+WIDTH/3]=BLANC;}
    for(int i=0;i<HEIGHT;i++){
    ww.t[i*WIDTH+2*WIDTH/3]=BLANC;}
    for(int i=0;i<HEIGHT;i++){
      for(int j=WIDTH/3+1;j<2*WIDTH/3;j++){
	ww.t[i*WIDTH+j]=BLEU;}}
    ww.t[HEIGHT/2 * WIDTH + 2*WIDTH/3]=0;
    for(int yy=2*WIDTH/3 +1;yy<WIDTH;yy++){
      ww.t[yy]=VERT;}
    ww.t[(HEIGHT-1)*WIDTH+WIDTH-1]=JAUNE;
    for(int yyy=WIDTH/3 +1;yyy<2*WIDTH/3 ;yyy++){
      ww.t[(HEIGHT-1)*WIDTH+yyy]=VERT;}
 int aa=nbr_sable(&ww);
  for(int a=0;a<8;a++){
    regles.rs[0].voisins[a]=-1;}
  regles.rs[0].voisins[2]=BLANC;
   regles.rs[0].voisins[4]=0;
  regles.rs[0].own_color=BLEU;
  regles.rs[0].new_color[0]=BLEU;
  regles.rs[0].dx[0]=0;
  regles.rs[0].dy[0]=1;
  for(int a=0;a<8;a++){
    regles.rs[1].voisins[a]=-1;}
  regles.rs[1].voisins[1]=BLANC;
    regles.rs[1].voisins[6]=BLANC;
  regles.rs[1].own_color=BLEU;
  regles.rs[1].new_color[0]=BLEU;
  regles.rs[1].dx[0]=0;
  regles.rs[1].dy[0]=1;
    for(int a=0;a<8;a++){
    regles.rs[2].voisins[a]=0;}
    regles.rs[2].voisins[0]=BLANC;
    regles.rs[2].voisins[5]=BLANC;
  regles.rs[2].own_color=BLEU;
  regles.rs[2].new_color[0]=BLEU;
  regles.rs[2].dx[0]=1;
  regles.rs[2].dy[0]=0;
  for(int a=0;a<8;a++){
    regles.rs[3].voisins[a]=0;}
    regles.rs[3].voisins[3]=BLANC;
     regles.rs[3].voisins[5]=BLANC;
    regles.rs[3].voisins[6]=0;
    
  regles.rs[3].own_color=BLEU;
  regles.rs[3].new_color[0]=BLEU;
  regles.rs[3].dx[0]=1;
  regles.rs[3].dy[0]=0;
   for(int a=0;a<8;a++){
    regles.rs[4].voisins[a]=0;}
    regles.rs[4].voisins[0]=BLANC;
     regles.rs[4].voisins[3]=BLANC;
       regles.rs[4].voisins[5]=BLANC;
    regles.rs[4].voisins[6]=0;
    
  regles.rs[4].own_color=BLEU;
  regles.rs[4].new_color[0]=BLEU;
  regles.rs[4].dx[0]=1;
  regles.rs[4].dy[0]=0;

 
 
    regles.rs[5].voisins[6]=0;
   
    
  regles.rs[5].own_color=BLEU;
  regles.rs[5].new_color[0]=BLEU;
  regles.rs[5].dx[0]=1;
  regles.rs[5].dy[0]=0;


   for(int a=0;a<8;a++){
    regles.rs[6].voisins[a]=-1;}
  regles.rs[6].voisins[1]=BLANC;
    regles.rs[6].voisins[6]=BLANC;
    regles.rs[6].voisins[4]=BLEU;
  regles.rs[6].own_color=BLEU;
  regles.rs[6].new_color[0]=BLEU;
  regles.rs[6].dx[0]=0;
  regles.rs[6].dy[0]=2;

  for(int a=0;a<8;a++){
    regles.rs[7].voisins[a]=-1;}
  regles.rs[7].voisins[6]=VERT;
   regles.rs[7].voisins[1]=BLEU;
  
  regles.rs[7].own_color=BLEU;
  regles.rs[7].new_color[0]=BLEU;
  regles.rs[7].dx[0]=0;
  regles.rs[7].dy[0]=1;
  for(int a=0;a<8;a++){
    regles.rs[8].voisins[a]=-1;}
  regles.rs[8].voisins[6]=VERT;
   regles.rs[8].voisins[0]=BLEU;
    regles.rs[8].voisins[3]=BLEU;
  
  regles.rs[8].own_color=BLEU;
  regles.rs[8].new_color[0]=BLEU;
  regles.rs[8].dx[0]=0;
  regles.rs[8].dy[0]=1;
  for(int a=0;a<8;a++){
    regles.rs[9].voisins[a]=-1;}
  regles.rs[9].voisins[6]=VERT;
   regles.rs[9].voisins[0]=0;
    regles.rs[9].voisins[3]=BLEU;
      
  
  regles.rs[9].own_color=BLEU;
  regles.rs[9].new_color[0]=BLEU;
  regles.rs[9].dx[0]=0;
  regles.rs[9].dy[0]=1;
   for(int a=0;a<8;a++){
    regles.rs[10].voisins[a]=-1;}
  regles.rs[10].voisins[4]=VERT;

  
  regles.rs[10].own_color=BLEU;
  regles.rs[10].new_color[0]=BLEU;
  regles.rs[10].dx[0]=-1;
  regles.rs[10].dy[0]=0;

  
    file_init();file_init2();
   int iterations;int c;char optstring[]="m";
  while((c=getopt(argc,argv,optstring))!=EOF){
    switch(c){
    case 'm':
      iterations=atoi(argv[optind]);
      break;}}
  printf("%d %d\n", WIDTH, HEIGHT);
  print_created_random_world(&ww);
   algo_iteration_4(&ww,&regles,iterations);
   
  
   //algo_iteration_2(&ww,iterations,&regles,0);
      printf("%d %d\n",aa,nbr_sable(&ww));
  return 0;
}
