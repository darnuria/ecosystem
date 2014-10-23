
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

// Deps
#include "list.h"

/* Pour utiliser la correction automatique:
   cavecorrector 6-7 repertoire
   */

static
animal_data_t *animal_data_new(int x, int y, float energie) {
  animal_data_t *animal = malloc(sizeof(animal_data_t));

  if (animal) {
    animal->x = x;
    animal->y = y;
    animal->energie = energie;
    animal->dir[0] = 0;
    animal->dir[1] = 0;
  } else {
    perror("animal_data_new: ");
  }
  return animal;
}


animal_t *creer_animal(int x, int y, float energie) {
  animal_t *animal_list = NULL;
  animal_data_t animal = animal_data_new(x, y, energie);

  if (animal) {
    animal_list = list_new(animal);
    if (animal_list == NULL) {
      perror("creer_animal: ");
      free(animal);
    }
  }
  return animal_list;
}

animal_t *ajouter_en_tete_animal(animal_t *liste, animal_t *animal) {
  return list_concat(animal, liste);
}

static
int find_animal_aux(animal_data_t *data, animal_data_t *to_find) {
  (void) data;
  (void) to_find;
  return (0);
}

void ajouter_animal(int x, int y, animal_t **liste_animal) {
  animal_t *new_lst = creer_animal(x, y, energy_g);

  if (new_lst) {
    *liste_animal = ajouter_en_tete_animal(*liste_animal, new_lst);
  } else {
    perror("ajouter_animal: ");
  }
}

void enlever_animal(animal_t **liste, animal_t *animal) {

}

unsigned int compte_animal_rec(animal_t *la) {
  /* a completer */
  return 0;
}

unsigned int compte_animal_it(animal_t *la) {
  return (list_length(la));
}

void bouger_animaux(animal_t *la) {
  /* a completer */
}

void reproduce(animal_t **liste_animal) {
  /* a completer */
}

void rafraichir_proies(animal_t **liste_proie) {
  /* a completer */
}

animal_t *animal_en_XY(animal_t *l, int x, int y) {
  /* a completer */
  return NULL;
}

void rafraichir_predateurs(animal_t **liste_predateur, animal_t **liste_proie) {
  /* a completer */

}

void afficher_ecosys(animal_t *liste_proie,animal_t *liste_predateur) {
  /* a completer */

}

void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}
