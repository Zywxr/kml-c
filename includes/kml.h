#ifndef KML_H_
# define KML_H_

# define XML_FILE "/bin/base/kml.xml"
# define XML_LOCAL "./base/kml.xml"
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
  /* KAMOUSULTE STUFF */
  PRESULTE,
  SULTE,
  POSTSULTE,
  /* KAMOUMAIL STUFF */
  MAIL
} k_type;

typedef struct KML_list {
  char **list;
  int len;
} s_kmllist;

typedef struct KML_cat {
  s_kmllist *nom;
  s_kmllist *noms;
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
  s_kmllist *mail;
} s_kmlcat;

typedef struct KML {
  s_kmlcat *kmlcat;
  k_type cat;
  xmlDocPtr xml;
  xmlNodePtr root;
} s_kml;

/* INIT */
int init_category(s_kmllist *category);
int init_kmlcat(s_kml **kml);
int init_kml(s_kml**);

/* XML */
void set_attribute(s_kml *kml, xmlNodePtr node);
void set_category(s_kml *kml, char *cat);
void append(s_kml *kml, char *content);
void store_kml(s_kml* kml, xmlNodePtr node);
int get_xml(s_kml **kml, char *file);

/* RUN */
int kamoulox(s_kml*);
int kamounom(s_kml*);
int kamouscuse(s_kml*);
int kamousulte(s_kml*);
int kamoumail(s_kml*);
int kamouipsum(s_kml*);

/* END */
void free_category(char **category);
void free_xml(s_kml**);

#endif /* KML_H_ */
