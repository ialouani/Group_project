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
#define JAUNE 16776990
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
  world_init();
  char optstring[]="m";int c;int iterations;
  while((c=getopt(argc,argv,optstring))!=EOF){
    switch(c){
    case 'm':
      iterations=atoi(argv[optind]);
      break;}}
  int index=(HEIGHT-1)/2;
  int index1_x=index-1;int index1_y=index+1;
  int index2_x=index-1;int index2_y=index-1;
  int index3_x=index+1;int index3_y=index-1;
  int index4_x=index+1;int index4_y=index+1;
  int index1=index1_x*WIDTH+index1_y;
  int index2=index2_x*WIDTH+index2_y;
  int index3=index3_x*WIDTH+index3_y;
  int index4=index4_x*WIDTH+index4_y;
  ww.t[index1]=JAUNE;
  ww.t[index2]=ROUGE;
  ww.t[index3]=BLEU;
  ww.t[index4]=VERT;
  for(int v=0;v<HEIGHT*WIDTH;v++){
    if(v!=index1 && v!=index2 && v!=index3 && v!=index4){
      ww.t[v]=0;}}
  for(int w=0;w<4;w++){
    for(int y=0;y<8;y++){
      regles.rs[w].voisins[y]=0;}
    if(w==0) regles.rs[w].own_color=JAUNE;
    if(w==1) regles.rs[w].own_color=ROUGE;
    if(w==2) regles.rs[w].own_color=BLEU;
    if(w==3) regles.rs[w].own_color=VERT;
    if(w==0) regles.rs[w].new_color[0]=JAUNE;
    if(w==1) regles.rs[w].new_color[0]=ROUGE;
    if(w==2) regles.rs[w].new_color[0]=BLEU;
    if(w==3) regles.rs[w].new_color[0]=VERT;
    if(w==0){regles.rs[w].dx[0]=-1;regles.rs[w].dy[0]=1;}
    if(w==1){regles.rs[w].dx[0]=-1;regles.rs[w].dy[0]=-1;}
    if(w==2){regles.rs[w].dx[0]=1;regles.rs[w].dy[0]=-1;}
    if(w==3){regles.rs[w].dx[0]=1;regles.rs[w].dy[0]=1;}
  }
  for(int a=4;a<8;a++){
    if(a==4){
      regles.rs[a].voisins[0]=VERT;
      regles.rs[a].voisins[1]=BLEU;
      regles.rs[a].voisins[3]=JAUNE;
      for(int b=0;b<8;b++){
	if(b!=0 && b!=1 && b!=3) regles.rs[a].voisins[b]=0;}
      regles.rs[a].own_color=ROUGE;
      regles.rs[a].new_color[0]=ROUGE;
      regles.rs[a].dx[0]=-1+(HEIGHT-1)/2;
      regles.rs[a].dy[0]=-1+(HEIGHT-1)/2;}
    if(a==5){
      regles.rs[a].voisins[1]=VERT;
      regles.rs[a].voisins[2]=BLEU;
      regles.rs[a].voisins[4]=ROUGE;
      for(int b=0;b<8;b++){
	if(b!=1 && b!=2 && b!=4) regles.rs[a].voisins[b]=0;}
      regles.rs[a].own_color=JAUNE;
      regles.rs[a].new_color[0]=JAUNE;
      regles.rs[a].dx[0]=-1+(HEIGHT-1)/2;
      regles.rs[a].dy[0]=1+1-WIDTH+(HEIGHT-1)/2;}
    if(a==6){
      regles.rs[a].voisins[4]=BLEU;
      regles.rs[a].voisins[6]=JAUNE;
      regles.rs[a].voisins[7]=ROUGE;
      for(int b=0;b<8;b++){
	if(b!=4 && b!=6 && b!=7) regles.rs[a].voisins[b]=0;}
      regles.rs[a].own_color=VERT;
      regles.rs[a].new_color[0]=VERT;
      regles.rs[a].dx[0]=1-HEIGHT+(HEIGHT-1)/2+1;
      regles.rs[a].dy[0]=1-HEIGHT+(HEIGHT-1)/2+1;}
    if(a==7){
      regles.rs[a].voisins[3]=VERT;
      regles.rs[a].voisins[6]=ROUGE;
      regles.rs[a].voisins[5]=JAUNE;
      for(int b=0;b<8;b++){
	if(b!=6 && b!=3 && b!=5) regles.rs[a].voisins[b]=0;}
      regles.rs[a].own_color=BLEU;
      regles.rs[a].new_color[0]=BLEU;
      regles.rs[a].dx[0]=2-HEIGHT+(HEIGHT-1)/2;
      regles.rs[a].dy[0]=(HEIGHT-1)/2 -1;}
  }   
    file_init();
    file_init2();
    printf("%d %d\n",WIDTH,HEIGHT);
    print_created_random_world(&ww);
    algo_iteration_4(&ww,&regles,iterations);
  return 0;}
