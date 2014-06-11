#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include "kml.h"
#include "error.h"
#include "utils.h"

int init_category(s_kmllist *category) {
  int ct;

  if ((category->list = malloc(sizeof(char*) * MAX_SIZE)) == NULL)
    return (FAILURE);
  category->len = 0;
  for (ct = 0; ct < MAX_SIZE; ct++)
    category->list[ct] = NULL;
  return (SUCCESS);
}

void init_kmlcat_tonull(s_kml **kml) {
  /* Base */
  (*kml)->kmlcat->nom->list = NULL;
  (*kml)->kmlcat->noms->list = NULL;
  (*kml)->kmlcat->gender = NULL;
  (*kml)->kmlcat->nompropre->list = NULL;
  (*kml)->kmlcat->nomspecial->list = NULL;
  (*kml)->kmlcat->comp_m->list = NULL;
  (*kml)->kmlcat->comp_f->list = NULL;
  (*kml)->kmlcat->verbe->list = NULL;
  (*kml)->kmlcat->inf->list = NULL;
  (*kml)->kmlcat->prenom->list = NULL;
  /* Scuse */
  (*kml)->kmlcat->prescuse->list = NULL;
  (*kml)->kmlcat->scuse1->list = NULL;
  (*kml)->kmlcat->scuse2->list = NULL;
  /* Sulte */
  (*kml)->kmlcat->presulte->list = NULL;
  (*kml)->kmlcat->sulte->list = NULL;
  (*kml)->kmlcat->postsulte->list = NULL;
  return ;
}

int init_kmlcat_base(s_kml **kml) {
  if (init_category((*kml)->kmlcat->nom) == FAILURE)
    return (error(E_MALLOC, "kmlcat: nom"));
  if (init_category((*kml)->kmlcat->noms) == FAILURE)
    return (error(E_MALLOC, "kmlcat: noms"));
  if (((*kml)->kmlcat->gender = malloc(MAX_SIZE)) == NULL)
    return (error(E_MALLOC, "kmlcat: gender"));
  memset((*kml)->kmlcat->gender, 0, MAX_SIZE);
  if (init_category((*kml)->kmlcat->nompropre) == FAILURE)
    return (error(E_MALLOC, "kmlcat: nompropre"));
  if (init_category((*kml)->kmlcat->nomspecial) == FAILURE)
    return (error(E_MALLOC, "kmlcat: nomspecial"));
  if (init_category((*kml)->kmlcat->comp_m) == FAILURE)
    return (error(E_MALLOC, "kmlcat: comp_m"));
  if (init_category((*kml)->kmlcat->comp_f) == FAILURE)
    return (error(E_MALLOC, "kmlcat: comp_f"));
  if (init_category((*kml)->kmlcat->verbe) == FAILURE)
    return (error(E_MALLOC, "kmlcat: verbe"));
  if (init_category((*kml)->kmlcat->inf) == FAILURE)
    return (error(E_MALLOC, "kmlcat: inf"));
  if (init_category((*kml)->kmlcat->prenom) == FAILURE)
    return (error(E_MALLOC, "kmlcat: prenom"));
  return (SUCCESS);
}

int init_kmlcat_scuse(s_kml **kml) {
  if (init_category((*kml)->kmlcat->prescuse) == FAILURE)
    return (error(E_MALLOC, "kmlcat: prescuse"));
  if (init_category((*kml)->kmlcat->scuse1) == FAILURE)
    return (error(E_MALLOC, "kmlcat: scuse1"));
  if (init_category((*kml)->kmlcat->scuse2) == FAILURE)
    return (error(E_MALLOC, "kmlcat: scuse2"));
  return (SUCCESS);
}

int init_kmlcat_sulte(s_kml **kml) {
  if (init_category((*kml)->kmlcat->presulte) == FAILURE)
    return (error(E_MALLOC, "kmlcat: presulte"));
  if (init_category((*kml)->kmlcat->sulte) == FAILURE)
    return (error(E_MALLOC, "kmlcat: sulte"));
  if (init_category((*kml)->kmlcat->postsulte) == FAILURE)
    return (error(E_MALLOC, "kmlcat: postsulte"));
  return (SUCCESS);
}

int init_kmlcat(s_kml **kml) {
  /* Set them all to NULL here in case of failure */
  init_kmlcat_tonull(kml);

  if (init_kmlcat_base(kml) == FAILURE)
    return (FAILURE);
  if (init_kmlcat_scuse(kml) == FAILURE)
    return (FAILURE);
  if (init_kmlcat_sulte(kml) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}

int init_kml_base(s_kml **kml) {
  if (((*kml)->kmlcat->nom = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: nom"));
  if (((*kml)->kmlcat->noms = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: noms"));
  if (((*kml)->kmlcat->nompropre = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: nompropre"));
  if (((*kml)->kmlcat->nomspecial = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: nomspecial"));
  if (((*kml)->kmlcat->comp_m = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: comp_m"));
  if (((*kml)->kmlcat->comp_f = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: comp_f"));
  if (((*kml)->kmlcat->verbe = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: verbe"));
  if (((*kml)->kmlcat->inf = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: inf"));
  if (((*kml)->kmlcat->prenom = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: prenom"));
  return (SUCCESS);
}

int init_kml_scuse(s_kml **kml) {
  if (((*kml)->kmlcat->prescuse = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: prescuse"));
  if (((*kml)->kmlcat->scuse1 = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: scuse1"));
  if (((*kml)->kmlcat->scuse2 = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: scuse2"));
  return (SUCCESS);
}

int init_kml_sulte(s_kml **kml) {
  if (((*kml)->kmlcat->presulte = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: presulte"));
  if (((*kml)->kmlcat->sulte = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: sulte"));
  if (((*kml)->kmlcat->postsulte = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: postsulte"));
  return (SUCCESS);
}

int init_kml(s_kml **kml) {
  if ((*kml = malloc(sizeof(s_kml))) == NULL)
    return (error(E_MALLOC, "kml"));
  (*kml)->kmlcat = NULL;
  (*kml)->xml = NULL;
  (*kml)->cat = NONE;

  if (((*kml)->kmlcat = malloc(sizeof(s_kmlcat))) == NULL)
    return (error(E_MALLOC, "kmlcat"));

  if (init_kml_base(kml) == FAILURE)
    return (FAILURE);
  if (init_kml_scuse(kml) == FAILURE)
    return (FAILURE);
  if (init_kml_sulte(kml) == FAILURE)
    return (FAILURE);

  if (init_kmlcat(kml) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}
