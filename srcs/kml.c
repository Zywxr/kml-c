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
  char *m;
  char *f;

  gender = NULL;
  if (kml->cat == NOM) {
    gender = (char*)xmlGetProp(node, (xmlChar*)"gender");
    if (gender)
      kml->kmlcat->gender[strlen(kml->kmlcat->gender)] = gender[0];
    free(gender);
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
}

void set_category(s_kml *kml, char *cat) {
  int i;
  char *cats[] = {"nom", "nompropre", "nomspecial", "verbe",
		  "complement", "prenom", "prescuse", "scuse1",
		  "scuse2", NULL};
  int values[] = {NOM, NOMPROPRE, NOMSPE, VERBE, COMP, PRENOM,
		  PRESCUSE, SCUSE1, SCUSE2, NONE};

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

int init_category(s_kmllist *category) {
  int ct;

  if ((category->list = malloc(sizeof(char*) * MAX_SIZE)) == NULL)
    return (FAILURE);
  category->len = 0;
  for (ct = 0; ct < MAX_SIZE; ct++)
    category->list[ct] = NULL;
  return (SUCCESS);
}

int init_kmlcat(s_kml **kml) {
  /* Set them all to NULL here in case of failure */
  (*kml)->kmlcat->nom->list = NULL;
  (*kml)->kmlcat->gender = NULL;
  (*kml)->kmlcat->nompropre->list = NULL;
  (*kml)->kmlcat->nomspecial->list = NULL;
  (*kml)->kmlcat->comp_m->list = NULL;
  (*kml)->kmlcat->comp_f->list = NULL;
  (*kml)->kmlcat->verbe->list = NULL;
  (*kml)->kmlcat->prenom->list = NULL;
  (*kml)->kmlcat->prescuse->list = NULL;
  (*kml)->kmlcat->scuse1->list = NULL;
  (*kml)->kmlcat->scuse2->list = NULL;
  if (init_category((*kml)->kmlcat->nom) == FAILURE)
    return (error(E_MALLOC, "kmlcat: nom"));
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
  if (init_category((*kml)->kmlcat->prenom) == FAILURE)
    return (error(E_MALLOC, "kmlcat: prenom"));
  if (init_category((*kml)->kmlcat->prescuse) == FAILURE)
    return (error(E_MALLOC, "kmlcat: prescuse"));
  if (init_category((*kml)->kmlcat->scuse1) == FAILURE)
    return (error(E_MALLOC, "kmlcat: scuse1"));
  if (init_category((*kml)->kmlcat->scuse2) == FAILURE)
    return (error(E_MALLOC, "kmlcat: scuse2"));
  return (SUCCESS);
}

int init_kml(s_kml **kml) {
  if ((*kml = malloc(sizeof(s_kml))) == NULL)
    return (error(E_MALLOC, "kml"));
  (*kml)->kmlcat = NULL;
  (*kml)->xml = NULL;
  (*kml)->cat = NONE;
  /* OMAGAD I'M DYING!! */
  if (((*kml)->kmlcat = malloc(sizeof(s_kmlcat))) == NULL)
    return (error(E_MALLOC, "kmlcat"));
  if (((*kml)->kmlcat->nom = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: nom"));
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
  if (((*kml)->kmlcat->prenom = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: prenom"));
  if (((*kml)->kmlcat->prescuse = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: prescuse"));
  if (((*kml)->kmlcat->scuse1 = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: scuse1"));
  if (((*kml)->kmlcat->scuse2 = malloc(sizeof(s_kmllist))) == NULL)
    return (error(E_MALLOC, "kmlcat: scuse2"));

  if (init_kmlcat(kml) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
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
      if (category[ct] != NULL) {
	free(category[ct]);
	category[ct] = NULL;
      }
    free(category);
  }
}

void free_xml(s_kml **kml) {
  if (*kml != NULL) {
    xmlFreeDoc((*kml)->xml);
    xmlCleanupParser();
    if ((*kml)->kmlcat != NULL) {
      free_category((*kml)->kmlcat->nom->list);
      free((*kml)->kmlcat->nom);
      if ((*kml)->kmlcat->gender != NULL)
      	free((*kml)->kmlcat->gender);
      free_category((*kml)->kmlcat->nompropre->list);
      free((*kml)->kmlcat->nompropre);
      free_category((*kml)->kmlcat->nomspecial->list);
      free((*kml)->kmlcat->nomspecial);
      free_category((*kml)->kmlcat->comp_m->list);
      free((*kml)->kmlcat->comp_m);
      free_category((*kml)->kmlcat->comp_f->list);
      free((*kml)->kmlcat->comp_f);
      free_category((*kml)->kmlcat->verbe->list);
      free((*kml)->kmlcat->verbe);
      free_category((*kml)->kmlcat->prenom->list);
      free((*kml)->kmlcat->prenom);
      free_category((*kml)->kmlcat->prescuse->list);
      free((*kml)->kmlcat->prescuse);
      free_category((*kml)->kmlcat->scuse1->list);
      free((*kml)->kmlcat->scuse1);
      free_category((*kml)->kmlcat->scuse2->list);
      free((*kml)->kmlcat->scuse2);
      free((*kml)->kmlcat);
    }
    free(*kml);
  }
}

int launch(int (*kmlfct)(s_kml*), int occur) {
  s_kml *kml;
  unsigned int i;
  int result;

  result = get_xml(&kml, XML_FILE);
  if (result == FAILURE) {
    free_xml(&kml);
    return (error(E_XML_GEN, XML_FILE));
  }
  srand(getpid());
  if (!occur)
    result = (*kmlfct)(kml);
  for (i = 0; i < (unsigned int)occur; i++) {
    result = (*kmlfct)(kml);
    if (result == FAILURE)
      return (error(E_ERROR, NULL));
  }
  free_xml(&kml);
  return (SUCCESS);
}

int main(int ac, char **av) {
  unsigned int i;
  int occur;
  int (*kmlfct)(s_kml*);

  occur = 0;
  kmlfct = NULL;
  if (ac > 3)
    return (error(USAGE, NULL));  /* Returns FAILURE */
  for (i = 1; i < (unsigned int)ac; i++) {
    if (!strcmp(av[i], "--help")) {
      printf("%s\n", HELP);
      return (SUCCESS);
    }
    else if (!strcmp(av[i], "kamounom"))
      kmlfct = &kamounom;
    else if (!strcmp(av[i], "kamouscuse") && !kmlfct)
      kmlfct = &kamouscuse;
    else if (!strcmp(av[i], "kamousulte") && !kmlfct)
      kmlfct = &kamousulte;
    else if (strlen(av[i]) >= 3 && av[i][0] == '-' && av[i][1] == 'n'
	     && isnum(&av[i][2]) == SUCCESS) {
      occur = atoi(&av[i][2]);
      if (occur <= 0 || occur > 100)
	return (error(E_ARG_OCC, NULL));
    }
    else
      return (error(USAGE, av[i]));
  }
  if (kmlfct == NULL)
    kmlfct = &kamoulox;
  /* Now we can start */
  return (launch(kmlfct, occur));
}
