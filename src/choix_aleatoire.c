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
  //rules_init()
  //on dispose de regles qu'on envoie a la valeur du deuxieme parametre.
  //on commence l'iteration (faire tours fois ceci..)
  int h;
  for(int k=0;k<tours;k++){
    //iteration numero k.
    h=0;//longueur future de la file.
    for(int i=0;i<HEIGHT;i++){
      for(int j=0;j<WIDTH;j++){
	//pour chaque(i,j) quelle regle matchera prochainement? (il existe une seule regle qui matches..)
	//car ça matches ou non<=>relatif au voisinage (valeurs des couleurs voisines)+la own_color.
	for(int k=0;k<rules_count();k++){
	  //iterer sur le nombre de regles.
	  struct rule* regle=rule_get(k);//on recupere la k-ieme regle
	  if(rule_match(w,regle,i,j)){//(i,j) matches avec la regle (de type struct rule*)
	    //file_init() et file_init2() est fait tout au debut (dans le main)
	    //ou a la fin de cette iteration.(avant le print_created_random_world(w))
	    struct coord xy={i,j};
	    ajouter_file(&f,xy,regle);//enfiler {{i,j},regle} dans la file *f.
	    ajouter_file(&ff,xy,regle);//enfiler {{i,j},regle} dans la file *ff.
	    h++;
	  }}}}
    //on a un 2 files maintenant qui ont stocke les changements en cours..
    //les changements sont de la forme (x,y) la case qui va prendre
    //le deuxieme champ color..
    //mais il faut que le (x,y) sa couleur initiale soit !=0..(VIDE)
    struct coord3 new_indices[h+1];//tableau de h elements
    //h==file.length(f/ff) on prend le pire des cas:
    //tous les futurs (x+dx,y+dy) sont vides.
    int x=0;
    while(x<h){
      new_indices[x]={{{-1000,-1000},-1},-1};x++;}
    int p=0;struct file* ptr=f;
    while(p<h){
      int x=(ptr->next)->xy.abs;int y=(ptr->next)->xy.ord;
      //on a un element p de la file en cours *f
      //on va voir l'element dx dans le tableau (ptr->next)->regle->dx[?]
      //le premier telque la case potentiellement occupee ne va pas
      //etre vide.
      int l=0;
      //calculons la couleur correspondant a l'indeterminisme 0.
      //puis faisons une boucle ..
      int dx=rule_change_dx(ptr->next->regle,l);
      int dy=rule_change_dy(ptr->next->regle,l);
      int len=rule_num_changes(ptr->next->regle);
      int first_color;
      //au moins len>=1.(base: l<0 saut vers if(l=0(initialement)==0)
      //donc structure de boucles operationnelle.
      while(w->t[index(x+dx,y+dy)]!=0 && l<len-1){//max=len-2
	l++;//au top: len-1
	dx=rule_change_dx(ptr->next->regle,l);
	dy=rule_change_dy(ptr->next->regle,l);}
      //on a teste les indeterminismes: 0..len-2 car pour l=len-2
      //l devient au passage par le corps de la boucle: len-1
      //et le test de la boucle ne se verifie pas (l!<len-1)
      //sortie a l=len-1.
      int bon_indice;
      if(l==len-1){//a tester si dernier indeterminisme pourrait marcher
	//les dx,dy correspondent a len-1 (les derniers dx,dy dans while{})
	if(w->t[index(x+dx,y+dy)]==0){bon_indice=len-1;
	  first_color=rule_change_to(ptr->next->regle,bon_indice);}
	if(w->t[index(x+dx,y+dy)]!=0) bon_indice=-1;}
      //sinon l!=len-1 donc logiquement ca veut dire
      //qu'il a trouve une future case VIDE (voir les 2 conditions de la boucle
      //)sinon ca revient a ce qu'on a dit avant: il a pas trouve de case
      //vide:->l augmente pas a pas jusqu'a len-1 sans tester l'indeterminisme
      //len-1 car len-2 le test se fera via les tests de la boucle
      //impossible car en l=len-2 ca devient a l'interieur len-1 et donc 
      //le test qui se fera apres pour voir est impredictible car len-1!<len-1 
      //donc en resume: soit trouver case vide reussi soit non(l=len-1) 
      //a la sortie.
      //CAS: IL A TROUVE UNE CASE VIDE::
      //vu que le test se fait debut boucle donc via les dx dy modifies dans 
      //tour precedent.
      else{
	//w->t[index(x+dx,y+dy)]==0
	//il faut recuperer le l.(ca sera le l DE SORTIE)
	indice_bon=l;
	first_color=rule_change_to(ptr->next->regle,indice_bon);}
      //donc soit bon_indice=-1 (aucune case vide)
      //soit len-1 si la derniere case est vide et tous les autres precedentes
      //ne le sont pas
      //soit <len-1 si une case vide se trouvait avant
      //~a partir de bon_indice, pour tout l'<bon_indice: elements 
      //correspondants a l' sont occupes.
      struct coord3 deplacements[len+1];//au top: indeterminisme sur 
      //len==rule_num_changes elements (dans les tableaux de dx,dy
      //tous les cases x+dx,y+dy sont vides)
      int m=indice_bon;int n=0;
      int o=0;
      while(o<len){
	deplacements[o]={{-1000,-1000},-1},p},p;o++;}
      if(m!=-1){
	struct coord xety={x+dx,y+dy};
	deplacements[n]={xety,first_color};n++;m++;      
      while(m<len){
	int xx=(ptr->next)->xy.abs+(ptr->next)->regle->dx[m];
	int yy=(ptr->next)->xy.ord+(ptr->next)->regle->dy[m];
	struct coord xety_plus={{xx,yy},rule_change_to(ptr->next->regle,m),p};
	if(w->t[index(xx,yy)]==0){
	deplacements[n]=xety_plus;
	n++;}
	m++;}
      }
      //deplacements relatifs a une case (x,y) via tableau des (x+dx,y+dy);COLOR
      //possibles suivant le (x+dx,y+dy) VIDE initialement.
      if(indice_bon!=-1){
	int indice_random=rand()%(n);
	new_indices[p]=deplacements[indice_random];}
      p++;
      ptr=ptr->next;}
    //on a actuellement le tableau new_indices qui est tableau des futurs
    //deplacements ~en correspondance avec la file.(SI TOUS les changements
    //concernes dans la file aboutissent a des changements de couleurs 
    //de cases non vides)
    int combien(struct coord3 tab[],struct coord x__y){
      int compteur=0;
      for(int w=0;w<h;w++){
	if(tab[w].coord_2.x_y.abs==x__y.abs && tab[w].coord_2.x_y.ord==x__y.ord){
	  compteur++;}}
      return compteur;}
    int v=0;struct file* ptr2=ff;
    while(v<h){
      //on dispose du tableau new_indices qui contient ~les elements de la file
      //avec un choix deterministe(si tous les elements de *ptr2 peuvent
      //aboutir a quelque chose de vide parmi les choix repertories dans
      //dx,dy,new_color[]).
      if(new_indices[v].new_color!=-1) v++;}
    //v=len(new_indices).
    //debut d'application des changements::
    struct file* ptr2=ff;
    int y=0;
    while(y<v){
      int x_dx=new_indices[y].coord_2.x_y.abs              ;
      int y_dy=new_indices[y].coord_2.x_y.ord;
      int nbr_fois=combien(new_indices,{x_dx,y_dy});
      if(nbr_fois==1){
	int color=new_indices[v].coord_2.color;
	w->t[x_dx*WIDTH+y_dy]=color;
      }
      if(nbr_fois>1){//choisir aleatoirement un des changements
	int random_number=rand()%nbr_fois;//<nbr_fois
	int u=0;int index_u;
	for(int uu=0;uu<nbr_fois;uu++){
	  while(new_indices[u].coord_2.x_y.abs!=x_dx && new_indices[u].coord_2.x_y.ord!=y_dy){
	    u++;}
	}
	//le u qui sort correspond a l'indice qui nous interesse.
	int new_x=new_indices[u].coord_2.x_y.abs;
	int new_y=new_indices[u].coord_2.x_y.ord;
	w->t[index(new_x,new_y)]=new_indices[u].coord_2.color;
      }
      y++;ptr2=ptr2->next;}
    print_created_random_world(w);
}






      















  
