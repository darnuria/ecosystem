#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "ecosys.h"
#include "list.h"

/*
 * Pour utiliser la correction automatique:
 * cavecorrector 6-7 repertoire
 */

static
int toric_coordinate(int x, int dir, int size) {
  return (x + dir + size) % size;
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

static
bool dead_or_alive(const animal_data_t *cmp, const animal_data_t *placeholder) {
  (void)placeholder;
  return (cmp->energie < 1.000);
}

static
void update_energy_proie(animal_data_t *animal) {
  animal->energie -= d_proie;
}

static
void rafraichir_proies_aux(animal_data_t *animal) {
  bouger_animaux(animal);
  update_energy(animal);
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
  list_t *poped = list_pop(*liste,
      (bool (*)(const void*, const void*)) &animal_eq, animal);
  free(poped);
}

unsigned int compte_animal_rec(animal_t *la) {
  if (la == NULL) {
    return 0;
  } else {
    return 1 + compte_animal_rec(la->suivant);
  }
}

unsigned int compte_animal_it(animal_t *la) {
  return (list_length(la));
}

void bouger_animaux(animal_t *la) {
  la->x = toric_coordinate(la->x, la->dir[0], SIZE_X);
  la->y = toric_coordinate(la->y, la->dir[1], SIZE_Y);
  if (p_ch_dir > rand() / RAND_MAX){
    la->dir [0] = rand() % 3 - 1;
    la->dir [1] = rand() % 3 - 1;
  }
}

void reproduce(animal_t **liste_animal) {
  for (animal_t *tmp = *list_animal; tmp != NULL; tmp = tmp-next) {
    if (p_reproduce > rand() / RAND_MAX) {
      ajouter_animal(tmp->x, tmp->y, *liste_animal);
    }
  }
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
