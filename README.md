KML Project
===========
Ca sert à rien, mais voici venir le KML Project en C ! (www.kmlproject.com)

Ceci est donc un générateur de Kamoulox en lignes de commandes, utile non
seulement pour votre divertissement personnel, mais aussi pour générer des
données de tests pour des programmes/sites web/autres.

    Usage: ./kamoulox [kamounom|kamouscuse|kamousulte] [-nX] --help pour l'aide.
    Options:
    -nX       : Le nombre X de phrases générées (de 1 à 100), par défaut 1.
    --help    : Ce message.
    Types de phrases:
    kamoulox  : (Sans argument) Je tabasse un porte-avion et j'interviewe un cassoulet.
    kamounom  : Jean-Christophe Petit-Suisse
    kamouscuse: Impossible, j'ai laissé mon ostréiculteur avec une friteuse chez Roger.
    kamousulte: Espèce de sale sosie de pot de mayonnaise du sud.

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

    kamoulox -n5
    Je fais pédaler une truelle à moteur et j'épluche un boomerang.
    Je percute l'Incroyable Hulk et j'arrache un raton-laveur.
    Je décongèle Gilbert Montagné et je roule sur un Bisounours.
    Casserole de ratatouille et pelleteuse en grève.
    J'embrasse une barrière et je chatouille un poussin en faisant le poirier.

### Kamounom
Générateur de noms rigolos. Idéal pour remplir une base de données de test.

    kamoulox kamounom -n5
    Jean-Jacques Suppositoire
    Tony Grenouille
    Pauline Barraque-à-frites
    Marcel Touillette
    Mohammed Crevette

### Kamouscuse
Générateur d'excuses crédibles. Pratique pour décliner une réunion pro.

    kamoulox kamouscuse -n5
    Désolé, il y a un frigo qui essaye de me broyer avec un concombre alcoolique.
    Je peux pas, il y a un zébu qui essaye de me faire sécher avec un sumo par ordre alphabétique.
    Impossible, il y a un sombrero qui essaye de me manger pour toiletter mon bidet.
    Impossible, une terrine forestière veut me décorer chez un rideau de douche en peluche.
    Désolé, je dois aller manger ma boîte aux lettres fluorescente sur un cochon mauve.


A venir
-------
### Kamousulte
Générateur d'insultes pas très sympas. Pour quand vous parlez politique.

### Kamou Ipsum
Lorem Ipsum version Kamoulox, reprenant les générateurs ci-dessus. Très pratique 
lorsque vous faites du web et que vous avez surexploité le Bacon Ipsum.

### Petits addons rigolos
Je sais pas encore quoi, tout simplement un installeur, un script qui ajoute
une phrase aléatoire à chaque lancement de terminal, d'autres trucs pour le
plaisir des développeurs et adminsys, que sais-je !