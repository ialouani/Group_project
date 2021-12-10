#include<stdio.h>
#include<stdlib.h>
//on doit inclure le fichier rule.h pour pouvoir implementer les modifications.
#ifndef __E
#define __E
#include "../src/rule.h"
#endif
//ça inclut world.h
//definition d'une regle (struct rule) qui code le contrat pour un certain (x,y)
//pour pouvoir lui appliquer le deplacement.
#define LEN_MAX 100
#include <time.h>
#define ENTIER_MAX 4294967295
#define MAX_RULES 50
#define BLEU 255
#define BLANC 16777215
#define JAUNE 16776960

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
  struct rule rs[MAX_RULES];};

struct world ww;

void create_random_world(struct world* monde, unsigned int seed);

void print_created_random_world(struct world* monde);

void world_init();

struct rules regles;

int main(int argc, char* argv[]){//au debut on fera les tests suivant un main
  //ici(dans RULE3.C).
  printf("%d %d\n", HEIGHT, WIDTH);
  world_init(ww);
  print_created_random_world(&ww);
  rules_init();//regles s'initialise..
  printf("-------------------------\n");
  printf("%d -- (%d,%d)\n",regles.rs[0].new_color[0],regles.rs[0].dx[0],regles.rs[0].dy[0]);//ca devrait donner normalement: -1 (0,0).
  //rappel: MAX_RULES est le len du tableau de regles: regles.rs
  //LEN_MAX est le nombre de choix(via l'indeterminisme sur le deplacement relie
  //à: la couleur.)
  //tjrs: LEN_MAX-1 et MAX_RULES-1.
  printf("%d -- (%d,%d)\n",regles.rs[MAX_RULES-1].new_color[0],regles.rs[MAX_RULES-1].dx[0],regles.rs[MAX_RULES-1].dy[0]);//on recupere le 1er choix dans la derniere regle.
  //on peut jouer et prendre le dernier choix suivant la 1ere regle qui sera:
  //regles.rs[0]
  printf("%d -- (%d;%d)\n",regles.rs[0].new_color[LEN_MAX-1],regles.rs[0].dx[LEN_MAX-1],regles.rs[0].dy[LEN_MAX-1]);
  printf("----------------------\n");
  //on a teste toutes les fonctions de world.c '' + fonction numero 1
  //de rule.h qui est: void rules_init(){..;}; .
  //reste les 5 fonctions de base + les 2 fonctions ajoutees:
  //rule_change_dx et rule_change_dy.
  //prennent une regle et idx et retournent le dx,dy suivant le choix numero
  //idx<rule_num_changes tout cela avec un type struct rule et pas
  //struct rules.
  printf("le nombre de regles ici est:%d\n",rules_count());//0 bien sur.
   printf("----------------------\n");
   //il faut un peu modifier pour voir.
   //regles.rs[0] est une regle (type struct rule) qu'on va essayer de
   //modifier ici:->
   //codons celle de l'achiev:1./
   regles.rs[0].voisins[1]=BLANC;
   regles.rs[0].voisins[3]=BLANC;
   regles.rs[0].voisins[8]=BLANC;
   regles.rs[0].own_color=0;
   //regles.rs[0] de type struct rule indique le voisinage et la couleur
   //que doit avoir la cellule;reste le deplacement dx,dy et la nouvelle
   //couleur qui va se deplacer.
   regles.rs[0].new_color[0]=JAUNE;
   regles.rs[0].new_color[1]=BLEU;//indeterminisme.
   //j'ajoute rien en terme de deplacement ici (pas de deplacement<=>achiev1.0).
   printf("le nombre de regles apres avoir ajouter (adapter) regles.rs[0] (la 1ere regle) est: %d\n",rules_count());
   //ça marche, maintenant essayons avec rule_get (ca fera 3 fonctions testees).
   struct rule* rule00=rule_get(0);//recuperer la 1ere regle
   //ici ca sera: regles.rs[0] en referencage.
   printf("%d|%d -- %d,%d|%d,%d \n", rule00->new_color[0],rule00->new_color[1],rule00->dx[0],rule00->dy[0],rule00->dx[1],rule00->dy[1]);
   printf("---------------------------\n");
   //now, test fonction rule_num_changes et rule_change_to :(rule_match apres car ca necessite un monde et avec random il devrait etre modifie,etc...) //
   //restera une seule fonction a tester: rule_match.
   //on a rule00 qui est de type struct rule*
   printf("le nombre de changements car indeterminisme de la regle regles.rs[0] est:%d\n",rule_num_changes(rule00));
   //recuperer la couleur du premier changement et la couleur du deuxieme changement
   //VIA la fonction: rule_change_to.
   printf("couleur1 possible et couleur2 possible respectivement:%d %d\n",rule_change_to(rule00,0),rule_change_to(rule00,1));
   //5 fonctions testees: rules_init, rules_count, rule_num_changes, rule_change_to, rule_get bien construites(rule.h.).
   //on teste les 2 autres:: rule_change_dx et rule_change_dy.
   //retournent le deplacement suivant x ou y numero idx=$2_`rule_change_dx/dy`
   //on change un peu la regle ici (rule00) en disant que le JAUNE va se deplacer suivant le vecteur (1,1) et le BLEU suivant le vecteur (vecteur de translation) (-1,-1)
   regles.rs[0].dx[0]=1;
   regles.rs[0].dy[0]=1;//regles.rs[0].own_color[0] lui correspond.
   regles.rs[0].dx[1]=-1;
   regles.rs[0].dy[1]=-1;
   printf("nouveau:(rule_change_to) __ne change pas =>::%d\n",rule_num_changes(&(regles.rs[0])));
   struct rule* rule00_2=rule_get(0);//up-dating *rule00.
   printf("le couple1 a prendre en compte:(%d,%d) ET le couple2 a prendre en compte:(%d,%d)\n",rule_change_dx(rule00_2,0),rule_change_dy(rule00_2,0),rule_change_dx(rule00_2,1),rule_change_dy(rule00_2,1));
   //ça marche.
   printf("-------------%d\n-----------------\n",rule00->dx[0]);
   //1 (rule00=rule_get(0) car &(regles.rs[0]) ne change pas c'est seulement
   //la modification des champs et du coup l'acces au nouveaux valeurs se fait
   //via la meme adresse et du coup rule00 s'adapte automatiquement apres modification de la 1ere regle: regles.rs[0]).
   //toutes les fonctions ont ete testees: reste RULE_MATCH.
   ww.t[1]=BLANC;
   ww.t[3]=BLANC;
   ww.t[8]=BLANC;
   ww.t[4]=0;
   print_created_random_world(&ww);
   printf("%d:((la case 4 conforme a la regle regles.rs[0]))\n---------------\n",rule_match(&ww,rule00,1,1));
   //a compiler avec -DHEIGHT=3 et -DWIDTH=3.
  return 0;}
  
  
