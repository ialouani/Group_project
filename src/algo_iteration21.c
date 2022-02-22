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
#define NB_VOISINS 9

struct rule{
  int voisins[NB_VOISINS];
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


struct coord2{
  struct coord x_y;
  int color;
};

struct file f;
struct file ff;
struct rules regles;
struct world ww;


void create_random_world(struct world* monde, unsigned int seed);
void print_created_random_world(struct world* monde);
void world_init();


int pas_meme(struct world w1, struct world w2){
  for(int f=0;f<HEIGHT*WIDTH;f++){
    if(w1.t[f]!=w2.t[f]) return 1;
  }
  return 0;
}



void algo_iteration_4(struct world* w, struct rules* regles, unsigned int tours){
  struct world* ww2=w;
 unsigned int index(int i, int j){
    return i*WIDTH+j;
  }
 int combien(struct coord2 tab[], struct coord coordos, int length){
   int compteur=0;int compteur2=0;
   while(compteur2 < length){
     if(tab[compteur2].x_y.abs == coordos.abs && tab[compteur2].x_y.ord==coordos.ord){
       compteur++;
     }
     compteur2++;
   }
   return compteur;
 }
  int h;
  for(int k=0;k<tours;k++){
    h=0;
    for(int i=0; i<HEIGHT; i++){
      for(int j=0; j<WIDTH; j++){
	for(int k=0; k<rules_count(); k++){
	  struct rule* regle = rule_get(k);
	  
	  if(rule_match(w,regle,i,j)){
	    struct coord xy = {i,j};
	    ajouter_elt(&f, xy, regle);
	    ajouter_elt(&ff, xy, regle);
	    h++;
	    break;
	  }
	}
      }
    }
    
    struct coord2 new_indices[h];
    struct coord new_indices2[h];
    int p=0;
    struct file* ptr=&f;
    
    while(p<h){
      new_indices[p].x_y.abs=-1;
      new_indices[p].x_y.ord=-1;
      new_indices[p].color=-1;
      new_indices2[p].abs=-3;
      new_indices2[p].ord=-3;
      p++;
     }
  
    for(int l=0; l<h; l++){
      int x = (ptr->next)->xy.abs;
      int y = (ptr->next)->xy.ord;
      int len = rule_num_changes(ptr->next->regle);
      struct coord2 deplacements[len];
      
      for(int n=0; n<len; n++){
	deplacements[n].x_y.abs = -1;
	deplacements[n].x_y.ord = -1;
	deplacements[n].color = -1;
      }
      int m=0;
      int v=0;
      while(m<len){
	if(rule_change_to(ptr->next->regle,m) != -1){
	int xdx = x+rule_change_dx(ptr->next->regle,m);
	int ydy = y+rule_change_dy(ptr->next->regle,m);
	
	if(xdx >= HEIGHT){
	   xdx=xdx%HEIGHT;
	}
	if(xdx < 0){
	  xdx=HEIGHT-xdx%HEIGHT;
	}
        if(ydy >= WIDTH){
	  ydy=ydy%WIDTH;
	}
	if(ydy < 0){
	  ydy = WIDTH-ydy%WIDTH;
	}
	if(w->t[index(xdx,ydy)] == 0){
	  deplacements[v].x_y.abs = xdx;
	  deplacements[v].x_y.ord = ydy;
	  deplacements[v].color = rule_change_to(ptr->next->regle,m);
	  v++;
	}}
	m++;
      }
      if(v!=0){
	int index_random = rand()%v;
	new_indices[l] = deplacements[index_random];
	new_indices2[l].abs = x;
	new_indices2[l].ord = y;
      }
      else{
	new_indices[l].x_y.abs = -2;
	new_indices[l].x_y.ord = -2;
	new_indices[l].color = -2;
        new_indices2[l].abs = x;
	new_indices2[l].ord = y;
      }
 
      ptr=ptr->next;
    }
    struct file* ptr2 = &ff;
    
    for(int u=0; u<h; u++){
      int xx = new_indices2[u].abs;
      int yy = new_indices2[u].ord;
      int x_dx = new_indices[u].x_y.abs;
      int y_dy = new_indices[u].x_y.ord;
      int x_dx2 = x_dx;
      int y_dy2 = y_dy;
      
      if(new_indices[u].color != -2){
	struct coord new={x_dx,y_dy};
	int nbr_fois=combien(new_indices,new,h);
	
	if(nbr_fois == 1 && new_indices[u].color != BLANC && w->t[index(x_dx,y_dy)]==0){
	  w->t[index(xx,yy)] = 0;
	   w->t[index(x_dx,y_dy)] = new_indices[u].color;
	}
	else{
	  int random_indice = (rand()%(nbr_fois+1))+1;
	  int cpt=0;
	  int cpt2=0;
	  
	  while(cpt2<random_indice && cpt<h){
	    if(new_indices[cpt].x_y.abs==x_dx && new_indices[cpt].x_y.ord==y_dy){
	      cpt2++;
	    }
	    cpt++;
	  }
	  int new_x = new_indices2[cpt-1].abs;
	  int new_y = new_indices2[cpt-1].ord;
	  if(new_indices[cpt-1].color != BLANC &&   w->t[index(x_dx,y_dy)] ==0){
	    w->t[index(new_x,new_y)] = 0;
	    w->t[index(x_dx,y_dy)] = new_indices[cpt-1].color;}
	}
      }

      for(int z=0; z<h; z++){
	if(new_indices[z].x_y.abs == x_dx2 && new_indices[z].x_y.ord==y_dy2){
	  new_indices[z].x_y.abs = -2;
	  new_indices[z].x_y.ord = -2;
	  new_indices[z].color = -2;
	}
      }
      ptr2 = ptr2->next;
    }
    print_created_random_world(w);
    if(pas_meme(*w,*ww2)) return;  
    file_init();
    file_init2();
  }
}

	
