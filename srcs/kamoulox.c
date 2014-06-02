#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include "kml.h"
#include "error.h"

char *capt(char *str) {
  if (str && strlen(str) > 0) {
    if (str[0] >= 'a' && str[0] <= 'z') {
      str[0] = str[0] - 32;
    }
  }
  return (str);
}

char *replace(char old, char new, char *str) {
  unsigned int i;

  if (!str)
    return (str);
  for (i = 0; i < strlen(str); i++) {
    if (str[i] == old)
      str[i] = new;
  }
  return (str);
}

char *familyname(char *str) {
  return (replace(' ', '-', capt(str)));
}

void kamoulox_t1_part(int turn, s_kml *kml) {
  int r1;
  char *v;

  if ((rand() % 5) == 2) {
    /* Avec nompropre */
    v = kml->kmlcat->verbe->list[rand() % kml->kmlcat->verbe->len];
    printf("%s %s", turn == 1 ? capt(v) : v, 
	   kml->kmlcat->nompropre->list[rand() % 
					kml->kmlcat->nompropre->len]);
  }
  else {
    /* Avec nom */
    r1 = rand() % kml->kmlcat->nom->len;
    v = kml->kmlcat->verbe->list[rand() % kml->kmlcat->verbe->len];
    printf("%s %s %s", turn == 1 ? capt(v) : v,
	   kml->kmlcat->gender[r1] == 'M' ? "un" : "une", 
	   kml->kmlcat->nom->list[r1]);
    /* On rajoute un complement ? */
    if ((rand() % 4) == 2) {
      if (kml->kmlcat->gender[r1] == 'M')
	printf(" %s", kml->kmlcat->comp_m->list[rand() %
						kml->kmlcat->comp_m->len]);
      else
      	printf(" %s", kml->kmlcat->comp_f->list[rand() %
						kml->kmlcat->comp_f->len]);
    }
  }
} 

/* Premier type de Kamoulox : je verbe un nom... */
int kamoulox_t1(s_kml *kml) {
  kamoulox_t1_part(1, kml);
  printf(" et ");
  kamoulox_t1_part(2, kml);
  printf(".\n");
  return (SUCCESS);
}

/* Second type de Kamoulox : nomspecial et nomspecial */
int kamoulox_t2(s_kml *kml) {
  printf("%s et %s.\n",
	 capt(kml->kmlcat->nomspecial->list[rand() %
					    kml->kmlcat->nomspecial->len]),
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

int kamounom(s_kml *kml) {
  printf("%s %s\n",
	 capt(kml->kmlcat->prenom->list[rand() %
					kml->kmlcat->prenom->len]),
	 familyname(kml->kmlcat->nom->list[rand() %
					   kml->kmlcat->nom->len]));
  return (SUCCESS);
}

int kamouscuse(s_kml *kml) {
  char* kamoustr;

  kamoustr = "KAMOUSCUSE !";
  kml = kml;
  return (SUCCESS);
}

int kamousulte(s_kml *kml) {
  char* kamoustr;

  kamoustr = "KAMOUSULTE !";
  kml = kml;
  return (SUCCESS);
}
