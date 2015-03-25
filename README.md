KML Project
===========
Ca sert à rien, mais voici venir le KML Project en C ! (www.kmlproject.com)

Ceci est donc un générateur de Kamoulox en lignes de commandes, utile non
seulement pour votre divertissement personnel, mais aussi pour générer des
données de tests pour des programmes/sites web/autres.

    Usage: kamoulox [kamounom|kamouscuse|kamousulte|ipsum] [-nX] --help pour l'aide.
    Options:
    -nX       : Le nombre X de phrases générées (de 1 à 100), par défaut 1.
    --help    : Ce message.
    Types de phrases:
    kamoulox  : (Sans argument) Je tabasse un porte-avion et j'interviewe un cassoulet.
    kamounom  : Jean-Christophe Petit-Suisse
    kamouscuse: Impossible, j'ai laissé mon ostréiculteur avec une friteuse chez Roger.
    kamousulte: Espèce de sale sosie de pot de mayonnaise du sud.
    ipsum     : Lorem ipsum.

Installation
------------
Pour installer le Kamoulox, utilisez le script d'install fourni (requiert les
droits administrateur).

    ./install

Très basique, il sera normalement portable (je n'ai pas testé en fait). Si non,
vous pouvez au choix l'utiliser sans install, ou me contacter.

Déjà disponibles
----------------
### Kamoulox
Générateur de Kamoulox simple. Utile dans toutes les situations de conversation.

    $> kamoulox -n5
    Je fais pédaler une truelle à moteur et j'épluche un boomerang.
    Je percute l'Incroyable Hulk et j'arrache un raton-laveur.
    Je décongèle Gilbert Montagné et je roule sur un Bisounours.
    Casserole de ratatouille et pelleteuse en grève.
    J'embrasse une barrière et je chatouille un poussin en faisant le poirier.

### Kamounom
Générateur de noms rigolos. Idéal pour remplir une base de données de test.

    $> kamoulox kamounom -n5
    Jean-Jacques Suppositoire
    Tony Grenouille
    Pauline Barraque-à-frites
    Marcel Touillette
    Mohammed Crevette

### Kamouscuse
Générateur d'excuses crédibles. Pratique pour décliner une réunion pro.

    $> kamoulox kamouscuse -n5
    Désolé, il y a un frigo qui essaye de me broyer avec un concombre alcoolique.
    Je peux pas, il y a un zébu qui essaye de me faire sécher avec un sumo par ordre alphabétique.
    Impossible, il y a un sombrero qui essaye de me manger pour toiletter mon bidet.
    Impossible, une terrine forestière veut me décorer chez un rideau de douche en peluche.
    Désolé, je dois aller manger ma boîte aux lettres fluorescente sur un cochon mauve.

### Kamousulte
Générateur d'insultes pas très sympas. Pour quand vous parlez politique.

    $> kamoulox kamousulte -n5
    Saleté de sosie de rateau.
    Vilain imitateur de rhinocéros en carton.
    Bouffeur de cow-boys.
    Immonde arracheur de cocottes-minute à moustaches.
    Espèce de stagiaire en pot de mayonnaise.

### Kamoumail
Générateur d'adresse email, très utile pour remplir une base de données. Un
peu comme le Kamounom, mais en pas pareil.

    $> kamoulox kamoumail -n5
    marc.antoine@assiette.com
    jean.jacques@tournevis.gov
    christophe@pigeon.voyageur.org
    ingrid@tiramisu.com
    paul@ornithologue.net

### Kamou Ipsum
Lorem Ipsum version Kamoulox, reprenant les générateurs ci-dessus. Très pratique 
lorsque vous faites du web et que vous avez surexploité le Bacon Ipsum.

    $> kamoulox ipsum -n2
    Espèce de oncle de Justin Bieber. J'insulte une cuvette et je me fais
    greffer un pompier en faisant le poirier. Désolé, je suis poursuivi 
    par un épouvantail avec un lapin en céramique. Je déballe un escalator
    de Noël et j'agrafe un pissenlit. Désolé, il y a un réacteur nucléaire
    qui essaye de me aspirer sur un castor alcoolique. Je peux pas, il y a
    un plat à gratin qui essaye de me brûler chez une corbeille à papier 
    en promotion.
    Espèce de ignoble destructeur de épouvantails. J'illumine un moteur de
    4L à la cantine et je m'installe sur un cochon. J'achète une valise 
    avec des tongs et j'aspire une cafetière. Espèce de fan de Nelson 
    Monfort. Je peux pas, je dois broyer ma tasse à café sur une 
    andouillette extraterrestre. Désolé, il faut que j'aille voir une 
    sauterelle chez un sombrero industriel.

Petits scripts à la con
-------
### MOTD
Le script *kmlmotd* vous permet de changer le message of the day sous Unix,
c'est à dire le message qui s'affiche lorsque vous vous logguez. Le message
affiché par le *kmlmotd* change tous les jours :)

### Ajouter une commande Kamoulox dans Emacs

Dans un fichier de configuration .emacs dans votre dossier home, mettre le
code Lisp suivant :

    (defun kamoulox ()
        (interactive)
        (shell-command "kamoulox"))

Il faut que le kml soit installé sur le système bien sûr. Ensuite, dans
Emacs :

    M-x kamoulox
    
Merci à Pierre pour le tuyau :D

### Autres petits addons rigolos

Pour l'instant il n'y a pas d'autres trucs rigolos, mais il y en aura ! Et
si vous avez des idées, je prend ;)
