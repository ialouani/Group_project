#include<stdio.h>
#include<stdlib.h>
#define BLANC 16777215
#define JAUNE 16776960
#define BLEU 255
#define ENTIER_MAX 4294967295
#define LEN_MAX 100

#ifndef __A
#define __A
#include "../src/rule.h"
#endif

void create_random_world(struct world* monde, unsigned int seed);
void print_created_random_world(struct world* monde);
void world_init();

//implémentation du type incomplet struct rule:
struct rule {
  int couleurs_voisins_utiles[9];//-1 ça nous interesse pas
  //sinon la couleur en question.
  int nouvelle_couleur[LEN_MAX+2];//on garde une seule regle pour tester
  //la nouvelle couleur a affecter à la couleur en cours.
int own_color;
  struct rule* next;
};

struct rule rules1;
struct world ww;
//QUAND ON inclut le fichier, c'est que les fonctions qui ont importées
//on redefinit les constantes (les 3 couleurs) + ENTIER_MAX et LEN_MAX 
//en cas de necessite sans oublier la structure pour rendre rules1 et ww 
//ici publiques, du coup n'importe quelle utilisation de fonction va utiliser
//cette derniere depuis le rule.c.

int main(int argc, char* argv[]){
  int graine=atoi(argv[argc-1]);
  //printf("valeur du generateur aleatoire: %d\n--------\n\n",graine);
  //printf("%d\n",graine);
  srand(graine);
  world_init();
  print_created_random_world(&ww);
  //a gerer apres.
    //juste pour construire la matrice en question.
  
  rules_init();
  struct world monde1;
  struct world* monde2=&monde1;
  unsigned int seed=atoi(argv[4]);
  //srand(seed);//on peut le faire à l'interieur de la fonction.
  create_random_world(monde2,seed);
  printf("-----Le monde est le suivant:-------\n");
  print_created_random_world(monde2);
  printf("\t\t\t---------------\t\t\t\n");
  //printf("\nla taille des regles est:%d\n------\n\n",rules_count());
  (monde2->t)[6]=0;
  printf("nouveau monde:\n");
  print_created_random_world(monde2);
  (monde2->t)[1]=BLANC;
  (monde2->t)[5]=BLANC;
  (monde2->t)[12]=BLANC;
 printf("nouveau monde:\n");
  print_created_random_world(monde2);
  printf("___________%d\n",rule_match(monde2,&rules1,1,1));
  printf("%d\n",rule_match(monde2,&rules1,2,2));
  (monde2->t)[4]=0;
  printf("nouveau monde:\n");
  print_created_random_world(monde2);
  (monde2->t)[3]=BLANC;
  (monde2->t)[24]=BLANC;
  printf("nouveau monde:\n");
  print_created_random_world(monde2);
  printf("_________%d\n",rule_match(monde2,&rules1,0,4));
  printf("%d\n",rule_match(monde2,&rules1,0,3));

  //Que des tests qui marchent tous jusqu'à présent.

  
  //test relatif à rule_num_changes.
  rules_init();//on dispose des regles a ce stade.(rules1)
  world_init();//pour que ww ne soit pas vide tout au début.
  (ww.t)[6]=0;
  (ww.t)[1]=BLANC;
  (ww.t)[5]=BLANC;
  (ww.t)[12]=BLANC;
  //on a au moins un pixel situé en 7ième position (tableau pas matrice)
  //de ww.t qui représente l'état de tous les cellules actuellement.
  (ww.t)[4]=0;
  (ww.t)[3]=BLANC;
  (ww.t)[24]=BLANC;
  print_created_random_world(&ww);
  printf("----------\n%d\n\n\n",rule_num_changes(&rules1));


  printf("%d\n",rules1.nouvelle_couleur[0]);
  printf("le nombre de couleurs possibles est: %d\n",rule_num_changes(&rules1));
  printf("la 1ere couleur possible (!==indice_tableau) est pour idx=0:\t%d\n",rule_change_to(&rules1,0)); //ça devrait retourner normalement le code de la couleur jaune.
  
  return 0;
}
