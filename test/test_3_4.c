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
  for(int i=0;i<HEIGHT/2;i++){
    for(int j=0;j<WIDTH;j++){
      ww.t[i*WIDTH+j]=rand()%2 *JAUNE;}}
 for(int i=HEIGHT/2;i<HEIGHT;i++){
    for(int j=0;j<WIDTH;j++){
      ww.t[i*WIDTH+j]=0;}}
 int height=3*HEIGHT/4;
 for(int j=0;j<WIDTH;j++){
   ww.t[height*WIDTH+j]=BLANC;}
 int aa=nbr_sable(&ww);
  for(int a=0;a<8;a++){
    regles.rs[0].voisins[a]=-1;}
  regles.rs[0].voisins[6]=0;
  regles.rs[0].own_color=JAUNE;
  regles.rs[0].new_color[0]=JAUNE;
  regles.rs[0].dx[0]=1;
  regles.rs[0].dy[0]=0;
  regles.rs[0].new_color[1]=JAUNE;
  regles.rs[0].dx[1]=1;
  regles.rs[0].dy[1]=-1;
    regles.rs[0].new_color[2]=JAUNE;
  regles.rs[0].dx[2]=1;
  regles.rs[0].dy[2]=1;
  for(int a=0;a<8;a++){
    regles.rs[1].voisins[a]=-1;}
  regles.rs[1].voisins[6]=JAUNE;
   regles.rs[1].voisins[5]=0;
    regles.rs[1].voisins[7]=0;
  regles.rs[1].own_color=JAUNE;
  regles.rs[1].new_color[0]=JAUNE;
  regles.rs[1].dx[0]=1;
  regles.rs[1].dy[0]=-1;
    regles.rs[1].new_color[1]=JAUNE;
  regles.rs[1].dx[1]=1;
  regles.rs[1].dy[1]=-1;
  
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
