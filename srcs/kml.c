#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include "kml.h"
#include "error.h"
#include "utils.h"

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
  if (!occur) {
    occur = 1;
  }
  for (i = 0; i < (unsigned int)occur; i++) {
    result = (*kmlfct)(kml);
    if (result == FAILURE) {
      free_xml(&kml);
      return (error(E_ERROR, NULL));
    }
    printf("\n");
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
    else if (!strcmp(av[i], "kamoumail") && !kmlfct)
      kmlfct = &kamoumail;
    else if (!strcmp(av[i], "ipsum") && !kmlfct)
      kmlfct = &kamouipsum;
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
