#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//utiliser la fonction getopt.
#include <getopt.h>
#include "project.h"
#ifndef __F
#define __F
#include "code_queue.h"
#endif
//indirectement on inclut le fichier world.h.
//a compiler avec rule.c et code_queue.c (pour avoir le resultat)
#define BLANC 16777215
#define JAUNE 16776960
#include <time.h>
#define BLEU 255
#define ROUGE 16711680
#define ENTIER_MAX 4294967295
#define LEN_MAX 100

int index(unsigned int i, unsigned int j);

int rule_match_R(struct world* w, const struct rule* r,unsigned int i, unsigned int j){

  int indice = i*WIDTH+j;
  int tab_voisinage[9];

  int i2 = i - 1;
  if (i2<0)
    i2 = HEIGHT - 1;
  int j2 = j - 1;
  if (j2<0)
    j2 = WIDTH - 1;
  int i3 = i + 1;
  if (i3 >= HEIGHT)
    i3 = 0;
  int j3 = j + 1;
  if (j3 >= WIDTH)
    j3 = 0;  
  tab_voisinage[0] = (w->t)[index(i2,j2)];
  tab_voisinage[1] = (w->t)[index(i2,j)];
  tab_voisinage[2] = (w->t)[index(i2,j3)];
  tab_voisinage[3] = (w->t)[index(i,j2)];
  tab_voisinage[4] = (w->t)[index(i,j3)];
  tab_voisinage[5] = (w->t)[index(i3,j2)];
  tab_voisinage[6] = (w->t)[index(i3,j)];
  tab_voisinage[7] = (w->t)[index(i3,j3)];

 int nombre_1 = 0;
 for(int compteur=0; compteur<8; compteur++){
   if(tab_voisinage[compteur] == BLANC){
    nombre_1++;
   }
  compteur++;
 }

 int color=(w->t)[indice];
 if(color==0 && nombre_1==3){
   return 1;//ça matche avec la regle numero1.(0->BLANC)
 }

 if(color == BLANC){
   if(nombre_1>3 || nombre_1<2){
     return 2;//appliquer la regle 2(blanc->0).
   }
 }

 return r->own_color;
}

struct rule rules1;
struct rule rules12;
struct rule rulesG;
struct rule* rules3 = &rulesG;
struct world ww;
struct file f;


void create_random_world2(struct world* monde, unsigned int seed){
  srand(seed);
  for(int i=0; i<HEIGHT*WIDTH; i++){
        (monde->t)[i] = rand()%(ENTIER_MAX+1);
    // (monde->t)[i]=rand()%(10);//pour avoir une matrice petite
  }
  return;
}

void print_created_random_world2(struct world* monde){
  printf("#\n");
  for(int i=0; i<HEIGHT*WIDTH; i++){
    printf("%d ", (monde->t)[i]);
    if((i+1)%WIDTH == 0){
      printf("\n");
    }
  }
}

void world_init2(){
  unsigned int seed = time(NULL);
  create_random_world2(&ww,seed);
}


 
void jeu_de_vie(int iterations){
   print_created_random_world2(&ww);
  int k=0;
  while(k<iterations){   
    for(int i=0; i<HEIGHT; i++){
      for(int j=0; j<WIDTH; j++){
	if(rule_match_R(&ww,rules3,i,j) == 1){//appliquer R1:0->BLANC
	  //printf("passage par là (1)\n");
	  //enfiler sur la file
	  //on doit creer r,(x,y) donc un type struct rule_index
	  struct rule_index coupleR1;
	  coupleR1.rules = rules1;
	  coupleR1.xy[0] = i;
	  coupleR1.xy[1] = j;
	  ajout_file(&f,coupleR1);
	}
	if(rule_match_R(&ww,rules3,i,j) == 2){//appliquer struct rule rules12;;
	  //printf("passage par là (2)\n");
	  struct rule_index coupleR2;
	  coupleR2.rules = rules12;
	  coupleR2.xy[0] = i;
	  coupleR2.xy[1] = j;
	  ajout_file(&f,coupleR2);
	}
      }
    }
    //j'ai enfile toutes les modifications
    //a faire pour la 1ere etape.
    //display_file(f);
    //je doit appliquer les modifications avant de passer a la prochaine
    //iteration..

    int index=0;
    
    while(f.couple_rxy[index].xy[0]==-1 && f.couple_rxy[index].xy[1]==-1){
      index++;
    }
    //index a la sortie sera l'indice du 1er element de la file non trivial.
    //enfilation depuis le bas!
    int limite_file = index;
    int limite = WIDTH*HEIGHT;
    
    while(index<limite){//iteration sur tous les elements non triviaux de la file
      int ii = f.couple_rxy[index].xy[0];
      int jj = f.couple_rxy[index].xy[1];
      int a = ii*WIDTH+jj;
      ww.t[a] = f.couple_rxy[index].rules.nouvelle_couleur[0];
      
      if(ww.t[a] == 0){
	int choisir = rand()%2;
      
	if(choisir == 0){
	  ww.t[a]=ROUGE;
	}
	else{
	  ww.t[a]=BLEU;
	}
      }
      index++;
    }
    //printf("---------------------\n");
    //display_file(f);
    //printf("------------------------\n");
    for(int p=0; p<HEIGHT*WIDTH-limite_file; p++){
      delete_file(&f);
    }
    //   display_file(f);
    print_created_random_world2(&ww);
    k++;
  }
  return;
}



int main(int argc, char* argv[]){
  rules3->own_color = 0;
  rules_init();
  //on dispose de rules0 de type struct rule
  rules1.nouvelle_couleur[0] = BLANC;
  //les autres nouvelles couleurs c'etaient en -1
  rules1.own_color = 0;
  rules1.next = NULL;
  int i = 0;
  for(int i=0; i<9; i++){
    rules1.couleurs_voisins_utiles[i] = -2;
  }
  //on dispose de R1 qui transforme la cellule blanche en noir.
  //struct rule rules12;//si on modifie rules2 ;rules0  ne sera pas modifiée.
  rules12.next=NULL;//avant possible car inclut code_queue.h qui definit la
  //struct rule.
  rules12.nouvelle_couleur[0] = 0;
  rules12.own_color = BLANC;
  
  for(int kh=1; kh<=LEN_MAX+1; kh++){
    rules12.nouvelle_couleur[kh] = -1;
  }
  for(int j=1; j<=LEN_MAX+1; j++){
    rules12.couleurs_voisins_utiles[j]=-2;
  }
  //on dispose de la regle R2 qui transforme la cellule noir en blanche.
  //unsigned int seed=atoi(argv[4]);
  //int nombre_images=atoi(argv[argc-3]);
  unsigned int seed = 0;
  int nombre_images = 0;
  char optstring[] = "ms";
  int c;
  while((c=getopt(argc,argv,optstring)) != EOF){//pas arrivee a la fin des arguments sur la ligne de commande apres le ./project::
   switch(c){
   case 'm'://<=>-m
     nombre_images = atoi(argv[optind]);//argv[optind] represente -m ?suivant 
   case 's':
     seed = (unsigned int)atoi(argv[optind]);//meme chose (seed et de type unsigned int)
   }
  }
  if(nombre_images==0){
    nombre_images=10;
  }
  if(seed==0){
    seed=rand();
  }
  srand(seed);
  world_init2();
  for(int i=0;i<HEIGHT;i++){
    for(int j=0;j<WIDTH;j++){
      ww.t[i*WIDTH+j] = (rand()%2)*BLANC;
    }
  }
  printf("%d %d\n",WIDTH,HEIGHT);
  // print_created_random_world2(&ww);
  queue_init();
  //display_file(f);
  jeu_de_vie(nombre_images);
  return 0;
}

