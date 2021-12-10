#include<stdio.h>
#include<stdlib.h>
#include "../src/code_queue.h"
#define BLANC 16777215
#define JAUNE 16776960
#include<time.h>
#define BLEU 255
#define ENTIER_MAX 4294967295
#define LEN_MAX 100

struct file f;


int main(int argc, char* argv[]){
  rules_init();
  queue_init();
  display_rxy(f.couple_rxy[0]);
  printf("---------------\n");
display_file(f);
 printf("------------------\n");
 printf("la file vide ou pas vide?->%d\n",file_vide(f));
 printf("------------------\n");
 struct rule_index rule_index1;
 rule_index1.rules=rules1;
 rule_index1.xy[0]=1;
 rule_index1.xy[1]=1;
struct rule_index rule_index2;
 rule_index2.rules=rules1;
 rule_index2.xy[0]=0;
 rule_index2.xy[1]=0;
 ajout_file(&f,rule_index2);
 display_file(f);
 ajout_file(&f,rule_index1);
 ajout_file(&f,rule_index1);
 printf("-------------------\n");
 display_file(f);
 printf("-----------------\n");
 delete_file(&f);
 display_file(f);
 printf("-------------\n");
 afficher_head_queue(&f);
 delete_file(&f);
 printf("--------------\n");display_file(f);printf("-----------\n");
 afficher_head_queue(&f);
  return 0;}
