
#ifndef ERROR_H_
# define ERROR_H_

int error(char*, char*);

/*** ERROR MESSAGES ***/
# define USAGE     "Usage: ./kamoulox [kamouscuse | kamousulte]"
# define E_MALLOC  "Could not allocate"
# define E_XML_GEN "Could not parse XML file"
# define E_XML_NAM "Empty filename"
# define E_XML_REA "Could not read file"

# define FAILURE -1
# define SUCCESS 0

#endif /* ERROR_H_ */
