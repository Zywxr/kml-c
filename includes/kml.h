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
  COMP,
  PRENOM
} k_type;

typedef struct KML_list {
  char **list;
  int len;
} s_kmllist;

typedef struct KML_cat {
  s_kmllist *nom;
  char      *gender;
  s_kmllist *nompropre;
  s_kmllist *nomspecial;
  s_kmllist *verbe;
  s_kmllist *comp_m;
  s_kmllist *comp_f;
  s_kmllist *prenom;
  /* char **nom; */
  /* int l_nom; */
  /* char *gender; */
  /* char **nompropre; */
  /* int l_nompropre; */
  /* char **nomspecial; */
  /* int l_nomspecial; */
  /* char **verbe; */
  /* int l_verbe; */
  /* char **comp_m; */
  /* char **comp_f; */
  /* int l_comp; */
  /* char **prenom; */
  /* int l_prenom; */
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
