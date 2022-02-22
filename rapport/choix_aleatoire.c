#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>
#include "code_queue3.h"
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

struct coord3{
  struct coord2 coord_2;
  int marqueur;
};

struct file f;
struct file ff;
struct rules regles;
struct world ww;


void create_random_world(struct world* monde, unsigned int seed);
void print_created_random_world(struct world* monde);
void world_init();

void algo_iteration_4(struct world* w, struct rules* regles, unsigned int tours){
  printf("%d %d",WIDTH,HEIGHT);
  int index(int i, int j){
    return i*WIDTH+j;
  }
  int h;
  for(int k=0;k<tours;k++){
    h=0;
    for(int i=0;i<HEIGHT;i++){
      for(int j=0;j<WIDTH;j++){
	for(int k=0;k<rules_count();k++){
	  struct rule* regle=rule_get(k);
	  if(rule_match(w,regle,i,j)){
	    struct coord xy={i,j};
	    ajouter_elt(&f,xy,regle);
	    ajouter_elt(&ff,xy,regle);
	    h++;
	    break;
	  }}}}
    struct coord3 new_indices[h+1];
    int x=0;
    while(x<h){
      new_indices[x].coord_2.x_y.abs=-1000;
      new_indices[x].coord_2.x_y.ord=-1000;
      new_indices[x].coord_2.color=-1;
      new_indices[x].marqueur=-1;
      x++;
    }
    int p=0;struct file* ptr=&f;
    while(p<h){
      int x=(ptr->next)->xy.abs;int y=(ptr->next)->xy.ord;
      int l=0;
      int dx=rule_change_dx(ptr->next->regle,l);
      int dy=rule_change_dy(ptr->next->regle,l);
      int len=rule_num_changes(ptr->next->regle);
      int first_color;
      while(w->t[index(x+dx,y+dy)]!=0 && l<len-1){
	l++;
	dx=rule_change_dx(ptr->next->regle,l);
	dy=rule_change_dy(ptr->next->regle,l);}
      int indice_bon;
      if(l==len-1){
	if(w->t[index(x+dx,y+dy)]==0){indice_bon=len-1;
	  first_color=rule_change_to(ptr->next->regle,indice_bon);}
	if(w->t[index(x+dx,y+dy)]!=0) indice_bon=-1;}
      else{
	indice_bon=l;
	first_color=rule_change_to(ptr->next->regle,indice_bon);}
      struct coord3 deplacements[len+1];
      int m=indice_bon;int n=0;
      int o=0;
      while(o<len){
    deplacements[o].coord_2.x_y.abs=-1000;
    deplacements[o].coord_2.x_y.ord=-1000;
    deplacements[o].coord_2.color=-1;
    deplacements[o].marqueur=p;
    o++;}
      if(m!=-1){
	struct coord xety={x+dx,y+dy};
	deplacements[n].coord_2.x_y=xety;
	deplacements[n].coord_2.color=first_color;
	deplacements[n].marqueur=p;
	n++;m++;
      while(m<len){
	int xx=(ptr->next)->xy.abs+(ptr->next)->regle->dx[m];
	int yy=(ptr->next)->xy.ord+(ptr->next)->regle->dy[m];
	struct coord3 xety_plus={{{xx,yy},rule_change_to(ptr->next->regle,m)},p};
	if(w->t[index(xx,yy)]==0){
	deplacements[n]=xety_plus;
	n++;}
	m++;}
      }
      if(indice_bon!=-1){
	int indice_random=rand()%(n);
	new_indices[p]=deplacements[indice_random];}
      p++;
      ptr=ptr->next;}
    int combien(struct coord3 tab[],struct coord x__y){
      int compteur=0;
      for(int w=0;w<h;w++){
	if(tab[w].coord_2.x_y.abs==x__y.abs && tab[w].coord_2.x_y.ord==x__y.ord){
	  compteur++;}}
      return compteur;}
    int v=0;struct file* ptr2=&ff;
      while(new_indices[v].coord_2.color!=-1) v++;
    int y=0;
    while(y<v){
      int x_dx=new_indices[y].coord_2.x_y.abs              ;
      int y_dy=new_indices[y].coord_2.x_y.ord;
      struct coord coordos={x_dx,y_dy};
      int nbr_fois=combien(new_indices,coordos);
      if(nbr_fois==1){
	int color=new_indices[v].coord_2.color;
	w->t[x_dx*WIDTH+y_dy]=color;
      }
      if(nbr_fois>1){
	int random_number=rand()%nbr_fois;
	int u=0;int index_u;
	for(int uu=0;uu<nbr_fois;uu++){
	  while(new_indices[u].coord_2.x_y.abs!=x_dx && new_indices[u].coord_2.x_y.ord!=y_dy){
	    u++;}
	}
	int new_x=new_indices[u].coord_2.x_y.abs;
	int new_y=new_indices[u].coord_2.x_y.ord;
	w->t[index(new_x,new_y)]=new_indices[u].coord_2.color;
      }
      y++;ptr2=ptr2->next;}
    print_created_random_world(w);
    file_init();
    file_init2();
  }}

 
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
  /*
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
  file_init2();
  int iterations;int c;char optstring[]="m";
  while((c=getopt(argc,argv,optstring))!=EOF){
    switch(c){
    case 'm':
      iterations=atoi(argv[optind]);
      break;}}
  algo_iteration_4(&ww,&regles,iterations);
  return 0;}








  
