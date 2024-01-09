Projet VAL
Ce projet, intitulé PROJET VAL, consiste à simuler d'un réseau de métro automatisé, 
mettant en œuvre des classes et des structures en C++ avec l'utilisation de la bibliothèque graphique SFML pour la visualisation.

Fichiers du Projet:

1er fichier : classe.h
Le fichier classe.h contient la définition des classes et des structures nécessaires à la mise en œuvre du projet. 
classes du projet :
Station: Classe définissant une station de métro avec des attributs tels que la position, le nom, le nombre de passagers.
Rame: Classe définissant une rame de métro avec des attributs comme la vitesse, la position, le nombre de passagers.
Le fichier contient également des fonctions globales pour la mise à jour des stations et des rames.

2eme fichier : main.cpp
Le fichier main.cpp est le point d'entrée du programme. Il initialise une fenêtre SFML, crée des objets rame et station, 
et lance des threads pour la mise à jour continue du système.

3eme fichier : def_classe.cpp
Le fichier VAL.cpp définit les fonctions de la classe rame. Il inclut également la bibliothèque SFML pour la manipulation graphique.
Le code comprend des fonctions pour mettre à jour la vitesse, la position et la gestion des passagers des rames, ainsi que des fonctions liées à l'affichage

thread : Pour que le programme n'ai pas de soucis, nous avons été obligé de séparer l'affichage et les métros à l'aide de thread. 
Chaque métro est un thread qui s'occupe de gérer toutes ses caractéristique tel que sa position ou les passagers. 
Pendant ce temps un thread s'occupe de l'affichage et réaffiche en permanence le métro, vérifie sa rotation et affiche les stations graphique.

Même si certaines fonctionnalités ont été plus ou moins dur à appliquer au projet, l'ensemble du cahier des charge a été respecté à notre compréhension. 
Lier l'affichage avec l'algorithmie nous a semblé être le plus dur puisque chacun s'occupé de sa partie nous n'avions donc pas les mêmes logique pour visualiser le projet.

Compilation et Exécution

Pour exécuter le programme il suffit d'avoir la bibliothèque SFML ainsi que les images qui doivent être mis dans le sous dossier /img 
qui se trouve dans le dossier SFML et la simulation est prête à être lancé.

Edgar Francq et Esteban PRZYSZCZYPKOWSKI