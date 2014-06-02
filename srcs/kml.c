#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include "kml.h"
#include "error.h"

void set_attribute(s_kml *kml, xmlNodePtr node) {
  char *gender;

  gender = NULL;
  if (kml->cat == NOM) {
    gender = (char*)xmlGetProp(node, (xmlChar*)"gender");
    if (gender)
      kml->kmlcat->gender[strlen(kml->kmlcat->gender)] = gender[0];
    free(gender);
  }
}

void set_category(s_kml *kml, char *cat) {
  if (!strcmp(cat, "nom"))
    kml->cat = NOM;
  else if (!strcmp(cat, "nompropre"))
    kml->cat = NOMPROPRE;
  else if (!strcmp(cat, "nomspecial"))
    kml->cat = NOMSPE;
  else if (!strcmp(cat, "verbe"))
    kml->cat = VERBE;
  else
    kml->cat = NONE;
}

void append(s_kml *kml, char *content) {

  if (kml->cat == NOM)
    kml->kmlcat->nom[kml->kmlcat->l_nom++] = (void*)content;
  else if (kml->cat == NOMPROPRE)
    kml->kmlcat->nompropre[kml->kmlcat->l_nompropre++] = (void*)content;
  else if (kml->cat == NOMSPE)
    kml->kmlcat->nomspecial[kml->kmlcat->l_nomspecial++] = (void*)content;
  else if (kml->cat == VERBE)
    kml->kmlcat->verbe[kml->kmlcat->l_verbe++] = (void*)content;
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
      set_attribute(kml, current);
      if (strlen((char*)content))
      	append(kml, (char*)content);
      else
	free(content);
    }
    /* Recursive stuff */
    store_kml(kml, current->children);
    current = current->next;
  }
}

int init_category(char **category) {
  int ct;

  for (ct = 0; ct < MAX_SIZE; ct++)
    category[ct] = NULL;
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
  (*kml)->kmlcat->nom = NULL;
  (*kml)->kmlcat->gender = NULL;
  (*kml)->kmlcat->nompropre = NULL;
  (*kml)->kmlcat->nomspecial = NULL;
  (*kml)->kmlcat->verbe = NULL;

  if (((*kml)->kmlcat->nom = malloc(sizeof(char*) * MAX_SIZE)) == NULL)
    return (error(E_MALLOC, "kmlcat: nom"));
  (*kml)->kmlcat->l_nom = 0;
  init_category((*kml)->kmlcat->nom);

  if (((*kml)->kmlcat->gender = malloc(MAX_SIZE)) == NULL)
    return (error(E_MALLOC, "kmlcat: gender"));
  memset((*kml)->kmlcat->gender, 0, MAX_SIZE);

  if (((*kml)->kmlcat->nompropre = malloc(sizeof(char*) * MAX_SIZE)) == NULL)
    return (error(E_MALLOC, "kmlcat: nompropre"));
  (*kml)->kmlcat->l_nompropre = 0;
  init_category((*kml)->kmlcat->nompropre);

  if (((*kml)->kmlcat->nomspecial = malloc(sizeof(char*)*MAX_SIZE)) == NULL)
    return (error(E_MALLOC, "kmlcat: nomspecial"));
  (*kml)->kmlcat->l_nomspecial = 0;
  init_category((*kml)->kmlcat->nomspecial);

  if (((*kml)->kmlcat->verbe = malloc(sizeof(char*)*MAX_SIZE)) == NULL)
    return (error(E_MALLOC, "kmlcat: verbe"));
  (*kml)->kmlcat->l_verbe = 0;
  init_category((*kml)->kmlcat->verbe);

  return (SUCCESS);
}

void debug(s_kml *kml) {
  int ct;

  for (ct = 0; ct < kml->kmlcat->l_nom; ct++) {
    if (kml->kmlcat->nom[ct] != NULL)
      printf("Nom: %s.\n", kml->kmlcat->nom[ct]);
  }
  for (ct = 0; ct < kml->kmlcat->l_nompropre; ct++) {
    if (kml->kmlcat->nompropre[ct] != NULL)
      printf("Nompropre: %s.\n", kml->kmlcat->nompropre[ct]);
  }
  for (ct = 0; ct < kml->kmlcat->l_nomspecial; ct++) {
    if (kml->kmlcat->nomspecial[ct] != NULL)
      printf("Nomspecial: %s.\n", kml->kmlcat->nomspecial[ct]);
  }
  for (ct = 0; ct < kml->kmlcat->l_verbe; ct++) {
    if (kml->kmlcat->verbe[ct] != NULL)
      printf("Verbe: %s.\n", kml->kmlcat->verbe[ct]);
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

void free_category(char **category) {
  int ct;

  if (category != NULL) {
    for (ct = 0; ct < MAX_SIZE; ct++)
      if (category[ct] != NULL)
	free(category[ct]);
    free(category);
  }
}

void free_xml(s_kml **kml) {
  if (*kml != NULL) {
    xmlFreeDoc((*kml)->xml);
    xmlCleanupParser();
    if ((*kml)->kmlcat != NULL) {
      free_category((*kml)->kmlcat->nom);
      if ((*kml)->kmlcat->gender != NULL)
      	free((*kml)->kmlcat->gender);
      free_category((*kml)->kmlcat->nompropre);
      free_category((*kml)->kmlcat->nomspecial);
      free_category((*kml)->kmlcat->verbe);
      free((*kml)->kmlcat);
    }
    free(*kml);
  }
}

int main(int ac, char **av) {
  int result;
  s_kml *kml;
  int (*kmlfct)(s_kml*);

  if (ac > 2)
    return (error(USAGE, NULL));  /* Returns FAILURE */

  kmlfct = NULL;
  if (ac == 1)
    kmlfct = &kamoulox;
  else if (ac == 2 && !strcmp(av[1], "kamouscuse"))
    kmlfct = &kamouscuse;
  else if (ac == 2 && !strcmp(av[1], "kamousulte"))
    kmlfct = &kamousulte;

  if (kmlfct == NULL)
    return (error(USAGE, NULL));
  
  result = get_xml(&kml, XML_FILE);
  if (result == FAILURE) {
    free_xml(&kml);
    return (error(E_XML_GEN, XML_FILE));
  }
  result = (*kmlfct)(kml);
  free_xml(&kml);
  return (result);
}
