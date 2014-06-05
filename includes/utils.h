#ifndef UTILS_H_
# define UTILS_H_

char *capt(char*);
int contains(char *container, char *search);
char *ccat(char *dest, char *s1, char *s2, char *s3);
char *replace(char old, char new, char *str);
char *supreplace(char *old, char *new, char *str);
int isnum(char*);
void debug(s_kml*);

# endif /* UTILS_H_ */
