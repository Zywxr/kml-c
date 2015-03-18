#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include "kml.h"
#include "error.h"
#include "utils.h"

/* Le compilo sera pas content sans ca */
char *strdup(const char *s);

void set_attribute(s_kml *kml, xmlNodePtr node) {
  char *gender;
  char *plural;
  char *m;
  char *f;
  char *inf;

  gender = NULL;
  if (kml->cat == NOM) {
    gender = (char*)xmlGetProp(node, (xmlChar*)"gender");
    if (gender)
      kml->kmlcat->gender[strlen(kml->kmlcat->gender)] = gender[0];
    free(gender);
    plural = (char*)xmlGetProp(node, (xmlChar*)"plural");
    if (plural)
      kml->kmlcat->noms->list[kml->kmlcat->noms->len++] = plural;
  }
  else if (kml->cat == COMP) {
    m = (char*)xmlGetProp(node, (xmlChar*)"m");
    f = (char*)xmlGetProp(node, (xmlChar*)"f");
    if (!f)
      f = strdup(m);
    f = f != NULL ? f : "";
    kml->kmlcat->comp_m->list[kml->kmlcat->comp_m->len] = m;
    kml->kmlcat->comp_f->list[kml->kmlcat->comp_f->len] = f;
    kml->kmlcat->comp_m->len++;
    kml->kmlcat->comp_f->len++;
  }
  else if (kml->cat == VERBE) {
    inf = (char*)xmlGetProp(node, (xmlChar*)"inf");
    if (inf)
      kml->kmlcat->inf->list[kml->kmlcat->inf->len++] = inf;
  }
}

void set_category(s_kml *kml, char *cat) {
  int i;
  char *cats[] = {"nom", "nompropre", "nomspecial", "verbe",
		  "complement", "prenom", "prescuse", "scuse1",
		  "scuse2", "presulte", "sulte", "postsulte",
		  "mail", NULL};
  int values[] = {NOM, NOMPROPRE, NOMSPE, VERBE, COMP, PRENOM,
		  PRESCUSE, SCUSE1, SCUSE2, PRESULTE, SULTE,
		  POSTSULTE, MAIL, NONE};

  kml->cat = NONE;
  for (i = 0; cats[i] != NULL; i++) {
    if (!strcmp(cat, cats[i])) {
      kml->cat = values[i];
      break ;
    }
  }
}

void append(s_kml *kml, char *content) {
  /* Any way to make it better? */
  s_kmllist *cat;

  cat = NULL;
  if (kml->cat == NOM)
    cat = kml->kmlcat->nom;
  else if (kml->cat == NOMSPE)
    cat = kml->kmlcat->nomspecial;
  else if (kml->cat == NOMPROPRE)
    cat = kml->kmlcat->nompropre;
  else if (kml->cat == VERBE)
    cat = kml->kmlcat->verbe;
  else if (kml->cat == PRENOM)
    cat = kml->kmlcat->prenom;
  else if (kml->cat == PRESCUSE)
    cat = kml->kmlcat->prescuse;
  else if (kml->cat == SCUSE1)
    cat = kml->kmlcat->scuse1;
  else if (kml->cat == SCUSE2)
    cat = kml->kmlcat->scuse2;
  else if (kml->cat == PRESULTE)
    cat = kml->kmlcat->presulte;
  else if (kml->cat == SULTE)
    cat = kml->kmlcat->sulte;
  else if (kml->cat == POSTSULTE)
    cat = kml->kmlcat->postsulte;
  else if (kml->cat == MAIL)
    cat = kml->kmlcat->mail;
  else
    free(content); /* No need to keep it if we don't need it. */

  if (cat != NULL)
    cat->list[cat->len++] = (void*)content;

}

void store_kml(s_kml* kml, xmlNodePtr node) {
  xmlNodePtr current;
  xmlChar *content;

  current = node;
  while (current != NULL) {
    /* This means it is a category of words. */
    if (current->type == XML_ELEMENT_NODE &&
	strcmp((char*)current->name, "word") &&
	strcmp((char*)current->name, (char*)kml->root->name)) {
      set_category(kml, (char*)current->name);
    }
    if (current->type == XML_ELEMENT_NODE &&
	!strcmp((char*)current->name, "word")) {
      content = xmlNodeGetContent(current);
      /* If the word has an attribute in this category */
      set_attribute(kml, current);
      if (strlen((char*)content))
      	append(kml, (char*)content);
      else {
	free(content);
      }
    }
    /* Recursive stuff */
    store_kml(kml, current->children);
    current = current->next;
  }
}

int get_xml(s_kml **kml, char *file) {
  (*kml) = NULL;
  if (file == NULL)
    return (error(E_XML_NAM, NULL));
  if (init_kml(kml) == FAILURE)
    return (FAILURE);
  /* XML Stuff */
  LIBXML_TEST_VERSION
  (*kml)->xml = xmlReadFile(file, NULL, 0);
  if ((*kml)->xml == NULL) {
    return (error(E_XML_REA, file));
  }
  (*kml)->root = xmlDocGetRootElement((*kml)->xml);

  store_kml(*kml, (*kml)->root);
  /* debug(*kml); */
  return (SUCCESS);
}
