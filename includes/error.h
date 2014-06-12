
#ifndef ERROR_H_
# define ERROR_H_

int error(char*, char*);

/*** ERROR MESSAGES ***/
# define HELP USAGE "\n\
Options:\n\
-nX       : Le nombre X de phrases générées (de 1 à 100), par défaut 1.\n\
--help    : Ce message.\n\
Types de phrases:\n\
kamoulox  : (Sans argument) Je tabasse un porte-avion et j'interviewe un \
cassoulet.\n\
kamounom  : Jean-Christophe Petit-Suisse\n\
kamouscuse: Impossible, j'ai laissé mon ostréiculteur avec une friteuse \
chez Roger.\n\
kamousulte: Espèce de sale sosie de pot de mayonnaise du sud.\n\
ipsum     : Lorem ipsum."

# define USAGE     "Usage: kamoulox [kamounom|kamouscuse|kamousulte|ipsum] [-nX]\
 --help pour l'aide."
# define E_ERROR   "Something went wrong."
# define E_ARG_OCC "Number of occurences should be between 1 and 100."
# define E_MALLOC  "Could not allocate."
# define E_XML_GEN "Could not parse XML file."
# define E_XML_NAM "Empty filename."
# define E_XML_REA "Could not read file."

# define FAILURE -1
# define SUCCESS 0

#endif /* ERROR_H_ */
