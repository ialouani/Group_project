#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>
#include "code_queue3.h"
#define LEN_MAX 100 //ou va le max. de l'indeterminisme.
#include <time.h>
#define ENTIER_MAX 4294967295 //~le nombre de couleurs possibles.
#define MAX_RULES 50 //~la taille du tableau de regle de type struct rule.
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

/*struct xyr{
  struct coord xy;
  struct rule* regle;}; //couple xy,&(regle_a_appliquer)*/

struct coord2{
  struct coord x_y;
  int color;};//relatif a la case qui va se voir affecter la valeur
//du champ color.

struct file f;
struct file ff;
struct rules regles;
struct world ww;


void create_random_world(struct world* monde, unsigned int seed);
void print_created_random_world(struct world* monde);
void world_init();

//algo iteration qui permet de faire tours tours de boucle.
//prend une structure contenant un tableau de regles, c'est la donnee
//globale: struct rules regles.
void algo_iteration_2(struct world* w,unsigned int tours,struct rules* rls,unsigned int numero_determinisme){
  //permet de faire des iterations depuis un world *w suivant un ensemble
  //de regles (struct rule (*rls).rs[]).
  printf("%d %d\n",HEIGHT,WIDTH);
  print_created_random_world(w);
  //file_init() pas la peine depuis le main.(ET AUSSI: file_init2();).
  unsigned int nombre_de_regles=rules_count();//globale en regles(struct rules)
  //on dispose ici du nombre de regles a verifier avec chaque (i,j)
  //dans le monde (on peut pas avoir (i,j)matches avec plusieurs regles sinon
  //ca sera la meme regle qui code le voisinage et la couleur que doit
  //avoir la cellule).((sinon choix multiples pour un meme matching=>pas
  //nouvelle regle mais indeterminisme sur le choix suivant un matching precis))
  int h;
  for(int k=0;k<tours;k++){//faire k fois cela:
    h=0;//compteur de matching pour le tour numero k.
    //iterer sur tous les (i,j) en fixant chacun d'eux et en iterant sur
    //l'ensemble des regles pour choisir la regle qui marchera(qui matches avec
    //(i,j)).
    for(int i=0;i<HEIGHT;i++){
      for(int j=0;j<WIDTH;j++){
	for(int n=0;n<nombre_de_regles;n++){
	  //recuperer la regle et tester si ca va matcher avec le couple (i,j)
	  struct rule *regle_h=rule_get(n);//&(regles.rs[n])
	  if(rule_match(w,regle_h,i,j)){
	    h++;
	    //enfiler sur la file directement (les conflits seront geres apres)
	    struct coord couple={i,j};
	    ajouter_elt(&f,couple,regle_h);
	    ajouter_elt(&ff,couple,regle_h);}}}}
    //h va etre ~ la longueur de la file.
    struct coord2 new_indices[h+1];//tableau de h elements contenant les
    //nouveaux indices x+dx et y+dy relatives a chaque changement (element
    //de la file))
    int p=0;struct file* ptr=&f;
    while(p<h){//new_indices[p] est un de type struct coord.
      new_indices[p].x_y.abs=(ptr->next)->regle->dx[numero_determinisme];
      new_indices[p].x_y.abs+=(ptr->next)->xy.abs;
      new_indices[p].x_y.ord=(ptr->next)->regle->dy[numero_determinisme];
      new_indices[p].x_y.ord+=(ptr->next)->xy.ord;
      new_indices[p].color=(ptr->next)->regle->new_color[numero_determinisme];
      ptr=ptr->next;
      p++;}
    int combien(struct coord2 tab[],struct coord xy,int len){
      int compteur=0;
      for (int z=0;z<len;z++){
	if(tab[z].x_y.abs==xy.abs && tab[z].x_y.ord==xy.ord) compteur++;}
      return compteur;}
    int dernier(struct coord2 tab[],struct coord xy, int len){
      int zz;//forcement il existera un indice pour lequel lelement
      //appartient.
      for (int z=0;z<len;z++){//correspondance entre new_indices et la file
	//donc le dernier element trouve quivant new_indices
	//lui correspond en terme d'indice le dernier x,y qui evalue ce
	//potentiel deplacement dans l'ordre de la file.
	if(tab[z].x_y.abs==xy.abs && tab[z].x_y.ord==xy.ord) zz=z;}
 return zz;} //suppose que l'element existe deja, ca retourne l'indice de la derniere case le contenant.
    int l=0;struct file* ptr2=&ff;
    //afficher_file(&ff);(verifier)
    while(l<h){//h==nombre d'elements de la file.
      int x=(ptr2->next)->xy.abs;
      int y=(ptr2->next)->xy.ord;
      int x_dx=(ptr2->next)->regle->dx[numero_determinisme];
      int y_dy=(ptr2->next)->regle->dy[numero_determinisme];
      int new_x=x+x_dx;
      int new_y=y+y_dy;
      int color_xy=(ptr2->next)->regle->new_color[numero_determinisme];
      struct coord xy={new_x,new_y};
      int combien_new_couple=combien(new_indices,xy,h);
      //nombre de cases voulant se deplacer au meme endroit.
      if(combien_new_couple>=2){//conflit
      int indice_interessant_pour_xy=dernier(new_indices,xy,h);
      struct coord2 xxyy=new_indices[indice_interessant_pour_xy];
      if(xxyy.color==color_xy){//le x,y dans la file correspond au
	//dernier element marquant le deplacement commun x+dx,y+dy.
	//la case xy devient noire et application de la modification
	//suivant x+dx,y+dy,color cad. xxyy (de type struct coord2)
	w->t[x*WIDTH+y]=0;
	int xdx=xxyy.x_y.abs;
	int ydy=xxyy.x_y.ord;
	if(xdx>=HEIGHT){//la prochaine case a se voir affecter la couleur
	  //se trouve en HEIGHT au moins on doit retrancher a xdx(le nouveau
	  //abcisse) HEIGHT pour avoir quelque chose>=0 (si HEIGHT donc
	  //vers le haut (ligne 0))
	  xxyy.x_y.abs=xdx-HEIGHT;}
	if(ydy>=WIDTH){//de meme.
	  xxyy.x_y.ord=ydy-WIDTH;}
	if(xdx<0){
	  xxyy.x_y.abs=HEIGHT+xdx;}
	if(ydy<0){
	  xxyy.x_y.ord=WIDTH+ydy;}//de meme la meme chose
	//cas minimale: ydy=-1 pour avoir deplacement tout en bas
	//en case HEIGHT-1 ou WIDTH-1.
	w->t[xxyy.x_y.abs * WIDTH + xxyy.x_y.ord]=xxyy.color;
      }}
      else{//pas de conflit le deplacement est unique parmi tous les deplacements dans l'ordre de la file calcules.
	w->t[x*WIDTH+y]=0;
	if(new_x>=HEIGHT){
	  new_x=new_x-HEIGHT;}
	if(new_y>=WIDTH){
	  new_y=new_y-WIDTH;}
	if(new_x<0){
	  new_x=HEIGHT+new_x;}
	if(new_y<0){
	  new_y=WIDTH+new_y;}
	w->t[new_x*WIDTH+new_y]=color_xy;}
      l++;ptr2=ptr2->next;}
    file_init();
    file_init2();print_created_random_world(w);}}
      
      
int main(int argc, char* argv[]){
  //initialiser le world et les regles tout au debut.
  rules_init();//regles dispos.(struct rules regles)
  world_init();//ww disponible.(tableau de couleurs aleatoires)
  //essayons de programmer au debut une case centrale qui va se deplacer
  //vers le bas.(HEIGHT==WIDTH==3)
  /*  ww.t[4]=JAUNE;
  for(int v=0;v<HEIGHT*WIDTH;v++){
    if(v!=4) ww.t[v]=BLANC;}
  //1 seul regle=>regles.rs[0] a modifier:>>
  int m=0;
  while(m<8){
    regles.rs[0].voisins[m]=BLANC;m++;}
  regles.rs[0].own_color=JAUNE;
  regles.rs[0].new_color[0]=ROUGE;
  regles.rs[0].dx[0]=1;
  regles.rs[0].dy[0]=0;
  //prototype de la fonction:
  //algo_iteration_2(struct world* w,unsigned int tours, struct rules* rs, unsigned int numero_determinisme)
  */
  char optstring[]="m";int c;int iterations;
  while((c=getopt(argc,argv,optstring))!=EOF){
    switch(c){
    case 'm':
      iterations=atoi(argv[optind]);
      break;}}
  //ici on changera nos regles et le monde..
  int index=(HEIGHT-1)/2;//case centrale.
  int index1_x=index-1;int index1_y=index+1;
  int index2_x=index-1;int index2_y=index-1;
  int index3_x=index+1;int index3_y=index-1;
  int index4_x=index+1;int index4_y=index+1;
  int index1=index1_x*WIDTH+index1_y;
  int index2=index2_x*WIDTH+index2_y;
  int index3=index3_x*WIDTH+index3_y;
  int index4=index4_x*WIDTH+index4_y;
  ww.t[index1]=JAUNE;
  ww.t[index2]=ROUGE;
  ww.t[index3]=BLEU;
  ww.t[index4]=VERT;
  for(int v=0;v<HEIGHT*WIDTH;v++){
    if(v!=index1 && v!=index2 && v!=index3 && v!=index4){
      ww.t[v]=0;}}
  for(int w=0;w<4;w++){//updater 4 regles.
    for(int y=0;y<8;y++){
      regles.rs[w].voisins[y]=0;}
    if(w==0) regles.rs[w].own_color=JAUNE;
    if(w==1) regles.rs[w].own_color=ROUGE;
    if(w==2) regles.rs[w].own_color=BLEU;
    if(w==3) regles.rs[w].own_color=VERT;
    if(w==0) regles.rs[w].new_color[0]=JAUNE;
    if(w==1) regles.rs[w].new_color[0]=ROUGE;
    if(w==2) regles.rs[w].new_color[0]=BLEU;
    if(w==3) regles.rs[w].new_color[0]=VERT;
    if(w==0){regles.rs[w].dx[0]=-1;regles.rs[w].dy[0]=1;}
    if(w==1){regles.rs[w].dx[0]=-1;regles.rs[w].dy[0]=-1;}
    if(w==2){regles.rs[w].dx[0]=1;regles.rs[w].dy[0]=-1;}
    if(w==3){regles.rs[w].dx[0]=1;regles.rs[w].dy[0]=1;}
  }
  for(int a=4;a<8;a++){
    //updater la regle regles.rs[a].
    if(a==4){//regles.rs[4]
      regles.rs[a].voisins[0]=VERT;
      regles.rs[a].voisins[1]=BLEU;
      regles.rs[a].voisins[3]=JAUNE;
      for(int b=0;b<8;b++){
	if(b!=0 && b!=1 && b!=3) regles.rs[a].voisins[b]=0;}
      regles.rs[a].own_color=ROUGE;
      regles.rs[a].new_color[0]=ROUGE;
      regles.rs[a].dx[0]=-1+(HEIGHT-1)/2;
      regles.rs[a].dy[0]=-1+(HEIGHT-1)/2;}
    if(a==5){//regles.rs[5]
      regles.rs[a].voisins[1]=VERT;
      regles.rs[a].voisins[2]=BLEU;
      regles.rs[a].voisins[4]=ROUGE;
      for(int b=0;b<8;b++){
	if(b!=1 && b!=2 && b!=4) regles.rs[a].voisins[b]=0;}
      regles.rs[a].own_color=JAUNE;
      regles.rs[a].new_color[0]=JAUNE;
      regles.rs[a].dx[0]=-1+(HEIGHT-1)/2;
      regles.rs[a].dy[0]=1+1-WIDTH+(HEIGHT-1)/2;}
    if(a==6){//regles.rs[6]
      regles.rs[a].voisins[4]=BLEU;
      regles.rs[a].voisins[6]=JAUNE;
      regles.rs[a].voisins[7]=ROUGE;
      for(int b=0;b<8;b++){
	if(b!=4 && b!=6 && b!=7) regles.rs[a].voisins[b]=0;}
      regles.rs[a].own_color=VERT;
      regles.rs[a].new_color[0]=VERT;
      regles.rs[a].dx[0]=1-HEIGHT+(HEIGHT-1)/2+1;
      regles.rs[a].dy[0]=1-HEIGHT+(HEIGHT-1)/2+1;}
    if(a==7){//regles.rs[7]
      regles.rs[a].voisins[3]=VERT;
      regles.rs[a].voisins[6]=ROUGE;
      regles.rs[a].voisins[5]=JAUNE;
      for(int b=0;b<8;b++){
	if(b!=6 && b!=3 && b!=5) regles.rs[a].voisins[b]=0;}
      regles.rs[a].own_color=BLEU;
      regles.rs[a].new_color[0]=BLEU;
      regles.rs[a].dx[0]=2-HEIGHT+(HEIGHT-1)/2;
      regles.rs[a].dy[0]=(HEIGHT-1)/2 -1;}
  }   
    file_init();
    file_init2();
  algo_iteration_2(&ww,iterations,&regles,0);
  //c'est un code tres general: il lui suffit le tableau de regles
  //le nombre d'iterations, le numero fixant l'indeterminisme(qui peut
  //etre suivant un rand dans le main(il suffit que ca correspond a
  //une nouvelle couleur!=-1 pour eviter les confusions)) et un tableau
  //de regles(struct rule) quelconque.
  return 0;}


  





























































