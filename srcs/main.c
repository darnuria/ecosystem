#include "ecosys.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>

#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000

int main(void) {
  animal_t *liste_proie = NULL;
  animal_t *liste_predateur = NULL;

  /*/ Initialisation (comme main1.c) */

  srand(time(NULL));
  for(size_t i = 0; i < NB_PROIES; i += 1) {
    ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, &liste_proie);
  }
  for(size_t i = 0;i < NB_PREDATEURS; i += 1) {
    ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, &liste_predateur);
  }

  /* Suite à completer (simulation)*/

  return 0;
}

