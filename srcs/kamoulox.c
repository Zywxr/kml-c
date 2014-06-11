#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include "kml.h"
#include "error.h"
#include "utils.h"

char *fill(s_kml *kml, char *str) {
  unsigned int i;
  char *filler[] = {"$nom$", "$noms$", "$nompropre$", "$nomspecial$",
		    "$un$", "$le$", "$mon$", 
		    "$verbe$", "$complement$", NULL};
  s_kmllist *cat;
  int rd;
  char gender;
  char *tmp;

  gender = 'M';
  for (i = 0; filler[i] != NULL; i++) {
    cat = NULL;
    if (contains(str, filler[i]) == FAILURE)
      continue ;
    if (!strcmp(filler[i], "$nom$")
	|| !strcmp(filler[i], "$noms$")
	|| !strcmp(filler[i], "$nomspecial$")
	|| !strcmp(filler[i], "$nompropre$")) {
      rd = rand() % kml->kmlcat->nom->len;
      if (!strcmp(filler[i], "$nom$")) {
	gender = kml->kmlcat->gender[rd];
	str = supreplace(filler[i], kml->kmlcat->nom->list[rd], str);
      }
      if (!strcmp(filler[i], "$noms$"))
	str = supreplace(filler[i], kml->kmlcat->noms->list[rd], str);
      if (!strcmp(filler[i], "$nomspecial$")) {
	rd = rand() % kml->kmlcat->nomspecial->len;
	str = supreplace(filler[i], kml->kmlcat->nomspecial->list[rd], str);
      }
      if (!strcmp(filler[i], "$nompropre$")) {
	rd = rand() % kml->kmlcat->nompropre->len;
	str = supreplace(filler[i], kml->kmlcat->nompropre->list[rd], str);
      }
      continue ;
    }
    tmp = str; /* Save address for free later */
    if (!strcmp(filler[i], "$un$"))
      str = supreplace(filler[i], gender == 'M' ? "un" : "une", str);
    else if (!strcmp(filler[i], "$le$"))
      str = supreplace(filler[i], gender == 'M' ? "le" : "la", str);
    else if (!strcmp(filler[i], "$mon$"))
      str = supreplace(filler[i], gender == 'M' ? "mon" : "ma", str);
    else if (!strcmp(filler[i], "$verbe$")) {
      rd = rand() % kml->kmlcat->inf->len;
      str = supreplace(filler[i], kml->kmlcat->inf->list[rd], str);
    }      
    else if (!strcmp(filler[i], "$complement$")) {
      cat = gender == 'M' ? kml->kmlcat->comp_m : kml->kmlcat->comp_f;
      str = supreplace(filler[i], cat->list[rand() % cat->len], str);
    }
    if (tmp != str)
      free(tmp);
  }
  return (str);
}

void kamoulox_t1_part(s_kml *kml) {
  int r1;
  char *v;
  
  if ((rand() % 5) == 2) {
    /* Avec nompropre */
    v = kml->kmlcat->verbe->list[rand() % kml->kmlcat->verbe->len];
    r1 = rand() % kml->kmlcat->nompropre->len;
    printf("%s %s", v, 
	   kml->kmlcat->nompropre->list[r1]);
  }
  else {
    /* Avec nom */
    r1 = rand() % kml->kmlcat->nom->len;
    v = kml->kmlcat->verbe->list[rand() % kml->kmlcat->verbe->len];
    printf("%s %s %s", v,
	   kml->kmlcat->gender[r1] == 'M' ? "un" : "une", 
	   kml->kmlcat->nom->list[r1]);
    /* On rajoute un complement ? */
    if ((rand() % 4) == 2) {
      if (kml->kmlcat->gender[r1] == 'M') {
	r1 = rand() % kml->kmlcat->comp_m->len;
	printf(" %s", kml->kmlcat->comp_m->list[r1]);
      }
      else {
	r1 = rand() % kml->kmlcat->comp_f->len;
      	printf(" %s", kml->kmlcat->comp_f->list[r1]);
      }
    }
  }
} 

/* Premier type de Kamoulox : je verbe un nom... */
int kamoulox_t1(s_kml *kml) {
  kamoulox_t1_part(kml);
  printf(" et ");
  kamoulox_t1_part(kml);
  printf(".\n");
  return (SUCCESS);
}

/* Second type de Kamoulox : nomspecial et nomspecial */
int kamoulox_t2(s_kml *kml) {
  char *v1;

  v1 = kml->kmlcat->nomspecial->list[rand() %
				     kml->kmlcat->nomspecial->len];
  printf("%s et %s.\n", v1,
	 kml->kmlcat->nomspecial->list[rand() %
				       kml->kmlcat->nomspecial->len]);
  return (SUCCESS);
}

int kamoulox(s_kml *kml) {
  /* Choix du type de phrase (type 1 ou 2) */
  if ((rand() % 5) == 2)
    return kamoulox_t2(kml);
  return kamoulox_t1(kml);
}

char *familyname(char *str) {
  return (replace(' ', '-', capt(str)));
}

int kamounom(s_kml *kml) {
  printf("%s %s\n",
	 capt(kml->kmlcat->prenom->list[rand() %
					kml->kmlcat->prenom->len]),
	 familyname(kml->kmlcat->nom->list[rand() %
					   kml->kmlcat->nom->len]));
  return (SUCCESS);
}

/* Kamouscuse : Prescuse, scuse1 scuse2 */
int kamouscuse(s_kml *kml) {
  char *s1;
  char *s2;
  int rd;

  rd = rand() % kml->kmlcat->scuse1->len;
  if ((s1 = fill(kml, kml->kmlcat->scuse1->list[rd])) == NULL)
    return (error(E_ERROR, NULL));
  rd = rand() % kml->kmlcat->scuse2->len;
  if ((s2 = fill(kml, kml->kmlcat->scuse2->list[rd])) == NULL) {
    free(s1);
    return (error(E_ERROR, NULL));      
  }
  rd = rand() % kml->kmlcat->prescuse->len;
  printf("%s, %s %s.\n",
	 capt(kml->kmlcat->prescuse->list[rd]),
	 s1, s2);
  free(s1);
  free(s2);
  return (SUCCESS);
}

int kamousulte(s_kml *kml) {
  char *s1;
  int rd;

  if ((rand() % 3) == 1) {
    printf("espèce de ");
  } 
  if ((rand() % 3) == 1) {
    rd = rand() % kml->kmlcat->presulte->len;
    printf("%s ", kml->kmlcat->presulte->list[rd]);
  }
  /* Sulte */
  rd = rand() % kml->kmlcat->sulte->len;
  if ((s1 = fill(kml, kml->kmlcat->sulte->list[rd])) == NULL)
    return (error(E_ERROR, NULL));
  printf("%s", s1);
  if ((rand() % 3) == 1) {
    rd = rand() % kml->kmlcat->postsulte->len;
    printf(" %s", kml->kmlcat->postsulte->list[rd]);
  }
  printf(".\n");
  free(s1);
  return (SUCCESS);
}
