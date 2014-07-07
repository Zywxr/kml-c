#include <string.h>
#include <libxml/parser.h>
#include "kml.h"
#include "error.h"

/* Returns either the location of search in container, or FAILURE */
int contains(char *container, char *search) {
  unsigned int i, c, s;

  if (!container || !search || !strlen(container) || !strlen(search)
      || strlen(container) < strlen(search))
    return (FAILURE);
  for (c = 0; c < strlen(container); c++) {
    if (search[0] == container[c]) {
      i = c;
      for(s = 0; s < strlen(search); s++) {
	if (search[s] != container[i])
	  break ;
	if (s == strlen(search) - 1)
	  return (c); /* Return location */
	i++;
      }
    }
  }
  return (FAILURE);
}

/* Concatene from two to three strings and stores them in dest */
char *ccat(char *dest, char *s1, char *s2, char *s3) {
  unsigned int i;
  unsigned int n;

  n = 0;
  if (s1 != NULL)
    for (i = 0; i < strlen(s1) && n < MAX_SIZE; i++)
      dest[n++] = s1[i];
  if (s2 != NULL)
    for (i = 0; i < strlen(s2) && n < MAX_SIZE; i++)
      dest[n++] = s2[i];
  if (s3 != NULL)
    for (i = 0; i < strlen(s3) && n < MAX_SIZE; i++)
      dest[n++] = s3[i];
  dest[n] = 0;
  return (dest);
}

/* Just captialize (first letter to upper), changes current string */
char *cap(char *str) {
  if (!str || strlen(str) <= 0)
    return (NULL);
  if (str[0] >= 'a' && str[0] <= 'z') {
    str[0] = str[0] - 32;
  }
  return (str);
}

/* Just uncapitalize (first letter to upper), changes current string */
char *uncap(char *str) {
  if (!str || strlen(str) <= 0)
    return (NULL);
  if (str[0] >= 'A' && str[0] <= 'Z') {
    str[0] = str[0] + 32;
  }
  return (str);
}

/* Replace old by new in str */
char *supreplace(char *old, char *new, char *str) {
  char *newstr;
  int len;
  int pos;

  /* Sounds good to check if there is something to be done */
  if ((pos = contains(str, old)) == FAILURE)
    return (old);
  len = strlen(str) + strlen(new) - strlen(old);
  if ((newstr = malloc(sizeof(char) * (len + 1))) == NULL)
      return (NULL);
  memset(newstr, 0, len + 1);
  /* Chunk before old */
  strncpy(newstr, str, pos);
  /* old to new */
  strncpy(&newstr[pos], new, strlen(new));
  /* Chunk after old */
  strncpy(&newstr[pos + strlen(new)], &str[pos + strlen(old)], strlen(str) - pos - strlen(old));

  return (newstr);
}                             

/* Replace all occurences of the character old by new in str */
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

/* Checks if opt contains only numeric characters */
int isnum(char *opt) {
  unsigned int i;

  if (!strlen(opt))
    return (FAILURE);
  for (i = 0; i < strlen(opt); i++)
    if (opt[i] < '0' || opt[i] > '9')
      return (FAILURE);
  return (SUCCESS);
}

/* Prints stuff */
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
