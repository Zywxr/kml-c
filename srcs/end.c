#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include "kml.h"
#include "error.h"
#include "utils.h"

void free_category(char **category) {
  int ct;

  if (category != NULL) {
    for (ct = 0; ct < MAX_SIZE; ct++)
      if (category[ct] != NULL) {
	free(category[ct]);
	category[ct] = NULL;
      }
    free(category);
  }
}

void free_xml_base(s_kml **kml) {
  /* Nom */
  free_category((*kml)->kmlcat->nom->list);
  free((*kml)->kmlcat->nom);
  free_category((*kml)->kmlcat->noms->list);
  free((*kml)->kmlcat->noms);
  /* Gender */
  if ((*kml)->kmlcat->gender != NULL)
    free((*kml)->kmlcat->gender);
  /* Nom propre */
  free_category((*kml)->kmlcat->nompropre->list);
  free((*kml)->kmlcat->nompropre);
  /* Nom special */
  free_category((*kml)->kmlcat->nomspecial->list);
  free((*kml)->kmlcat->nomspecial);
  /* Complement */
  free_category((*kml)->kmlcat->comp_m->list);
  free((*kml)->kmlcat->comp_m);
  free_category((*kml)->kmlcat->comp_f->list);
  free((*kml)->kmlcat->comp_f);
  /* Verbe */
  free_category((*kml)->kmlcat->verbe->list);
  free((*kml)->kmlcat->verbe);
  free_category((*kml)->kmlcat->inf->list);
  free((*kml)->kmlcat->inf);
  /* Prenom */
  free_category((*kml)->kmlcat->prenom->list);
  free((*kml)->kmlcat->prenom);
}

void free_xml_scuse(s_kml **kml) {
  free_category((*kml)->kmlcat->prescuse->list);
  free((*kml)->kmlcat->prescuse);
  free_category((*kml)->kmlcat->scuse1->list);
  free((*kml)->kmlcat->scuse1);
  free_category((*kml)->kmlcat->scuse2->list);
  free((*kml)->kmlcat->scuse2);
}

void free_xml_sulte(s_kml **kml) {
  free_category((*kml)->kmlcat->presulte->list);
  free((*kml)->kmlcat->presulte);
  free_category((*kml)->kmlcat->sulte->list);
  free((*kml)->kmlcat->sulte);
  free_category((*kml)->kmlcat->postsulte->list);
  free((*kml)->kmlcat->postsulte);
}

void free_xml(s_kml **kml) {
  if (*kml != NULL) {
    xmlFreeDoc((*kml)->xml);
    xmlCleanupParser();
    if ((*kml)->kmlcat != NULL) {
      free_xml_base(kml);
      free_xml_scuse(kml);
      free_xml_sulte(kml);
      free((*kml)->kmlcat);
    }
    free(*kml);
  }
}
