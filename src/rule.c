#include <stdio.h>
#include <stdlib.h>
#include "rule.h"
#define BLANC 16777215
#define JAUNE 16776960
#include <time.h>
#define BLEU 255
#define ENTIER_MAX 4294967295
#define LEN_MAX 100

//implémentation du type incomplet struct rule:
struct rule {
  int couleurs_voisins_utiles[9];//-1 ça nous interesse pas
  //sinon la couleur en question.
  int nouvelle_couleur[LEN_MAX+2];//on garde une seule regle pour tester
  //la nouvelle couleur a affecter à la couleur en cours.
int own_color;
  struct rule* next;
};

//fonctions de world.c
//la premiere cree un monde & la deuxieme l'affiche 
void create_random_world(struct world* monde, unsigned int seed){
  srand(seed);
  for(int i=0; i<HEIGHT*WIDTH; i++){
        (monde->t)[i] = rand()%(ENTIER_MAX+1);
    // (monde->t)[i]=rand()%(10);//pour avoir une matrice petite
  }
}

void print_created_random_world(struct world* monde){
  printf("#\n");
  for(int i=0; i<HEIGHT*WIDTH; i++){
    printf("%d ", (monde->t)[i]);
    if((i+1)%WIDTH == 0){
      printf("\n");
    }
  }
}
//fin des fonctions de world.c.(création+affichage)

struct rule rules1;//considération d'un ensemble de regles
//pour que rules_init opere dessus donc cette façon de faire
//évite d'avoir un parametre (struct rule*) lorsqu'on veut appliquer
//ceci dans le main car rules1 ainsi declaré est accessible partout.


void rules_init(){
  int tab[9] = {-1, BLANC, -1, BLANC, -1, -1, -1, BLANC};
  int new_color = JAUNE;
  int new_color2 = BLEU;
  for(int i=0; i<8; i++){
    rules1.couleurs_voisins_utiles[i]=tab[i];
  }
  rules1.nouvelle_couleur[0] = new_color;
  rules1.nouvelle_couleur[1] = new_color2;
  for(int h=2; h<=LEN_MAX+1; h++){
    rules1.nouvelle_couleur[h]=-1;
  }
  rules1.next = NULL;
  rules1.own_color = 0;
}  //initialiser une liste de regles.(ça peut varier selon
//les regles qu'on veut mettre en oeuvre)

struct world ww;  //monde accessible par toutes les fonctions de rule.c.

void world_init(){
  unsigned int seed = time(NULL);
  create_random_world(&ww,seed);
  //avec la graine qui vaut time(NULL) l'execution donnera toujours
  //dans une suite d'executions la meme matrice aleatoire de couleurs.
}
//de la meme façon une fonction d'initialisation d'un monde
//sans parametre qui va etre appelee ulterieurement dans le main.


unsigned int rules_count(){
  unsigned int i = 1;
  struct rule* rules_next = rules1.next;
  while(rules_next != NULL){
    i++;
    rules_next = rules_next->next;
  }
  return i;
}


struct rule* rule_get(unsigned int i){
  if( i >rules_count()){
    fprintf(stdout, "regle inexistante!\n");
    exit(EXIT_FAILURE);
  }
  struct rule* rules_ptr = rules1.next;
  unsigned int j = 1;
  if(i == j){
    return &rules1;
  }
  j = 2;
  while(j < i){
    rules_ptr = rules_ptr->next;
    j++;
  }
  return rules_ptr;
}


int index(unsigned int i, unsigned int j){
  return i*WIDTH+j;
}
 

int rule_match(const struct world* w, const struct rule* r,unsigned int i, unsigned int j){
 unsigned int indice=i*WIDTH+j;//indice dans w->t (grille HEIGHT*WIDTH)
  int tab_voisinage[9];
  //on remplit de haut en bas et de gauche a droite
  //world->t[indice] represente la couleur dont on en cherche le voisinage
  //problemes dans i-1,j-1,i+1,j+1
  int i2 = 0;//i-1
  //printf("i-1 VAUT: %d\n ------%d------ \n",i-1,(-1)<0);
  if(i == 0){//le point est dans la 1ere ligne.
    //printf("passage par ici");
    i2 = HEIGHT-1;
  }
  else{ 
    i2 = i-1;
  }
  //printf("_____-----------\t%d|_|%d\t %d\n",i2,i-1,HEIGHT-1);
  int j2 = 0;//j-1
  if(j == 0){//le point est dans la 1ere colonne.
    j2 = WIDTH-1;
  }
  else{
    j2 = j-1;
  }
  int i3 = 0;//i+1
  if((i+1) >= HEIGHT){//le point est dans la derniere ligne.
    i3 = 0;
  }
  else{ 
    i3 = i+1;
  }
  int j3 = 0;//j+1
  if((j+1) >= WIDTH){//le point est dans la derniere colonne.
    j3 = 0;
  }
  else{
    j3 = j+1;
  }
  // printf("---------i2===%d\n",i2);
  //en 0, c'est tout en haut tout à gauche.
  tab_voisinage[0] = (w->t)[index(i2,j2)];
  tab_voisinage[1] = (w->t)[index(i2,j)];
  tab_voisinage[2] = (w->t)[index(i2,j3)];
  tab_voisinage[3] = (w->t)[index(i,j2)];
  tab_voisinage[4] = (w->t)[index(i,j3)];
  tab_voisinage[5] = (w->t)[index(i3,j2)];
  tab_voisinage[6] = (w->t)[index(i3,j)];
  tab_voisinage[7] = (w->t)[index(i3,j3)];
  //on dispose actuellement du voisinage de (i,j)
  //on compare avec rules1.couleurs_voisins_utiles
  if(w->t[indice] != (unsigned int)(r->own_color)){
    return 0;
  }
  //printf("%d\n",index(i,j));
  for(int k=0; k<8; k++){  
    if(r->couleurs_voisins_utiles[k] != -1){//voir si c'est la meme 
      //dans tab_voisinage
      //  printf("%d--%d\n",k,tab_voisinage[k]);
      int color = r->couleurs_voisins_utiles[k];
      if(color != tab_voisinage[k]){
	return 0;
      }
    }
  }
  return 1;
}


unsigned int rule_num_changes(const struct rule* r){
  //pour une regle *r, on a plusieurs choix (non deterministe)
  //calculer la longueur du tableau r->nouvelle_couleur
  int len = 0;
  while(r->nouvelle_couleur[len] != -1){
    len++;
  }
  return len;
}//le tableau est rempli dés un indice de -1 (jusqu'à la fin)
//les valeurs des indices precedents sont les couleurs possibles à affecter
//à la case qui verifie la condition de rule_match.
    


unsigned int rule_change_to(const struct rule* r, unsigned int idx){
  //idx exprime le changement numero idx.
  //idx forcement < rule_num_changes par exemple idx=1 représente la deuxieme couleur possible
  //en cas de test de rule_match vrai.
  return r->nouvelle_couleur[idx];
}
