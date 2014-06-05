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

int isnum(char *opt) {
  unsigned int i;

  if (!strlen(opt))
    return (FAILURE);
  for (i = 0; i < strlen(opt); i++)
    if (opt[i] < '0' || opt[i] > '9')
      return (FAILURE);
  return (SUCCESS);
}

void debug(s_kml *kml) {
  /* UGLY, but who cares? it's debug */
  int ct;

  for (ct = 0; ct < kml->kmlcat->nom->len; ct++) {
    if (kml->kmlcat->nom->list[ct] != NULL)
      printf("Nom: %s.\n", kml->kmlcat->nom->list[ct]);
  }
  for (ct = 0; ct < kml->kmlcat->nompropre->len; ct++) {
    if (kml->kmlcat->nompropre->list[ct] != NULL)
      printf("Nompropre: %s.\n", kml->kmlcat->nompropre->list[ct]);
  }
  for (ct = 0; ct < kml->kmlcat->nomspecial->len; ct++) {
    if (kml->kmlcat->nomspecial->list[ct] != NULL)
      printf("Nomspecial: %s.\n", kml->kmlcat->nomspecial->list[ct]);
  }
  for (ct = 0; ct < kml->kmlcat->comp_m->len; ct++) {
    if (kml->kmlcat->comp_m->list[ct] != NULL
	&& kml->kmlcat->comp_f->list[ct] != NULL)
      printf("Complement: %s - %s.\n", kml->kmlcat->comp_m->list[ct],
	     kml->kmlcat->comp_f->list[ct]);
  }
  for (ct = 0; ct < kml->kmlcat->verbe->len; ct++) {
    if (kml->kmlcat->verbe->list[ct] != NULL)
      printf("Verbe: %s.\n", kml->kmlcat->verbe->list[ct]);
  }
}
