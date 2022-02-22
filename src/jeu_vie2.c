#include<stdio.h>
#include<stdlib.h>
#include "code_queue3.h"
#define BLANC 16777215
#define NOIR 0
#define LEN_MAX 100 //maximum de 99 regles differentes au sein d'une meme.
//indeterminisme.
#define MAX_RULES 50 //maximum de 49 regles separees
//de type struct rule.
#include<unistd.h>
#include<getopt.h>
#include<time.h>


void create_random_world(struct world* monde, unsigned int seed);
void print_created_random_world(struct world* monde);
void world_init();
struct world ww;
struct coord{
  int abs;
  int ord;
};

struct file{
  struct coord xy;
  struct rule* regle;
  struct file* next;
};

//a compiler avec code_queue3.c ..
struct rule{
  int (*match_1)(struct world*,unsigned int,unsigned int);
  int (*match_2)(struct world*,unsigned int,unsigned int);
};

int index(int i, int j){
  return i*WIDTH+j;
}


int regle_match1(struct world* w, unsigned int i, unsigned int j){
  int indice = index(i,j);
  int i2 = (i == 0)?HEIGHT-1:i-1;
  int i3 = (i == HEIGHT-1)?0:i+1;
  int j2 = (j == 0)?WIDTH-1:j-1;
  int j3 = (j == WIDTH-1)?0:j+1;
  int voisinage[8];
  voisinage[0] = w->t[index(i2,j2)];
  voisinage[1] = w->t[index(i2,j)];
  voisinage[2] = w->t[index(i2,j3)];
  voisinage[3] = w->t[index(i,j2)];
  voisinage[4] = w->t[index(i,j3)];
  voisinage[5] = w->t[index(i3,j2)];
  voisinage[6] = w->t[index(i3,j)];
  voisinage[7] = w->t[index(i3,j3)];
  if(w->t[indice] != NOIR){
    return 0;
  }
  if(w->t[indice] == NOIR){
    int cpt=0;
    for(int p=0; p<8; p++){
      if(voisinage[p]==BLANC){
	cpt++;
      }
    }
    if(cpt == 3){
      return 1;
    }
  }
  return 0;
}


int regle_match2(struct world* w,unsigned int i,unsigned int j){
  int indice = index(i,j);
  int i2 = (i == 0)?HEIGHT-1:i-1;
  int i3 = (i == HEIGHT-1)?0:i+1;
  int j2 = (j == 0)?WIDTH-1:j-1;
  int j3 = (j == WIDTH-1)?0:j+1;
  int voisinage[8];
  
  voisinage[0] = w->t[index(i2,j2)];
  voisinage[1] = w->t[index(i2,j)];
  voisinage[2] = w->t[index(i2,j3)];
  voisinage[3] = w->t[index(i,j2)];
  voisinage[4] = w->t[index(i,j3)];
  voisinage[5] = w->t[index(i3,j2)];
  voisinage[6] = w->t[index(i3,j)];
  voisinage[7] = w->t[index(i3,j3)];
  if(w->t[indice] != BLANC){
    return 0;
  }
  if(w->t[indice] == BLANC){
    int cpt=0;
    int p=0;
    
    for(int p=0; p<8; p++){
      if(voisinage[p]==BLANC){
	cpt++;
      }
    }
    if(cpt==1 || cpt>=4 || cpt==0){
      return 1;
    }
  return 0;
  }
}
  
struct rule rule1_2;
struct file f;
struct file ff;
 
void jeu_vie_4(struct world* w,struct rule* r1_2, int nbr_fois){
  for(int k=0; k<nbr_fois; k++){
    file_init();
    file_init2();
    for(int i=0; i<HEIGHT; i++){
      for(int j=0; j<WIDTH; j++){
	if(r1_2->match_1(w,i,j)){
	  struct coord xety = {i,j};
	  ajouter_elt(&f, xety, r1_2);
	}
	if(r1_2->match_2(w,i,j)){
	  struct coord xety = {i,j};
	  ajouter_elt(&ff, xety, r1_2);
	}
      }
    }
    //1ere file => appliquer les changements en transformant les cases en BLANC
    //2ieme file=>appliquer les changements en transformant les cases en NOIR
    struct file* ptr1 = &f;
    while(ptr1->next != NULL){
      int x = ptr1->next->xy.abs;
      int y = ptr1->next->xy.ord;
      w->t[index(x,y)] = BLANC;
      ptr1 = ptr1->next;
      //supprimer_premier_elt(&f);
    }
    struct file* ptr2 = &ff;
    while(ptr2->next != NULL){
      int x = ptr2->next->xy.abs;
      int y = ptr2->next->xy.ord;
      w->t[index(x,y)] = NOIR;
      ptr2 = ptr2->next;
      //supprimer_premier_elt(&ff);
    }
    print_created_random_world(w);
  }
}
	


int main(int argc, char* argv[]){
  rule1_2.match_1 = regle_match1;
  rule1_2.match_2 = regle_match2;
  srand(time(NULL));
  world_init();
  for(int ij=0; ij<HEIGHT*WIDTH; ij++){
    ww.t[ij] = (rand()%2)*BLANC;}
  int tab[WIDTH*HEIGHT];int h=0;
  for(int i=0;i<2*HEIGHT/3;i++){
    for(int j=0;j<WIDTH/3;j++){
      ww.t[i*WIDTH+j]=BLANC;int limite=HEIGHT*WIDTH;
      ww.t[(i*WIDTH+j+1)%limite]=BLANC;
      ww.t[(i*WIDTH+j+2)%limite]=BLANC;
      ww.t[(i*WIDTH+j+WIDTH)%limite]=BLANC;
      ww.t[(i*WIDTH+j+WIDTH+WIDTH+1)%limite]=BLANC;
      tab[h]=i*WIDTH+j;h++;
      tab[h]=(i*WIDTH+j+1)%limite;h++;
      tab[h]=(i*WIDTH+j+2)%limite;h++;
      tab[h]=(i*WIDTH+j+WIDTH)%limite;h++;
      tab[h]=(i*WIDTH+j+WIDTH+WIDTH+1)%limite;h++;
}
  }
  for(int k=h;k<WIDTH*HEIGHT;k++){
    tab[k]=0;
  }
  int contient(int index,int tab[],int len){
    for(int h=0;h<len;h++){
      if(tab[h]==index) return 1;
    }
    return 0;
  }
  for(int x=0;x<WIDTH*HEIGHT;x++){
    if(!contient(x,tab,HEIGHT*WIDTH)) ww.t[x]=NOIR;}
  int c;
  int iterations;
  char optstr[]="m";
  while((c=getopt(argc,argv,optstr)) != EOF){
    switch(c){
    case 'm':
      iterations = atoi(argv[optind]);
      break;
    }
  }
  //on a le nombre d'iterations suivant une lecture sur la ligne de commande
  //"-m ..(valeur??///)".
  //on dispose du world ww (struct world TYPE)
  //qui est une grille noir et blanc.
  //on dipose de struct rule a adapter suivant nos besois sur
  //la derniere fonction a implementer lancant le jeu de la vie.
  printf("%d %d\n", WIDTH, HEIGHT);
  file_init();
  file_init2();
  jeu_vie_4(&ww, &rule1_2, iterations);
  return 0;
}
