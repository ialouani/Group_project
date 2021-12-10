#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>
#include "project.h"
#ifndef __F
#define __F
#include "code_queue.h"
#endif
//indirectement on inclut le fichier world.h.
//a compiler avec rule.c et code_queue.c (pour avoir le resultat)
#define BLANC 16777215
#define JAUNE 16776960
#include<time.h>
#define BLEU 255
#define ENTIER_MAX 4294967295
#define LEN_MAX 100
#define ROUGE 16711680//(pour la suite)///

//on implemente le changement indeterministe suivant 2 couleurs possibles,
//NOUB && R : 16711680.

//d'abord on implementera le developpement de la regle rules1
//qui consiste a dire qu'une noire devient jaune, là on s'inspirera de ce que
//c'etait illustre dans la figure, une noire peut se transformer soit en
//en rouge soit en bleue.
//1 seule regle donc declaration de rules1 seulement (en globale).

struct rule rules1;
struct world ww;
struct file f;

void jeu_indeterministe_ordre1(int iterations){
  //on a initialise la regle rules1 indeterministe qui fixe un voisinage
  //et un choix pour la prochaine couleur avec own_color==0.
  //AUSSI: un monde de 0 et de BLANC (figure noire et blanche)
  print_created_random_world(&ww);
  int k=0;
   //tester sur tous les (x,y) al validite de la regle.
    //tester la validite revient a verifier le voisinage, la couleur
    //d'origine et pas DU TOUT la prochaine couleur => rule_match de rule.c
    //marhe parfaitement dans ce cas.(dans le cas de jeu de la vie, ca serait
    //impossible car verifier le voisinage ne sert a rien vis-a-vis
    //de la regle implementee qui est -2,..,-2 (aucun tour car tous <0)
    //=>adaptation de la rule_match via des compteurs de BLANC par exemple
    //possible (inclusion de rule.h+compilation avec rule.c+rule_matchR --new)
  while(k<iterations){
    for(int i=0;i<HEIGHT;i++){
      for(int j=0;j<WIDTH;j++){
	if(rule_match(&ww,&rules1,i,j)){
	  //creer le couple de type struct rule_index (r,(x,y))
	  struct rule_index couple0;
	  couple0.rules=rules1;
	  couple0.xy[0]=i;
	  couple0.xy[1]=j;
	  ajout_file(&f,couple0);}}}
    int index=0;
    while(f.couple_rxy[index].xy[0]==-1 && f.couple_rxy[index].xy[1]==-1){
      index++;}
    //à partir de index, les elements de la file ne sont plus triviaux.
    int debut=index;
    int limite=HEIGHT*WIDTH-index;
    while(debut<HEIGHT*WIDTH){
      unsigned int seed2=rand();
      srand(seed2);//pour à chaque tour resultat different
      //donc choix parmi R/B varie a chaque iteration sur les changement
      //a appliquer.(procedure pre-défilation de l'entiere file)
      struct rule_index couple_apply=f.couple_rxy[debut];
      int ii=couple_apply.xy[0];
      int jj=couple_apply.xy[1];
      //(x,y) qui va changer de couleur.
      int r=rand()%2;
      int possibilite=couple_apply.rules.nouvelle_couleur[r];
       ww.t[ii*WIDTH+jj]=possibilite;
      debut++;}
    int p=0;
    while(p<limite){
      delete_file(&f);p++;}
    print_created_random_world(&ww);k++;}
  //rq: la grille reste constante car si on suppose qu'il existe un element a la 2ieme iteration pouvant se modifier donc est noir donc etait noir (car la regle rules1 ne transforme par en noir) donc etait noir a l'iteraion 0(debut du programme);meme chose pour ses cases voisines utiles blanches , donc il existe une configuration qui n'a pas ete traite precedemment vu que ca n'a pas ete change d'apres notre hypothese (le rule_matche verifie la couleur les cases de voisins utiles uniquement[2]) donc il n'existe pas de configuration a l'iteration 2 qui va se faire appliquer la regle indeterministe parametree ici: R/B depuis le noir .
  return ;}
    

int main(int argc, char* argv[]){
  rules_init();
  //rules1 avec le voisinage correspondant, own_color==0 mais..
  rules1.nouvelle_couleur[0]=BLEU;
  rules1.nouvelle_couleur[1]=ROUGE;
  //2 couleurs possibles à l'instant;les autres tous à -1 deja fait par
  //rules_init().
  //on dispose de notre regle indeterministe rules1.()
  unsigned int seed=0;
  int nombre_images=0;
  char optstring[]="ms";
  int c;
  while((c=getopt(argc,argv,optstring))!=EOF){
    switch(c){
    case 'm':
      nombre_images=atoi(argv[optind]);
    case 's':
      seed=(unsigned int)atoi(argv[optind]);
    }}
  if(nombre_images==0) nombre_images=10;
  if(seed==0) seed=rand();
  srand(seed);
    world_init();
  for(int i=0;i<HEIGHT;i++){
    for(int j=0;j<WIDTH;j++){
      ww.t[i*WIDTH+j]=(rand()%2)*BLANC;
    }}
  //au debut une grille contenant que des 0 ou des BLANC comme SUR la figure
  //apres transformation d'etats a un etat aleatoire(R ou B) selon l'etat
  //de la cellule(pixel) en question (en gros, si elle respecte la regle).
  //on dispose maintenant d'un monde adapte a notre mini-test.
  printf("%d %d\n",HEIGHT,WIDTH);
  queue_init();//f accessible a tous.
  //  print_created_random_world(&ww);
  jeu_indeterministe_ordre1(nombre_images);
  return 0;
}
  
  
  
