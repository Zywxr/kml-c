#ifndef KML_H_
# define KML_H_

# define XML_FILE "base/kml.xml"
# define MAX_SIZE 512

typedef enum {
  NONE,
  NOM,
  GENDER,
  NOMPROPRE,
  NOMSPE,
  VERBE,
  COMP_M,
  COMP_F
} k_type;

typedef struct KML_cat {
  char **nom;
  int l_nom;
  char *gender;
  char **nompropre;
  int l_nompropre;
  char **nomspecial;
  int l_nomspecial;
  char **verbe;
  int l_verbe;
  char **comp_m;
  char **comp_f;
  int l_comp;
  /* FIX: Do one struct per type with list and size */
} s_kmlcat;

typedef struct KML {
  s_kmlcat *kmlcat;
  k_type cat;
  xmlDocPtr xml;
  xmlNodePtr root;
} s_kml;

int kamoulox(s_kml*);
int kamounom(s_kml*);
int kamouscuse(s_kml*);
int kamousulte(s_kml*);

#endif /* KML_H_ */
