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

int kamoulox(s_kml *kml) {
  int r;
  char *n1, *n2;
  char g1, g2;
  char *v1, *v2;

  r = rand() % kml->kmlcat->l_nom;
  n1 = kml->kmlcat->nom[r];
  g1 = kml->kmlcat->gender[r];
  v1 = kml->kmlcat->verbe[rand() % kml->kmlcat->l_verbe];
  if (!n1 || !g1 || !v1)
    return (FAILURE);

  r = rand() % kml->kmlcat->l_nom;
  n2 = kml->kmlcat->nom[r];
  g2 = kml->kmlcat->gender[r];
  v2 = kml->kmlcat->verbe[rand() % kml->kmlcat->l_verbe];
  if (!n2 || !g2 || !v2)
    return (FAILURE);

  printf("%s %s %s et %s %s %s.\n", 
	 capt(v1), g1 == 'M' ? "un" : "une", n1, 
	 v2, g2 == 'M' ? "un" : "une", n2);
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
