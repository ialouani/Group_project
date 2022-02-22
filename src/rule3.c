#include <stdio.h>
#include <stdlib.h>
//on doit inclure le fichier rule.h pour pouvoir implementer les modifications.
#include "rule.h"
//ça inclut world.h
//definition d'une regle (struct rule) qui code le contrat pour un certain (x,y)
//pour pouvoir lui appliquer le deplacement.
#define LEN_MAX 100
#include <time.h>
#define ENTIER_MAX 4294967295
#define MAX_RULES 50
#define BLEU 255
#define BLANC 16777215
#define JAUNE 16776990

struct rule{
  int voisins[9];//le voisinage sa forme
  int own_color;//la couleur que doit avoir la cellule pour se modifier
  int new_color[LEN_MAX];//indeterminisme (l'operation autorise plusieurs couleurs)
  int dx[LEN_MAX];//si ça marche(achiev0)->deplacement suivant x+dx qui prend la couleur
  int dy[LEN_MAX];//de meme (y+dy) pour avoir le nouveau: (x',y').
};
//Les 3 champs sont lies, ainsi un random donnant la 3ieme couleur
//doit impliquer un deplacement suivant dx,dy correspondants a la 3ieme
//couleur.

struct rules{
  struct rule rs[MAX_RULES];
};

struct world ww;

void create_random_world(struct world* monde, unsigned int seed){
  srand(seed);
  for(int i=0; i<HEIGHT*WIDTH; i++){
        (monde->t)[i] = rand()%(ENTIER_MAX+1);
  }
}

void print_created_random_world(struct world* monde){
  printf("#\n");
  for(int i=0; i<HEIGHT*WIDTH; i++){
    printf("%d ", (monde->t)[i]);
    if((i+1)%WIDTH==0){
      printf("\n");
    }
  }
}

void world_init(){
  unsigned int seed = time(NULL);
  create_random_world(&ww,seed);
}


//fonctions de rule.c
//rules_init();
struct rules regles;//structure contenant un tableau de regles.
void rules_init(){//initialise le tableau de regles
  for(int k=0; k<MAX_RULES; k++){
    //regles.rs[k]
    //lui affecter un voisinage d'abord
    for(int h=0; h<8; h++){         
      regles.rs[k].voisins[h] = -1;//initialisation comme ceci: le voisinage ne nous interesse pas
    }
    //puis faire la meme chose avec own_color
    regles.rs[k].own_color = -1;
    for(int l=0; l<LEN_MAX; l++){         
      regles.rs[k].new_color[l] = -1;
    }
    //initialiser de meme les dx,dy avec que des 0;ca sera mieux(<=> aucun deplacement)
    for(int p=0; p<LEN_MAX; p++){
      regles.rs[k].dx[p] = 0;
      regles.rs[k].dy[p]=0;
    }
  }
}
  
unsigned int rules_count(){//compte le nombre de regles
  unsigned int i=0;
  //on opere sur regles
  while(regles.rs[i].new_color[0]!=-1){
    i++;
  }//l'indeterminisme mais forcement la 1ere probabibilite non ss_triviale.
  return i;
}

struct rule* rule_get(unsigned int i){
  //recuperer dans regles (de type struct rules) la i-ème regle.
  return &(regles.rs[i]);
}//regle en indice i dans le tableau de regles regles.rs[MAX_RULES].


//maintenant, la fonction: rule_match: prend un *r,*w et prouve si ça marche
//<=>le voisinage le meme que celui dans la regle de type struct rule
//&& et la own_color , du coup le rule_match dans src/rule.c marche.

unsigned int rule_num_changes(const struct rule* r){//le nombre de couleurs futures possibles relatives
  //a une seule regle.
  int l = 0;
  while(r->new_color[l]!=-1){
    l++;
  }
  return l;
}//ça compte le nombre de couleurs possibles a affecter.

unsigned int rule_change_to(const struct rule* r, unsigned int idx){
  //renvoie la couleur suivant le choix numero idx.
  return r->new_color[idx];
}//idx<rule_num_changes(r).

int rule_change_dx(const struct rule* r, unsigned int idx){
  //prend une regle de type struct rule et renvoie le idx-ième element possible
  return r->dx[idx];
}
    
int rule_change_dy(const struct rule* r, unsigned int idy){
  return r->dy[idy];
}
//a compiler avec rule.c pour avoir la version du matching specifiee dans le fichier rule.h.

int rule_match(const struct world* w, const struct rule* r, unsigned int i, unsigned int j){//si ca marche pour une seule regle (pseudo-boucle)
  int index(unsigned int k1, unsigned int k2){
    return k1*WIDTH+k2;
  }
  unsigned int color = w->t[index(i,j)];//couleur de la cellule (x,y).
  //la le voisinage est important (pour le jeu de la vie non..)
  //recuperer tous les voisinages de cette cellule.
  /*int i2=((i-1)<0)? HEIGHT-1 :i-1;
  int j2=((j-1)<0)? WIDTH-1 : j-1;
  int i3=((i+1)>=HEIGHT)? 0: i+1;
  int j3=((j+1)>=WIDTH)? 0: j+1;
  */
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
  //recuperant les couleurs dans un tableau toujours de plus haut tout a gauche.
  unsigned int colors[9];
  colors[0]=w->t[index(i2,j2)];
  colors[1]=w->t[index(i2,j)];
  colors[2]=w->t[index(i2,j3)];
  colors[3]=w->t[index(i,j2)];
  colors[4]=w->t[index(i,j3)];
  colors[5]=w->t[index(i3,j2)];
  colors[6]=w->t[index(i3,j)];
  colors[7]=w->t[index(i3,j3)];
  
  if(color!=r->own_color){
    return 0;
  }
  
  for(int l=0; l<8; l++){
    if(r->voisins[l] != -1){  //couleur nous interesse(et donc a tester)
      if(colors[l] != r->voisins[l]){
	return 0;
      }
    }
  }
  return 1;
}






