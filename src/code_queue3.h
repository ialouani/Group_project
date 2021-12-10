#ifndef __R
#define __R
#include "rule.h"

struct file;
struct coord;


void file_init();
void file_init2();
void afficher_premier_elt(struct file* f);
void ajouter_elt(struct file* f, struct coord co, struct rule* r);
void supprimer_premier_elt(struct file* f);
void afficher_file(struct file* f);


#endif
