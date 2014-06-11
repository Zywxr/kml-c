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
  PRENOM,
  /* KAMOUSCUSE STUFF */
  PRESCUSE,
  SCUSE1,
  SCUSE2,
  PRESULTE,
  SULTE,
  POSTSULTE
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
  s_kmllist *inf;
  s_kmllist *comp_m;
  s_kmllist *comp_f;
  s_kmllist *prenom;
  s_kmllist *prescuse;
  s_kmllist *scuse1;
  s_kmllist *scuse2;
  s_kmllist *presulte;
  s_kmllist *sulte;
  s_kmllist *postsulte;
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
