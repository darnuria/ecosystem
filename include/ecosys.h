#ifndef ECOSYS_H
# define ECOSYS_H

#include "list.h"

# define SIZE_X 20
# define SIZE_Y 20
# define EPSILON 0.00001

typedef list_t animal_t;
typedef struct _animal {
  int x;
  int y;
  int dir[2]; // direction courante sous la forme (dx, dy)
  float energie;
} animal_data_t;

static const float p_ch_dir_g = 0.01;
static const float d_proie_g = 1;
static const float d_predateur_g = 1;
static const float p_manger_g = 0.2;
static const float p_reproduce_g = 0.01;
static const float energie_g = 50;

animal_t *creer_animal(int x, int y, float energie);
animal_t *ajouter_en_tete_animal(animal_t *liste, animal_t *animal);
void ajouter_animal(int x, int y, animal_t **liste_animal);
void enlever_animal(animal_t **liste, animal_t *animal);
unsigned int compte_animal_rec(const animal_t *la);
unsigned int compte_animal_it(const animal_t *la);
void bouger_animaux(animal_data_t *la);
// animal_t *animal_en_XY(animal_t *l, int x, int y);
void rafraichir_predateurs(animal_t **liste_predateur, animal_t **liste_proie);
void rafraichir_proies(animal_t **liste_proie);
void afficher_ecosys(animal_t *liste_predateur, animal_t *liste_proie, char *map);
void clear_screen(void);
void reproduce(animal_t **liste_animal);

#endif // ECOSYS_H
