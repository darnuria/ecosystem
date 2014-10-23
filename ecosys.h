#ifndef _ECOSSYS_H_
#define _ECOSYS_H_

#define SIZE_X 20
#define SIZE_Y 20

typedef list_t animal_t;
typedef struct _animal {
  int x;
  int y;
  int dir[2]; // direction courante sous la forme (dx, dy)
  float energie;
} animal_data_t;

extern float p_ch_dir = 0.01;
extern float d_proie = 1;
extern float d_predateur = 1;
extern float p_manger = 0.2;
extern float p_reproduce = 0.01;
extern float energie = 50;

animal_t *creer_animal(int x, int y, float energie);
animal_t *ajouter_en_tete_animal(animal_t *liste, animal_t *animal);
void ajouter_animal(int x, int y, animal_t **liste_animal);
void enlever_animal(animal_t **liste, animal_t *animal);
unsigned int compte_animal_rec(animal_t *la);
unsigned int compte_animal_it(animal_t *la);
void bouger_animaux(animal_t *la);
animal_t *animal_en_XY(animal_t *l, int x, int y);
void rafraichir_predateurs(animal_t **liste_predateur, animal_t **liste_proie);
void rafraichir_proies(animal_t **liste_proie);
void afficher_ecosys(animal_t *liste_predateur, animal_t *liste_proie);
void clear_screen();

#endif
