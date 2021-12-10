#include<stdio.h>
#include<stdlib.h>
#ifndef __a
#define __a
#include "rule.h" //et donc world.h aussi.
#endif
#include<time.h>
#define MAX_RULES 30
#define MAX_COLOR 4294967295 //le plus grand entier sur 32 bits
#define BLANC 16777215
#define JAUNE 16776960

//implementation de struct rule au debut.

struct rule{
  int couleurs_voisinage[9];//couleurs des 8 cases voisines
  int own_color;
  int new_color;//pas tableau(deterministe)
};

struct rules{
  struct rule r[MAX_RULES];
};
//donc la structure rule est une structure avec un seul champ le tableau
//des rule_one qui indique chacun le voisinage la couleur a avoir
//et la couleur potentielle a affecter au cas ou.

//implementation des fonctions de world.h..
struct world w;//on le rend publique,c'est pas important
//car ca sera modifiee par la suite(les pixels) ou bien random donc
//le resultat peut varier..
struct world world_init(){
  srand(time(NULL));
  for(int i=0;i<HEIGHT;i++){
    for(int j=0;j<WIDTH;j++){
      w.t[i*WIDTH+j]=rand()%(MAX_COLOR+1);}}
  return w;}

void display_world(struct world w){
  printf("#\n");
  for(int k=0;k<HEIGHT*WIDTH;k++){
    printf("%d ",w.t[k]);
    if((k+1)%WIDTH==0) printf("\n");}
  return;}

struct rules all;//all de type struct struct rule donc contient
//le champ rules de dimension MAX_RULES(chaque element est de type
//struct rule_one qui est le struct rule classique sans *next).

void rules_init(){
  //initialise le tableau des regles a des regles sans importance
  //ainsi un appel a rules_init permet d'avoir un tableau de regles
  //qu'on modifiera pour s'adapter a nos besoins.
  int h=0;
  while(h<MAX_RULES){
    //recuperer la h-ieme regle:
    //struct rule all;(champ rules a recuperer)
    //et puis son h-ième element(de type struct rule_une)
    struct rule rule_h=all.r[h];//variable locale independante disparaissant
    //a la fin.
    //on a recupere la h-ième regle.
    all.r[h].own_color=-1;//existe pas donc regle trivial
    all.r[h].new_color=-1;//rien donc de meme
    int p=0;
    while(p<8){
      all.r[h].couleurs_voisinage[p]=-1;p++;}
    h++;}}
//avec cette fonction on peut recuperer un tableau de rules initialise qu'on
//modifiera par la suite.

unsigned int rules_count(){
  //rules_init() apres modification apres appel a rules_count qui utilisera la
  //nouvelle version du tableau de regles.
  int len=0;
  while(len<MAX_RULES && all.r[len].own_color!=-1 && all.r[len].new_color!=-1){//les conditions importantes le voisinage et son utilite se voient sur le jeu de la vie.
    len++;}
  return len;}

struct rule* rule_get(unsigned int i){
  struct rule rule_i=all.r[i];//de type struct rule.
  //rappels(modifis.): struct rules constituee de struct rule r[MAX_RULES]
  return &(all.r[i]);}

int rule_match(const struct world* w, const struct rule* r, unsigned int i, unsigned int j){//si ca marche pour une seule regle (pseudo-boucle)
  int index(unsigned int k1, unsigned int k2){
    return k1*WIDTH+k2;}
  unsigned int color=w->t[index(i,j)];//couleur de la cellule (x,y).
  //la le voisinage est important (pour le jeu de la vie non..)
  //recuperer tous les voisinages de cette cellule.
  int i2=((i-1)<0)? HEIGHT-1 :i-1;
  int j2=((j-1)<0)? WIDTH-1 : j-1;
  int i3=((i+1)>=HEIGHT)? 0: i+1;
  int j3=((j+1)>=WIDTH)? 0: j+1;
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
  if(color!=r->own_color) return 0;
  int l=0;
  while(l<8){
    if(r->couleurs_voisinage[l]!=-1){//couleur nous interesse(et donc a tester)
      if(colors[l]!=r->couleurs_voisinage[l]) return 0;}
    l++;}
  return 1;
}

//les suivantes fonctions ne sont pas importantes.
unsigned int rule_num_changes(const struct rule* r){
  return 1;//par indeterminisme
}

unsigned int rule_change_to(const struct rule* r, unsigned int idx){
  //idx<rule_num_changes(r).
  //ici idx forcement 1 car une regle ne peut pas imposer un choix (determinisme)
  return r->new_color;}




  



  
  










  
  




    
  
  
