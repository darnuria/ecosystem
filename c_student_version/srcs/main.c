#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>
#include <unistd.h>

#include "my_string.h"
#include "ecosys.h"

#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000
#define K_ITERATION 15

int main(void) {
  char *map = my_memcalloc(SIZE_X * SIZE_Y, sizeof(char), '.');
  animal_t *liste_proie = NULL;
  animal_t *liste_predateur = NULL;

  /*/ Initialisation (comme main1.c) */

  srand(time(NULL));
  for(size_t i = 0; i < NB_PROIES; i += 1) {
    ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, &liste_proie);
  }
  for(size_t i = 0; i < NB_PREDATEURS; i += 1) {
    ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, &liste_predateur);
  }
  for (size_t i = 0; i < K_ITERATION; i += 1) {
    clear_screen();
    printf("i: %zu\n", i);
    afficher_ecosys(liste_proie, liste_predateur, map);
    rafraichir_proies(&liste_proie);
    rafraichir_predateurs(&liste_predateur, &liste_proie);

    sleep(1);
  }

  free(map);
  list_delete(&liste_proie, free);
  list_delete(&liste_predateur, free);
  /* Suite à completer (simulation)*/

  return 0;
}

