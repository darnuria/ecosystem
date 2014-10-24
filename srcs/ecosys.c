
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "ecosys.h"

#define EPSILON 0.00001
// Deps
#include "list.h"

/* Pour utiliser la correction automatique:
   cavecorrector 6-7 repertoire
   */

static
int random_range(int range) {
  int random = abs(rand()) % range;
  if (random == 0) {
    return -1;
  } else if (random == 1) {
    return 0;
  } else {
    return 1;
  }
}

static
animal_data_t *animal_data_new(int x, int y, float energie) {
  animal_data_t *animal = malloc(sizeof(animal_data_t));

  if (animal) {
    animal->x = x;
    animal->y = y;
    animal->dir[0] = random_range(2);
    animal->dir[1] = random_range(2);
    animal->energie = energie;
  } else {
    perror("animal_data_new: ");
  }
  return animal;
}

static
bool animal_eq(const animal_data_t *a1, const animal_data_t *a2) {
  return (a1->x == a2->x &&
      a1->y == a2->y &&
      a1->dir[0] == a2->dir[0] &&
      a1->dir[1] == a2->dir[1] &&
      (fabsf(a1->energie - a2->energie) < EPSILON));
}


animal_t *creer_animal(int x, int y, float energie) {
  animal_t *animal_list = NULL;
  animal_data_t *animal = animal_data_new(x, y, energie);

  if (animal) {
    animal_list = list_new_shallow(animal);
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

void ajouter_animal(int x, int y, animal_t **liste_animal) {
  animal_t *new_lst = creer_animal(x, y, energie_g);

  if (new_lst) {
    *liste_animal = ajouter_en_tete_animal(*liste_animal, new_lst);
  } else {
    perror("ajouter_animal: ");
  }
}

void enlever_animal(animal_t **liste, animal_t *animal) {
  list_t *poped = list_pop(*liste, (bool (*)(const void*, const void*)) &animal_eq, animal);
  free(poped);
}

unsigned int compte_animal_rec(animal_t *la) {
  (void) la;
  return 0;
}

unsigned int compte_animal_it(animal_t *la) {
  return (list_length(la));
}

void bouger_animaux(animal_t *la) {
  (void) la;
  /* a completer */
}

void reproduce(animal_t **liste_animal) {
  (void) liste_animal;
  /* a completer */
}

void rafraichir_proies(animal_t **liste_proie) {
  (void) liste_proie;
  /* a completer */
}

animal_t *animal_en_XY(animal_t *l, int x, int y) {
  (void) l;
  (void) x;
  (void) y;
  /* a completer */
  return NULL;
}

void rafraichir_predateurs(animal_t **liste_predateur, animal_t **liste_proie) {
  (void) liste_predateur;
  (void) liste_proie;
  /* a completer */
}

static
void* memcalloc(size_t size, size_t word_size, char placeholder) {
    char *string = malloc(size * word_size);
    memset(string, placeholder, size);
}

void set(char *map, int x, int y, char val) {
  ASSERT!(x <= SIZE_X);
  ASSERT!(y <= SIZE_Y);
  map[x + SIZE_Y * y] = val;
}

void afficher_ecosys(animal_t *liste_proie, animal_t *liste_predateur) {
  static char *map = memcalloc(size, word_size, ' ');
  for (list_t *tmp = liste_proie; tmp != NULL; tmp = tmp->next) {
    set(map, tmp->x, tmp->y, 'O');
  }
  for (list_t *tmp = liste_proie; tmp != NULL; tmp = tmp->next) {
    set(map, tmp->x, tmp->y, '@');
  }
  for (size_t i = 0; i < SIZE_Y; i += 1) {
    write(1, map * SIZE_Y, SIZE_X);
    putchar('\n');
  }
}

void clear_screen(void) {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}
