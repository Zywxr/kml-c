#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include "kml.h"
#include "error.h"
#include "utils.h"

void superfree(void *ptr) {
  free(ptr);
  ptr = NULL;
}

void free_category(char **category) {
  int ct;

  if (category != NULL) {
    for (ct = 0; ct < MAX_SIZE; ct++)
      if (category[ct] != NULL) {
	superfree(category[ct]);
      }
    superfree(category);
  }
}

void free_xml_base(s_kml **kml) {
  /* Nom */
  free_category((*kml)->kmlcat->nom->list);
  superfree((*kml)->kmlcat->nom);
  free_category((*kml)->kmlcat->noms->list);
  superfree((*kml)->kmlcat->noms);
  /* Gender */
  if ((*kml)->kmlcat->gender != NULL)
    superfree((*kml)->kmlcat->gender);
  /* Nom propre */
  free_category((*kml)->kmlcat->nompropre->list);
  superfree((*kml)->kmlcat->nompropre);
  /* Nom special */
  free_category((*kml)->kmlcat->nomspecial->list);
  superfree((*kml)->kmlcat->nomspecial);
  /* Complement */
  free_category((*kml)->kmlcat->comp_m->list);
  superfree((*kml)->kmlcat->comp_m);
  free_category((*kml)->kmlcat->comp_f->list);
  superfree((*kml)->kmlcat->comp_f);
  /* Verbe */
  free_category((*kml)->kmlcat->verbe->list);
  superfree((*kml)->kmlcat->verbe);
  free_category((*kml)->kmlcat->inf->list);
  superfree((*kml)->kmlcat->inf);
  /* Prenom */
  free_category((*kml)->kmlcat->prenom->list);
  superfree((*kml)->kmlcat->prenom);
}

void free_xml_scuse(s_kml **kml) {
  free_category((*kml)->kmlcat->prescuse->list);
  superfree((*kml)->kmlcat->prescuse);
  free_category((*kml)->kmlcat->scuse1->list);
  superfree((*kml)->kmlcat->scuse1);
  free_category((*kml)->kmlcat->scuse2->list);
  superfree((*kml)->kmlcat->scuse2);
}

void free_xml_sulte(s_kml **kml) {
  free_category((*kml)->kmlcat->presulte->list);
  superfree((*kml)->kmlcat->presulte);
  free_category((*kml)->kmlcat->sulte->list);
  superfree((*kml)->kmlcat->sulte);
  free_category((*kml)->kmlcat->postsulte->list);
  superfree((*kml)->kmlcat->postsulte);
}

void free_xml_mail(s_kml **kml) {
  free_category((*kml)->kmlcat->mail->list);
  superfree((*kml)->kmlcat->mail);
}


void free_xml(s_kml **kml) {
  if (*kml != NULL) {
    xmlFreeDoc((*kml)->xml);
    xmlCleanupParser();
    if ((*kml)->kmlcat != NULL) {
      free_xml_base(kml);
      free_xml_scuse(kml);
      free_xml_sulte(kml);
      free_xml_mail(kml);
      superfree((*kml)->kmlcat);
    }
    superfree(*kml);
  }
}
