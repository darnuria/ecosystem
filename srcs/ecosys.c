
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

// Deps
#include "list.h"

/* Pour utiliser la correction automatique:
cavecorrector 6-7 repertoire
 */

animal_t *creer_animal(int x, int y, float energie) {
  animal_data_t *animal = malloc(sizeof(animal_data_t));
  animal_t *animal_list = NULL;

  if (animal) {
    animal->x = x;
    animal->y = y;
    animal->energie = energie;
    animal->dir[0] = 0;
    animal->dir[1] = 0;
    animal_list = list_new(animal);
    if (animal_list == NULL) {
      perror("creer_animal: ");
      free(animal);
      return NULL;
    }
  } else {
    perror("creer_animal: ");
  }
  return animal_list;
}

animal_t *ajouter_en_tete_animal(animal_t *liste, animal_t *animal) {
  /* a completer */
  return liste;
}

void ajouter_animal(int x, int y, animal_t **liste_animal) {
  /* a completer */
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
